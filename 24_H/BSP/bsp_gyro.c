#include "bsp_gyro.h"

//Serial
uint8_t Gyro_DMA_Buffer[33];

uint8_t  JY61P_ULOCK_CMD[5] = {0xFF, 0xAA, 0x69, 0x88, 0xB5}; //解锁
uint8_t  JY61P_BAUD_CMD [5] = {0xFF, 0xAA, 0x04, 0x06, 0x00}; //波特率修改为115200
uint8_t  JY61P_SAVE_CMD [5] = {0xFF, 0xAA, 0x00, 0x00, 0x00}; //保存
uint8_t  JY61P_XY0_CMD  [5] = {0xFF, 0xAA, 0x01, 0x08, 0x00}; //XY角度归零
uint8_t  JY61P_Z0_CMD   [5] = {0xFF, 0xAA, 0x01, 0x04, 0x00}; //Z轴归零

GYRO_DATA Gyro_Data;
PID Gyro_PID;

void Gyro_Init(void)
{
    DL_DMA_setSrcAddr(DMA, DMA_GYRO_CHAN_ID, (uint32_t)(&UART_GYRO_INST->RXDATA));
    DL_DMA_setDestAddr(DMA, DMA_GYRO_CHAN_ID, (uint32_t) &Gyro_DMA_Buffer[0]);
    DL_DMA_setTransferSize(DMA, DMA_GYRO_CHAN_ID, 32);
    DL_DMA_enableChannel(DMA, DMA_GYRO_CHAN_ID);

    NVIC_EnableIRQ(UART_GYRO_INST_INT_IRQN);

    Gyro_YawZero();
}

void UART_GYRO_INST_IRQHandler(void)
{
    uint8_t checkSum, packCnt = 0;
    extern uint8_t Gyro_DMA_Buffer[33];

    DL_DMA_disableChannel(DMA, DMA_GYRO_CHAN_ID);
    uint8_t rxSize = 32 - DL_DMA_getTransferSize(DMA, DMA_GYRO_CHAN_ID);

    if(DL_UART_isRXFIFOEmpty(UART_GYRO_INST) == false)
        Gyro_DMA_Buffer[rxSize++] = DL_UART_receiveData(UART_GYRO_INST);

    while(rxSize >= 11)
    {
        checkSum=0;
        for(int i=packCnt*11; i<(packCnt+1)*11-1; i++)
            checkSum += Gyro_DMA_Buffer[i];

        if((Gyro_DMA_Buffer[packCnt*11] == 0x55) && (checkSum == Gyro_DMA_Buffer[packCnt*11+10]))
        {
            if(Gyro_DMA_Buffer[packCnt*11+1] == 0x51)
            {
                Gyro_Data.ax = (int16_t)((Gyro_DMA_Buffer[packCnt*11+3]<<8)|Gyro_DMA_Buffer[packCnt*11+2]) / 2.048; //mg
                Gyro_Data.ay = (int16_t)((Gyro_DMA_Buffer[packCnt*11+5]<<8)|Gyro_DMA_Buffer[packCnt*11+4]) / 2.048; //mg
                Gyro_Data.az = (int16_t)((Gyro_DMA_Buffer[packCnt*11+7]<<8)|Gyro_DMA_Buffer[packCnt*11+6]) / 2.048; //mg
                Gyro_Data.temperature =  (int16_t)((Gyro_DMA_Buffer[packCnt*11+9]<<8)|Gyro_DMA_Buffer[packCnt*11+8]) / 100.0; //°C
            }
            else if(Gyro_DMA_Buffer[packCnt*11+1] == 0x52)
            {
                Gyro_Data.gx = (int16_t)((Gyro_DMA_Buffer[packCnt*11+3]<<8)|Gyro_DMA_Buffer[packCnt*11+2]) / 16.384; //°/S
                Gyro_Data.gy = (int16_t)((Gyro_DMA_Buffer[packCnt*11+5]<<8)|Gyro_DMA_Buffer[packCnt*11+4]) / 16.384; //°/S
                Gyro_Data.gz = (int16_t)((Gyro_DMA_Buffer[packCnt*11+7]<<8)|Gyro_DMA_Buffer[packCnt*11+6]) / 16.384; //°/S
            }
            else if(Gyro_DMA_Buffer[packCnt*11+1] == 0x53)
            {
                Gyro_Data.roll  = (int16_t)((Gyro_DMA_Buffer[packCnt*11+3]<<8)|Gyro_DMA_Buffer[packCnt*11+2]) / 32768.0 * 180.0; //°
                Gyro_Data.pitch = (int16_t)((Gyro_DMA_Buffer[packCnt*11+5]<<8)|Gyro_DMA_Buffer[packCnt*11+4]) / 32768.0 * 180.0; //°
                Gyro_Data.yaw   = (int16_t)((Gyro_DMA_Buffer[packCnt*11+7]<<8)|Gyro_DMA_Buffer[packCnt*11+6]) / 32768.0 * 180.0; //°
                //if (Gyro_Data.yaw < 0)  Gyro_Data.yaw += 360.0;
                Gyro_Data.version = (int16_t)((Gyro_DMA_Buffer[packCnt*11+9]<<8)|Gyro_DMA_Buffer[packCnt*11+8]);
            }
        }

        rxSize -= 11;
        packCnt++;
    }
    
    uint8_t dummy[4];
    DL_UART_drainRXFIFO(UART_GYRO_INST, dummy, 4);

    DL_DMA_setDestAddr(DMA, DMA_GYRO_CHAN_ID, (uint32_t) &Gyro_DMA_Buffer[0]);
    DL_DMA_setTransferSize(DMA, DMA_GYRO_CHAN_ID, 32);
    DL_DMA_enableChannel(DMA, DMA_GYRO_CHAN_ID);
}

void UART_1_SendBuff(uint8_t *buff, uint8_t len)
{
    if (buff == NULL || len == 0)
        return;

    for (uint16_t i = 0; i < len; i++) {
        DL_UART_transmitDataBlocking(UART_GYRO_INST, buff[i]);
    }
}

/* IMU归零函数 */
void Gyro_YawZero(void)
{
    UART_1_SendBuff(JY61P_ULOCK_CMD, sizeof(JY61P_ULOCK_CMD));  //解锁
    delay_ms(200);
    // UART_1_SendBuff(JY61P_XY0_CMD, sizeof(JY61P_XY0_CMD));    //XY轴归零
    // delay_ms(200);
    UART_1_SendBuff(JY61P_Z0_CMD, sizeof(JY61P_Z0_CMD));      //Z轴归零
    delay_ms(200);
    UART_1_SendBuff(JY61P_SAVE_CMD, sizeof(JY61P_SAVE_CMD));    //保存
    delay_ms(200);
}


void Gyro_PID_Init(void)
{
    PID_Init(&Gyro_PID);
    
    PID_SetParameter(&Gyro_PID, GYRO_PID_P, GYRO_PID_I, GYRO_PID_D, GYRO_PID_SL, GYRO_PID_UL, 1);
}

float Gyro_GetError(float Target_Angle)
{
    float error = Gyro_Data.yaw - Target_Angle;
    float pro_error = error;

    if (error < -180)
        pro_error = error + 360.0;
    else if (error > 180)
        pro_error = error - 360.0;

    return pro_error;
}

uint8_t Gyro_Angle_PID_Work(float Target_Angle)
{
    PID_AnglePID(&Gyro_PID, Gyro_GetError(Target_Angle));
    // PID_PositionalPID(&Gyro_PID, Target_Angle, Gyro_Data.yaw);
    if (Gyro_PID.preError > -0.8 && Gyro_PID.preError < 0.8)
        return 1;

    PWMA += (int32_t)Gyro_PID.ut;
    PWMB += -(int32_t)Gyro_PID.ut;

    return 0;
}

// IIC
// volatile Gyro_Struct Gyro_Structure;

// PID Gyro_PID;

// void Gyro_Init(void)
// {
	
// 	/*================Z轴归零==================*/
	
// 	// 寄存器解锁
// 	uint8_t unlock_reg1[2] = {0x88,0xB5};
// 	writeDataJy61p(IIC_ADDR,UN_REG,unlock_reg1,2);
// 	delay_ms(200);
// 	// Z轴归零
// 	uint8_t z_axis_reg[2] = {0x04,0x00};
// 	writeDataJy61p(IIC_ADDR,ANGLE_REFER_REG,z_axis_reg,2);	
// 	delay_ms(200);	
// 	// 保存
// 	uint8_t save_reg1[2] = {0x00,0x00};
// 	writeDataJy61p(IIC_ADDR,SAVE_REG,save_reg1,2);
// 	delay_ms(200);
	
// 	/*================角度归零==================*/
	
// 	// 寄存器解锁
// 	uint8_t unlock_reg[2] = {0x88,0xB5};
// 	writeDataJy61p(IIC_ADDR,UN_REG,unlock_reg,2);
// 	delay_ms(200);
// 	// 角度归零
// 	uint8_t angle_reg[2] = {0x08,0x00};
// 	writeDataJy61p(IIC_ADDR,ANGLE_REFER_REG,angle_reg,2);	
// 	delay_ms(200);
// 	// 保存
// 	uint8_t save_reg[2] = {0x00,0x00};
// 	writeDataJy61p(IIC_ADDR,SAVE_REG,save_reg,2);
// 	delay_ms(200);
		
// 	// 清空结构体
// 	memset((void*)&Gyro_Structure,0,sizeof(Gyro_Structure));
// }


// /******************************************************************
//  * 函 数 名 称：get_angle
//  * 函 数 说 明：读角度数据
//  * 函 数 形 参：无
//  * 函 数 返 回：返回结构体
//  * 作       者：LC
//  * 备       注：无
// ******************************************************************/
// float Gyro_GetAngle(void)
// {
// 	// 数据缓存
// 	volatile uint8_t sda_angle[6] = {0};
	
// 	int ret = 0;

// 	// 清空数据缓存
// 	memset((void*)sda_angle,0,sizeof(sda_angle));
	
// 	// 读取寄存器数据
// 	ret	= readDataJy61p(IIC_ADDR,0x3D,(uint8_t*)sda_angle,6);
	
// 	if(ret == 0)
// 	{	
// 		// 读取失败
// 		printf("Read Error\r\n");
// 	}
	
// 	#if GYRO_DEBUG
	
// 	printf("RollL = %x\r\n",sda_angle[0]);
// 	printf("RollH = %x\r\n",sda_angle[1]);
// 	printf("PitchL = %x\r\n",sda_angle[2]);
// 	printf("PitchH = %x\r\n",sda_angle[3]);
// 	printf("YawL = %x\r\n",sda_angle[4]);
// 	printf("YawH = %x\r\n",sda_angle[5]);
	
// 	#endif
	
//     // 计算 RollX, PitchY 和 YawZ 并确保它们在 -180 到 180 的范围内
//     float RollX = (float)(((sda_angle[1] << 8) | sda_angle[0]) / 32768.0 * 180.0);
//     if (RollX > 180.0)
//     {
//         RollX -= 360.0;
//     }
//     else if (RollX < -180.0)
//     {
//         RollX += 360.0;
//     }

//     float PitchY = (float)(((sda_angle[3] << 8) | sda_angle[2]) / 32768.0 * 180.0);
//     if (PitchY > 180.0)
//     {
//         PitchY -= 360.0;
//     }
//     else if (PitchY < -180.0)
//     {
//         PitchY += 360.0;
//     }

//     float YawZ = (float)(((sda_angle[5] << 8) | sda_angle[4]) / 32768.0 * 180.0);
//     if (YawZ > 180.0)
//     {
//         YawZ -= 360.0;
//     }
//     else if (YawZ < -180.0)
//     {
//         YawZ += 360.0;
//     }

//     // 将计算结果保存到结构体中
//     Gyro_Structure.x = RollX;
//     Gyro_Structure.y = PitchY;
//     Gyro_Structure.z = YawZ;

//     // if (YawZ < 0)
//     // {
//     //     YawZ += 360.0;
//     // }
	
// 	// 返回角度数据
// 	return YawZ;
// }

// void Gyro_PID_Init(void)
// {
//     PID_Init(&Gyro_PID);
    
//     PID_SetParameter(&Gyro_PID, GYRO_PID_P, GYRO_PID_I, GYRO_PID_D, GYRO_PID_SL, GYRO_PID_UL, 1);
// }

// uint8_t Gyro_Angle_PID_Work(float Target_Angle)
// {
//     PID_PositionalPID(&Gyro_PID, Target_Angle, Gyro_GetAngle());
    
//     if (Gyro_PID.preError > -0.8 && Gyro_PID.preError < 0.8)
//         return 1;

//     PWMA += (int32_t)Gyro_PID.ut;
//     PWMB += -(int32_t)Gyro_PID.ut;

//     return 0;
// }



// /******************************************************************
//  * 函 数 名 称：IIC_Start
//  * 函 数 说 明：IIC起始时序
//  * 函 数 形 参：无
//  * 函 数 返 回：无
//  * 作       者：LC
//  * 备       注：无
// ******************************************************************/
// void Gyro_IIC_Start(void)
// {
//     IIC_Start();
// }
// /******************************************************************
//  * 函 数 名 称：IIC_Stop
//  * 函 数 说 明：IIC停止信号
//  * 函 数 形 参：无
//  * 函 数 返 回：无
//  * 作       者：LC
//  * 备       注：无
// ******************************************************************/
// void Gyro_IIC_Stop(void)
// {
//     IIC_Stop();
// }

// /******************************************************************
//  * 函 数 名 称：IIC_Send_Ack
//  * 函 数 说 明：主机发送应答或者非应答信号
//  * 函 数 形 参：0发送应答  1发送非应答
//  * 函 数 返 回：无
//  * 作       者：LC
//  * 备       注：无
// ******************************************************************/
// void Gyro_IIC_Send_Ack(unsigned char ack)
// {
//     IIC_Send_Ack(ack);
// }


// /******************************************************************
//  * 函 数 名 称：I2C_WaitAck
//  * 函 数 说 明：等待从机应答
//  * 函 数 形 参：无
//  * 函 数 返 回：0有应答  1超时无应答
//  * 作       者：LC
//  * 备       注：无
// ******************************************************************/
// unsigned char Gyro_IIC_WaitAck(void)
// {
//     return IIC_WaitAck();
// }

// /******************************************************************
//  * 函 数 名 称：Send_Byte
//  * 函 数 说 明：写入一个字节
//  * 函 数 形 参：dat要写人的数据
//  * 函 数 返 回：无
//  * 作       者：LC
//  * 备       注：无
// ******************************************************************/
// void Gyro_Send_Byte(uint8_t dat)
// {
// 	Send_Byte(dat);
// }

// /******************************************************************
//  * 函 数 名 称：Read_Byte
//  * 函 数 说 明：IIC读时序
//  * 函 数 形 参：无
//  * 函 数 返 回：读到的数据
//  * 作       者：LC
//  * 备       注：无
// ******************************************************************/
// unsigned char Gyro_Read_Byte(void)
// {
//     return Read_Byte();
// }

// /******************************************************************
//  * 函 数 名 称：writeDataJy61p
//  * 函 数 说 明：写数据
//  * 函 数 形 参：dev 设备地址
// 				reg 寄存器地址
// 				data 数据首地址
// 				length 数据长度
//  * 函 数 返 回：返回0则写入成功
//  * 作       者：LC
//  * 备       注：无
// ******************************************************************/
// uint8_t writeDataJy61p(uint8_t dev, uint8_t reg, uint8_t* data, uint32_t length)
// {
//     uint32_t count = 0;
	
//     Gyro_IIC_Start();
	
//     Gyro_Send_Byte(dev<<1);	 
//     if(Gyro_IIC_WaitAck() == 1)return 0;
	
//     Gyro_Send_Byte(reg);   
//     if(Gyro_IIC_WaitAck() == 1)return 0;
	
//     for(count=0; count<length; count++)
//     {
//         Gyro_Send_Byte(data[count]);
//         if(Gyro_IIC_WaitAck() == 1)return 0;
//     }
	
//     Gyro_IIC_Stop();

//     return 1; 
// }

// /******************************************************************
//  * 函 数 名 称：readDataJy61p
//  * 函 数 说 明：读数据数据
//  * 函 数 形 参：dev 设备地址
// 				reg 寄存器地址
// 				data 数据存储地址
// 				length 数据长度
//  * 函 数 返 回：返回0则写入成功
//  * 作       者：LC
//  * 备       注：无
// ******************************************************************/
// uint8_t readDataJy61p(uint8_t dev, uint8_t reg, uint8_t *data, uint32_t length)
// {
//     uint32_t count = 0;

//     Gyro_IIC_Start();
	
//     Gyro_Send_Byte((dev<<1)|0);	
//     if(Gyro_IIC_WaitAck() == 1)return 0;
	
//     Gyro_Send_Byte(reg);
//     if(Gyro_IIC_WaitAck() == 1)return 0;
	
// 	delay_us(5);
	
//     Gyro_IIC_Start();
	
//     Gyro_Send_Byte((dev<<1)|1); 
//     if(Gyro_IIC_WaitAck() == 1)return 0;
	
//     for(count=0; count<length; count++)
//     {
//         if(count!=length-1)
// 		{
// 			data[count]=Gyro_Read_Byte();
// 			Gyro_IIC_Send_Ack(0);
// 		}
//         else
// 		{
// 			data[count]=Gyro_Read_Byte();
// 			Gyro_IIC_Send_Ack(1);
// 		} 
				 
//     }
	
//     Gyro_IIC_Stop();
	
//     return 1; 
// }



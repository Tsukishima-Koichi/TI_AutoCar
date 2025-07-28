#include "bsp_motor.h"

PID MotorA_PID, MotorB_PID;//A左 B右

int32_t Motor_Target = MOTOR_TARGET_SPEED;

int32_t PWMA,PWMB;
int32_t Get_Encoder_CountA, Get_Encoder_CountB, EncoderA_Cnt, EncoderB_Cnt;

uint32_t gpio_interrup;

void Motor_Init(void)
{
	//编码器引脚外部中断
	NVIC_ClearPendingIRQ(GPIOB_INT_IRQn);
	NVIC_EnableIRQ(GPIOB_INT_IRQn);
  //定时器中断
	NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);  

	//printf("Motor initialized successfully\r\n");
}

//左右电机速度控制，范围0-9999
void Set_PWM(int pwma,int pwmb)
{
	if(pwma > 0) //左轮前进
	{
		DL_GPIO_setPins(MOTOR_AIN1_PORT,MOTOR_AIN1_PIN);
		DL_GPIO_clearPins(MOTOR_AIN2_PORT,MOTOR_AIN2_PIN);
		DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,ABS(pwma),GPIO_PWM_MOTOR_C0_IDX);
	}
	else //左轮后退
	{
        DL_GPIO_setPins(MOTOR_AIN2_PORT,MOTOR_AIN2_PIN);
		DL_GPIO_clearPins(MOTOR_AIN1_PORT,MOTOR_AIN1_PIN);	
		DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,ABS(pwma),GPIO_PWM_MOTOR_C0_IDX);		
	}
	if(pwmb > 0)//右轮前进
	{
		DL_GPIO_setPins(MOTOR_BIN1_PORT,MOTOR_BIN1_PIN);
		DL_GPIO_clearPins(MOTOR_BIN2_PORT,MOTOR_BIN2_PIN);
		DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,ABS(pwmb),GPIO_PWM_MOTOR_C1_IDX);
	}
  else//右轮后退
	{
		DL_GPIO_setPins(MOTOR_BIN2_PORT,MOTOR_BIN2_PIN);
		DL_GPIO_clearPins(MOTOR_BIN1_PORT,MOTOR_BIN1_PIN);
		DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,ABS(pwmb),GPIO_PWM_MOTOR_C1_IDX);
	}		

}

void Motor_SetSpeed(void)
{
	Set_PWM(PWMA, PWMB);
}

void Motor_Stop(void)
{
		DL_GPIO_setPins(MOTOR_AIN1_PORT,MOTOR_AIN1_PIN);
		DL_GPIO_setPins(MOTOR_AIN2_PORT,MOTOR_AIN2_PIN);
		DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,0,GPIO_PWM_MOTOR_C0_IDX);

		DL_GPIO_setPins(MOTOR_BIN2_PORT,MOTOR_BIN2_PIN);
		DL_GPIO_setPins(MOTOR_BIN1_PORT,MOTOR_BIN1_PIN);
		DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,0,GPIO_PWM_MOTOR_C1_IDX);

}

void Motor_PID_Init(void)
{
    PID_Init(&MotorA_PID);
    PID_Init(&MotorB_PID);
    
    PID_SetParameter(&MotorA_PID, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_SL, MOTOR_PID_UL, 1);
    PID_SetParameter(&MotorB_PID, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_SL, MOTOR_PID_UL, 1);
}

void Motor_Velocity_PID_Work(void)
{
    PID_IncrementalPID(&MotorA_PID, Motor_Target, EncoderA_Data);
    PID_IncrementalPID(&MotorB_PID, Motor_Target, EncoderB_Data);
    PWMA += MotorA_PID.ut;
    PWMB += MotorB_PID.ut;
}


//外部中断模拟编码器信号
void GROUP1_IRQHandler(void)
{
	//获取中断信号
	gpio_interrup = DL_GPIO_getEnabledInterruptStatus(GPIOB,ENCODER_E1A_PIN|ENCODER_E1B_PIN|ENCODER_E2A_PIN|ENCODER_E2B_PIN);
	//encoderA
	if((gpio_interrup & ENCODER_E1A_PIN)==ENCODER_E1A_PIN)
	{
		if(!DL_GPIO_readPins(GPIOB,ENCODER_E1B_PIN))
		{
			Get_Encoder_CountA--;
		}
		else
		{
			Get_Encoder_CountA++;
		}
	}
	else if((gpio_interrup & ENCODER_E1B_PIN)==ENCODER_E1B_PIN)
	{
		if(!DL_GPIO_readPins(GPIOB,ENCODER_E1A_PIN))
		{
			Get_Encoder_CountA++;
		}
		else
		{
			Get_Encoder_CountA--;
		}
	}
	//encoderB
	if((gpio_interrup & ENCODER_E2A_PIN)==ENCODER_E2A_PIN)
	{
		if(!DL_GPIO_readPins(GPIOB,ENCODER_E2B_PIN))
		{
			Get_Encoder_CountB--;
		}
		else
		{
			Get_Encoder_CountB++;
		}
	}
	else if((gpio_interrup & ENCODER_E2B_PIN)==ENCODER_E2B_PIN)
	{
		if(!DL_GPIO_readPins(GPIOB,ENCODER_E2A_PIN))
		{
			Get_Encoder_CountB++;
		}
		else
		{
			Get_Encoder_CountB--;
		}
	}
	DL_GPIO_clearInterruptStatus(GPIOB,ENCODER_E1A_PIN|ENCODER_E1B_PIN|ENCODER_E2A_PIN|ENCODER_E2B_PIN);
}

void Encoder_GetCnt(void)
{
    EncoderA_Cnt = Get_Encoder_CountA;//两个电机安装相反，所以编码器值也要相反
    EncoderB_Cnt = -Get_Encoder_CountB;
    Get_Encoder_CountA = 0;//编码器计数值清零
    Get_Encoder_CountB = 0;
}

//------------------------------------------------------------
//状态机
uint8_t Encoder_readFinishStatus = 0;

//------------------------------基础数据------------------------------
//数据
int16_t EncoderA_DataRead = 0;                        //电机1采集到的数据
int16_t EncoderB_DataRead = 0;                        //电机2采集到的数据
int16_t Encoder_leftFilter[ENCODER_FILTER_MAX + 1];   //左轮滤波队列缓冲区
int16_t Encoder_rightFilter[ENCODER_FILTER_MAX + 1];  //右轮滤波队列缓冲区
int16_t Encoder_dataPointer = 0;                      //做一个指针,做个循环队列
int16_t EncoderA_Data = 0;                            //电机1滤波后的数据
int16_t EncoderB_Data = 0;                            //电机2滤波后的数据
//------------------------------
//数据滤波时候的权重
float Encoder_filterWeight[ENCODER_FILTER_MAX] = {0.8, 0.1, 0.06, 0.04};


/**
 * @brief   编码器读取一次数据并进行滤波
 * @return  NULL
 */
void Encoder_SpeedRead(void) {
    Encoder_readFinishStatus = 0;
    //数据采集的工作
    EncoderA_DataRead = EncoderA_Cnt;
    EncoderB_DataRead = EncoderB_Cnt;
    //这里是做编码器的矫正的问题 ->  否则会显示负数据(很怪)
    EncoderA_Data = 0;
    EncoderB_Data = 0;
    //进行一个滑动窗口的滤波
    Encoder_leftFilter[Encoder_dataPointer] = EncoderA_DataRead;
    Encoder_rightFilter[Encoder_dataPointer] = EncoderB_DataRead;
    for (int i = 0; i < ENCODER_FILTER_MAX; ++i) {
        int index = Encoder_dataPointer - i;
        if (index < 0)
            index += ENCODER_FILTER_MAX;
        EncoderA_Data += Encoder_leftFilter[index] * Encoder_filterWeight[i];
        EncoderB_Data += Encoder_rightFilter[index] * Encoder_filterWeight[i];
    }
    Encoder_dataPointer = (Encoder_dataPointer + 1) % ENCODER_FILTER_MAX;
    Encoder_readFinishStatus = 1;
}

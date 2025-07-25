#include "bsp_iic.h"

/******************************************************************
 * 函 数 名 称：IIC_Start
 * 函 数 说 明：IIC起始时序
 * 函 数 形 参：无
 * 函 数 返 回：无
******************************************************************/
void IIC_Start(void)
{
    SDA_OUT();

    SCL(0);
    SDA(1);
    SCL(1);

    delay_us(5);

    SDA(0);
    delay_us(5);
    SCL(0);
    delay_us(5);
}
/******************************************************************
 * 函 数 名 称：IIC_Stop
 * 函 数 说 明：IIC停止信号
 * 函 数 形 参：无
 * 函 数 返 回：无
******************************************************************/
void IIC_Stop(void)
{
    SDA_OUT();
    SCL(0);
    SDA(0);

    SCL(1);
    delay_us(5);
    SDA(1);
    delay_us(5);
}

/******************************************************************
 * 函 数 名 称：IIC_Send_Ack
 * 函 数 说 明：主机发送应答或者非应答信号
 * 函 数 形 参：0发送应答  1发送非应答
 * 函 数 返 回：无
******************************************************************/
void IIC_Send_Ack(unsigned char ack)    // Only Gyro used.
{
    SDA_OUT();
    SCL(0);
    SDA(0);
    delay_us(5);
    if(!ack) SDA(0);
    else     SDA(1);
    SCL(1);
    delay_us(5);
    SCL(0);
    SDA(1);
}


/******************************************************************
 * 函 数 名 称：I2C_WaitAck
 * 函 数 说 明：等待从机应答
 * 函 数 形 参：无
 * 函 数 返 回：0有应答  1超时无应答
******************************************************************/
unsigned char IIC_WaitAck(void)
{
    char ack = 0;
    char ack_flag = 50;

    SDA_IN();

    SDA(1);
    while( (SDA_GET()==1) && ( ack_flag ) )
    {
        ack_flag--;
        delay_us(5);
    }

    if( ack_flag == 0 )
    {
        IIC_Stop();
        return 1;
    }
    else
    {
        SCL(1);
        delay_us(5);
        SCL(0);
        SDA_OUT();
    }
    return ack;
}

/******************************************************************
 * 函 数 名 称：Send_Byte
 * 函 数 说 明：写入一个字节
 * 函 数 形 参：dat要写人的数据
 * 函 数 返 回：无
******************************************************************/
void Send_Byte(uint8_t dat)
{
	int i = 0;
	SDA_OUT();
	SCL(0);//拉低时钟开始数据传输
	
	for( i = 0; i < 8; i++ )
	{
		SDA( (dat & 0x80) >> 7 );
		delay_us(2);
	
		SCL(1);
		delay_us(5);
	
		SCL(0);
		delay_us(5);
	
		dat<<=1;
	}
}

/******************************************************************
 * 函 数 名 称：Read_Byte
 * 函 数 说 明：IIC读时序
 * 函 数 形 参：无
 * 函 数 返 回：读到的数据
******************************************************************/
unsigned char Read_Byte(void)   // Only Gyro used.
{
    unsigned char i,receive=0;
    SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
    {
        SCL(0);
        delay_us(5);
        SCL(1);
        delay_us(5);
        receive<<=1;
        if( SDA_GET() )
        {
            receive|=1;
        }
        delay_us(5);
    }

    return receive;
}
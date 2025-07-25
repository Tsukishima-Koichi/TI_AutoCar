#ifndef __BSP_IIC_H__
#define __BSP_IIC_H__

#include "board.h"

//设置SDA输出模式
#define SDA_OUT()   {                                                  \
                        DL_GPIO_initDigitalOutput(IIC_SDA_IOMUX);     \
                        DL_GPIO_setPins(IIC_PORT, IIC_SDA_PIN);      \
                        DL_GPIO_enableOutput(IIC_PORT, IIC_SDA_PIN); \
                    }
//设置SDA输入模式
#define SDA_IN()    { DL_GPIO_initDigitalInput(IIC_SDA_IOMUX); }

//获取SDA引脚的电平变化
#define SDA_GET()   ( ( ( DL_GPIO_readPins(IIC_PORT,IIC_SDA_PIN) & IIC_SDA_PIN ) > 0 ) ? 1 : 0 )

//SDA与SCL输出
#define SDA(x)      ( (x) ? (DL_GPIO_setPins(IIC_PORT,IIC_SDA_PIN)) : (DL_GPIO_clearPins(IIC_PORT,IIC_SDA_PIN)) )
#define SCL(x)      ( (x) ? (DL_GPIO_setPins(IIC_PORT,IIC_SCL_PIN)) : (DL_GPIO_clearPins(IIC_PORT,IIC_SCL_PIN)) )

void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_Ack(unsigned char ack);
unsigned char IIC_WaitAck(void);
void Send_Byte(uint8_t dat);
unsigned char Read_Byte(void);


#endif
/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 立创论坛：https://oshwhub.com/forum
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-30     LCKFB        陀螺仪
 */
#ifndef	__BSP_GYRO_H__
#define __BSP_GYRO_H__

#include "board.h"
#include "bsp_iic.h"
#include "bsp_motor.h"
#include "bsp_pid.h"

// Serial
typedef struct {
    float pitch;
    float roll;
    float yaw;
    float temperature;
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t gx;
    int16_t gy;
    int16_t gz;
    int16_t version;
} GYRO_DATA;

//角度环 位置
#define GYRO_PID_P             (80)
#define GYRO_PID_I             (0)
#define GYRO_PID_D             (5.8)
#define GYRO_PID_SL            (0)
#define GYRO_PID_UL            (9999)

#define GYRO_TARGET_ANGLE       (0)

extern GYRO_DATA Gyro_Data;

void Gyro_Init(void);
void UART_1_SendBuff(uint8_t *buff, uint8_t len);
void Gyro_YawZero(void);

void Gyro_PID_Init(void);
float Gyro_GetError(float Target_Angle);
uint8_t Gyro_Angle_PID_Work(float Target_Angle);


// IIC
// // 调试开关
// #define GYRO_DEBUG	0

// // 定义一个结构体来存储
// typedef struct {
//     float x;
//     float y;
//     float z;
// } Gyro_Struct;

// extern volatile Gyro_Struct Gyro_Structure;

// // 模块地址
// #define	IIC_ADDR		0x50
// // 航向角地址
// #define YAW_REG_ADDR	0x3F	
// // 寄存器解锁
// #define UN_REG			0x69
// // 保存寄存器
// #define SAVE_REG		0x00
// // 角度参考寄存器
// #define ANGLE_REFER_REG	0x01

// //角度环 位置
// #define GYRO_PID_P             (50)
// #define GYRO_PID_I             (0)
// #define GYRO_PID_D             (5.8)
// #define GYRO_PID_SL            (0)
// #define GYRO_PID_UL            (9999)

// #define GYRO_TARGET_ANGLE       (0)

// void Gyro_Init(void);
// uint8_t readDataJy61p(uint8_t dev, uint8_t reg, uint8_t *data, uint32_t length);
// uint8_t writeDataJy61p(uint8_t dev, uint8_t reg, uint8_t* data, uint32_t length);
// float Gyro_GetAngle(void);

// void Gyro_PID_Init(void);
// uint8_t Gyro_Angle_PID_Work(float Target_Angle);

#endif
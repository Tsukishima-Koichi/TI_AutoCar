#ifndef	__BSP_MOTOR_H__
#define __BSP_MOTOR_H__

#include "board.h"
#include "bsp_pid.h"

#define ABS(a)      (a>0 ? a:(-a))

extern int32_t Motor_Target;
#define MOTOR_TARGET_SPEED      (5)

//速度环 增量
#define MOTOR_PID_P             (4.15)
#define MOTOR_PID_I             (0.9)
#define MOTOR_PID_D             (0)
#define MOTOR_PID_SL            (0)
#define MOTOR_PID_UL            (9999)

extern PID Motor_PID;

extern int32_t PWMA, PWMB;
extern int32_t EncoderA_Cnt, EncoderB_Cnt;

void Motor_Init(void);
void Set_PWM(int pwma,int pwmb);
void Motor_SetSpeed(void);
void Motor_Stop(void);

void Motor_PID_Init(void);
void Motor_Velocity_PID_Work(void);

void Encoder_GetCnt(void);

#endif

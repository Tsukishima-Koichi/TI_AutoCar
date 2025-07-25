#ifndef	__BSP_TRACK_H__
#define __BSP_TRACK_H__

#include "ti_msp_dl_config.h"
#include "board.h"
#include "stdio.h"
#include "bsp_motor.h"
#include "bsp_pid.h"

#define L3	(DL_GPIO_readPins(TRACK_S1_PORT, TRACK_S1_PIN) > 0 ? 0 : 1)
#define L2	(DL_GPIO_readPins(TRACK_S2_PORT, TRACK_S2_PIN) > 0 ? 0 : 1)
#define L1	(DL_GPIO_readPins(TRACK_S3_PORT, TRACK_S3_PIN) > 0 ? 0 : 1)
#define L0	(DL_GPIO_readPins(TRACK_S4_PORT, TRACK_S4_PIN) > 0 ? 0 : 1)
#define R0	(DL_GPIO_readPins(TRACK_S5_PORT, TRACK_S5_PIN) > 0 ? 0 : 1)
#define R1	(DL_GPIO_readPins(TRACK_S6_PORT, TRACK_S6_PIN) > 0 ? 0 : 1)
#define R2	(DL_GPIO_readPins(TRACK_S7_PORT, TRACK_S7_PIN) > 0 ? 0 : 1)
#define R3	(DL_GPIO_readPins(TRACK_S8_PORT, TRACK_S8_PIN) > 0 ? 0 : 1)

#define TRACK_PID_P             (250)
#define TRACK_PID_I             (0)
#define TRACK_PID_D             (7)
#define TRACK_PID_SL            (0)
#define TRACK_PID_UL            (9999)

extern PID Track_PID;

void Track_PID_Init(void);
float Track_Scan(void);
void Track_Position_PID_Work(void);

#endif

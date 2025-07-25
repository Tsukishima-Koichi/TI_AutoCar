#ifndef	__BSP_TASK_H__
#define __BSP_TASK_H__

#include "ti_msp_dl_config.h"
#include "board.h"
#include "stdio.h"
#include "bsp_motor.h"
#include "bsp_gyro.h"
#include "bsp_pid.h"
#include "bsp_track.h"
#include "bsp_oled.h"


uint8_t task1 (void);
uint8_t task2 (void);


#endif

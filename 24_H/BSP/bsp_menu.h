#ifndef __BSP_MENU_H__
#define __BSP_MENU_H__

#include "board.h"
#include "bsp_motor.h"
#include "bsp_pid.h"
#include "bsp_gyro.h"
#include "bsp_track.h"
#include "bsp_oled.h"
#include "bsp_task.h"
#include "bsp_key.h"

extern uint8_t Menu_Flag[];

void Menu_Show(void);
uint8_t Menu_Set(void);

#endif
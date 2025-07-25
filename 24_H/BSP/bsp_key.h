#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include "board.h"

#define K1  (DL_GPIO_readPins(KEY_PORT, KEY_KEY1_PIN) > 0 ? 1 : 0)
#define K2  (DL_GPIO_readPins(KEY_PORT, KEY_KEY2_PIN) > 0 ? 1 : 0)
#define K3  (DL_GPIO_readPins(KEY_PORT, KEY_KEY3_PIN) > 0 ? 1 : 0)
#define K4  (DL_GPIO_readPins(KEY_PORT, KEY_KEY4_PIN) > 0 ? 1 : 0)

typedef struct KEY_Struct
{
	uint8_t stage;
	uint8_t flag;
	uint8_t single;
	uint8_t time;
} KEY;

extern KEY Key[];

void Key_Scan(void);


#endif
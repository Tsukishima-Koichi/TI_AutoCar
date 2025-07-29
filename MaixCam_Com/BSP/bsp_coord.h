#ifndef __BSP_COORD_H__
#define __BSP_COORD_H__

#include "board.h"

// 坐标数据结构体
typedef struct {
    int32_t red_x;    // 红色目标X坐标
    int32_t red_y;    // 红色目标Y坐标
    int32_t blue_x;   // 蓝色目标X坐标
    int32_t blue_y;   // 蓝色目标Y坐标
} COORD_DATA;

// 0xAA LEN_2BYTE LOAT_16BYTE CHECK_1BYTE 0x55

#define PACK_LEN    (1+2+16+1+1)
#define LOAD_LEN    16
#define PACK_HEAD   0xAA
#define PACK_TAIL   0x55

extern COORD_DATA Coord_Data;

void Coord_Init(void);

#endif
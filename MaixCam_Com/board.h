#ifndef	__BOARD_H__
#define __BOARD_H__

#include "ti_msp_dl_config.h"
#include "math.h"
#include "stdio.h"
#include "string.h"




#define NO_1    0
#define NO_2    1
#define NO_3    2
#define NO_4    3

int fputc(int c, FILE* stream);
int fputs(const char* restrict s, FILE* restrict stream);
int puts(const char *_ptr);

void board_init(void);

void delay_us(unsigned long __us);
void delay_ms(unsigned long ms);
void delay_1us(unsigned long __us);
void delay_1ms(unsigned long ms);



#endif

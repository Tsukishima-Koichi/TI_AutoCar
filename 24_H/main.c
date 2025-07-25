/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "main.h"

volatile uint8_t Timer0_Flag = 0;
volatile uint8_t Timer1_Cnt = 0;
volatile int32_t frame_cnt = 0;

uint8_t Task_Flag = 0;

int main(void)
{
    board_init();

    OLED_Init();
    
    Motor_Init(); //开启电机编码器引脚外部中断
    Motor_PID_Init();
    Gyro_Init();	//串口陀螺仪Jy61p初始化
    Gyro_PID_Init();
    Track_PID_Init();

    while (1)
    {
        if (Timer1_Cnt >= 8)
        {
            Task_Flag = Menu_Set();
            Menu_Show();
            Timer1_Cnt = 0;
            if (Task_Flag != 0)
                break;
        }
    }

    while (1) {
        
		// printf("%d,%d,%d,%d\n", EncoderA_Cnt,PWMA, EncoderB_Cnt, PWMB);
        // printf("%.2f\n", Track_Scan());
        //delay_ms(100);
        // printf("%d,%d,%d,%d,%d,%d,%d,%d\n", L3, L2, L1, L0, R0, R1, R2, R3);

        if (Timer0_Flag == 1)
        {		
            // Motor_Velocity_PID_Debug();
            // Motor_Velocity_PID_Work();
            // Track_Position_PID_Work();
            // Gyro_Angle_PID_Work(0);
            // Move_Straight(35.0);

            // Motor_SetSpeed();

            switch (Task_Flag)
            {
                case 1: {if(task1()) Task_Flag = 0;} break;
                case 2: task2(); break;
                case 3: break;
                case 4: break;
            }

            Timer0_Flag = 0;
        }
        // printf("%.2f\n", Gyro_Data.yaw);
        
        // if (Timer1_Cnt >= 8)
        // {
        //    OLED_ShowFloatNum(0, 0, Gyro_Data.yaw, 3, 2, OLED_8X16);
        //    OLED_Update();
        // }
    }
}


void TIMER_0_INST_IRQHandler(void)  //5ms
{
	if (DL_TimerA_getPendingInterrupt(TIMER_0_INST) == DL_TIMER_IIDX_ZERO)
	{
        Encoder_GetCnt();
        Timer0_Flag = 1;
	}
}

void TIMER_1_INST_IRQHandler(void) //10ms
{
    if (DL_TimerA_getPendingInterrupt(TIMER_1_INST) == DL_TIMER_IIDX_ZERO)
    {
        Key_Scan();
        frame_cnt++;
        Timer1_Cnt++;
    }

}


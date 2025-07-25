#include "bsp_task.h"
#include "bsp_motor.h"
#include "math.h"

uint8_t task1 (void)
{
    if (!(!L3 && !L2 && !L1 && !L0 && !R0 && !R1 && !R2 && !R3)) 
    {
        Motor_Stop();
        return 1;
    }
    Motor_Velocity_PID_Work();
    Gyro_Angle_PID_Work(0);
    Motor_SetSpeed();

    return 0;
}


extern int32_t frame_cnt;
uint8_t task2 (void)
{
    uint8_t track_flag = 0, blind_flag = 1;
    uint8_t blind_cnt = 0;
    if (frame_cnt == 3 && blind_flag == 0)
    {
        blind_flag = 1;
        track_flag = 0;
        blind_cnt ++;
        if(blind_cnt == 2) {
            Motor_Stop();
            return 1;
        } 
    }

    if (!(!L3 && !L2 && !L1 && !L0 && !R0 && !R1 && !R2 && !R3) && blind_flag == 1) 
    {
        track_flag = 1;
        blind_flag = 0;
    }

    if(track_flag == 1)
    {
        Motor_Velocity_PID_Work();
        Track_Position_PID_Work();
        Motor_SetSpeed();
    }
    
    if(blind_flag == 1) 
    {
        if(blind_cnt % 2 == 0) {
            Motor_Velocity_PID_Work();
            Gyro_Angle_PID_Work(0);
            Motor_SetSpeed();
        }
        else {
            Motor_Velocity_PID_Work();
            Gyro_Angle_PID_Work(179);
            Motor_SetSpeed();
        }
    }

    return 0;
}

void task3(void)
{
    uint8_t track_flag = 0, blind_flag = 1;
    uint8_t blind_cnt = 0;
    if (frame_cnt == 3 && blind_flag == 0)
    {
        blind_flag = 1;
        track_flag = 0;
        blind_cnt ++;
        if(blind_cnt == 2) {
            Motor_Stop();
            return;
        } 
    }

    if (!(!L3 && !L2 && !L1 && !L0 && !R0 && !R1 && !R2 && !R3) && blind_flag == 1) 
    {
        track_flag = 1;
        blind_flag = 0;
    }

    if(track_flag == 1)
    {
        Motor_Velocity_PID_Work();
        Track_Position_PID_Work();
        Set_PWM(PWMA, PWMB);
    }
    
    if(blind_flag == 1) 
    {
        if(blind_cnt % 2 == 0) {
            Gyro_Angle_PID_Work(37);
            Set_PWM(PWMA, PWMB);
        }
        else {
            Gyro_Angle_PID_Work(323);
            Set_PWM(PWMA, PWMB);
        }
    }
}

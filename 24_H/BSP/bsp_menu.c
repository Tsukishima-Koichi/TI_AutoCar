#include "bsp_menu.h"

uint8_t Menu_Flag[2] = {0, 0};

void Menu_Show(void)
{
    switch (Menu_Flag[1])
    {
        case 0:
        {
            OLED_ShowString(0, 0, "Task1           ", OLED_8X16);
            OLED_ShowString(0, 16, "Task2           ", OLED_8X16);
            OLED_ShowString(0, 32, "Task3           ", OLED_8X16);
            OLED_ShowString(0, 48, "Task4           ", OLED_8X16);
            OLED_ReverseArea(0, Menu_Flag[0] * 16, 128, 16);
        } break;
        case 1:
        {
            OLED_ShowString(0, 0, "Kp:             ", OLED_8X16);
            OLED_ShowNum(3*8, 0, Track_PID.kP, 3, OLED_8X16);
            OLED_ShowString(0, 16, "Ki:             ", OLED_8X16);
            OLED_ShowNum(3*8, 16, Track_PID.kI, 2, OLED_8X16);
            OLED_ShowString(0, 32, "Kd:             ", OLED_8X16);
            OLED_ShowNum(3*8, 32, Track_PID.kD, 2, OLED_8X16);
            OLED_ShowString(0, 48, "TarSpd:         ", OLED_8X16);
            OLED_ShowNum(7*8, 48, Motor_Target, 2, OLED_8X16);
            OLED_ReverseArea(0, Menu_Flag[0] * 16, 128, 16);
        } break;
    }

    OLED_Update();
}

uint8_t Menu_Set(void)
{
    if (Key[0].single == 1)
    {
        Menu_Flag[0] = Menu_Flag[0] + 1;
        if (Menu_Flag[0] == 4)
        {
            Menu_Flag[0] = 0;
            Menu_Flag[1] = (Menu_Flag[1]+1) % 2;
        }
        Key[0].single = 0;
    }

    if (Menu_Flag[1] == 0)
    {
        if (Key[3].single == 1)
        {
            switch (Menu_Flag[0])
            {
                case 0: return 1;
                case 1: return 2;
                case 2: return 3;
                case 3: return 4;
            }
        }
    }
    else if (Menu_Flag[1] == 1)
    {
        if (Key[1].single == 1)
        {
            switch(Menu_Flag[0])
            {
                case 0:
                {
                    Track_PID.kP += 5;
                    Key[1].single = 0;
                } break;
                case 1:
                {
                    Track_PID.kI += 1;
                    Key[1].single = 0;
                } break;
                case 2:
                {
                    Track_PID.kD += 1;
                    Key[1].single = 0;
                } break;
                case 3:
                {
                    Motor_Target += 1;
                    Key[1].single = 0;
                } break;
            }
        }
        if (Key[2].single == 1)
        {
            switch(Menu_Flag[0])
            {
                case 0:
                {
                    Track_PID.kP -= 1;
                    Key[2].single = 0;
                } break;
                case 1:
                {
                    Track_PID.kI -= 1;
                    Key[2].single = 0;
                } break;
                case 2:
                {
                    Track_PID.kD -= 1;
                    Key[2].single = 0;
                } break;
                case 3:
                {
                    Motor_Target -= 1;
                    Key[2].single = 0;
                } break;
            }
        }
    }

    return 0;
}



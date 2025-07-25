#include "bsp_key.h"

KEY Key[4] = {0, 0, 0, 0};

void Key_Scan(void)
{
	
	Key[0].flag = K1;
	Key[1].flag = K2;
	Key[2].flag = K3;
	Key[3].flag = K4;
	
	for (char i = 0; i < 4; i++)
	{
		switch (Key[i].stage)
		{
			case 0:
			{
				if (Key[i].flag == 0)
					Key[i].stage = 1;
			} break;
			case 1:
			{
				if (Key[i].flag == 1)
					Key[i].stage = 0;
				else if (Key[i].flag == 0)
				{
					Key[i].stage = 2;
					Key[i].time = 0;
				}
			} break;
			case 2:
			{
				if (Key[i].flag == 1)
				{	
					Key[i].stage = 0;
					Key[i].single = 1;
					// if (Key[i].time <= 20)
					// 	Key[i].single = 1;
					// else if (Key[i].time > 20)
					// 	Key[i].single = 2;
				}
				else
					Key[i].time++;
			} break;
		}
	}
}

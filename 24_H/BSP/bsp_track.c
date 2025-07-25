#include "bsp_track.h"

PID Track_PID;


float Track_Scan(void)
{
    float position = 0;

	if(L3 && !L2 && !L1 && !L0 && !R0 && !R1 && !R2 && !R3)// 1 0 0 0 0 0 0 0
	{
		position = -4;
	}
	else if(L3 && L2 && !L1 && !L0 && !R0 && !R1 && !R2 && !R3)// 1 1 0 0 0 0 0 0
	{
		position = -3.5;
	}
	else if(!L3 && L2 && !L1 && !L0 && !R0 && !R1 && !R2 && !R3)// 0 1 0 0 0 0 0 0
	{
		position = -3;
	}
	else if(!L3 && L2 && L1 && !L0 && !R0 && !R1 && !R2 && !R3)// 0 1 1 0 0 0 0 0
	{
		position = -2.5;
	}
	else if(!L3 && !L2 && L1 && !L0 && !R0 && !R1 && !R2 && !R3)// 0 0 1 0 0 0 0 0
	{
		position = -2;
	}
	else if(!L3 && !L2 && L1 && L0 && !R0 && !R1 && !R2 && !R3)// 0 0 1 1 0 0 0 0
	{
		position = -1.5;
	}
	else if(!L3 && !L2 && !L1 && L0 && !R0 && !R1 && !R2 && !R3)// 0 0 0 1 0 0 0 0
	{
		position = -1;
	}
	else if(!L3 && !L2 && !L1 && L0 && R0 && !R1 && !R2 && !R3)// 0 0 0 1 1 0 0 0
	{
		position = 0;
	}
	else if(!L3 && !L2 && !L1 && !L0 && R0 && !R1 && !R2 && !R3)// 0 0 0 0 1 0 0 0
	{
		position = 1;
	}
	else if(!L3 && !L2 && !L1 && !L0 && R0 && R1 && !R2 && !R3)// 0 0 0 0 1 1 0 0
	{
		position = 1.5;
	}
	else if(!L3 && !L2 && !L1 && !L0 && !R0 && R1 && !R2 && !R3)// 0 0 0 0 0 1 0 0
	{
		position = 2;
	}
	else if(!L3 && !L2 && !L1 && !L0 && !R0 && R1 && R2 && !R3)// 0 0 0 0 0 1 1 0
	{
		position = 2.5;
	}
	else if(!L3 && !L2 && !L1 && !L0 && !R0 && !R1 && R2 && !R3)// 0 0 0 0 0 0 1 0
	{
		position = 3;
	}
	else if(!L3 && !L2 && !L1 && !L0 && !R0 && !R1 && R2 && R3)// 0 0 0 0 0 0 1 1
	{
		position = 3.5;
	}
	else if(!L3 && !L2 && !L1 && !L0 && !R0 && !R1 && !R2 && R3)// 0 0 0 0 0 0 0 1
	{
		position = 4;
	}
	else if(!L3 && !L2 && !L1 && !L0 && !R0 && !R1 && !R2 && !R3)// 0 0 0 0 0 0 0 0
	{
		position = 0;
	}
	else if(L3 && L2 && L1 && L0 && R0 && R1 && R2 && R3)// 1 1 1 1 1 1 1 1 
	{
		position = 0;
	}

	return position;
}


void Track_PID_Init(void)
{
    PID_Init(&Track_PID);

    PID_SetParameter(&Track_PID, TRACK_PID_P, TRACK_PID_I, TRACK_PID_D, TRACK_PID_SL, TRACK_PID_UL, 1);
}

void Track_Position_PID_Work(void)
{
    PID_PositionalPID(&Track_PID, 0, Track_Scan());

    PWMA += (int32_t)Track_PID.ut;
    PWMB += -(int32_t)Track_PID.ut;
}

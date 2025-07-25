#include "bsp_motor.h"

PID MotorA_PID, MotorB_PID;//A左 B右

int32_t Motor_Target = MOTOR_TARGET_SPEED;

int32_t PWMA,PWMB;
int32_t Get_Encoder_CountA, Get_Encoder_CountB, EncoderA_Cnt, EncoderB_Cnt;

uint32_t gpio_interrup;

void Motor_Init(void)
{
	//编码器引脚外部中断
	NVIC_ClearPendingIRQ(GPIOB_INT_IRQn);
	NVIC_EnableIRQ(GPIOB_INT_IRQn);
  //定时器中断
	NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);  

	//printf("Motor initialized successfully\r\n");
}

//左右电机速度控制，范围0-9999
void Set_PWM(int pwma,int pwmb)
{
	if(pwma > 0) //左轮前进
	{
		DL_GPIO_setPins(MOTOR_AIN1_PORT,MOTOR_AIN1_PIN);
		DL_GPIO_clearPins(MOTOR_AIN2_PORT,MOTOR_AIN2_PIN);
		DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,ABS(pwma),GPIO_PWM_MOTOR_C0_IDX);
	}
	else //左轮后退
	{
        DL_GPIO_setPins(MOTOR_AIN2_PORT,MOTOR_AIN2_PIN);
		DL_GPIO_clearPins(MOTOR_AIN1_PORT,MOTOR_AIN1_PIN);	
		DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,ABS(pwma),GPIO_PWM_MOTOR_C0_IDX);		
	}
	if(pwmb > 0)//右轮前进
	{
		DL_GPIO_setPins(MOTOR_BIN1_PORT,MOTOR_BIN1_PIN);
		DL_GPIO_clearPins(MOTOR_BIN2_PORT,MOTOR_BIN2_PIN);
		DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,ABS(pwmb),GPIO_PWM_MOTOR_C1_IDX);
	}
  else//右轮后退
	{
		DL_GPIO_setPins(MOTOR_BIN2_PORT,MOTOR_BIN2_PIN);
		DL_GPIO_clearPins(MOTOR_BIN1_PORT,MOTOR_BIN1_PIN);
		DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,ABS(pwmb),GPIO_PWM_MOTOR_C1_IDX);
	}		

}

void Motor_SetSpeed(void)
{
	Set_PWM(PWMA, PWMB);
}

void Motor_Stop(void)
{
		DL_GPIO_setPins(MOTOR_AIN1_PORT,MOTOR_AIN1_PIN);
		DL_GPIO_setPins(MOTOR_AIN2_PORT,MOTOR_AIN2_PIN);
		DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,0,GPIO_PWM_MOTOR_C0_IDX);

		DL_GPIO_setPins(MOTOR_BIN2_PORT,MOTOR_BIN2_PIN);
		DL_GPIO_setPins(MOTOR_BIN1_PORT,MOTOR_BIN1_PIN);
		DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST,0,GPIO_PWM_MOTOR_C1_IDX);

}

void Motor_PID_Init(void)
{
    PID_Init(&MotorA_PID);
    PID_Init(&MotorB_PID);
    
    PID_SetParameter(&MotorA_PID, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_SL, MOTOR_PID_UL, 1);
    PID_SetParameter(&MotorB_PID, MOTOR_PID_P, MOTOR_PID_I, MOTOR_PID_D, MOTOR_PID_SL, MOTOR_PID_UL, 1);
}

void Motor_Velocity_PID_Work(void)
{
    PID_IncrementalPID(&MotorA_PID, Motor_Target, EncoderA_Cnt);
    PID_IncrementalPID(&MotorB_PID, Motor_Target, EncoderB_Cnt);
    PWMA = MotorA_PID.ut;
    PWMB = MotorB_PID.ut;
}


//外部中断模拟编码器信号
void GROUP1_IRQHandler(void)
{
	//获取中断信号
	gpio_interrup = DL_GPIO_getEnabledInterruptStatus(GPIOB,ENCODER_E1A_PIN|ENCODER_E1B_PIN|ENCODER_E2A_PIN|ENCODER_E2B_PIN);
	//encoderA
	if((gpio_interrup & ENCODER_E1A_PIN)==ENCODER_E1A_PIN)
	{
		if(!DL_GPIO_readPins(GPIOB,ENCODER_E1B_PIN))
		{
			Get_Encoder_CountA--;
		}
		else
		{
			Get_Encoder_CountA++;
		}
	}
	else if((gpio_interrup & ENCODER_E1B_PIN)==ENCODER_E1B_PIN)
	{
		if(!DL_GPIO_readPins(GPIOB,ENCODER_E1A_PIN))
		{
			Get_Encoder_CountA++;
		}
		else
		{
			Get_Encoder_CountA--;
		}
	}
	//encoderB
	if((gpio_interrup & ENCODER_E2A_PIN)==ENCODER_E2A_PIN)
	{
		if(!DL_GPIO_readPins(GPIOB,ENCODER_E2B_PIN))
		{
			Get_Encoder_CountB--;
		}
		else
		{
			Get_Encoder_CountB++;
		}
	}
	else if((gpio_interrup & ENCODER_E2B_PIN)==ENCODER_E2B_PIN)
	{
		if(!DL_GPIO_readPins(GPIOB,ENCODER_E2A_PIN))
		{
			Get_Encoder_CountB++;
		}
		else
		{
			Get_Encoder_CountB--;
		}
	}
	DL_GPIO_clearInterruptStatus(GPIOB,ENCODER_E1A_PIN|ENCODER_E1B_PIN|ENCODER_E2A_PIN|ENCODER_E2B_PIN);
}

void Encoder_GetCnt(void)
{
    EncoderA_Cnt = Get_Encoder_CountA;//两个电机安装相反，所以编码器值也要相反
    EncoderB_Cnt = -Get_Encoder_CountB;
    Get_Encoder_CountA = 0;//编码器计数值清零
    Get_Encoder_CountB = 0;
}


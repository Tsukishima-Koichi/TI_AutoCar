#ifndef	__BSP_PID_H__
#define __BSP_PID_H__


//PID类型
typedef enum{
    PostionalPID,IncrementalPID
}PIDCLASS_enum;

//PID结构体
struct STRUCT_PID {
        float kP;
        float kI;
        float kD;
        float kPSet;
        float kISet;
        float kDSet;
        float sum;
        float preError;
        float ppreError;
        float ut;
        float sumLimit;
        float utLimit;
};

typedef struct STRUCT_PID PID;
void PID_Init(PID *p);
void PID_SetParameter(PID *p, float setP, float setI, float setD, float pLimit, float coLimit, float boost);
void PID_PositionalPID(PID *p, float target, float cur);
void PID_AnglePID(PID *p, float error);
void PID_IncrementalPID(PID *p, float target, float cur);


#endif

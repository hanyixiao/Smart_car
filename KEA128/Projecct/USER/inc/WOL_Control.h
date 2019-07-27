#ifndef _WOL_CONTROL_H_
#define _WOL_CONTROL_H_

#include "headfile.h"

typedef struct
{
  int16 LeftSpeed;
  int16 RightSpeed;
} MotorType;

//--------------WOL�ǶȻ�����--------------
extern float Acc_Z;
extern float Gyro_Y,Gyro_X;
extern float GyroYRead[3];
extern float GyroXRead[3];
extern float Angle;
extern float AngularSpeed;
extern float Car_Angle;
extern float Angle_Speed;
//--------------WOL�ٶȻ�����--------------
extern float TargetAngle;
extern float RunTime;
extern float Distance;
extern float CarSpeed ;
extern float ControlSpeed;
extern uint8 IfInSpeedway;
extern int16 SpeedReadRight;
extern int16 SpeedReadLeft;
extern int32 PluseRight;
extern int32 PluseLeft;
extern float SetSpeed;
extern float SpeedControlIntegral;
extern float Speed_100ms_Addtion;
extern float SpeedControlOutOld,SpeedControlOutNew;
extern float SpeedNeedAngleLast;
//--------------WOLת�򻷱���----------------
extern float TurnError;
extern float TurnErrorLast;
//--------------WOL������Ʊ���--------------
extern MotorType MotorSpeed;
extern PIDType Angle_PID,Speed_PID,Turn_PID;

extern MotorType MotorSpeed;
extern PIDType Angle_PID,Speed_PID,Turn_PID;

void GetAttitude();
void KalmanAngalCalculate();
void Angle_Control();
void SpeedGet();
void SpeedControl();
void Speed_Control_Output();
void TurnRing(float ringR);
void Direction_Control();
void LocationCheck();
void Motor_Speed_Set();

#endif //_WOL_CONTROL_H_
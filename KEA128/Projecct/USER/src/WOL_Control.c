#include "headfile.h"

//--------------WOL角度环变量--------------
float Acc_Z;
float Gyro_Y,Gyro_X;
float GyroYRead[3]={0,0,0};
float GyroXRead[3]={0,0,0};
float Angle = 0.0;
float AngularSpeed = 0.0;
float Car_Angle = 0;
float Angle_Speed = 0;
//--------------WOL速度环变量--------------
float TargetAngle = 0.0;
float RunTime = 0.0;
float Distance = 0.0;
float CarSpeed = 0.0;
float ControlSpeed = 0.0;
uint8 IfInSpeedway = 1;
int16 SpeedReadRight = 0;
int16 SpeedReadLeft = 0;
int32 PluseRight = 0;
int32 PluseLeft = 0;
float SetSpeed = 150.0;
float Speed_100ms_Addtion = 0.0;
float SpeedControlIntegral = 0.0;
float SpeedControlOutOld,SpeedControlOutNew;
float SpeedNeedAngle = 0.0;
float SpeedNeedAngleLast = 0.0;
//--------------WOL转向环变量--------------
float TurnError = 0;
float TurnErrorLast = 0;
//--------------WOL脉宽调制变量--------------
MotorType MotorSpeed;
PIDType Angle_PID,Speed_PID,Turn_PID;
//-------------------------------------------------------
static  float Q_angle=0.25, Q_gyro=0.0001, R_angle=15, dt=0.005;
static float Pk[2][2];
volatile float Pdot[4] ={0,0,0,0};
static float q_bias=0, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
void Kalman_Filter(float angle_m,float gyro_m)			
{
        Pk[0][0]=1;
        Pk[0][1]=0;
        Pk[1][0]=0;
        Pk[1][1]=1;
	Car_Angle+=(gyro_m-q_bias) * dt; ///预测值
	Pdot[0]=Q_angle - Pk[0][1] - Pk[1][0];
	Pdot[1]=- Pk[1][1];
        Pdot[2]=- Pk[1][1];
	Pdot[3]=Q_gyro;
	
	Pk[0][0] += Pdot[0] * dt;
	Pk[0][1] += Pdot[1] * dt;
	Pk[1][0] += Pdot[2] * dt;
	Pk[1][1] += Pdot[3] * dt;
	
	angle_err = angle_m -Car_Angle;///测量值-预测值
	
	PCt_0 =  Pk[0][0];
	PCt_1 =  Pk[1][0];
	
	E = R_angle + PCt_0;
	
	K_0 = PCt_0 / E; ///卡尔曼增益
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = Pk[0][1];

	Pk[0][0] -= K_0 * t_0;
	Pk[0][1] -= K_0 * t_1;
	Pk[1][0] -= K_1 * t_0;
	Pk[1][1] -= K_1 * t_1;
	
	Car_Angle+= K_0 * angle_err; ///最优角度=预测值+卡尔曼增益*(测量值-预测值)
	q_bias	+= K_1 * angle_err;
	Angle_Speed = gyro_m-q_bias;
}

void GetAttitude()
{
  Acc_Z = MPU6050_ACCEL_Z_data();
  GyroYRead[0] = MPU6050_GYRO_Y_data() + GroY_offset; 
  GyroXRead[0] = MPU6050_GYRO_X_data() + GroX_offset;
  Gyro_X = GyroXRead[0]*0.5 + GyroXRead[1]*0.3 + GyroXRead[2]*0.2;
  Gyro_Y = GyroYRead[0]*0.5 + GyroYRead[1]*0.3 + GyroYRead[2]*0.2;
  GyroXRead[2] = GyroXRead[1];
  GyroXRead[1] = GyroXRead[0];
  GyroYRead[2] = GyroYRead[1];
  GyroYRead[1] = GyroYRead[0];
  
#if Watch_Ware == Angle_Ware
    OutData[0] = Acc_Z;
    OutData[1] = Gyro_X;
    OutData[2] = Gyro_Y;
    OutData[3] = 0;
    OutData[4] = 0;
    OutData[5] = 0;
#endif
}

void KalmanAngalCalculate()
{
  GetAttitude();
  Angle = (Acc_Z-Acc_Z_Offset)*KalmanRatioAcc;
  AngularSpeed = (-Gyro_Y)*KalmanRatioGro;
  Kalman_Filter((float)Angle,(float)AngularSpeed);
#if Watch_Ware == Kalman_Ware
    OutData[0] = Angle;
    OutData[1] = AngularSpeed;
    OutData[2] = Car_Angle;
    OutData[3] = Angle_Speed;
    OutData[4] = Acc_Z;
    OutData[5] = 0;
#endif
}

void SpeedGet()
{
  int8 dir_r=0;
  int8 dir_l=0;
  
  SpeedReadRight = ftm_count_get(Right_Count_FTM);
  SpeedReadLeft = ftm_count_get(Left_Count_FTM);
  ftm_count_clean(Right_Count_FTM);
  ftm_count_clean(Left_Count_FTM);
  dir_r = gpio_get(Right_Direction_PORT);
  dir_l = gpio_get(Left_Direction_PORT);
  if(dir_r == Back_Status_R) SpeedReadRight = -SpeedReadRight;
  if(dir_l == Back_Status_L) SpeedReadLeft = -SpeedReadLeft;
  PluseRight += SpeedReadRight;
  PluseLeft += SpeedReadLeft;
  Distance += (SpeedReadRight + SpeedReadLeft)*0.000074;
  
  CarSpeed = CarSpeed*0.1 + 0.45*(SpeedReadRight + SpeedReadLeft);
  ControlSpeed = ControlSpeed*0.8 + CarSpeed*0.2;
#if Watch_Ware == Speed_Ware_Get
    OutData[0] = CarSpeed;
    OutData[1] = ControlSpeed;
    OutData[2] = Distance;
    OutData[3] = PluseRight;
    OutData[4] = PluseLeft;
    OutData[5] = SpeedReadRight; 
#endif
}

void SpeedControl()
{
  float speederror = 0.0;
  
  speederror = SetSpeed - Speed_100ms_Addtion*SpeedRatio;
  SpeedControlIntegral += speederror * Speed_PID.I;
  SpeedControlIntegral = limit_ab(SpeedControlIntegral,-80.0,80.0);
  SpeedControlOutOld = SpeedControlOutNew;
  SpeedControlOutNew = speederror*Speed_PID.P + SpeedControlIntegral;
  
  SpeedNeedAngleLast = Speed_PID.OUT;
  Speed_PID.OUT = SpeedControlOutNew*Speed2Angle;
  if(Speed_PID.OUT - SpeedNeedAngleLast > MaxSpeedchange) 
  {
    Speed_PID.OUT = SpeedNeedAngleLast + MaxSpeedchange;
  }
  else if(Speed_PID.OUT - SpeedNeedAngleLast < -MaxSpeedchange) 
  {
    Speed_PID.OUT = SpeedNeedAngleLast - MaxSpeedchange;
  }
  Speed_PID.OUT = limit_ab(Speed_PID.OUT,MinSafeAngle,MaxSafeAngle);
}

void Speed_Control_Output()
{
  float fValue;
  fValue = Speed_PID.OUT - SpeedNeedAngleLast;
  SpeedNeedAngle = fValue*(PIT0_InterTimes + 1)/Speed_Filter_Times + SpeedNeedAngleLast;
#if Watch_Ware == Speed_Ware
    OutData[0] = Speed_PID.OUT;
    OutData[1] = SpeedNeedAngle;
    OutData[2] = SetSpeed;
    OutData[3] = TargetAngle;
    OutData[4] = Speed_100ms_Addtion;
    OutData[5] = Car_Angle; 
#endif
}

void Angle_Control()
{
  TargetAngle = Car_Angle + SpeedNeedAngle;
  if(TargetAngle > MaxSafeAngle) 
  {
    TargetAngle = MaxSafeAngle;
  }
  else if(TargetAngle < MinSafeAngle) 
  {
    TargetAngle = MinSafeAngle;
  }
  Angle_PID.Pout = Angle_PID.P * TargetAngle;
  Angle_PID.Dout = Angle_PID.D *Angle_Speed;
  Angle_PID.OUT = Angle_PID.Pout + Angle_PID.Dout;
}

void TurnRing(float ringR)
{
  static float speed_get_r[5];
  static float speed_get_l[5];
  static float speed_l=0;
  static float speed_r=0;
  static float round_speed=0;
  static float round_error=0;
  static float round_error_old=0;
  static float speed_gyro[5];
  speed_get_r[4]=SpeedReadRight;
  speed_get_l[4]=SpeedReadLeft;
  speed_gyro[4]=Gyro_X;
  for(uint8 i=0;i<=3;i++)
  {
    speed_get_r[i]=speed_get_r[i+1];
    speed_get_l[i]=speed_get_l[i+1];
    speed_gyro[i]=speed_gyro[i+1];
  }
  speed_r=(speed_get_r[0]+speed_get_r[1]+speed_get_r[2]+speed_get_r[3]+speed_get_r[4])/5;
  speed_l=(speed_get_l[0]+speed_get_l[1]+speed_get_l[2]+speed_get_l[3]+speed_get_l[4])/5;
  
  round_speed=speed_r-speed_l;
  round_error=ringR-round_speed;
  Turn_PID.P=25.0;//15
  Turn_PID.D=0.0;//0.01
  Turn_PID.G=0.045; //0.045
  Turn_PID.OUT=Turn_PID.P*round_error+Turn_PID.D*(round_error-round_error_old)+Turn_PID.G*Gyro_X;
  round_error_old=round_error;
}
float  Turn_Out_Filter(float turn_out)      
{
  float Turn_Out_Filtered; 
  static float Pre_Turn_Error[4]; 
  Pre_Turn_Error[3] = Pre_Turn_Error[2];
  Pre_Turn_Error[2] = Pre_Turn_Error[1];
  Pre_Turn_Error[1] = Pre_Turn_Error[0];
  Pre_Turn_Error[0] = turn_out;
  Turn_Out_Filtered = Pre_Turn_Error[0]*0.4+Pre_Turn_Error[1]*0.3+Pre_Turn_Error[2]*0.2+Pre_Turn_Error[3]*0.1;
  return Turn_Out_Filtered;
}
void Direction_Control()
{
  Inductor_Error_Get();
 // TurnError=Turn_Out_Filter(TurnError);
  TurnRing(TurnError*0.55);
  
//  if(myabs((int16)TurnError) < TurnStageFirst)
//  {
//    Turn_PID.P = TurnFirstP;
//    Turn_PID.D = TurnFirstD;
//    Turn_PID.G = TurnFirstG;
//  }
//  else if(myabs((int16)TurnError) < TurnStageSecond)
//  {
//    Turn_PID.P = TurnSecondP;
//    Turn_PID.D = TurnSecondD;
//    Turn_PID.G = TurnSecondG;    
//  }
//  else if(myabs((int16)TurnError) < TurnStageThird)
//  {
//    Turn_PID.P = TurnThirdP;
//    Turn_PID.D = TurnThirdD;
//    Turn_PID.G = TurnThirdG;    
//  }
//  else 
//  {
//    TurnError = TurnErrorLast; 
//    Turn_PID.P = TurnThirdP;
//    Turn_PID.D = TurnThirdD;
//    Turn_PID.G = TurnThirdG;
//  }
//  Turn_PID.OUT = Turn_PID.P*TurnError + Turn_PID.D*(TurnError - TurnErrorLast) + Turn_PID.G*(Gyro_X);
//  TurnErrorLast = TurnError;
// // Turn_PID.OUT = Turn_Out_Filter(Turn_PID.OUT);
}

void LocationCheck()
{   IfInSpeedway = 1;

    if(((Inductor_R[4] <= 20.0) && (Inductor_L[4] <= 20.0))) 
    {
      IfInSpeedway = 0;
      PathType = 0;
    }
    else 
    {
    IfInSpeedway = 1;
    }

}

//电机输出
void Motor_Speed_Set()
{
  float FinalSpeed;
  
  FinalSpeed = Angle_PID.OUT;
  
  if(FinalSpeed > SpeedLimitOne) FinalSpeed = SpeedLimitOne;
  else if(FinalSpeed < -SpeedLimitOne) FinalSpeed = -SpeedLimitOne;
  
  MotorSpeed.LeftSpeed = (int16)(FinalSpeed + Death_Left) - (int16)(Turn_PID.OUT);
  MotorSpeed.RightSpeed = (int16)(FinalSpeed + Death_Right) + (int16)(Turn_PID.OUT);
  
  if(MotorSpeed.LeftSpeed > SpeedLimitTwo) MotorSpeed.LeftSpeed = SpeedLimitTwo;
  else if(MotorSpeed.LeftSpeed < -SpeedLimitTwo) MotorSpeed.LeftSpeed = -SpeedLimitTwo;
  if(MotorSpeed.RightSpeed > SpeedLimitTwo) MotorSpeed.RightSpeed = SpeedLimitTwo;
  else if(MotorSpeed.RightSpeed < -SpeedLimitTwo) MotorSpeed.RightSpeed = -SpeedLimitTwo;
  
  if(IfInSpeedway == 1)
  {
    if(MotorSpeed.LeftSpeed >= 0)
    {
      ftm_pwm_duty(Motor_FTM,Motor_CH1,0);
      ftm_pwm_duty(Motor_FTM,Motor_CH0,MotorSpeed.LeftSpeed);
    }
    if(MotorSpeed.LeftSpeed < 0)
    {
      MotorSpeed.LeftSpeed = -MotorSpeed.LeftSpeed;
      ftm_pwm_duty(Motor_FTM,Motor_CH1,MotorSpeed.LeftSpeed);
      ftm_pwm_duty(Motor_FTM,Motor_CH0,0);
    }
    
    if(MotorSpeed.RightSpeed >= 0)
    {
      ftm_pwm_duty(Motor_FTM,Motor_CH3,0);
      ftm_pwm_duty(Motor_FTM,Motor_CH2,MotorSpeed.RightSpeed);
    }
    if(MotorSpeed.RightSpeed < 0)
    {
      MotorSpeed.RightSpeed = -MotorSpeed.RightSpeed;
      ftm_pwm_duty(Motor_FTM,Motor_CH3,MotorSpeed.RightSpeed);
      ftm_pwm_duty(Motor_FTM,Motor_CH2,0);
    }
  }
  else
  {
    ftm_pwm_duty(Motor_FTM,Motor_CH0,0);
    ftm_pwm_duty(Motor_FTM,Motor_CH1,0);
    ftm_pwm_duty(Motor_FTM,Motor_CH2,0);
    ftm_pwm_duty(Motor_FTM,Motor_CH3,0);
  }
}
/*!
 * @file       WOL_PARA.h
 * @brief      参量宏定义文件
 * @author     光之翼-周浩男
 * @version    v1.0.0                              
 * @date       2017-11-21
 */
#ifndef _WOL_PARA_H_
#define _WOL_PARA_H_

#define Whitout_Ware   0
#define ADC_Ware       1
#define Angle_Ware     2
#define Speed_Ware     3
#define Speed_Ware_Get 4
#define Run_Ware       5
#define TurnPIDWare    6
#define Kalman_Ware    7
   
#define Watch_Ware  ADC_Ware

#define BAUD_ZHN  9600
#define WARE_UART uart2   
   
typedef struct
{
  float P,Pout;
  float I,Iout;
  float D,Dout,G;
  float OUT;
} PIDType;

extern uint8 PIT0_InterTimes;

/***********电机控制参数************/ 
#define Motor_FTM ftm2

#define Motor_CH0 ftm_ch1
#define Motor_CH1 ftm_ch0
#define Motor_CH2 ftm_ch2
#define Motor_CH3 ftm_ch3

#define FTM_Freq 10000
 
/***********直立控制变量************/   
#define Acc_Z_Offset 1400//1080
#define KalmanRatioGro 0.080
#define KalmanRatioAcc 0.01
#define GroY_offset 280
#define GroX_offset 270
#define Angle_P 50//17.0//16.5f
#define Angle_D 0.80

#define Death_Left 20
#define Death_Right 20

#define MaxSafeAngle 45
#define MinSafeAngle (-10)

/***********速度控制变量************/  
#define Right_Count_FTM ftm1
#define Left_Count_FTM ftm0
#define Right_Direction_PORT H5
#define Left_Direction_PORT H7
#define Back_Status_R 1
#define Back_Status_L 0

#define SpeedRatio 0.1679
#define Speed2Angle (-0.03)//(-0.06)
#define MaxSpeedchange 0.5//3
#define Speed_Filter_Times 20

#define Speed_P 3.2f
#define Speed_I 0.02//0.02f
#define SpeedFilterRatio 0.85f
#define Speed_Filter_Times 20
#define SpeedLimitOne 450//600

/***********转向控制变量************/ 
#define TurnStageFirst  30
#define TurnFirstP      3.6//3.0
#define TurnFirstD      6.0//6.0
#define TurnFirstG      0.020//0.020//0.025
#define TurnStageSecond 80
#define TurnSecondP     3.0//2.5//2.5//3.0
#define TurnSecondD     6.0//16.0
#define TurnSecondG     0.040//0.020
#define TurnStageThird  130
#define TurnThirdP      2.4//2.0//2.0
#define TurnThirdD      10.0//8.0//15.0
#define TurnThirdG      0.015
#define TurnLimit       380
#define Fuzzy_P_Ratio  0.0015//0.020//0.016//0.0032 
#define Fuzzy_G_Ratio  0.00020// 0.00025    
/**********************************/
#define SpeedLimitTwo 900


#endif

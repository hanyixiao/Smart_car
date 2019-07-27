#include "headfile.h"

KEYX_n KEY_Flag;

void Speed_Init()
{
  while(1)
  {
    KEY_Flag = Read_KEYMassage();
    if(KEY_Flag == CenterKey)
    {
      OLED_Fill(0x00);
      OLED_P6x8Str(0,0,"OK!");
      OLED_Print_Num1(18,0,(int16)SetSpeed);
      break;
    }
    else if(KEY_Flag == RightKey)
    {
      SetSpeed += 10;
      OLED_Print_Num1(36,0,(int16)SetSpeed);
    }
    else if(KEY_Flag == LeftKey)
    {
      SetSpeed -= 10;
      OLED_Print_Num1(36,0,(int16)SetSpeed);
    }
     else if(KEY_Flag == UpKey)
    {
      SetSpeed += 50;
      OLED_Print_Num1(36,0,(int16)SetSpeed);
    }
     else if(KEY_Flag == DownKey)
    {
      SetSpeed -= 50;
      OLED_Print_Num1(36,0,(int16)SetSpeed);
    }
  }
}

void AllInit()
{
  get_clk();              //获取时钟频率 必须执行
  
  Angle_PID.P = Angle_P;
  Angle_PID.D = Angle_D;
  Speed_PID.P = Speed_P;
  Speed_PID.I = Speed_I;
  
  IIC_init();
  InitMPU6050();
  OLED_Init();
  OLED_Fill(0x00);
  OLED_P6x8Str(0,0,"Speed:");
  OLED_Print_Num1(36,0,(int16)SetSpeed);
  WOL_LED_Init(LED_ALL,LED_OFF);
  KEY_Init(AllKey);
  Speed_Init();
  Inductor_Init();
  uart_init(WARE_UART,BAUD_ZHN);
  ftm_count_init(Right_Count_FTM);
  ftm_count_init(Left_Count_FTM);
  gpio_init(Right_Direction_PORT,GPI,0);
  gpio_init(Left_Direction_PORT,GPI,0);
  ftm_pwm_init(Motor_FTM,Motor_CH0,FTM_Freq,0);
  ftm_pwm_init(Motor_FTM,Motor_CH1,FTM_Freq,500);//LEFT
  ftm_pwm_init(Motor_FTM,Motor_CH2,FTM_Freq,0);
  ftm_pwm_init(Motor_FTM,Motor_CH3,FTM_Freq,500);//RIGNT  
  pit_init(pit0,5 * bus_clk_khz);
  set_irq_priority(PIT_CH0_IRQn,1);
  enable_irq(PIT_CH0_IRQn);
  EnableInterrupts;
}


int main(void)
{
  AllInit();
  
  while(1)
  {
      WOL_SendWare((uint8*)OutData,sizeof(OutData));
  }
}


#include "headfile.h"

uint8 PIT0_InterTimes = 0;

void PIT_CH0_IRQHandler(void)
{
  PathTypeLEDSet();
  RunTime += 0.005;
  KalmanAngalCalculate();
  SpeedGet();
  Speed_100ms_Addtion += ControlSpeed;
  PIT0_InterTimes++;
  if(PIT0_InterTimes == 20)
  {
    PIT0_InterTimes = 0;
    SpeedControl();
    Speed_100ms_Addtion = 0;
  }
  Speed_Control_Output();
  Direction_Control();
  Angle_Control();
  LocationCheck();
  Motor_Speed_Set();
  
  PIT_FLAG_CLR(pit0);
}

void PIT_CH1_IRQHandler(void)
{
    PIT_FLAG_CLR(pit1);

    
}

void IRQ_IRQHandler(void)
{
    CLEAR_IRQ_FLAG;
    
}


void KBI0_IRQHandler(void)
{
    CLEAN_KBI0_FLAG;
    
}





/*
�жϺ������ƣ��������ö�Ӧ���ܵ��жϺ���
Sample usage:��ǰ���������ڶ�ʱ�� ͨ��0���ж�
void PIT_CH0_IRQHandler(void)
{
    ;
}
�ǵý����жϺ������־λ

FTMRE_IRQHandler      
PMC_IRQHandler        
IRQ_IRQHandler        
I2C0_IRQHandler       
I2C1_IRQHandler       
SPI0_IRQHandler       
SPI1_IRQHandler       
UART0_IRQHandler 
UART1_IRQHandler 
UART2_IRQHandler 
ADC0_IRQHandler       
ACMP0_IRQHandler      
FTM0_IRQHandler       
FTM1_IRQHandler       
FTM2_IRQHandler       
RTC_IRQHandler        
ACMP1_IRQHandler      
PIT_CH0_IRQHandler    
PIT_CH1_IRQHandler    
KBI0_IRQHandler       
KBI1_IRQHandler       
Reserved26_IRQHandler 
ICS_IRQHandler        
WDG_IRQHandler        
PWT_IRQHandler        
MSCAN_Rx_IRQHandler   
MSCAN_Tx_IRQHandler   
*/




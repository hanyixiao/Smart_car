#include "headfile.h"

//LED初始化
void WOL_LED_Init(uint8 led,uint8 state)
{
  if(led & LED1)
  {
    gpio_init(LED1_PORT,GPO,state);
  }
  if(led & LED2)
  { 
    gpio_init(LED2_PORT,GPO,state);
  }
  if(led & LED3)
  {
    gpio_init(LED3_PORT,GPO,state);
  }
  if(led & LED4)
  {
    gpio_init(LED4_PORT,GPO,state);
  }
}
//LED状态设置
void WOL_LED_Set(uint8 led,uint8 state)
{
  if(led & LED1)
  {
    gpio_set(LED1_PORT,state);
  }
  if(led & LED2)
  {
    gpio_set(LED2_PORT,state);
  }
  if(led & LED3)
  {
    gpio_set(LED3_PORT,state);
  }
  if(led & LED4)
  {
    gpio_set(LED4_PORT,state);
  }
}
//LED反转
void WOL_LED_Turn(uint8 led)
{
  if(led & LED1)
  {
    gpio_turn(LED1_PORT);
  }
  if(led & LED2)
  {
    gpio_turn(LED2_PORT);
  }
  if(led & LED3)
  {
    gpio_turn(LED3_PORT);
  }
  if(led & LED4)
  {
    gpio_turn(LED4_PORT);
  }
}

void PathTypeLEDSet()
{
  switch(PathType)
  {
  case 0:
    WOL_LED_Set(LED_ALL,LED_OFF);
    break;
  case 1:
    WOL_LED_Set(LED_ALL,LED_OFF);
    WOL_LED_Set(LED1,LED_ON);
    break;    
  case 2:
    WOL_LED_Set(LED_ALL,LED_OFF);
    WOL_LED_Set(LED2,LED_ON);
    break; 
  case 3:
    WOL_LED_Set(LED_ALL,LED_OFF);
    WOL_LED_Set(LED3,LED_ON);
    break;
  case 4:
    WOL_LED_Set(LED_ALL,LED_OFF);
    WOL_LED_Set(LED4,LED_ON);
    break;
  case 5:
    WOL_LED_Set(LED_ALL,LED_OFF);
    WOL_LED_Set(LED1,LED_ON);
    WOL_LED_Set(LED2,LED_ON);
    break;
  case 6:
    WOL_LED_Set(LED_ALL,LED_OFF);
    WOL_LED_Set(LED3,LED_ON);
    WOL_LED_Set(LED4,LED_ON);
    break; 
  case 15:
    WOL_LED_Set(LED_ALL,LED_ON);
    break; 
  default:
    break;
  }
}
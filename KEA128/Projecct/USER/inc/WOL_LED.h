#ifndef _WOL_LED_
#define _WOL_LED_

#include "headfile.h"

#define LED1 0x01 
#define LED2 0x02
#define LED3 0x04
#define LED4 0x08
#define LED_ALL 0x0F

#define LED1_PORT D3
#define LED2_PORT D2
#define LED3_PORT A3
#define LED4_PORT A2

#define LED_ON 0x00 
#define LED_OFF 0x0F

void WOL_LED_Init(uint8 led,uint8 state);
void WOL_LED_Set(uint8 led,uint8 state);
void WOL_LED_Turn(uint8 led);
void PathTypeLEDSet();

#endif //_WOL_LED_
#include "headfile.h"

void KEY_Init(KEYX_n key)
{
  if((key == LeftKey)||(key == AllKey))
  {
    gpio_init(LeftKeyPORT,GPI,1);
  }
  
  if((key == RightKey)||(key == AllKey))
  {
    gpio_init(RightKeyPORT,GPI,1);
  }
  
  if((key == CenterKey)||(key == AllKey))
  {
    gpio_init(CenterKeyPORT,GPI,1);
  }
  
  if((key == UpKey)||(key == AllKey))
  {
    gpio_init(UpKeyPORT,GPI,1);
  }
  
  if((key == DownKey)||(key == AllKey))
  {
    gpio_init(DownKeyPORT,GPI,1);
  }
}

KEYX_n Read_KEYMassage()
{
  while(1)
  {
    if(gpio_get(LeftKeyPORT) == 0)
    {
      DELAY_MS(1);
      if(gpio_get(LeftKeyPORT) == 0)
      {
        while(gpio_get(LeftKeyPORT) == 0);
        return LeftKey;
      }
    }
    if(gpio_get(RightKeyPORT) == 0)
    {
      DELAY_MS(1);
      if(gpio_get(RightKeyPORT) == 0)
      {
        while(gpio_get(RightKeyPORT) == 0);
        return RightKey;
      }
    }
    if(gpio_get(CenterKeyPORT) == 0)
    {
      DELAY_MS(1);
      if(gpio_get(CenterKeyPORT) == 0)
      {
        while(gpio_get(CenterKeyPORT) == 0);
        return CenterKey;
      }
    }
    if(gpio_get(UpKeyPORT) == 0)
    {
      DELAY_MS(1);
      if(gpio_get(UpKeyPORT) == 0)
      {
        while(gpio_get(UpKeyPORT) == 0);
        return UpKey;
      }
    }
    if(gpio_get(DownKeyPORT) == 0)
    {
      DELAY_MS(1);
      if(gpio_get(DownKeyPORT) == 0)
      {
        while(gpio_get(DownKeyPORT) == 0);
        return DownKey;
      }
    }
  }
}

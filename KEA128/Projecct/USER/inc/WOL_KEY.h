#ifndef _WOL_KEY_H_
#define _WOL_KEY_H_

#include "headfile.h"

typedef enum KEYType
{
  RightKey,
  CenterKey,
  LeftKey,
  UpKey,
  DownKey,
  AllKey
} KEYX_n;

#define RightKeyPORT F2
#define CenterKeyPORT E4
#define LeftKeyPORT A6
#define UpKeyPORT A7
#define DownKeyPORT F3

void KEY_Init(KEYX_n key);
KEYX_n Read_KEYMassage();

#endif //_WOL_KEY_H_
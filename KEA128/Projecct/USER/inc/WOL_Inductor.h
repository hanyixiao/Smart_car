#ifndef _WOL_INDUCTOR_H_
#define _WOL_INDUCTOR_H_

extern float gf_inductor_left;
extern float gf_inductor_right;
extern uint8 PathType;

extern uint8 Inductor_L[10];
extern uint8 Inductor_R[10];

void Inductor_Init();
void Inductor_get();
void Inductor_Error_Get();

#endif //_WOL_INDUCTOR_H_
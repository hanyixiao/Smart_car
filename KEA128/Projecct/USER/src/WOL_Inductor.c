#include "headfile.h"
#include "math.h"

uint8 Inductor_L[10] = {0};
uint8 Inductor_R[10] = {0};
uint8 Inductor_MM[10] = {0};
uint8 Inductor_ML[10] = {0};
uint8 Inductor_MR[10] = {0};

uint8 IslandFlag = 0;
uint8 IslandInFlag = 0;
uint8 risingcount=0; 
uint8 ringflag=0;
uint8 fallingflag=0;
float gf_inductor_left = 0;
float gf_inductor_right = 0;
float gf_inductor_middle = 0;
float gf_inductor_leftm = 0;
float gf_inductor_rightm = 0;
float DistanceIsland = 0;
float DistanceInIsland = 0;
float Turn_M = 0;
float Turn_H = 0;
float IslandDistance = 0;
uint8 PathType = 0;
uint16 PathCount = 0;
float SlopeDistance = 0;
uint8 SlopeCount = 0;

extern float Speed_100ms_Addtion;

void Inductor_Init()
{
  adc_init(ADC0_SE6);
  adc_init(ADC0_SE7);
  adc_init(ADC0_SE12);
  adc_init(ADC0_SE13);
  adc_init(ADC0_SE14);
}

void Inductor_get()
{
  uint8 i;
  for(i = 9;i > 0;i--)
  {
    Inductor_L[i]=Inductor_L[i-1];
    Inductor_R[i]=Inductor_R[i-1];
    Inductor_MM[i]=Inductor_ML[i-1];
    Inductor_ML[i]=Inductor_ML[i-1];
    Inductor_MR[i]=Inductor_MR[i-1];
  }
  Inductor_L[0]=adc_once(ADC0_SE6,ADC_8bit);
  Inductor_ML[0]=adc_once(ADC0_SE7,ADC_8bit);
  Inductor_MM[0]=adc_once(ADC0_SE12,ADC_8bit);
  Inductor_MR[0]=adc_once(ADC0_SE13,ADC_8bit);
  Inductor_R[0]=adc_once(ADC0_SE14,ADC_8bit);

  if(Inductor_L[0]<=1.0) Inductor_L[0]=1.0;
  if(Inductor_R[0]<=1.0) Inductor_R[0]=1.0;
  if(Inductor_MM[0]<=1.0) Inductor_ML[0]=1.0;
  if(Inductor_ML[0]<=1.0) Inductor_ML[0]=1.0;
  if(Inductor_MR[0]<=1.0) Inductor_MR[0]=1.0;

//  if(Inductor_ML[0]-Inductor_ML[1]>50) Inductor_ML[0]=Inductor_ML[1]+50;
//  if(Inductor_ML[0]-Inductor_ML[1]<-50) Inductor_ML[0]=Inductor_ML[1]-50;
//  if(Inductor_MR[0]-Inductor_MR[1]>50) Inductor_MR[0]=Inductor_MR[1]+50;
//  if(Inductor_MR[0]-Inductor_MR[1]<-50) Inductor_MR[0]=Inductor_MR[1]-50;
  

}

void Inductor_Error_Get()
{
  uint8 i = 0;
  for(i=0;i<10;i++)
  {
    Inductor_get();
  }
  gf_inductor_left = 0;
  gf_inductor_right = 0;
  gf_inductor_leftm = 0;
  gf_inductor_rightm = 0;
  gf_inductor_middle = 0;
  for(i = 0;i < 10;i++)
  {
    gf_inductor_left +=(Inductor_L[i]*0.1);
    gf_inductor_right +=(Inductor_R[i]*0.1);   
    gf_inductor_leftm +=(Inductor_ML[i]*0.1);
    gf_inductor_rightm +=(Inductor_MR[i]*0.1); 
    gf_inductor_middle += (Inductor_MM[i]*0.1);
  }
  
  TurnErrorLast = TurnError; 
  
  Turn_H = 200*(gf_inductor_left - gf_inductor_right)/(gf_inductor_left + gf_inductor_right + gf_inductor_middle);
  Turn_M = 200*(gf_inductor_rightm - gf_inductor_leftm)/(gf_inductor_rightm + gf_inductor_leftm+gf_inductor_middle);
  Turn_M = limit(Turn_M,100);
  
  if((gf_inductor_left + gf_inductor_right < 240) && gf_inductor_middle > 60)
  {
    SlopeCount++;
  }
  else
  {
    SlopeCount = 0;
    if(PathType == 15 && Distance > SlopeDistance)
    {
      PathType = 0;
    }
  }
  
  if(SlopeCount >= 5)
  {
    SlopeCount = 5;
    PathType = 15;
    SlopeDistance = Distance + 1.0;
  }
  
  if(PathType == 0)
  {
    TurnError = Turn_H;
    if((gf_inductor_left > 130) && (gf_inductor_right > 130) && (gf_inductor_left + gf_inductor_right > 320))
    {
      PathCount++;
    }
    else 
    {
      PathCount = 0;
    }
    if(PathCount >= 15)
    {
      PathCount = 15;
      PathType++;
    }
  }
  if(PathType == 1)
  {
    if(myabs((int)(gf_inductor_rightm - gf_inductor_leftm)) < 50)
    {
      PathCount++;
    }
    else
    {
      PathCount = 15;
    }
    if(PathCount >= 20)
    {
      PathCount = 20;
      PathType++;
    }     
  }
  if(PathType==2)
  {
     if(myabs((int)(gf_inductor_rightm - gf_inductor_leftm)) > 50)
    {
      PathCount++;
    }
    else
    {
      PathCount = 20;
    }
    if(PathCount >= 30)
    {
      PathCount = 30;
      IslandDistance = Distance +1.0; 
      PathType++;
    }     
  }
  if(PathType == 3)
  {
    TurnError = Turn_M;
    /*if(Turn_M < -50)
    {
      if(Turn_H > 50)
      {
        TurnError += 2*Turn_H;
      }
    }
    else if(Turn_M > 50)
    {
      if(Turn_H < -50)
      {
        TurnError += 2*Turn_H;
      }
    }*/
    if((gf_inductor_left <180) || (gf_inductor_right < 180) || (gf_inductor_left + gf_inductor_right < 320))
    {
      TurnError += Turn_H;
      TurnError = limit(TurnError,100);
    }
    if(Distance > IslandDistance)
    {
      PathCount = 30;
      PathType++;
    }
  }
  if(PathType == 4)
  {
 
     if((gf_inductor_left > 130) && (gf_inductor_right > 130) && (gf_inductor_left + gf_inductor_right > 320))
    {
      PathCount++;
    }
    else 
    {
      PathCount = 30;
    }
    if(PathCount>=40)
    {
      PathType++;
      
    }
  }
   if(PathType == 5)
  {
   if(myabs((int)(gf_inductor_rightm - gf_inductor_leftm)) < 50)
   {
     PathCount++;
   }
    else 
   {
      PathCount = 40;
   }
   if(PathCount>=50)
    {
      PathType++;
      IslandDistance = Distance +0.8; 
    }
  }
  if(PathType == 6)
  {
   if(gf_inductor_rightm - gf_inductor_leftm>0)
   {
   TurnError=(0.5*Turn_H-0.5*Turn_M);
   }
   else
   {
     TurnError=(0.5*Turn_H-0.5*Turn_M);
   }
   TurnError=limit(Turn_H,50);
   if(Distance>IslandDistance)
    {
      PathType =0;
      PathCount =0;
    }
  }
  if(PathType != 3&&PathType !=6)
  {
   TurnError=Turn_H;  
   TurnError=limit(TurnError,150);
  }
  TurnError=TurnError*0.7+ TurnErrorLast*0.3;
 
#if Watch_Ware == ADC_Ware
    OutData[0]=gf_inductor_left;
    OutData[1]=gf_inductor_right;
    OutData[2]=gf_inductor_leftm;
    OutData[3]=gf_inductor_rightm; 
    OutData[4]=gf_inductor_middle;
    OutData[5]=TurnError;
#endif

}
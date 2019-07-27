#include "headfile.h"
#include "WOL_fuzzy.h"
/********��С���˷�����б��************/
int sumX=0,sumY=0,avrX=0,avrY=0;
int num=0,B_up1=0,B_up2=0,B_up=0,B_down=0;

float regression(int startline,int endline,float X[10]) //��С���˷����㺯�� ע�����鷶Χ
{
    float slope=0;//б��
    int num,i;
    sumX=0;sumY=0;avrX=0;avrY=0 ;
    num=0;B_up1=0;B_up2=0;
    for(i=startline;i<=endline;i++)
    {
         if(X[i]) 
         {
            num++;
            sumX+=i;
            sumY+=X[i];
         }
    }
    avrX=sumX/num;
    avrY=sumY/num;
    B_up=0;
    B_down=0;
    for(i=startline;i<=endline;i++)
    {
	         if(X[i]) 
	         { 
	            B_up1=(int)X[i]-(int)avrY;
	            B_up2=i-avrX;
	            B_up+=(int)B_up1*(int)B_up2;
	            //B_up=B_up/100*100;
	            B_down+=(int)(i-avrX)*(int)(i-avrX);
	         }
   }
   if(B_down==0) slope=0;
   else slope=B_up*10/B_down;
   
   return slope;
}
float Fuzzy(float P,float D)
{
/*������P����ֵ������*/
//float PFF[7]={-24,-12,-6,0,6,12,24};
float PFF[7]={-180,-120,-50,0,50,120,180};  
/*������D����ֵ������*/
//float DFF[5]={-6.5,-3,0,3,6.5};
float DFF[5]={-15,-10,5,10,15};
/*�����U����ֵ������(������������ѡ��ͬ�����ֵ)*/
float UFF[7]={0,15,30,45,60,75,90};

int rule[7][5]={
//  -2  -1   0   1   2 ec    e

 
// -2  -1   0   1   2 ec    e

//  { 5,  4,  3,  1,  1}, //  -3      ģ�������Ϊ   ec\e -450 -300 -150 0 150 300 450
//  { 4,  3,  2,  1,  0}, //  -2                     -15|     
//  { 3,  2,  1,  0,  0}, //  -1                     -10|         
 // { 2,  1,  0,  1,  2}, //   0                      5
//  { 0,  0,  1,  2,  3}, //   1                      10
//  { 0,  1,  2,  3,  4}, //   2                      15     
//  { 1,  2,  3,  4,  5}  //   3
//// -2  -1   0   1   2 ec 
//  { 6,  3,  1,  3,  6}, //  -3
//  { 4,  4,  1,  4,  4}, //  -2
//  { 6,  5,  5,  5,  6}, //  -1
//  { 6,  6,  0,  6,  6}, //   0
//  { 6,  5,  5,  5,  6}, //   1
//  { 4,  4,  1,  4,  4}, //   2
//  { 6,  3,  1,  3,  6}  //   3
  
 

  { 1,  1,  1,  0,  0}, 
  { 4,  2,  1,  0,  0}, 
  { 6,  4,  1,  1,  0}, 
  { 3,  3,  0,  3,  3}, 
  { 0,  1,  1,  4,  6}, 
  { 0,  0,  1,  2,  4},
  { 0,  0,  1,  1,  1} 
  
};

//


float U=0;  /*ƫ��,ƫ��΢���Լ����ֵ�ľ�ȷ��*/
float PF[2]={0},DF[2]={0},UF[4]={0};
 /*ƫ��,ƫ��΢���Լ����ֵ��������*/
int Pn=0,Dn=0,Un[4]={0};
float t1=0,t2=0,t3=0,t4=0,temp1=0,temp2=0;
/*�����ȵ�ȷ��*/
/*����PD��ָ������ֵ�����Ч������*/
 if(P>PFF[0] && P<PFF[6])
{
 if(P<=PFF[1])
 {
  Pn=-2;
  PF[0]=(PFF[1]-P)/(PFF[1]-PFF[0]);
 }
 else if(P<=PFF[2])
 {
  Pn=-1;
  PF[0]=(PFF[2]-P)/(PFF[2]-PFF[1]);
 }
 else if(P<=PFF[3])
 {
  Pn=0;
  PF[0]=(PFF[3]-P)/(PFF[3]-PFF[2]);
 }
 else if(P<=PFF[4])
 {
  Pn=1;
  PF[0]=(PFF[4]-P)/(PFF[4]-PFF[3]);
 }
 else if(P<=PFF[5])
 {
  Pn=2;
  PF[0]=(PFF[5]-P)/(PFF[5]-PFF[4]);
 }
 else if(P<=PFF[6])
 {
  Pn=3;
  PF[0]=(PFF[6]-P)/(PFF[6]-PFF[5]);
 }
}

 else if(P<=PFF[0])
 {
  Pn=-2;
  PF[0]=1;
 }
 else if(P>=PFF[6])
 {
  Pn=3;
  PF[0]=0;
 }

PF[1]=1-PF[0];


//�ж�D��������
 if(D>DFF[0]&&D<DFF[4])
 {
  if(D<=DFF[1])
  {
   Dn=-2;
   DF[0]=(DFF[1]-D)/(DFF[1]-DFF[0]);
  }
 else if(D<=DFF[2])
 {
  Dn=-1;
  DF[0]=(DFF[2]-D)/(DFF[2]-DFF[1]);
  }
 else if(D<=DFF[3])
 {
  Dn=0;
  DF[0]=(DFF[3]-D)/(DFF[3]-DFF[2]);
  }
 else if(D<=DFF[4])
 {
  Dn=1;
  DF[0]=(DFF[4]-D)/(DFF[4]-DFF[3]);
 }
 }
 //���ڸ�����������
 else if (D<=DFF[0])
 {
  Dn=-2;
  DF[0]=1;
 }
 else if(D>=DFF[4])
 {
  Dn=1;
  DF[0]=0;
 }

DF[1]=1-DF[0];

 /*ʹ����Χ�Ż���Ĺ����rule[7][7]*/
 /*���ֵʹ��13����������,����ֵ��UFF[7]ָ��*/
 /*һ�㶼���ĸ�������Ч*/

//���ڹ����ǽ������ŵ�
Un[0]=rule[Pn-1+3][Dn-1+3];
Un[1]=rule[Pn+3][Dn-1+3];
Un[2]=rule[Pn-1+3][Dn+3];
Un[3]=rule[Pn+3][Dn+3];



//���Ӧ�õ�ֵģ������ö�Ӧ�������������
 if(PF[0]<=DF[0])    //��С ����U�������ȣ�
  UF[0]=PF[0];
 else
  UF[0]=DF[0];
 if(PF[1]<=DF[0])
  UF[1]=PF[1];
 else
  UF[1]=DF[0];
 if(PF[0]<=DF[1])
  UF[2]=PF[0];
 else
  UF[2]=DF[1];
 if(PF[1]<=DF[1])
  UF[3]=PF[1];
 else
  UF[3]=DF[1];
 
 
/*ͬ���������������ֵ���*/
 if(Un[0]==Un[1])      //����ȵ�����ֵ�������Ƚ��д���
 {
  if(UF[0]>UF[1])
  UF[1]=0;
  else
  UF[0]=0;
 }
 if(Un[0]==Un[2])
 {
  if(UF[0]>UF[2])
  UF[2]=0;
  else
  UF[0]=0;
 }
 if(Un[0]==Un[3])
 {
  if(UF[0]>UF[3])
  UF[3]=0;
  else
  UF[0]=0;
 }
 if(Un[1]==Un[2])
 {
  if(UF[1]>UF[2])
  UF[2]=0;
  else
  UF[1]=0;
 }
 if(Un[1]==Un[3])
 {
  if(UF[1]>UF[3])
  UF[3]=0;
  else
  UF[1]=0;
 }
 if(Un[2]==Un[3])
 {
  if(UF[2]>UF[3])
  UF[3]=0;
  else
  UF[2]=0;
 }




 t1=UF[0]*UFF[Un[0]];
 t2=UF[1]*UFF[Un[1]];
 t3=UF[2]*UFF[Un[2]];
 t4=UF[3]*UFF[Un[3]];
 
 temp1=t1+t2+t3+t4;
 temp2=UF[0]+UF[1]+UF[2]+UF[3];//ģ�������
 U=temp1/temp2;
 return U;
}


/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		MPU6050
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 * @note	
					接线定义
					------------------------------------ 
						SCL                 查看SEEKFREE_IIC文件内的SEEKFREE_SCL宏定义
						SDA                 查看SEEKFREE_IIC文件内的SEEKFREE_SDA宏定义
					------------------------------------ 
 ********************************************************************************************************************/



#include "SEEKFREE_MPU6050.h"

int16 MPU_Gyro_X,MPU_Gyro_Y;
int16 MPU_Acc_Z;



//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化MPU6050
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void InitMPU6050(void)
{
    simiic_write_reg(MPU6050_DEV_ADDR, PWR_MGMT_1, 0x00);	   //解除休眠状态
    simiic_write_reg(MPU6050_DEV_ADDR, SMPLRT_DIV, 0x04);      //125HZ采样率
    simiic_write_reg(MPU6050_DEV_ADDR, CONFIG, 0x00);          //
    simiic_write_reg(MPU6050_DEV_ADDR, GYRO_CONFIG, 0x18);     //2000
    simiic_write_reg(MPU6050_DEV_ADDR, ACCEL_CONFIG, 0x10);    //8g
    simiic_write_reg(MPU6050_DEV_ADDR, User_Control, 0x00);
    simiic_write_reg(MPU6050_DEV_ADDR, INT_PIN_CFG, 0x02);
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取MPU6050加速度计数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void Get_AccData(void)
{
    uint8 dat[2];
    
    simiic_read_regs(MPU6050_DEV_ADDR, ACCEL_ZOUT_H, dat, 2, IIC);  
    MPU_Acc_Z = (int16)(((uint16)dat[0]<<8 | dat[1]));
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取MPU6050陀螺仪数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void Get_Gyro(void)
{
    uint8 dat[6];
    
    simiic_read_regs(MPU6050_DEV_ADDR, GYRO_XOUT_H, dat, 4, IIC);  
    MPU_Gyro_X = (int16)(((uint16)dat[0]<<8 | dat[1]));
    MPU_Gyro_Y = (int16)(((uint16)dat[2]<<8 | dat[3]));
}

//-------------以下程序光之翼-周浩男修改添加-----------------
int16 MPU6050_ACCEL_X_data() 
{
  int8 DATA_H,DATA_L;
  DATA_H = simiic_read_reg(MPU6050_DEV_ADDR,ACCEL_XOUT_H,IIC);
  DATA_L = simiic_read_reg(MPU6050_DEV_ADDR,ACCEL_XOUT_L,IIC);
  return (DATA_H<<8)+DATA_L; 
}

int16 MPU6050_ACCEL_Y_data() 
{
  int8 DATA_H,DATA_L;
  DATA_H = simiic_read_reg(MPU6050_DEV_ADDR,ACCEL_YOUT_H,IIC);
  DATA_L = simiic_read_reg(MPU6050_DEV_ADDR,ACCEL_YOUT_L,IIC);
  return (DATA_H<<8)+DATA_L; 
}

int16 MPU6050_ACCEL_Z_data() 
{
  int8 DATA_H,DATA_L;
  DATA_H = simiic_read_reg(MPU6050_DEV_ADDR,ACCEL_ZOUT_H,IIC);
  DATA_L = simiic_read_reg(MPU6050_DEV_ADDR,ACCEL_ZOUT_L,IIC);
  return (DATA_H<<8)+DATA_L; 
}

int16 MPU6050_GYRO_X_data() 
{
  int8 DATA_H,DATA_L;
  DATA_H = simiic_read_reg(MPU6050_DEV_ADDR,GYRO_XOUT_H,IIC);
  DATA_L = simiic_read_reg(MPU6050_DEV_ADDR,GYRO_XOUT_L,IIC);
  return (DATA_H<<8)+DATA_L; 
}

int16 MPU6050_GYRO_Y_data() 
{
  int8 DATA_H,DATA_L;
  DATA_H = simiic_read_reg(MPU6050_DEV_ADDR,GYRO_YOUT_H,IIC);
  DATA_L = simiic_read_reg(MPU6050_DEV_ADDR,GYRO_YOUT_L,IIC);
  return (DATA_H<<8)+DATA_L; 
}

int16 MPU6050_GYRO_Z_data() 
{
  int8 DATA_H,DATA_L;
  DATA_H = simiic_read_reg(MPU6050_DEV_ADDR,GYRO_ZOUT_H,IIC);
  DATA_L = simiic_read_reg(MPU6050_DEV_ADDR,GYRO_ZOUT_L,IIC);
  return (DATA_H<<8)+DATA_L; 
}

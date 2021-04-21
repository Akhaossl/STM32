#ifndef __KINEMATICS_MECANUM_H
#define __KINEMATICS_MECANUM_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define WHEEL_CIRCUMFERENCE 0.307876f//轮子周长 m
#define LR_WHEELS_DISTANCE 0.198f//左右轮距 m
#define FR_WHEELS_DISTANCE 0.15f//前后轮距 m

typedef struct
{
	__IO float Linear_X;	//X轴线速度 m/s
	__IO float Linear_Y;	//Y轴线速度 m/s
	__IO float Angular_Z;	//Z轴角速度 rad/s	
	__IO float M1_RPM;	  //M1电机转速 rpm
	__IO float M2_RPM;	  //M2电机转速 rpm
	__IO float M3_RPM;	  //M3电机转速 rpm
	__IO float M4_RPM;	  //M4电机转速 rpm
}Kinematics_Struct;//车体运动学结构体参数

void Kinematics_Mecanum_CalculateRPM(Kinematics_Struct *Kinematics);//麦克纳姆轮运动学逆解函数
void Kinematics_Mecanum_GetVelocities(Kinematics_Struct *Kinematics);//麦克纳姆轮运动学正解函数	

#ifdef __cplusplus
}
#endif

#endif

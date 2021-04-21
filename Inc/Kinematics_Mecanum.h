#ifndef __KINEMATICS_MECANUM_H
#define __KINEMATICS_MECANUM_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define WHEEL_CIRCUMFERENCE 0.307876f//�����ܳ� m
#define LR_WHEELS_DISTANCE 0.198f//�����־� m
#define FR_WHEELS_DISTANCE 0.15f//ǰ���־� m

typedef struct
{
	__IO float Linear_X;	//X�����ٶ� m/s
	__IO float Linear_Y;	//Y�����ٶ� m/s
	__IO float Angular_Z;	//Z����ٶ� rad/s	
	__IO float M1_RPM;	  //M1���ת�� rpm
	__IO float M2_RPM;	  //M2���ת�� rpm
	__IO float M3_RPM;	  //M3���ת�� rpm
	__IO float M4_RPM;	  //M4���ת�� rpm
}Kinematics_Struct;//�����˶�ѧ�ṹ�����

void Kinematics_Mecanum_CalculateRPM(Kinematics_Struct *Kinematics);//�����ķ���˶�ѧ��⺯��
void Kinematics_Mecanum_GetVelocities(Kinematics_Struct *Kinematics);//�����ķ���˶�ѧ���⺯��	

#ifdef __cplusplus
}
#endif

#endif

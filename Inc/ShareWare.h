#ifndef __SHAREWARE_H
#define __SHAREWARE_H
#include "main.h"
#include <stdarg.h>
#include <math.h>
#include "adc1.h"
#include "uart.h"
#include "tim2.h"
#include "tim3.h"
#include "tim4.h"
#include "tim5.h"
#include "tim8.h"
#include "delayus.h"
#include "MotorControl.h"
#include "RC.h"
#include "Encoder.h"
#include "pid.h"
#include "VelocityControl.h"
#include "Kinematics_Mecanum.h"
#include "LowPassFilter.h"
#include "BatteryInfor.h"
#include "RingBuff.h"
#include "DataProtocol.h"
#include "DataCom.h"
#include "IndicatorDevice.h"
#include "i2c.h"
#include "mpu6050.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define Constrain(AMT, MIN, MAX) ((AMT) < (MIN)? (MIN):( (AMT) > (MAX)?(MAX):(AMT) ))//Լ������

union floatHex_union
{
	uint8_t Hex[4];
	float floatValue;
};

extern DataCom_RX_Struct DataCom_RX;//��������Э��ṹ�����

extern LPF_Struct LPF_Linear_X;//������ͨ�˲�����X�����ٶȽṹ�����
extern LPF_Struct LPF_Linear_Y;//������ͨ�˲�����Y�����ٶȽṹ�����
extern LPF_Struct LPF_Angular_Z;//������ͨ�˲�����Z����ٶȽṹ�����

extern LPF_Struct LPF_SupplyVoltage;//������ͨ�˲���Դ��ѹֵ�ṹ�����
extern Battery_Struct Battery;//���״̬��Ϣ�ṹ�����

extern RC_Struct RC;//����RCң�����ṹ�����

extern IncPID_Struct PID_M1;//����M1���PID�ṹ�����
extern IncPID_Struct PID_M2;//����M2���PID�ṹ�����
extern IncPID_Struct PID_M3;//����M3���PID�ṹ�����
extern IncPID_Struct PID_M4;//����M4���PID�ṹ�����

extern Encoder_Struct Encoder_M1;//����M1�������ṹ�����
extern Encoder_Struct Encoder_M2;//����M2�������ṹ�����
extern Encoder_Struct Encoder_M3;//����M3�������ṹ�����
extern Encoder_Struct Encoder_M4;//����M4�������ṹ�����

extern VelControl_Struct VelControl;//�������ת�ٿ��ƽṹ�����

extern Kinematics_Struct Kinematics_Inverse;//���������˶�ѧ���ṹ�����
extern Kinematics_Struct Kinematics_Forward;//���������˶�ѧ����ṹ�����

extern RingBuf_Struct RingBuff_Mast;//����һ��ringBuff�Ļ��λ���������
extern ParseData_Struct ParseData_Mast;//����һ��ringBuff�Ļ��λ������ṹ�����

extern MPU6050_Struct MPU6050;//����MPU6050�ṹ�����

extern union floatHex_union floatHex;


#ifdef __cplusplus
}
#endif

#endif

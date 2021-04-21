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

#define Constrain(AMT, MIN, MAX) ((AMT) < (MIN)? (MIN):( (AMT) > (MAX)?(MAX):(AMT) ))//约束函数

union floatHex_union
{
	uint8_t Hex[4];
	float floatValue;
};

extern DataCom_RX_Struct DataCom_RX;//创建数据协议结构体参数

extern LPF_Struct LPF_Linear_X;//创建低通滤波车体X轴线速度结构体参数
extern LPF_Struct LPF_Linear_Y;//创建低通滤波车体Y轴线速度结构体参数
extern LPF_Struct LPF_Angular_Z;//创建低通滤波车体Z轴角速度结构体参数

extern LPF_Struct LPF_SupplyVoltage;//创建低通滤波电源电压值结构体参数
extern Battery_Struct Battery;//电池状态信息结构体参数

extern RC_Struct RC;//创建RC遥控器结构体参数

extern IncPID_Struct PID_M1;//创建M1电机PID结构体参数
extern IncPID_Struct PID_M2;//创建M2电机PID结构体参数
extern IncPID_Struct PID_M3;//创建M3电机PID结构体参数
extern IncPID_Struct PID_M4;//创建M4电机PID结构体参数

extern Encoder_Struct Encoder_M1;//创建M1编码器结构体参数
extern Encoder_Struct Encoder_M2;//创建M2编码器结构体参数
extern Encoder_Struct Encoder_M3;//创建M3编码器结构体参数
extern Encoder_Struct Encoder_M4;//创建M4编码器结构体参数

extern VelControl_Struct VelControl;//创建电机转速控制结构体参数

extern Kinematics_Struct Kinematics_Inverse;//创建车体运动学逆解结构体参数
extern Kinematics_Struct Kinematics_Forward;//创建车体运动学正解结构体参数

extern RingBuf_Struct RingBuff_Mast;//创建一个ringBuff的环形缓冲区参数
extern ParseData_Struct ParseData_Mast;//创建一个ringBuff的环形缓冲区结构体参数

extern MPU6050_Struct MPU6050;//创建MPU6050结构体参数

extern union floatHex_union floatHex;


#ifdef __cplusplus
}
#endif

#endif

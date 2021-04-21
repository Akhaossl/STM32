#include "ShareWare.h"

DataCom_RX_Struct DataCom_RX;//创建数据协议结构体参数

LPF_Struct LPF_Linear_X;//创建低通滤波车体X轴线速度结构体参数
LPF_Struct LPF_Linear_Y;//创建低通滤波车体Y轴线速度结构体参数
LPF_Struct LPF_Angular_Z;//创建低通滤波车体Z轴角速度结构体参数

Battery_Struct Battery;//电池状态信息结构体参数
LPF_Struct LPF_SupplyVoltage;//创建低通滤波电源电压值结构体参数

RC_Struct RC;//创建RC遥控器结构体参数

IncPID_Struct PID_M1;//创建M1电机PID结构体参数
IncPID_Struct PID_M2;//创建M2电机PID结构体参数
IncPID_Struct PID_M3;//创建M3电机PID结构体参数
IncPID_Struct PID_M4;//创建M4电机PID结构体参数

Encoder_Struct Encoder_M1;//创建M1编码器结构体参数
Encoder_Struct Encoder_M2;//创建M2编码器结构体参数
Encoder_Struct Encoder_M3;//创建M3编码器结构体参数
Encoder_Struct Encoder_M4;//创建M4编码器结构体参数

VelControl_Struct VelControl;//创建电机转速控制结构体参数

Kinematics_Struct Kinematics_Inverse;//创建车体运动学逆解结构体参数
Kinematics_Struct Kinematics_Forward;//创建车体运动学正解结构体参数

RingBuf_Struct RingBuff_Mast;//创建一个RingBuff的环形缓冲区结构体参数
ParseData_Struct ParseData_Mast;//创建一个解析数据结构体参数

MPU6050_Struct MPU6050;//创建MPU6050结构体参数

union floatHex_union floatHex;


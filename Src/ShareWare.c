#include "ShareWare.h"

DataCom_RX_Struct DataCom_RX;//��������Э��ṹ�����

LPF_Struct LPF_Linear_X;//������ͨ�˲�����X�����ٶȽṹ�����
LPF_Struct LPF_Linear_Y;//������ͨ�˲�����Y�����ٶȽṹ�����
LPF_Struct LPF_Angular_Z;//������ͨ�˲�����Z����ٶȽṹ�����

Battery_Struct Battery;//���״̬��Ϣ�ṹ�����
LPF_Struct LPF_SupplyVoltage;//������ͨ�˲���Դ��ѹֵ�ṹ�����

RC_Struct RC;//����RCң�����ṹ�����

IncPID_Struct PID_M1;//����M1���PID�ṹ�����
IncPID_Struct PID_M2;//����M2���PID�ṹ�����
IncPID_Struct PID_M3;//����M3���PID�ṹ�����
IncPID_Struct PID_M4;//����M4���PID�ṹ�����

Encoder_Struct Encoder_M1;//����M1�������ṹ�����
Encoder_Struct Encoder_M2;//����M2�������ṹ�����
Encoder_Struct Encoder_M3;//����M3�������ṹ�����
Encoder_Struct Encoder_M4;//����M4�������ṹ�����

VelControl_Struct VelControl;//�������ת�ٿ��ƽṹ�����

Kinematics_Struct Kinematics_Inverse;//���������˶�ѧ���ṹ�����
Kinematics_Struct Kinematics_Forward;//���������˶�ѧ����ṹ�����

RingBuf_Struct RingBuff_Mast;//����һ��RingBuff�Ļ��λ������ṹ�����
ParseData_Struct ParseData_Mast;//����һ���������ݽṹ�����

MPU6050_Struct MPU6050;//����MPU6050�ṹ�����

union floatHex_union floatHex;


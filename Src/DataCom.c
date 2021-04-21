/**************************************************************************
文件版本：神炽焰 V1.0
文件功能：
1、设置与反馈车体目标速度
2、反馈车体实时速度
3、反馈电源管理信息
4、反馈车体IMU信息
**************************************************************************/
#include "DataCom.h"
#include "ShareWare.h"

/*-----------------------------------------------------------
函数功能: 数据接收接口
输入参数: 数据数组地址
返 回 值: None
说    明: 将解析出的数据帧传入该函数实现数值更新
 -----------------------------------------------------------*/
void DataCom_RX_Function(DataCom_RX_Struct *DataCom_RX, uint8_t *Buff)
{
	switch(Buff[3])
	{
		case 1://设置与反馈车体目标速度
		{
			for(uint8_t i=0; i<4; i++) floatHex.Hex[3-i] =  Buff[4+i];
			DataCom_RX->Linear_X = floatHex.floatValue;//车体X轴目标线速度值 m/s
			
			for(uint8_t i=0; i<4; i++) floatHex.Hex[3-i] =  Buff[8+i];
			DataCom_RX->Linear_Y = floatHex.floatValue;//车体Y轴目标线速度值 m/s
			
			for(uint8_t i=0; i<4; i++) floatHex.Hex[3-i] =  Buff[12+i];
			DataCom_RX->Angular_Z = floatHex.floatValue;//车体Z轴目标角速度值 rad/s
			
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 1;
			Usart2_TX_Buf[3] = 1;
			
			uint8_t SumCheck=0;//校验和
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//计算校验和
			
			Usart2_TX_Buf[4] = SumCheck;//校验和
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//串口DMA发送指令
		}break;
		
		case 2://反馈车体实时速度
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 13;
			Usart2_TX_Buf[3] = 2;
			
			floatHex.floatValue = Kinematics_Forward.Linear_X;//车体当前X轴线速度 m/s
			Usart2_TX_Buf[4] = floatHex.Hex[3];
			Usart2_TX_Buf[5] = floatHex.Hex[2];
			Usart2_TX_Buf[6] = floatHex.Hex[1];
			Usart2_TX_Buf[7] = floatHex.Hex[0];
			
			floatHex.floatValue = Kinematics_Forward.Linear_Y;//车体当前Y轴线速度 m/s
			Usart2_TX_Buf[8] = floatHex.Hex[3];
			Usart2_TX_Buf[9] = floatHex.Hex[2];
			Usart2_TX_Buf[10] = floatHex.Hex[1];
			Usart2_TX_Buf[11] = floatHex.Hex[0];
			
			floatHex.floatValue = Kinematics_Forward.Angular_Z;//车体当前Z轴角速度 rad/s
			Usart2_TX_Buf[12] = floatHex.Hex[3];
			Usart2_TX_Buf[13] = floatHex.Hex[2];
			Usart2_TX_Buf[14] = floatHex.Hex[1];
			Usart2_TX_Buf[15] = floatHex.Hex[0];
			
			uint8_t SumCheck=0;//校验和
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//计算校验和
			
			Usart2_TX_Buf[16] = SumCheck;//校验和
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//串口DMA发送指令
		}break;
		
		case 3://反馈电源管理信息
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 4;
			Usart2_TX_Buf[3] = 3;
			
			uint16_t Voltage = Battery.Voltage * 1000;//电池电压值 mv
			Usart2_TX_Buf[4]= Voltage >> 8;
			Usart2_TX_Buf[5]= Voltage & 0xFF;
	
			Usart2_TX_Buf[6]= Battery.Capacity;//电池电量值 %
			
			uint8_t SumCheck=0;//校验和
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//计算校验和
			
			Usart2_TX_Buf[7] = SumCheck;//校验和
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//串口DMA发送指令
		}break;
		
		case 4://反馈车体IMU信息
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 25;
			Usart2_TX_Buf[3] = 4;
			
			floatHex.floatValue = MPU6050.Accel_X;//加速度计X轴数值 m/s^2
			Usart2_TX_Buf[4] = floatHex.Hex[3];
			Usart2_TX_Buf[5] = floatHex.Hex[2];
			Usart2_TX_Buf[6] = floatHex.Hex[1];
			Usart2_TX_Buf[7] = floatHex.Hex[0];
			
			floatHex.floatValue = MPU6050.Accel_Y;//加速度计Y轴数值 m/s^2
			Usart2_TX_Buf[8] = floatHex.Hex[3];
			Usart2_TX_Buf[9] = floatHex.Hex[2];
			Usart2_TX_Buf[10] = floatHex.Hex[1];
			Usart2_TX_Buf[11] = floatHex.Hex[0];
			
			floatHex.floatValue = MPU6050.Accel_Z;//加速度计Z轴数值 m/s^2
			Usart2_TX_Buf[12]= floatHex.Hex[3];
			Usart2_TX_Buf[13]= floatHex.Hex[2];
			Usart2_TX_Buf[14]= floatHex.Hex[1];
			Usart2_TX_Buf[15]= floatHex.Hex[0];
			
			floatHex.floatValue = MPU6050.Gyro_X;//角速度X轴数值 rad/s
			Usart2_TX_Buf[16]= floatHex.Hex[3];
			Usart2_TX_Buf[17]= floatHex.Hex[2];
			Usart2_TX_Buf[18]= floatHex.Hex[1];
			Usart2_TX_Buf[19]= floatHex.Hex[0];
			
			floatHex.floatValue = MPU6050.Gyro_Y;//角速度Y轴数值 rad/s
			Usart2_TX_Buf[20]= floatHex.Hex[3];
			Usart2_TX_Buf[21]= floatHex.Hex[2];
			Usart2_TX_Buf[22]= floatHex.Hex[1];
			Usart2_TX_Buf[23]= floatHex.Hex[0];
			
			floatHex.floatValue = MPU6050.Gyro_Z;//角速度Z轴数值 rad/s
			Usart2_TX_Buf[24]= floatHex.Hex[3];
			Usart2_TX_Buf[25]= floatHex.Hex[2];
			Usart2_TX_Buf[26]= floatHex.Hex[1];
			Usart2_TX_Buf[27]= floatHex.Hex[0];
			
			uint8_t SumCheck=0;//校验和
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//计算校验和
			
			Usart2_TX_Buf[28] = SumCheck;//校验和
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//串口DMA发送指令
		}break;
		
		default:break;
	}

}

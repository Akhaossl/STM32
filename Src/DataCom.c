/**************************************************************************
�ļ��汾������� V1.0
�ļ����ܣ�
1�������뷴������Ŀ���ٶ�
2����������ʵʱ�ٶ�
3��������Դ������Ϣ
4����������IMU��Ϣ
**************************************************************************/
#include "DataCom.h"
#include "ShareWare.h"

/*-----------------------------------------------------------
��������: ���ݽ��սӿ�
�������: ���������ַ
�� �� ֵ: None
˵    ��: ��������������֡����ú���ʵ����ֵ����
 -----------------------------------------------------------*/
void DataCom_RX_Function(DataCom_RX_Struct *DataCom_RX, uint8_t *Buff)
{
	switch(Buff[3])
	{
		case 1://�����뷴������Ŀ���ٶ�
		{
			for(uint8_t i=0; i<4; i++) floatHex.Hex[3-i] =  Buff[4+i];
			DataCom_RX->Linear_X = floatHex.floatValue;//����X��Ŀ�����ٶ�ֵ m/s
			
			for(uint8_t i=0; i<4; i++) floatHex.Hex[3-i] =  Buff[8+i];
			DataCom_RX->Linear_Y = floatHex.floatValue;//����Y��Ŀ�����ٶ�ֵ m/s
			
			for(uint8_t i=0; i<4; i++) floatHex.Hex[3-i] =  Buff[12+i];
			DataCom_RX->Angular_Z = floatHex.floatValue;//����Z��Ŀ����ٶ�ֵ rad/s
			
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 1;
			Usart2_TX_Buf[3] = 1;
			
			uint8_t SumCheck=0;//У���
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//����У���
			
			Usart2_TX_Buf[4] = SumCheck;//У���
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//����DMA����ָ��
		}break;
		
		case 2://��������ʵʱ�ٶ�
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 13;
			Usart2_TX_Buf[3] = 2;
			
			floatHex.floatValue = Kinematics_Forward.Linear_X;//���嵱ǰX�����ٶ� m/s
			Usart2_TX_Buf[4] = floatHex.Hex[3];
			Usart2_TX_Buf[5] = floatHex.Hex[2];
			Usart2_TX_Buf[6] = floatHex.Hex[1];
			Usart2_TX_Buf[7] = floatHex.Hex[0];
			
			floatHex.floatValue = Kinematics_Forward.Linear_Y;//���嵱ǰY�����ٶ� m/s
			Usart2_TX_Buf[8] = floatHex.Hex[3];
			Usart2_TX_Buf[9] = floatHex.Hex[2];
			Usart2_TX_Buf[10] = floatHex.Hex[1];
			Usart2_TX_Buf[11] = floatHex.Hex[0];
			
			floatHex.floatValue = Kinematics_Forward.Angular_Z;//���嵱ǰZ����ٶ� rad/s
			Usart2_TX_Buf[12] = floatHex.Hex[3];
			Usart2_TX_Buf[13] = floatHex.Hex[2];
			Usart2_TX_Buf[14] = floatHex.Hex[1];
			Usart2_TX_Buf[15] = floatHex.Hex[0];
			
			uint8_t SumCheck=0;//У���
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//����У���
			
			Usart2_TX_Buf[16] = SumCheck;//У���
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//����DMA����ָ��
		}break;
		
		case 3://������Դ������Ϣ
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 4;
			Usart2_TX_Buf[3] = 3;
			
			uint16_t Voltage = Battery.Voltage * 1000;//��ص�ѹֵ mv
			Usart2_TX_Buf[4]= Voltage >> 8;
			Usart2_TX_Buf[5]= Voltage & 0xFF;
	
			Usart2_TX_Buf[6]= Battery.Capacity;//��ص���ֵ %
			
			uint8_t SumCheck=0;//У���
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//����У���
			
			Usart2_TX_Buf[7] = SumCheck;//У���
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//����DMA����ָ��
		}break;
		
		case 4://��������IMU��Ϣ
		{
			Usart2_TX_Buf[0] = 0xFE;
			Usart2_TX_Buf[1] = 0xEF;
			Usart2_TX_Buf[2] = 25;
			Usart2_TX_Buf[3] = 4;
			
			floatHex.floatValue = MPU6050.Accel_X;//���ٶȼ�X����ֵ m/s^2
			Usart2_TX_Buf[4] = floatHex.Hex[3];
			Usart2_TX_Buf[5] = floatHex.Hex[2];
			Usart2_TX_Buf[6] = floatHex.Hex[1];
			Usart2_TX_Buf[7] = floatHex.Hex[0];
			
			floatHex.floatValue = MPU6050.Accel_Y;//���ٶȼ�Y����ֵ m/s^2
			Usart2_TX_Buf[8] = floatHex.Hex[3];
			Usart2_TX_Buf[9] = floatHex.Hex[2];
			Usart2_TX_Buf[10] = floatHex.Hex[1];
			Usart2_TX_Buf[11] = floatHex.Hex[0];
			
			floatHex.floatValue = MPU6050.Accel_Z;//���ٶȼ�Z����ֵ m/s^2
			Usart2_TX_Buf[12]= floatHex.Hex[3];
			Usart2_TX_Buf[13]= floatHex.Hex[2];
			Usart2_TX_Buf[14]= floatHex.Hex[1];
			Usart2_TX_Buf[15]= floatHex.Hex[0];
			
			floatHex.floatValue = MPU6050.Gyro_X;//���ٶ�X����ֵ rad/s
			Usart2_TX_Buf[16]= floatHex.Hex[3];
			Usart2_TX_Buf[17]= floatHex.Hex[2];
			Usart2_TX_Buf[18]= floatHex.Hex[1];
			Usart2_TX_Buf[19]= floatHex.Hex[0];
			
			floatHex.floatValue = MPU6050.Gyro_Y;//���ٶ�Y����ֵ rad/s
			Usart2_TX_Buf[20]= floatHex.Hex[3];
			Usart2_TX_Buf[21]= floatHex.Hex[2];
			Usart2_TX_Buf[22]= floatHex.Hex[1];
			Usart2_TX_Buf[23]= floatHex.Hex[0];
			
			floatHex.floatValue = MPU6050.Gyro_Z;//���ٶ�Z����ֵ rad/s
			Usart2_TX_Buf[24]= floatHex.Hex[3];
			Usart2_TX_Buf[25]= floatHex.Hex[2];
			Usart2_TX_Buf[26]= floatHex.Hex[1];
			Usart2_TX_Buf[27]= floatHex.Hex[0];
			
			uint8_t SumCheck=0;//У���
			uint8_t i = Usart2_TX_Buf[2] + 3;
			for(;(i--)>0;) SumCheck += Usart2_TX_Buf[i];//����У���
			
			Usart2_TX_Buf[28] = SumCheck;//У���
			
			HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, Usart2_TX_Buf[2] + 4);//����DMA����ָ��
		}break;
		
		default:break;
	}

}

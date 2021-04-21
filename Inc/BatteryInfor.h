#ifndef __BATTERYINFOR_H
#define __BATTERYINFOR_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
typedef struct
{
	__IO uint16_t ADchx;//��ص�ѹADCֵ
	__IO uint16_t ADre; //STM32�ڲ����յ�ѹADCֵ
	__IO float Voltage; //��ص�ѹֵ
	__IO uint8_t Capacity;//��ص����ٷֱ� 0-100
} Battery_Struct;//���״̬��Ϣ�ṹ�����

void UpdateBatteryInfor(Battery_Struct *Battery, uint32_t *ADCx_DMA_Buff);//���µ��״̬��Ϣ
uint8_t GetdBatteryCapacity(float BatteryVoltag, uint8_t BatterySeriesNumber);//��������ʣ������ٷֱ�

#ifdef __cplusplus
}
#endif

#endif

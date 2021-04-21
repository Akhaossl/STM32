#ifndef __INDICATORDEVICE_H
#define __INDICATORDEVICE_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif

void Buzzer_GPIO_Init(void);//������IO�ڳ�ʼ��
void LED_Green_GPIO_Init(void);//��ɫLED��IO�ڳ�ʼ��
void LED_Red_GPIO_Init(void);//��ɫLED��IO�ڳ�ʼ��
void BuzzerControl(uint16_t Times, uint16_t PeriodTime);//���������ƺ���
void LED_Green_Control(uint16_t Times, uint16_t PeriodTime);//��ɫLED���ƺ���
void LED_Red_Control(uint16_t Times, uint16_t PeriodTime);//��ɫLED���ƺ���
void IndicatorDeviceControl(void);//ָʾ�豸���ƺ���

#ifdef __cplusplus
}
#endif

#endif

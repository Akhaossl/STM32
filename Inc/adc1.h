#ifndef __ADC1_H
#define __ADC1_H
#include "main.h"
#define ADC1_DMA_BuffLEN 2//ADC1�ɼ�����DMA���泤��
extern __IO uint32_t ADC1_DMA_Buff[ADC1_DMA_BuffLEN];//ADC1�ɼ�����DMA����
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma1;
void MX_ADC1_Init(void);//ADC1��ʼ��
#endif

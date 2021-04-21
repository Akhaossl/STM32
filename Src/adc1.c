#include "adc1.h"
#include "BatteryInfor.h"

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma1;

__IO uint32_t ADC1_DMA_Buff[ADC1_DMA_BuffLEN];//ADC1�ɼ�����DMA����
/*-----------------------------------------------------------
��������: ADC1��ʼ������
�������: None
�� �� ֵ: None
˵    ��: ����ADC1-IN4��ADC1-IN17�������ɼ��ⲿ��ѹ���ڲ����յ�ѹADCֵ
 -----------------------------------------------------------*/
void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;

  hadc1.Instance = ADC1;//ADC1
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;//���ͨ���ɼ�
  hadc1.Init.ContinuousConvMode = ENABLE;//�����ɼ�
  hadc1.Init.DiscontinuousConvMode = DISABLE;//���ü��ģʽ
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;//���������ʽ
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;//�������Ҷ���
  hadc1.Init.NbrOfConversion = 2;//2������
  HAL_ADC_Init(&hadc1);

  sConfig.Channel = ADC_CHANNEL_4;//ͨ��4
  sConfig.Rank = ADC_REGULAR_RANK_1;//����˳�����
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;//����ʱ��
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	
	sConfig.Channel = ADC_CHANNEL_17;//ͨ��17,�ڲ����յ�ѹ 1.16V~1.2V~1.24V
  sConfig.Rank = ADC_REGULAR_RANK_2;//����˳�����
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	
	/* ����ADת����ʹ��DMA������ж� */
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC1_DMA_Buff, ADC1_DMA_BuffLEN);  
	
	HAL_ADC_Start(&hadc1);//ADC��ʼ�ɼ�ADCֵ
}

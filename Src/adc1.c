#include "adc1.h"
#include "BatteryInfor.h"

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma1;

__IO uint32_t ADC1_DMA_Buff[ADC1_DMA_BuffLEN];//ADC1采集数据DMA缓存
/*-----------------------------------------------------------
函数功能: ADC1初始化配置
输入参数: None
返 回 值: None
说    明: 配置ADC1-IN4和ADC1-IN17参数，采集外部电压和内部参照电压ADC值
 -----------------------------------------------------------*/
void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig;

  hadc1.Instance = ADC1;//ADC1
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;//多个通道采集
  hadc1.Init.ContinuousConvMode = ENABLE;//连续采集
  hadc1.Init.DiscontinuousConvMode = DISABLE;//禁用间断模式
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;//软件触发方式
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;//数据向右对齐
  hadc1.Init.NbrOfConversion = 2;//2个列组
  HAL_ADC_Init(&hadc1);

  sConfig.Channel = ADC_CHANNEL_4;//通道4
  sConfig.Rank = ADC_REGULAR_RANK_1;//采样顺序序号
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;//采样时间
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	
	sConfig.Channel = ADC_CHANNEL_17;//通道17,内部参照电压 1.16V~1.2V~1.24V
  sConfig.Rank = ADC_REGULAR_RANK_2;//采样顺序序号
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	
	/* 启动AD转换并使能DMA传输和中断 */
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC1_DMA_Buff, ADC1_DMA_BuffLEN);  
	
	HAL_ADC_Start(&hadc1);//ADC开始采集ADC值
}

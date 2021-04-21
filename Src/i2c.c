#include "i2c.h"

I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_i2c1_tx;
__IO uint8_t I2C1_Tx_Flag=0;//I2C1数据发送完成标志位
__IO uint8_t I2C1_Rx_Flag=0;//I2C1数据接收完成标志位

/*-----------------------------------------------------------
函数功能: I2C1初始化函数
输入参数: None
返 回 值: None
说    明: 配置I2C1参数 通信速率400K
 -----------------------------------------------------------*/
void MX_I2C1_Init(void)
{
	__HAL_RCC_AFIO_CLK_ENABLE();//重映射必须要开AFIO时钟
	
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  HAL_I2C_Init(&hi2c1);
}


void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *i2cHandle)
{
	
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *i2cHandle)
{
	if(i2cHandle->Instance ==  I2C1)
	{
		I2C1_Tx_Flag = 1;//I2C1数据发送完成标志位
	}
}


void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *i2cHandle)
{
	if(i2cHandle->Instance ==  I2C1)
	{
		I2C1_Rx_Flag = 1;//I2C1接收数据完成标志位
		
		MPU6050_Update(&MPU6050);//更新MPU原始数值函数
		MPU6050_UpdateAccel(&MPU6050);
		MPU6050_UpdateGyro(&MPU6050);
	}
}

/**
  ******************************************************************************
  * File Name          : stm32f1xx_hal_msp.c
  * Description        : This file provides code for the MSP Initialization 
  *                      and de-Initialization codes.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "ShareWare.h"

extern void _Error_Handler(char *, int);
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_AFIO_CLK_ENABLE();

  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/
  /* MemoryManagement_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
  /* BusFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
  /* UsageFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
  /* SVCall_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
  /* DebugMonitor_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
  /* PendSV_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

    /**NOJTAG: JTAG-DP Disabled and SW-DP Enabled 
    */
  __HAL_AFIO_REMAP_SWJ_NOJTAG();

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}



void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	if(htim_pwm->Instance==TIM8)
  {
    /* Peripheral clock enable */
		__HAL_RCC_TIM8_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
    /**TIM8 GPIO Configuration    
    PC6     ------> TIM8_CH1
    PC7     ------> TIM8_CH2
		PC8     ------> TIM8_CH3
		PC9     ------> TIM8_CH4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	}		
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{
	if(htim_pwm->Instance==TIM8)
  {
		__HAL_RCC_TIM8_CLK_DISABLE();
		/**TIM8 GPIO Configuration    
    PC6     ------> TIM8_CH1
    PC7     ------> TIM8_CH2
		PC8     ------> TIM8_CH3
		PC9     ------> TIM8_CH4
    */
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9);
	}
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(hadc->Instance==ADC1)
  {
    /* Peripheral clock enable */
		__HAL_RCC_ADC1_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration    
    PA4     ------> ADC1_IN4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH ;//���Ӧ����IO�����ٶ�
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		/* DMAʱ��ʹ�� */
		__HAL_RCC_DMA1_CLK_ENABLE();
		/* DMA�����ʼ������ */  
    hdma1.Instance = DMA1_Channel1;
    hdma1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma1.Init.MemInc = DMA_MINC_ENABLE;
    hdma1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma1.Init.Mode = DMA_CIRCULAR;
    hdma1.Init.Priority = DMA_PRIORITY_HIGH;
    HAL_DMA_Init(&hdma1);
    /* ����DMA */
    __HAL_LINKDMA(hadc,DMA_Handle,hdma1);
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
  if(hadc->Instance==ADC1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();
    /**ADC1 GPIO Configuration    
    PA4     ------> ADC1_IN4 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);
		/* DMA���跴��ʼ��*/
    HAL_DMA_DeInit(hadc->DMA_Handle);
  }
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct;
		
	if(huart->Instance==USART2)
	{
		/* USART2 clock enable */
		__HAL_RCC_USART2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART2 GPIO Configuration    
		PA2     ------> USART2_TX
		PA3     ------> USART2_RX 
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		__HAL_RCC_DMA1_CLK_ENABLE();
		
		/* USART2_TX Init */
		hdma_usart2_tx.Instance = DMA1_Channel7;
		hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart2_tx.Init.Mode = DMA_NORMAL;
		hdma_usart2_tx.Init.Priority = DMA_PRIORITY_HIGH;
		HAL_DMA_Init(&hdma_usart2_tx);

		__HAL_LINKDMA(&huart2,hdmatx,hdma_usart2_tx);
		
		/* USART2_RX Init */
		hdma_usart2_rx.Instance = DMA1_Channel6;
		hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart2_rx.Init.Mode = DMA_NORMAL;
		hdma_usart2_rx.Init.Priority = DMA_PRIORITY_HIGH;
		HAL_DMA_Init(&hdma_usart2_rx);

		__HAL_LINKDMA(&huart2,hdmarx,hdma_usart2_rx);
	
		HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
		
		HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
		
		/* USART2 interrupt Init */
		HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(USART2_IRQn);
	}
	
	else if(huart->Instance==UART4)
  {
    /* Peripheral clock enable */
    __HAL_RCC_UART4_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
    /**UART4 GPIO Configuration    
    PC10     ------> UART4_TX
    PC11     ------> UART4_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH ;//���Ӧ����IO�����ٶ�
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		
		__HAL_RCC_DMA2_CLK_ENABLE();

		/* UART4_TX Init */
		hdma_uart4_tx.Instance = DMA2_Channel5;
		hdma_uart4_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_uart4_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_uart4_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_uart4_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_uart4_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_uart4_tx.Init.Mode = DMA_NORMAL;
		hdma_uart4_tx.Init.Priority = DMA_PRIORITY_LOW;
		HAL_DMA_Init(&hdma_uart4_tx);

		__HAL_LINKDMA(huart,hdmatx,hdma_uart4_tx);
		
		/* UART4_RX Init */
		hdma_uart4_rx.Instance = DMA2_Channel3;
		hdma_uart4_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_uart4_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_uart4_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_uart4_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_uart4_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_uart4_rx.Init.Mode = DMA_NORMAL;
		hdma_uart4_rx.Init.Priority = DMA_PRIORITY_LOW;
		HAL_DMA_Init(&hdma_uart4_rx);

		__HAL_LINKDMA(huart,hdmarx,hdma_uart4_rx);
		
		HAL_NVIC_SetPriority(DMA2_Channel3_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(DMA2_Channel3_IRQn);
		
		HAL_NVIC_SetPriority(DMA2_Channel4_5_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(DMA2_Channel4_5_IRQn);
		
		/* UART4 interrupt Init */
		HAL_NVIC_SetPriority(UART4_IRQn, 1, 0);//�����ж����ȼ�����
		HAL_NVIC_EnableIRQ(UART4_IRQn);
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{	
  if(huart->Instance==USART2)
  {
		/* Peripheral clock disable */
		__HAL_RCC_USART2_CLK_DISABLE();
		
		/**USART2 GPIO Configuration    
		PA2     ------> USART2_TX
		PA3     ------> USART2_RX 
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);
		HAL_NVIC_DisableIRQ(USART2_IRQn);
		HAL_DMA_DeInit(huart->hdmarx);
  }
	
	else if(huart->Instance==UART4)
  {
    /* Peripheral clock disable */
    __HAL_RCC_UART4_CLK_DISABLE();
  
    /**UART4 GPIO Configuration    
    PC10     ------> UART4_TX
    PC11     ------> UART4_RX 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_11);
		HAL_NVIC_DisableIRQ(UART4_IRQn);
		HAL_DMA_DeInit(huart->hdmarx);
  }
}

void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* htim_encoder)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  if(htim_encoder->Instance==TIM2)
  {
    /* Peripheral clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();
  	__HAL_AFIO_REMAP_TIM2_PARTIAL_1();//TIM2 CH1ӳ�䵽PA15 CH2ӳ�䵽PB3
    __HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM2 GPIO Configuration    
    pA15     ------> TIM2_CH1
    PB3      ------> TIM2_CH2 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
  }
	
	if(htim_encoder->Instance==TIM3)
  {
    /* Peripheral clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM3 GPIO Configuration    
    PA6     ------> TIM3_CH1
    PA7     ------> TIM3_CH2 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		HAL_NVIC_SetPriority(TIM3_IRQn, 1, 1);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
  }
	
	if(htim_encoder->Instance==TIM4)
  {
    /* Peripheral clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM4 GPIO Configuration    
    PB6     ------> TIM4_CH1
    PB7     ------> TIM4_CH2 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		HAL_NVIC_SetPriority(TIM4_IRQn, 1, 2);
		HAL_NVIC_EnableIRQ(TIM4_IRQn);
  }
	
	if(htim_encoder->Instance==TIM5)
  {
    /* Peripheral clock enable */
    __HAL_RCC_TIM5_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM5 GPIO Configuration    
    PA0     ------> TIM5_CH1
    PA1     ------> TIM5_CH2 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		HAL_NVIC_SetPriority(TIM5_IRQn, 1, 3);
		HAL_NVIC_EnableIRQ(TIM5_IRQn);
  }
}

void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef* htim_encoder)
{
	if(htim_encoder->Instance==TIM2)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();
		__HAL_AFIO_REMAP_TIM2_DISABLE();//ʧ��TIM2����ӳ��
  
    /**TIM2 GPIO Configuration    
    PA15     ------> TIM2_CH1
    PB3      ------> TIM2_CH2 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_15);
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3);
		
		HAL_NVIC_DisableIRQ(TIM2_IRQn);
  }
	
	if(htim_encoder->Instance==TIM3)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();
  
    /**TIM3 GPIO Configuration    
    PA6     ------> TIM3_CH1
    PA7     ------> TIM3_CH2 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_6|GPIO_PIN_7);
		
		HAL_NVIC_DisableIRQ(TIM3_IRQn);
  }
	
	if(htim_encoder->Instance==TIM4)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM4_CLK_DISABLE();
  
    /**TIM4 GPIO Configuration    
    PB6     ------> TIM4_CH1
    PB7     ------> TIM4_CH2 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);
		
		HAL_NVIC_DisableIRQ(TIM4_IRQn);
  }
	
	if(htim_encoder->Instance==TIM5)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM5_CLK_DISABLE();
  
    /**TIM5 GPIO Configuration    
    PA0     ------> TIM5_CH1
    PA1     ------> TIM5_CH2 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1);
		
		HAL_NVIC_DisableIRQ(TIM5_IRQn);
  }
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
	
	if(i2cHandle->Instance==I2C1)
  {
		__HAL_AFIO_REMAP_I2C1_ENABLE();//I2C1 SCLӳ�䵽PB8 SDAӳ�䵽PB9  ��亯��������ʹ�ܲ���Ч
		/* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
		
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration    
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
    /* I2C1 interrupt Init */
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{
	if(i2cHandle->Instance==I2C1)
  {
		__HAL_AFIO_REMAP_I2C1_DISABLE();
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();
		
    /**I2C1 GPIO Configuration    
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

    /* I2C1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
  }
} 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

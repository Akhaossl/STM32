#include "uart.h"
#include <stdarg.h>
#include "ShareWare.h"

UART_HandleTypeDef huart2;
__IO uint8_t Usart2_TX_Buf[Usart2_TX_LEN];//����2������������
__IO uint8_t Usart2_RX_Buf[Usart2_RX_LEN];//����2������������
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

UART_HandleTypeDef huart4;
__IO uint8_t Uart4_TX_Buf[Uart4_TX_LEN];
__IO uint8_t Uart4_RX_Buf[Uart4_RX_LEN];
DMA_HandleTypeDef hdma_uart4_rx;
DMA_HandleTypeDef hdma_uart4_tx;

/*-----------------------------------------------------------
��������: ����2��ʼ������
�������: None
�� �� ֵ: None
˵    ��: ���ô���2���� ������115200
 -----------------------------------------------------------*/
void MX_USART2_Init(void)
{
  huart2.Instance = USART2;//����2
  huart2.Init.BaudRate = 230400;//������
  huart2.Init.WordLength = UART_WORDLENGTH_8B;//8λ����λ
  huart2.Init.StopBits = UART_STOPBITS_1;//1λֹͣλ
  huart2.Init.Parity = UART_PARITY_NONE;//��У��
  huart2.Init.Mode = UART_MODE_TX_RX;//ȫ˫������ģʽ
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart2);
		
	HAL_UART_Receive_DMA(&huart2, (uint8_t*)Usart2_RX_Buf, Usart2_RX_LEN);//����DMA����
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);//�������н����ж�
}

/*-----------------------------------------------------------
��������: ����4��ʼ������
�������: None
�� �� ֵ: None
˵    ��: ���ô���4���� ������100000
 -----------------------------------------------------------*/
void MX_UART4_Init(void)
{
  huart4.Instance = UART4;//����4
  huart4.Init.BaudRate = 100000;//������
  huart4.Init.WordLength = UART_WORDLENGTH_9B;//8λ����λ��1λУ��λ
  huart4.Init.StopBits = UART_STOPBITS_1;//1λֹͣλ
  huart4.Init.Parity = UART_PARITY_EVEN;//żУ��
  huart4.Init.Mode = UART_MODE_TX_RX;//ȫ˫������ģʽ
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart4);

	HAL_UART_Receive_DMA(&huart4, (uint8_t*)Uart4_RX_Buf, Uart4_RX_LEN);//����DMA����
	__HAL_UART_ENABLE_IT(&huart4, UART_IT_IDLE);//�������н����ж�
}

/*-----------------------------------------------------------
��������: ���ڽ��տ����жϺ���
�������: ���ھ������ָ��
�� �� ֵ: None
˵    ��: ���ڽ��յ����ݺ�һ��byte�ĸߵ�ƽ(����)״̬�ͻᴥ�������жϽ���ú�����
					�û��ں����ж�ȡ���ڽ��յ�������
 -----------------------------------------------------------*/
void UsartReceive_IDLE(UART_HandleTypeDef *huart)//���ڽ��տ����жϺ���
{
	uint32_t temp = 0;
	if((__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE) != RESET))  
	{			
		/*------------Usart2-------------*/
		if(huart->Instance == USART2)
		{
			__HAL_UART_CLEAR_IDLEFLAG(huart);
			temp = huart->Instance->SR;
			temp = huart->Instance->DR;
			temp = hdma_usart2_rx.Instance->CNDTR; 
			HAL_UART_DMAStop(huart);
		
			RingBuff_Write(&RingBuff_Mast, (uint8_t*)Usart2_RX_Buf, Usart2_RX_LEN-temp);//�����λ�����д��һ�����ݺ���
			
			HAL_UART_Receive_DMA(huart, (uint8_t*)Usart2_RX_Buf, Usart2_RX_LEN);//����DMA����
		}
		/*-------------Uart4--------------*/
		else if(huart->Instance == UART4)
		{
			__HAL_UART_CLEAR_IDLEFLAG(huart);
			temp = huart->Instance->SR;
			temp = huart->Instance->DR;
			temp = hdma_uart4_rx.Instance->CNDTR; 
			HAL_UART_DMAStop(huart);
			
			RC_Update(&RC, (uint8_t*)Uart4_RX_Buf);//ң�������ݽ�������
			
			HAL_UART_Receive_DMA(huart, (uint8_t*)Uart4_RX_Buf, Uart4_RX_LEN);//����DMA����
		}
	}
}

/*-----------------------------------------------------------
��������: ���ڽ�������жϺ���
�������: ���ھ������ָ��
�� �� ֵ: None
˵    ��: ���ڽ��������ݺ��жϽ���ú������û��ں����ж�ȡ���ڽ��յ�������
 -----------------------------------------------------------*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)//���ڽ����ж�
{	

}

/*-----------------------------------------------------------
��������: ���ڷ�������жϺ���
�������: ���ھ������ָ��
�� �� ֵ: None
˵    ��: ���ڷ��������ݺ��жϽ���ú���
 -----------------------------------------------------------*/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)//���ڷ����ж�
{

}


void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	/*���ĵ�˵����Ҫ���ORE�ж���Ҫ��˳���ȡUSART_SR��USART_DR�Ĵ�����*/
  uint32_t isrflags   = READ_REG(huart->Instance->SR);//�ֲ����н��������Ҫ�ȶ�SR
	if((__HAL_UART_GET_FLAG(huart, UART_FLAG_PE))!=RESET)
	{
		READ_REG(huart->Instance->DR);//�ڶ�����DR
		__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_PE);//PE���־	
	}
	if((__HAL_UART_GET_FLAG(huart, UART_FLAG_FE))!=RESET)
	{
		READ_REG(huart->Instance->DR);//�ڶ�����DR
		__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_FE);//FE���־
	}
        
	if((__HAL_UART_GET_FLAG(huart, UART_FLAG_NE))!=RESET)
	{
		READ_REG(huart->Instance->DR);//�ڶ�����DR
		__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_NE);//NE���־
  }        
        
  if((__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE))!=RESET)
  {
    READ_REG(huart->Instance->CR1);//�ڶ�����CR
		__HAL_UART_CLEAR_FLAG(huart, UART_FLAG_ORE);//ORE���־
  }      
}


void dma_printf(const char *format, ...)//DMA���ͷ�ʽprintf()����
{
	uint32_t length;
	va_list args;
	va_start(args, format);
	length = vsnprintf((char *)Usart2_TX_Buf, sizeof(Usart2_TX_Buf), (char *)format, args);
	va_end(args);
	
	HAL_UART_Transmit_DMA(&huart2, (uint8_t *)Usart2_TX_Buf, length);
}

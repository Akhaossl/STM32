/**************************************************************************
�ļ��汾������� V1.0
�ļ����ܣ�
1�����Ʒ��������д���������ʱ��
2�����ƺ�ɫLED�������������ʱ��
3��������ɫLED�������������ʱ��
**************************************************************************/
#include "IndicatorDevice.h"

__IO uint16_t Buzzer_Times=0;//���������д���
__IO uint16_t Buzzer_PeriodTime=0;//����������ʱ��
__IO uint16_t Buzzer_PeriodTimeBuffer;//�������������ʱ��
__IO uint8_t Buzzer_LockedStatus=0;//����������״̬ =1�������� =0����δ����

__IO uint16_t LED_Green_Times=0;//��ɫLED��˸����
__IO uint16_t LED_Green_PeriodTime=0;//��ɫLED��˸ʱ��
__IO uint16_t LED_Green_PeriodTimeBuffer;//������ɫLED����ʱ��
__IO uint8_t LED_Green_LockedStatus=0;//��ɫLED����״̬ =1�������� =0����δ����

__IO uint16_t LED_Red_Times=0;//��ɫLED��˸����
__IO uint16_t LED_Red_PeriodTime=0;//��ɫLED����ʱ��
__IO uint16_t LED_Red_PeriodTimeBuffer;//�����ɫLED��˸ʱ��
__IO uint8_t LED_Red_LockedStatus=0;//��ɫLED����״̬ =1�������� =0����δ����

#define Buzzer(a) 																						 \
						if(a) 																						 \
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5,GPIO_PIN_SET);\
						else 																							 \
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5,GPIO_PIN_RESET)
						
#define Buzzer_Toggle HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_5)
								
#define LED_Green(a) 																						 \
						if(a) 																						 \
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,GPIO_PIN_SET);\
						else 																							 \
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,GPIO_PIN_RESET)
						
#define LED_Green_Toggle HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1)//����LED1 IO�ڷ�ת�ӿ�

#define LED_Red(a)																				 \
						if(a) 																						 \
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_SET);\
						else 																							 \
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_RESET)			

#define LED_Red_Toggle HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0)
						
void Buzzer_GPIO_Init(void)//������IO�ڳ�ʼ��
{
   /* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	
	/*�������оƬ1��ӦGPIO��������*/
  GPIO_InitStruct.Pin = GPIO_PIN_5;//�趨��Ӧ����IO���
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//�趨��Ӧ����IOΪ���ģʽ
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW ;//���Ӧ����IO�����ٶ�
	GPIO_InitStruct.Pull = GPIO_NOPULL;//�ڲ�����
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);//��ʼ����Ӧ����IO  
}

void LED_Green_GPIO_Init(void)//��ɫLED IO�ڳ�ʼ��
{
   /* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	
	/*�������оƬ1��ӦGPIO��������*/
  GPIO_InitStruct.Pin = GPIO_PIN_1;//�趨��Ӧ����IO���
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//�趨��Ӧ����IOΪ���ģʽ
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW ;//���Ӧ����IO�����ٶ�
	GPIO_InitStruct.Pull = GPIO_NOPULL;//�ڲ�����
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);//��ʼ����Ӧ����IO  
}

void LED_Red_GPIO_Init(void)//��ɫLED IO�ڳ�ʼ��
{
   /* ����IOӲ����ʼ���ṹ����� */
  GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE();//ʹ��(����)���Ŷ�ӦIO�˿�ʱ��
	
	/*�������оƬ1��ӦGPIO��������*/
  GPIO_InitStruct.Pin = GPIO_PIN_0;//�趨��Ӧ����IO���
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//�趨��Ӧ����IOΪ���ģʽ
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW ;//���Ӧ����IO�����ٶ�
	GPIO_InitStruct.Pull = GPIO_NOPULL;//�ڲ�����
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);//��ʼ����Ӧ����IO  
}

/*-----------------------------------------------------------
��������: ���������ƺ���
�������: ��������������Ƶ��
�� �� ֵ: None
˵    ��: 
������Times���Ǳ������� 
��������������������������Ĵ���������ò���Ϊ5������������ᱨ��5�κ�ֹͣ
��ֵΪ0ʱ����رշ��������У���ֵΪ0xFFFFʱ��������������

������PeriodTime��������Ƶ�� 
����Ƶ�ʴ�����������кͲ��е�ʱ�����ڣ�����ò���Ϊ5�����������һ�α����е����кͲ��е�ʱ���Ϊ5ms
��ֵΪ0ʱ����رշ��������У���ֵΪ0xFFFFʱ�������������
 -----------------------------------------------------------*/
void BuzzerControl(uint16_t Times, uint16_t PeriodTime)//���������ƺ���
{
	static uint16_t LastTimes=0,LastPeriodTime=0;
	if(LastTimes != Times || LastPeriodTime != PeriodTime || (!Buzzer_Times && !Buzzer_PeriodTime))//��ֹ�������øú������²�����ִ��
	{
		LastTimes=Times;
		LastPeriodTime=PeriodTime;
		
		Buzzer_LockedStatus=1;//����������״̬Ϊ1
		
		if(!Times)//��������Ϊ0
		{
			Buzzer(0);//������������
			return;//�˳�����
		}
		else if(!PeriodTime)//����Ƶ��Ϊ0
		{
			Buzzer(0);//������������
			return;//�˳�����
		}
		else
		{
			if(PeriodTime == 0xFFFF)//����
			{
				Buzzer(1);//����������
				return;//�˳�����
			}	
			else if(Times == 0xFFFF)//��������
			{
				Buzzer(0);//������������
				Buzzer_Times =  Times;//��ֵ0xFFFF
				Buzzer_PeriodTimeBuffer= PeriodTime;//���»������������Ƶ��
				Buzzer_PeriodTime =0;//����������Ƶ��ʱ����0
			}
			else
			{
				Buzzer(0);//������������
				Buzzer_Times =  Times * 2;//���������д���*2  PS��һ��һ��Ϊһ�����ڣ������Ҫ��2
				Buzzer_PeriodTimeBuffer= PeriodTime;//���»������������Ƶ��
				Buzzer_PeriodTime =0;//����������Ƶ��ʱ����0
			}
			Buzzer_LockedStatus=0;//����������״̬Ϊ0
		}	
	}
}


/*-----------------------------------------------------------
��������: ��ɫLED���ƺ���
�������: ��˸��������˸����
�� �� ֵ: None
˵    ��: 
��˸��������LED��������˸�Ĵ���������ò���Ϊ5������LED����˸5�κ�ֹͣ������ò���Ϊ0xFFFF���������LEDһֱ��˸��ͣ
��˸���ڴ���LED�����ƺ���Ƶ�ʱ�����ڣ�����ò���Ϊ5������LED��һ����˸�еĵ����ƺ���Ƶ�ʱ��Ϊ5ms������ò���Ϊ0xFFFF���������LEDһֱ��������״̬
 -----------------------------------------------------------*/
void LED_Green_Control(uint16_t Times, uint16_t PeriodTime)//��ɫLED���ƺ���
{
	static uint16_t LastTimes=0,LastPeriodTime=0;
	if(LastTimes != Times || LastPeriodTime != PeriodTime || (!LED_Green_Times && !LED_Green_PeriodTime))//��ֹ�������øú������²�����ִ��
	{
		LastTimes=Times;
		LastPeriodTime=PeriodTime;
		
		LED_Green_LockedStatus=1;//��ɫLED����״̬Ϊ1
			
		if(!Times)//��˸����Ϊ0
		{
			LED_Green(0);//��ɫLED����
			return;//�˳�����
		}
		else if(!PeriodTime)//��˸Ƶ��Ϊ0
		{
			LED_Green(0);//��ɫLED����
			return;//�˳�����
		}
		else
		{
			if(PeriodTime == 0xFFFF)//����
			{
				LED_Green(1);//��ɫLED��
				return;//�˳�����
			}	
			else if(Times == 0xFFFF)//������˸
			{
				LED_Green(0);//��ɫLED����
				LED_Green_Times =  Times;//��ֵ0xFFFF
				LED_Green_PeriodTimeBuffer= PeriodTime;//���»���LED��˸Ƶ��
				LED_Green_PeriodTime =0;//LED��˸Ƶ��ʱ����0
			}
			else
			{
				LED_Green(0);//��ɫLED����
				LED_Green_Times =  Times * 2;//LED��˸����*2  PS��һ��һ��Ϊһ�����ڣ������Ҫ��2
				LED_Green_PeriodTimeBuffer= PeriodTime;//���»���LED��˸Ƶ��
				LED_Green_PeriodTime =0;//LED��˸Ƶ��ʱ����0
			}
			LED_Green_LockedStatus=0;//LED����״̬Ϊ0
		}	
	}
}

/*-----------------------------------------------------------
��������: ��ɫLED���ƺ���
�������: ��˸��������˸����
�� �� ֵ: None
˵    ��: 
��˸��������LED��������˸�Ĵ���������ò���Ϊ5������LED����˸5�κ�ֹͣ������ò���Ϊ0xFFFF���������LEDһֱ��˸��ͣ
��˸���ڴ���LED�����ƺ���Ƶ�ʱ�����ڣ�����ò���Ϊ5������LED��һ����˸�еĵ����ƺ���Ƶ�ʱ��Ϊ5ms������ò���Ϊ0xFFFF���������LEDһֱ��������״̬
 -----------------------------------------------------------*/
void LED_Red_Control(uint16_t Times, uint16_t PeriodTime)//��ɫLED���ƺ���
{	
	static uint16_t LastTimes=0,LastPeriodTime=0;
	if(LastTimes != Times || LastPeriodTime != PeriodTime || (!LED_Red_Times && !LED_Red_PeriodTime))//��ֹ�������øú������²�����ִ��
	{
		LastTimes=Times;
		LastPeriodTime=PeriodTime;
		
		LED_Red_LockedStatus=1;//��ɫLED����״̬Ϊ1
		
		if(!Times)//��˸����Ϊ0
		{
			LED_Red(0);//��ɫLED����
			return;//�˳�����
		}
		else if(!PeriodTime)//��˸Ƶ��Ϊ0
		{
			LED_Red(0);//��ɫLED����
			return;//�˳�����
		}
		else
		{
			if(PeriodTime == 0xFFFF)//����
			{
				LED_Red(1);//��ɫLED��
				return;//�˳�����
			}	
			else if(Times == 0xFFFF)//������˸
			{
				LED_Red(0);//��ɫLED����
				LED_Red_Times =  Times;//��ֵ0xFFFF
				LED_Red_PeriodTimeBuffer= PeriodTime;//���»���LED��˸Ƶ��
				LED_Red_PeriodTime =0;//LED��˸Ƶ��ʱ����0
			}
			else
			{
				LED_Red(0);//��ɫLED����
				LED_Red_Times =  Times * 2;//LED��˸����*2  PS��һ��һ��Ϊһ�����ڣ������Ҫ��2
				LED_Red_PeriodTimeBuffer= PeriodTime;//���»���LED��˸Ƶ��
				LED_Red_PeriodTime =0;//LED��˸Ƶ��ʱ����0
			}
			LED_Red_LockedStatus=0;//LED����״̬Ϊ0
		}	
	}
}

/*-----------------------------------------------------------
��������: ָʾ�豸���ƺ���
�������: None
�� �� ֵ: None
˵    ��: �ú����ǿ���ָʾ�豸�Ŀ�����״̬����Ҫ���ú����ŵ�
�δ�ʱ���жϺ���������
 -----------------------------------------------------------*/
void IndicatorDeviceControl(void)
{
	if(Buzzer_PeriodTime) Buzzer_PeriodTime--;//����������ʱ��
	if(LED_Green_PeriodTime) LED_Green_PeriodTime--;//��ɫLED��˸ʱ��
	if(LED_Red_PeriodTime) LED_Red_PeriodTime--;//��ɫLED����ʱ��
	
	if(!Buzzer_LockedStatus)//������û��������ִ��
	{
		if(Buzzer_Times && !Buzzer_PeriodTime)//����������Ϊ0������Ƶ��ʱ��Ϊ0
		{
			Buzzer_Toggle;//���Ʒ�����IO�ڵ�ƽ��ת
			if(Buzzer_Times != 0xFFFF) Buzzer_Times--;//����������������޴��򱨾�������1
			Buzzer_PeriodTime = Buzzer_PeriodTimeBuffer;//����������Ƶ��ʱ�����¸�ֵ
		}
	}
	
	/*------------------*/
	if(!LED_Green_LockedStatus)//��ɫLEDû��������ִ��
	{
		if(LED_Green_Times && !LED_Green_PeriodTime)//��ɫLED��˸������Ϊ0����˸Ƶ��ʱ��Ϊ0
		{
			LED_Green_Toggle;//������ɫLED IO�ڵ�ƽ��ת
			if(LED_Green_Times != 0xFFFF) LED_Green_Times--;//�����˸���������޴�����˸������1
			LED_Green_PeriodTime = LED_Green_PeriodTimeBuffer;//��ɫLED��˸Ƶ��ʱ�����¸�ֵ
		}
	}
	
	/*------------------*/
	if(!LED_Red_LockedStatus)//��ɫLEDû��������ִ��
	{	
		if(LED_Red_Times && !LED_Red_PeriodTime)//��ɫLED��˸������Ϊ0����˸Ƶ��ʱ��Ϊ0
		{
			LED_Red_Toggle;//���ƺ�ɫLED IO�ڵ�ƽ��ת
			if(LED_Red_Times != 0xFFFF) LED_Red_Times--;//�����˸���������޴�����˸������1
			LED_Red_PeriodTime = LED_Red_PeriodTimeBuffer;//��ɫLED��˸Ƶ��ʱ�����¸�ֵ
		}
	}
}

/**************************************************************************
�ļ��汾������� V1.0
**************************************************************************/
#include "main.h"
#include "ShareWare.h"


void SystemClock_Config(void);       

__IO uint16_t Loop_5msTime=0;//5ms��ѯʱ��
__IO uint16_t Loop_10msTime=0;//10ms��ѯʱ��
__IO uint16_t Loop_500msTime=0;//500ms��ѯʱ��
__IO uint16_t HeartbeatTime=0;//������ʱ��

__IO uint64_t EndTime=1000000;
__IO uint32_t LeftTime1=100000;
__IO uint32_t LeftTime2=100000;
__IO uint32_t LeftTime3=100000;
__IO uint32_t RightTime1=100000;
__IO uint32_t RightTime2=100000;
__IO uint32_t RightTime3=100000;
__IO uint32_t ForwardTime1=100000;
__IO uint32_t ForwardTime2=100000;
__IO uint32_t ForwardTime3=100000;
__IO uint32_t StopTime1=100000;
__IO uint32_t StopTime2=100000;
__IO uint32_t StopTime3=100000;
__IO uint32_t BackTime1=100000;
__IO uint32_t BackTime2=100000;
__IO uint32_t BackTime3=100000;

/*
�豸������ʱ��ΪEndTime�����һ����ʱ������ʱEndTmie��Ϊ0��ͣ��
speedX��speedY��ֵ��Ϊ�����ƶ����򣬵���ʱ��˳�򵽴�ʱ��Ӧ�ڵ���ʱ������if���޸���һ�ƶ������ƶ���ʱ
*/
float speedX=1.0f;float speedY=0.0f;

void Init()
{
	HAL_Init();//��ʼ��HAL��
	SystemClock_Config();//ϵͳʱ������
	MX_TIM8_Init();//TIM8-PWM��ʼ��
	Motor1_GPIO_Init();//�������1 IO��ʼ������
	Motor2_GPIO_Init();//�������2 IO��ʼ������
	Motor3_GPIO_Init();//�������3 IO��ʼ������
	Motor4_GPIO_Init();//�������4 IO��ʼ������
	
	MX_ADC1_Init();//ADC1��ʼ��
	LPF_Struct_Init(&LPF_SupplyVoltage, 0.3);//��ͨ�˲��ṹ�������ʼ��
	LPF_Struct_Init(&LPF_Linear_X, 0.1);//��ͨ�˲��ṹ�������ʼ��
	LPF_Struct_Init(&LPF_Linear_Y, 0.1);//��ͨ�˲��ṹ�������ʼ��
	LPF_Struct_Init(&LPF_Angular_Z, 0.1);//��ͨ�˲��ṹ�������ʼ��
	
	MX_USART2_Init();//����2��ʼ������
	MX_UART4_Init();//����4��ʼ������
	
	RingBuff_Init(&RingBuff_Mast, 100);//���λ�����������ʼ������
	ParseData_Init(&ParseData_Mast, 30);//�������ݲ�����ʼ��
	
	MX_TIM2_Init();//TIM2-������ģʽ��ʼ��
	MX_TIM3_Init();//TIM3-������ģʽ��ʼ��
	MX_TIM4_Init();//TIM4-������ģʽ��ʼ��
	MX_TIM5_Init();//TIM5-������ģʽ��ʼ��
	Encoder_Struct_Init(&Encoder_M1, 4);//��ʼ���������ṹ�����
	Encoder_Struct_Init(&Encoder_M2, 2);//��ʼ���������ṹ�����
	Encoder_Struct_Init(&Encoder_M3, 5);//��ʼ���������ṹ�����
	Encoder_Struct_Init(&Encoder_M4, 3);//��ʼ���������ṹ�����
	
	IncPID_Init(&PID_M1, -26.7688, -2.38301, -6.28552);//PID������ʼ��
	IncPID_Init(&PID_M2, -26.7688, -2.38301, -6.28552);//PID������ʼ��
	IncPID_Init(&PID_M3, -26.7688, -2.38301, -6.28552);//PID������ʼ��
	IncPID_Init(&PID_M4, -26.7688, -2.38301, -6.28552);//PID������ʼ��
	
	Buzzer_GPIO_Init();//������IO�ڳ�ʼ��
	LED_Green_GPIO_Init();//��ɫLED IO�ڳ�ʼ��
	LED_Red_GPIO_Init();//��ɫLED IO�ڳ�ʼ��
	HAL_Delay(600);
	MX_I2C1_Init();//I2C1��ʼ��
	MPU6050_Init(&MPU6050);//MPU6050��ʼ������
	
	BuzzerControl(2, 50);//���������ƺ���
	LED_Green_Control(2,50);//��ɫLED�ƿ��ƺ���
	LED_Red_Control(2,50);//��ɫLED�ƿ��ƺ���
}



int main(void)
{
	Init();
	LeftTime1=500;					//-x=1000ms//1��
	while (1)
  {	
		if(LeftTime1==0)
		{
			LED_Red_Control(2,50);//��ɫLED�ƿ��ƺ���
			BuzzerControl(3, 50);
			speedX=0.0f;
			speedY=1.0f;
			ForwardTime1=1500;		//y=1500ms//y������2��
			LeftTime1=1000000;
		}
		if(ForwardTime1==0)
		{
			LED_Green_Control(2,50);//��ɫLED�ƿ��ƺ���
			BuzzerControl(2, 50);
			speedX=0.0f;
			speedY=0.0f;
			StopTime1=2000;				//Ϊ��һ������ļ�ʱ����ֵ//ͣ��2s
			ForwardTime1=1000000; //��һ����ʱ�����س���ֵ
		}
		if(StopTime1==0)
		{
			LED_Green_Control(2,50);//��ɫLED�ƿ��ƺ���
			BuzzerControl(2, 100);
			speedX=0.0f;
			speedY=1.0f;
			ForwardTime2=4000;
			StopTime1=1000000;
		}
		if(ForwardTime2==0)
		{
			LED_Red_Control(2,50);//��ɫLED�ƿ��ƺ���
			BuzzerControl(3, 100);
			EndTime=0;
			ForwardTime2=1000000;
		}
		if(!Loop_10msTime)//10ms��ѯһ��
		{
			if(EndTime)//�����������ά������
			{
				LPF_Linear_X.a = 1.0f;
				LPF_Linear_Y.a = 1.0f;
				LPF_Angular_Z.a = 1.0f;
				Kinematics_Inverse.Linear_X = speedX;
				Kinematics_Inverse.Linear_Y = (-1)*speedY;
				Kinematics_Inverse.Angular_Z = 0.0f;
			}
			else//����Ϊ������ʱ ����ͣ��
			{
				LED_Green_Control(2,50);//��ɫLED�ƿ��ƺ���
				LPF_Linear_X.a = 0.1f;
				LPF_Linear_Y.a = 0.1f;
				LPF_Angular_Z.a = 0.1f;
				DataCom_RX.Linear_X =  DataCom_RX.Linear_Y =  DataCom_RX.Angular_Z = 0;			
				Kinematics_Inverse.Linear_X = 0;
				Kinematics_Inverse.Linear_Y = 0;
				Kinematics_Inverse.Angular_Z = 0;
			}
			
			LPF_Linear_X.SampleValue = Kinematics_Inverse.Linear_X;//ͨ����������X��Ŀ�����ٶ�ֵ����ͨ�˲����ṹ���еĲɼ�ֵ
			Kinematics_Inverse.Linear_X = LowPassFilter(&LPF_Linear_X);//����X��Ŀ�����ٶ�ֵ������ͨ�˲�������ֵ�����ƽ��
			
			LPF_Linear_Y.SampleValue = Kinematics_Inverse.Linear_Y;//ͨ����������Y��Ŀ�����ٶ�ֵ����ͨ�˲����ṹ���еĲɼ�ֵ
			Kinematics_Inverse.Linear_Y = LowPassFilter(&LPF_Linear_Y);//����Y��Ŀ�����ٶ�ֵ������ͨ�˲�������ֵ�����ƽ��
			
			LPF_Angular_Z.SampleValue = Kinematics_Inverse.Angular_Z;//ͨ����������Z��Ŀ����ٶ�ֵ����ͨ�˲����ṹ���еĲɼ�ֵ
			Kinematics_Inverse.Angular_Z = LowPassFilter(&LPF_Angular_Z);//����Z��Ŀ����ٶ�ֵ������ͨ�˲�������ֵ�����ƽ��
			
			Kinematics_Mecanum_CalculateRPM(&Kinematics_Inverse);//�����ķ���˶�ѧ��⺯��
			VelControl.M1_SetRPM = Kinematics_Inverse.M1_RPM;//ת��ֵ��ֵ
			VelControl.M2_SetRPM = Kinematics_Inverse.M2_RPM;//ת��ֵ��ֵ
			VelControl.M3_SetRPM = Kinematics_Inverse.M3_RPM;//ת��ֵ��ֵ
			VelControl.M4_SetRPM = Kinematics_Inverse.M4_RPM;//ת��ֵ��ֵ
			VelocityControl_4WD(&VelControl);//4WD�ٶȱջ����ƺ���

			Kinematics_Forward.M1_RPM = VelControl.M1_RPM;
			Kinematics_Forward.M2_RPM = VelControl.M2_RPM;
			Kinematics_Forward.M3_RPM = VelControl.M3_RPM;
			Kinematics_Forward.M4_RPM = VelControl.M4_RPM;			

			Kinematics_Mecanum_GetVelocities(&Kinematics_Forward);//�����ķ���˶�ѧ���⺯��
			
			Loop_10msTime = 10;//���¸�ֵʱ��
		}
		
		if(!Loop_5msTime)//5ms��ѯһ��
		{
			HAL_I2C_Mem_Read_IT(&hi2c1, MPU6050_DevAddr, MPU6050_RA_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, (uint8_t*)MPU6050.Buf, 14);//I2C��������
			Loop_5msTime = 5;//���¸�ֵʱ��
		}
		
		if(!Loop_500msTime)//500msѭ��һ��
		{
			UpdateBatteryInfor(&Battery, (uint32_t*)ADC1_DMA_Buff);//���µ��״̬��Ϣ
			Loop_500msTime=500;//���¸�ֵʱ��
		}
  }
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV4;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
// _Error_Handler(__FILE__, __LINE__);
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

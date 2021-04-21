/**************************************************************************
文件版本：神炽焰 V1.0
**************************************************************************/
#include "main.h"
#include "ShareWare.h"


void SystemClock_Config(void);       

__IO uint16_t Loop_5msTime=0;//5ms轮询时间
__IO uint16_t Loop_10msTime=0;//10ms轮询时间
__IO uint16_t Loop_500msTime=0;//500ms轮询时间
__IO uint16_t HeartbeatTime=0;//心跳包时间

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
设备运行总时长为EndTime，最后一个计时器到达时EndTmie设为0，停车
speedX，speedY初值即为初试移动方向，当计时器顺序到达时，应在到达时刻所在if中修改下一移动方向及移动计时
*/
float speedX=1.0f;float speedY=0.0f;

void Init()
{
	HAL_Init();//初始化HAL库
	SystemClock_Config();//系统时钟配置
	MX_TIM8_Init();//TIM8-PWM初始化
	Motor1_GPIO_Init();//电机驱动1 IO初始化函数
	Motor2_GPIO_Init();//电机驱动2 IO初始化函数
	Motor3_GPIO_Init();//电机驱动3 IO初始化函数
	Motor4_GPIO_Init();//电机驱动4 IO初始化函数
	
	MX_ADC1_Init();//ADC1初始化
	LPF_Struct_Init(&LPF_SupplyVoltage, 0.3);//低通滤波结构体参数初始化
	LPF_Struct_Init(&LPF_Linear_X, 0.1);//低通滤波结构体参数初始化
	LPF_Struct_Init(&LPF_Linear_Y, 0.1);//低通滤波结构体参数初始化
	LPF_Struct_Init(&LPF_Angular_Z, 0.1);//低通滤波结构体参数初始化
	
	MX_USART2_Init();//串口2初始化函数
	MX_UART4_Init();//串口4初始化函数
	
	RingBuff_Init(&RingBuff_Mast, 100);//环形缓冲区参数初始化函数
	ParseData_Init(&ParseData_Mast, 30);//解析数据参数初始化
	
	MX_TIM2_Init();//TIM2-编码器模式初始化
	MX_TIM3_Init();//TIM3-编码器模式初始化
	MX_TIM4_Init();//TIM4-编码器模式初始化
	MX_TIM5_Init();//TIM5-编码器模式初始化
	Encoder_Struct_Init(&Encoder_M1, 4);//初始化编码器结构体参数
	Encoder_Struct_Init(&Encoder_M2, 2);//初始化编码器结构体参数
	Encoder_Struct_Init(&Encoder_M3, 5);//初始化编码器结构体参数
	Encoder_Struct_Init(&Encoder_M4, 3);//初始化编码器结构体参数
	
	IncPID_Init(&PID_M1, -26.7688, -2.38301, -6.28552);//PID参数初始化
	IncPID_Init(&PID_M2, -26.7688, -2.38301, -6.28552);//PID参数初始化
	IncPID_Init(&PID_M3, -26.7688, -2.38301, -6.28552);//PID参数初始化
	IncPID_Init(&PID_M4, -26.7688, -2.38301, -6.28552);//PID参数初始化
	
	Buzzer_GPIO_Init();//蜂鸣器IO口初始化
	LED_Green_GPIO_Init();//绿色LED IO口初始化
	LED_Red_GPIO_Init();//红色LED IO口初始化
	HAL_Delay(600);
	MX_I2C1_Init();//I2C1初始化
	MPU6050_Init(&MPU6050);//MPU6050初始化函数
	
	BuzzerControl(2, 50);//蜂鸣器控制函数
	LED_Green_Control(2,50);//绿色LED灯控制函数
	LED_Red_Control(2,50);//红色LED灯控制函数
}



int main(void)
{
	Init();
	LeftTime1=500;					//-x=1000ms//1格
	while (1)
  {	
		if(LeftTime1==0)
		{
			LED_Red_Control(2,50);//红色LED灯控制函数
			BuzzerControl(3, 50);
			speedX=0.0f;
			speedY=1.0f;
			ForwardTime1=1500;		//y=1500ms//y轴正向2格
			LeftTime1=1000000;
		}
		if(ForwardTime1==0)
		{
			LED_Green_Control(2,50);//绿色LED灯控制函数
			BuzzerControl(2, 50);
			speedX=0.0f;
			speedY=0.0f;
			StopTime1=2000;				//为下一个到达的计时器赋值//停车2s
			ForwardTime1=1000000; //上一个计时器赋回超大值
		}
		if(StopTime1==0)
		{
			LED_Green_Control(2,50);//绿色LED灯控制函数
			BuzzerControl(2, 100);
			speedX=0.0f;
			speedY=1.0f;
			ForwardTime2=4000;
			StopTime1=1000000;
		}
		if(ForwardTime2==0)
		{
			LED_Red_Control(2,50);//红色LED灯控制函数
			BuzzerControl(3, 100);
			EndTime=0;
			ForwardTime2=1000000;
		}
		if(!Loop_10msTime)//10ms轮询一次
		{
			if(EndTime)//如果心跳周期维持正常
			{
				LPF_Linear_X.a = 1.0f;
				LPF_Linear_Y.a = 1.0f;
				LPF_Angular_Z.a = 1.0f;
				Kinematics_Inverse.Linear_X = speedX;
				Kinematics_Inverse.Linear_Y = (-1)*speedY;
				Kinematics_Inverse.Angular_Z = 0.0f;
			}
			else//否则为心跳超时 立即停车
			{
				LED_Green_Control(2,50);//绿色LED灯控制函数
				LPF_Linear_X.a = 0.1f;
				LPF_Linear_Y.a = 0.1f;
				LPF_Angular_Z.a = 0.1f;
				DataCom_RX.Linear_X =  DataCom_RX.Linear_Y =  DataCom_RX.Angular_Z = 0;			
				Kinematics_Inverse.Linear_X = 0;
				Kinematics_Inverse.Linear_Y = 0;
				Kinematics_Inverse.Angular_Z = 0;
			}
			
			LPF_Linear_X.SampleValue = Kinematics_Inverse.Linear_X;//通过采样车体X轴目标线速度值给低通滤波器结构体中的采集值
			Kinematics_Inverse.Linear_X = LowPassFilter(&LPF_Linear_X);//车体X轴目标线速度值经过低通滤波器后数值会更加平滑
			
			LPF_Linear_Y.SampleValue = Kinematics_Inverse.Linear_Y;//通过采样车体Y轴目标线速度值给低通滤波器结构体中的采集值
			Kinematics_Inverse.Linear_Y = LowPassFilter(&LPF_Linear_Y);//车体Y轴目标线速度值经过低通滤波器后数值会更加平滑
			
			LPF_Angular_Z.SampleValue = Kinematics_Inverse.Angular_Z;//通过采样车体Z轴目标角速度值给低通滤波器结构体中的采集值
			Kinematics_Inverse.Angular_Z = LowPassFilter(&LPF_Angular_Z);//车体Z轴目标角速度值经过低通滤波器后数值会更加平滑
			
			Kinematics_Mecanum_CalculateRPM(&Kinematics_Inverse);//麦克纳姆轮运动学逆解函数
			VelControl.M1_SetRPM = Kinematics_Inverse.M1_RPM;//转速值赋值
			VelControl.M2_SetRPM = Kinematics_Inverse.M2_RPM;//转速值赋值
			VelControl.M3_SetRPM = Kinematics_Inverse.M3_RPM;//转速值赋值
			VelControl.M4_SetRPM = Kinematics_Inverse.M4_RPM;//转速值赋值
			VelocityControl_4WD(&VelControl);//4WD速度闭环控制函数

			Kinematics_Forward.M1_RPM = VelControl.M1_RPM;
			Kinematics_Forward.M2_RPM = VelControl.M2_RPM;
			Kinematics_Forward.M3_RPM = VelControl.M3_RPM;
			Kinematics_Forward.M4_RPM = VelControl.M4_RPM;			

			Kinematics_Mecanum_GetVelocities(&Kinematics_Forward);//麦克纳姆轮运动学正解函数
			
			Loop_10msTime = 10;//重新赋值时间
		}
		
		if(!Loop_5msTime)//5ms轮询一次
		{
			HAL_I2C_Mem_Read_IT(&hi2c1, MPU6050_DevAddr, MPU6050_RA_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, (uint8_t*)MPU6050.Buf, 14);//I2C发送数据
			Loop_5msTime = 5;//重新赋值时间
		}
		
		if(!Loop_500msTime)//500ms循环一次
		{
			UpdateBatteryInfor(&Battery, (uint32_t*)ADC1_DMA_Buff);//更新电池状态信息
			Loop_500msTime=500;//重新赋值时间
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

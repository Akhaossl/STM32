/**************************************************************************
文件版本：神炽焰 V1.0
文件功能：
1、控制蜂鸣器鸣叫次数、鸣叫时长
2、控制红色LED亮灭次数、亮灭时长
3、控制绿色LED亮灭次数、亮灭时长
**************************************************************************/
#include "IndicatorDevice.h"

__IO uint16_t Buzzer_Times=0;//蜂鸣器鸣叫次数
__IO uint16_t Buzzer_PeriodTime=0;//蜂鸣器鸣叫时间
__IO uint16_t Buzzer_PeriodTimeBuffer;//缓存蜂鸣器鸣叫时间
__IO uint8_t Buzzer_LockedStatus=0;//蜂鸣器上锁状态 =1代表上锁 =0代表未上锁

__IO uint16_t LED_Green_Times=0;//绿色LED闪烁次数
__IO uint16_t LED_Green_PeriodTime=0;//绿色LED闪烁时间
__IO uint16_t LED_Green_PeriodTimeBuffer;//缓存绿色LED亮灯时间
__IO uint8_t LED_Green_LockedStatus=0;//绿色LED上锁状态 =1代表上锁 =0代表未上锁

__IO uint16_t LED_Red_Times=0;//红色LED闪烁次数
__IO uint16_t LED_Red_PeriodTime=0;//红色LED闪速时间
__IO uint16_t LED_Red_PeriodTimeBuffer;//缓存红色LED闪烁时间
__IO uint8_t LED_Red_LockedStatus=0;//红色LED上锁状态 =1代表上锁 =0代表未上锁

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
						
#define LED_Green_Toggle HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1)//控制LED1 IO口翻转接口

#define LED_Red(a)																				 \
						if(a) 																						 \
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_SET);\
						else 																							 \
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_RESET)			

#define LED_Red_Toggle HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0)
						
void Buzzer_GPIO_Init(void)//蜂鸣器IO口初始化
{
   /* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	
	/*电机驱动芯片1对应GPIO引脚配置*/
  GPIO_InitStruct.Pin = GPIO_PIN_5;//设定对应引脚IO编号
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//设定对应引脚IO为输出模式
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW ;//设对应引脚IO操作速度
	GPIO_InitStruct.Pull = GPIO_NOPULL;//内部浮空
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);//初始化对应引脚IO  
}

void LED_Green_GPIO_Init(void)//绿色LED IO口初始化
{
   /* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	
	/*电机驱动芯片1对应GPIO引脚配置*/
  GPIO_InitStruct.Pin = GPIO_PIN_1;//设定对应引脚IO编号
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//设定对应引脚IO为输出模式
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW ;//设对应引脚IO操作速度
	GPIO_InitStruct.Pull = GPIO_NOPULL;//内部浮空
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);//初始化对应引脚IO  
}

void LED_Red_GPIO_Init(void)//红色LED IO口初始化
{
   /* 定义IO硬件初始化结构体变量 */
  GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE();//使能(开启)引脚对应IO端口时钟
	
	/*电机驱动芯片1对应GPIO引脚配置*/
  GPIO_InitStruct.Pin = GPIO_PIN_0;//设定对应引脚IO编号
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//设定对应引脚IO为输出模式
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW ;//设对应引脚IO操作速度
	GPIO_InitStruct.Pull = GPIO_NOPULL;//内部浮空
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);//初始化对应引脚IO  
}

/*-----------------------------------------------------------
函数功能: 蜂鸣器控制函数
输入参数: 报警次数，鸣叫频率
返 回 值: None
说    明: 
参数“Times”是报警次数 
报警次数代表蜂鸣器连续报警的次数，例如该参数为5，代表蜂鸣器会报警5次后停止
该值为0时代表关闭蜂鸣器鸣叫，该值为0xFFFF时代表报警次数无限

参数“PeriodTime”是鸣叫频率 
鸣叫频率代表蜂鸣器鸣叫和不叫的时间周期，例如该参数为5，代表蜂鸣器一次报警中的鸣叫和不叫的时间各为5ms
该值为0时代表关闭蜂鸣器鸣叫，该值为0xFFFF时代表蜂鸣器长鸣
 -----------------------------------------------------------*/
void BuzzerControl(uint16_t Times, uint16_t PeriodTime)//蜂鸣器控制函数
{
	static uint16_t LastTimes=0,LastPeriodTime=0;
	if(LastTimes != Times || LastPeriodTime != PeriodTime || (!Buzzer_Times && !Buzzer_PeriodTime))//防止反复调用该函数导致不正常执行
	{
		LastTimes=Times;
		LastPeriodTime=PeriodTime;
		
		Buzzer_LockedStatus=1;//蜂鸣器上锁状态为1
		
		if(!Times)//报警次数为0
		{
			Buzzer(0);//蜂鸣器不鸣叫
			return;//退出函数
		}
		else if(!PeriodTime)//鸣叫频率为0
		{
			Buzzer(0);//蜂鸣器不鸣叫
			return;//退出函数
		}
		else
		{
			if(PeriodTime == 0xFFFF)//长鸣
			{
				Buzzer(1);//蜂鸣器鸣叫
				return;//退出函数
			}	
			else if(Times == 0xFFFF)//持续报警
			{
				Buzzer(0);//蜂鸣器不鸣叫
				Buzzer_Times =  Times;//赋值0xFFFF
				Buzzer_PeriodTimeBuffer= PeriodTime;//更新缓存蜂鸣器鸣叫频率
				Buzzer_PeriodTime =0;//蜂鸣器鸣叫频率时间清0
			}
			else
			{
				Buzzer(0);//蜂鸣器不鸣叫
				Buzzer_Times =  Times * 2;//蜂鸣器鸣叫次数*2  PS：一开一关为一个周期，因此需要乘2
				Buzzer_PeriodTimeBuffer= PeriodTime;//更新缓存蜂鸣器鸣叫频率
				Buzzer_PeriodTime =0;//蜂鸣器鸣叫频率时间清0
			}
			Buzzer_LockedStatus=0;//蜂鸣器上锁状态为0
		}	
	}
}


/*-----------------------------------------------------------
函数功能: 绿色LED控制函数
输入参数: 闪烁次数，闪烁周期
返 回 值: None
说    明: 
闪烁次数代表LED灯连续闪烁的次数，例如该参数为5，代表LED会闪烁5次后停止，如果该参数为0xFFFF，则代表让LED一直闪烁不停
闪烁周期代表LED灯亮灯和灭灯的时间周期，例如该参数为5，代表LED灯一次闪烁中的灯亮灯和灭灯的时间为5ms，如果该参数为0xFFFF，则代表让LED一直保持亮的状态
 -----------------------------------------------------------*/
void LED_Green_Control(uint16_t Times, uint16_t PeriodTime)//绿色LED控制函数
{
	static uint16_t LastTimes=0,LastPeriodTime=0;
	if(LastTimes != Times || LastPeriodTime != PeriodTime || (!LED_Green_Times && !LED_Green_PeriodTime))//防止反复调用该函数导致不正常执行
	{
		LastTimes=Times;
		LastPeriodTime=PeriodTime;
		
		LED_Green_LockedStatus=1;//绿色LED上锁状态为1
			
		if(!Times)//闪烁次数为0
		{
			LED_Green(0);//绿色LED不亮
			return;//退出函数
		}
		else if(!PeriodTime)//闪烁频率为0
		{
			LED_Green(0);//绿色LED不亮
			return;//退出函数
		}
		else
		{
			if(PeriodTime == 0xFFFF)//常亮
			{
				LED_Green(1);//绿色LED亮
				return;//退出函数
			}	
			else if(Times == 0xFFFF)//持续闪烁
			{
				LED_Green(0);//绿色LED不亮
				LED_Green_Times =  Times;//赋值0xFFFF
				LED_Green_PeriodTimeBuffer= PeriodTime;//更新缓存LED闪烁频率
				LED_Green_PeriodTime =0;//LED闪烁频率时间清0
			}
			else
			{
				LED_Green(0);//绿色LED不亮
				LED_Green_Times =  Times * 2;//LED闪烁次数*2  PS：一开一关为一个周期，因此需要乘2
				LED_Green_PeriodTimeBuffer= PeriodTime;//更新缓存LED闪烁频率
				LED_Green_PeriodTime =0;//LED闪烁频率时间清0
			}
			LED_Green_LockedStatus=0;//LED上锁状态为0
		}	
	}
}

/*-----------------------------------------------------------
函数功能: 红色LED控制函数
输入参数: 闪烁次数，闪烁周期
返 回 值: None
说    明: 
闪烁次数代表LED灯连续闪烁的次数，例如该参数为5，代表LED会闪烁5次后停止，如果该参数为0xFFFF，则代表让LED一直闪烁不停
闪烁周期代表LED灯亮灯和灭灯的时间周期，例如该参数为5，代表LED灯一次闪烁中的灯亮灯和灭灯的时间为5ms，如果该参数为0xFFFF，则代表让LED一直保持亮的状态
 -----------------------------------------------------------*/
void LED_Red_Control(uint16_t Times, uint16_t PeriodTime)//红色LED控制函数
{	
	static uint16_t LastTimes=0,LastPeriodTime=0;
	if(LastTimes != Times || LastPeriodTime != PeriodTime || (!LED_Red_Times && !LED_Red_PeriodTime))//防止反复调用该函数导致不正常执行
	{
		LastTimes=Times;
		LastPeriodTime=PeriodTime;
		
		LED_Red_LockedStatus=1;//红色LED上锁状态为1
		
		if(!Times)//闪烁次数为0
		{
			LED_Red(0);//红色LED不亮
			return;//退出函数
		}
		else if(!PeriodTime)//闪烁频率为0
		{
			LED_Red(0);//红色LED不亮
			return;//退出函数
		}
		else
		{
			if(PeriodTime == 0xFFFF)//常亮
			{
				LED_Red(1);//红色LED亮
				return;//退出函数
			}	
			else if(Times == 0xFFFF)//持续闪烁
			{
				LED_Red(0);//红色LED不亮
				LED_Red_Times =  Times;//赋值0xFFFF
				LED_Red_PeriodTimeBuffer= PeriodTime;//更新缓存LED闪烁频率
				LED_Red_PeriodTime =0;//LED闪烁频率时间清0
			}
			else
			{
				LED_Red(0);//红色LED不亮
				LED_Red_Times =  Times * 2;//LED闪烁次数*2  PS：一开一关为一个周期，因此需要乘2
				LED_Red_PeriodTimeBuffer= PeriodTime;//更新缓存LED闪烁频率
				LED_Red_PeriodTime =0;//LED闪烁频率时间清0
			}
			LED_Red_LockedStatus=0;//LED上锁状态为0
		}	
	}
}

/*-----------------------------------------------------------
函数功能: 指示设备控制函数
输入参数: None
返 回 值: None
说    明: 该函数是控制指示设备的开、关状态，需要将该函数放到
滴答定时器中断函数中运行
 -----------------------------------------------------------*/
void IndicatorDeviceControl(void)
{
	if(Buzzer_PeriodTime) Buzzer_PeriodTime--;//蜂鸣器鸣叫时间
	if(LED_Green_PeriodTime) LED_Green_PeriodTime--;//绿色LED闪烁时间
	if(LED_Red_PeriodTime) LED_Red_PeriodTime--;//红色LED闪速时间
	
	if(!Buzzer_LockedStatus)//蜂鸣器没有上锁才执行
	{
		if(Buzzer_Times && !Buzzer_PeriodTime)//报警次数不为0，鸣叫频率时间为0
		{
			Buzzer_Toggle;//控制蜂鸣器IO口电平翻转
			if(Buzzer_Times != 0xFFFF) Buzzer_Times--;//如果报警次数非无限次则报警次数减1
			Buzzer_PeriodTime = Buzzer_PeriodTimeBuffer;//蜂鸣器鸣叫频率时间重新赋值
		}
	}
	
	/*------------------*/
	if(!LED_Green_LockedStatus)//绿色LED没有上锁才执行
	{
		if(LED_Green_Times && !LED_Green_PeriodTime)//绿色LED闪烁次数不为0，闪烁频率时间为0
		{
			LED_Green_Toggle;//控制绿色LED IO口电平翻转
			if(LED_Green_Times != 0xFFFF) LED_Green_Times--;//如果闪烁次数非无限次则闪烁次数减1
			LED_Green_PeriodTime = LED_Green_PeriodTimeBuffer;//绿色LED闪烁频率时间重新赋值
		}
	}
	
	/*------------------*/
	if(!LED_Red_LockedStatus)//红色LED没有上锁才执行
	{	
		if(LED_Red_Times && !LED_Red_PeriodTime)//红色LED闪烁次数不为0，闪烁频率时间为0
		{
			LED_Red_Toggle;//控制红色LED IO口电平翻转
			if(LED_Red_Times != 0xFFFF) LED_Red_Times--;//如果闪烁次数非无限次则闪烁次数减1
			LED_Red_PeriodTime = LED_Red_PeriodTimeBuffer;//红色LED闪烁频率时间重新赋值
		}
	}
}

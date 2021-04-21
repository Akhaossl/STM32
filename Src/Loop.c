#include "Loop.h"
#include "IndicatorDevice.h"

extern __IO uint16_t Loop_5msTime;//5ms轮询时间
extern __IO uint16_t Loop_10msTime;//10ms轮询时间
extern __IO uint16_t Loop_500msTime;//500ms轮询时间
extern __IO uint16_t HeartbeatTime;//心跳包时间
extern __IO uint64_t EndTime;

extern __IO uint32_t LeftTime1;
extern __IO uint32_t LeftTime2;
extern __IO uint32_t LeftTime3;
extern __IO uint32_t RightTime1;
extern __IO uint32_t RightTime2;
extern __IO uint32_t RightTime3;
extern __IO uint32_t RightTime1;
extern __IO uint32_t ForwardTime1;
extern __IO uint32_t ForwardTime2;
extern __IO uint32_t ForwardTime3;
extern __IO uint32_t StopTime1;
extern __IO uint32_t StopTime2;
extern __IO uint32_t StopTime3;
extern __IO uint32_t BackTime1;
extern __IO uint32_t BackTime2;
extern __IO uint32_t BackTime3;
/*-----------------------------------------------------------
函数功能: 滴答定时器中断函数
输入参数: None
返 回 值: None
说    明: 滴答定时器中断周期为1ms，每隔1ms就会进入一次该函数
 -----------------------------------------------------------*/
void HAL_SYSTICK_Callback()//系统滴答定时器1ms中断函数
{
	if(StopTime1) 		StopTime1--;
	//if(StopTime2) 		StopTime2--;
	//if(StopTime3) 		StopTime3--;
	if(EndTime) 			EndTime--;
	if(LeftTime1) 		LeftTime1--;
	if(LeftTime2)		 	LeftTime2--;
	//if(LeftTime3) 		LeftTime3--;
	if(RightTime1) 		RightTime1--;
	if(RightTime2) 		RightTime2--;
	//if(RightTime3) 		RightTime3--;
	if(ForwardTime1) 	ForwardTime1--;
	if(ForwardTime2) 	ForwardTime2--;
	//if(ForwardTime3) 	ForwardTime3--;
	if(BackTime1) 		BackTime1--;
	if(BackTime2) 		BackTime2--;
	//if(BackTime3) 		BackTime3--;
	if(Loop_5msTime) 	Loop_5msTime--;//5ms轮询时间自减
	if(Loop_10msTime) Loop_10msTime--;//10ms轮询时间自减
	if(Loop_500msTime)Loop_500msTime--;//500ms轮询时间自减
	if(HeartbeatTime) HeartbeatTime--;//心跳包时间自减
	IndicatorDeviceControl();//指示设备控制函数
}

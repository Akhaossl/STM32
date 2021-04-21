#include "Loop.h"
#include "IndicatorDevice.h"

extern __IO uint16_t Loop_5msTime;//5ms��ѯʱ��
extern __IO uint16_t Loop_10msTime;//10ms��ѯʱ��
extern __IO uint16_t Loop_500msTime;//500ms��ѯʱ��
extern __IO uint16_t HeartbeatTime;//������ʱ��
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
��������: �δ�ʱ���жϺ���
�������: None
�� �� ֵ: None
˵    ��: �δ�ʱ���ж�����Ϊ1ms��ÿ��1ms�ͻ����һ�θú���
 -----------------------------------------------------------*/
void HAL_SYSTICK_Callback()//ϵͳ�δ�ʱ��1ms�жϺ���
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
	if(Loop_5msTime) 	Loop_5msTime--;//5ms��ѯʱ���Լ�
	if(Loop_10msTime) Loop_10msTime--;//10ms��ѯʱ���Լ�
	if(Loop_500msTime)Loop_500msTime--;//500ms��ѯʱ���Լ�
	if(HeartbeatTime) HeartbeatTime--;//������ʱ���Լ�
	IndicatorDeviceControl();//ָʾ�豸���ƺ���
}

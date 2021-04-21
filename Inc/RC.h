#ifndef __RC_H
#define __RC_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif

enum RC_Enum
{
	RC_UP=0,		//��ť���ز���
	RC_Middle,	//��ť���ز��м�
	RC_DOWN			//��ť���ز���
};

typedef struct
{		
	__IO float Left_X; //���ҡ��Xֵ����ֵ��Χ -1.0f ~ 1.0f
	__IO float Left_Y; //���ҡ��Yֵ����ֵ��Χ -1.0f ~ 1.0f
	__IO float Right_X;//�Ҳ�ҡ��Xֵ����ֵ��Χ -1.0f ~ 1.0f
	__IO float Right_Y;//�Ҳ�ҡ��Yֵ����ֵ��Χ -1.0f ~ 1.0f
	__IO uint8_t CH5;	 //������ť���أ�[RC_UP������]��[RC_Middle�����м�]��[RC_DOWN������]
	__IO uint16_t CH6;	 //201-1801
	__IO uint8_t ConnectState;//ң���������������״̬ 0=δ���ӣ�1=��������
	
	__IO float Left_X_a;	//���ҡ��Xֵ ������ϵ�� ��ֵ��Χ 0.0f ~ 1.0f 
	__IO float Left_Y_a;	//���ҡ��Yֵ ������ϵ�� ��ֵ��Χ 0.0f ~ 1.0f
	__IO float Right_X_a; //�Ҳ�ҡ��Xֵ ������ϵ�� ��ֵ��Χ 0.0f ~ 1.0f
	__IO float Right_Y_a; //�Ҳ�ҡ��Yֵ ������ϵ�� ��ֵ��Χ 0.0f ~ 1.0f
}RC_Struct;//RCң�����ṹ�����

/*-----------------------------------------------------------
��������: ң�������º���
�������: ң�����ṹ�����
�� �� ֵ: None
˵    ��: �ú������ڴ���DMA�����жϺ����н��е���
 -----------------------------------------------------------*/
void RC_Update(RC_Struct *RC, uint8_t *Data);//ң�������º���

#ifdef __cplusplus
}
#endif

#endif

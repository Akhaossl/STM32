#ifndef __RINGBUFF_H
#define __RINGBUFF_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define ShenChiYan_RingBuff
	 
typedef struct
{
	__IO uint16_t Head;//ͷ��
	__IO uint16_t Tail;//β��
	__IO uint16_t DataLenght;//��ǰ���ݳ���
	__IO uint16_t BufLenght;//���泤��
	__IO uint8_t* Ring_Buff;//�����׵�ַ
	
	/*���λ��������Ᵽ������*/
	__IO uint16_t Count1;
	__IO uint16_t LastCount1;
	__IO uint16_t Count2;
	__IO uint16_t LastCount2;
	__IO uint8_t CoundState;
}RingBuf_Struct;

void RingBuff_Init(RingBuf_Struct *RingBuf, uint16_t BufLeng);//���λ�����������ʼ������
uint8_t RingBuff_Write(RingBuf_Struct *RingBuf, uint8_t *Buff, uint16_t Leng);//�����λ�����д��һ�����ݺ���
uint8_t RingBuff_Read(RingBuf_Struct *RingBuf, uint8_t *Data);//�ӻ��λ�������ȡһ�����ݺ���
void RingBuff_Mutex(RingBuf_Struct *RingBuf);//���λ��������Ᵽ������

#ifdef __cplusplus
}
#endif

#endif

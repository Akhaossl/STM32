#ifndef __RINGBUFF_H
#define __RINGBUFF_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define ShenChiYan_RingBuff
	 
typedef struct
{
	__IO uint16_t Head;//头部
	__IO uint16_t Tail;//尾部
	__IO uint16_t DataLenght;//当前数据长度
	__IO uint16_t BufLenght;//缓存长度
	__IO uint8_t* Ring_Buff;//缓存首地址
	
	/*环形缓存区互斥保护参数*/
	__IO uint16_t Count1;
	__IO uint16_t LastCount1;
	__IO uint16_t Count2;
	__IO uint16_t LastCount2;
	__IO uint8_t CoundState;
}RingBuf_Struct;

void RingBuff_Init(RingBuf_Struct *RingBuf, uint16_t BufLeng);//环形缓冲区参数初始化函数
uint8_t RingBuff_Write(RingBuf_Struct *RingBuf, uint8_t *Buff, uint16_t Leng);//往环形缓冲区写入一组数据函数
uint8_t RingBuff_Read(RingBuf_Struct *RingBuf, uint8_t *Data);//从环形缓冲区读取一个数据函数
void RingBuff_Mutex(RingBuf_Struct *RingBuf);//环形缓存区互斥保护函数

#ifdef __cplusplus
}
#endif

#endif

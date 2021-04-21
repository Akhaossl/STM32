#ifndef __i2c_H
#define __i2c_H
#include "main.h"
#include "ShareWare.h"

#ifdef __cplusplus
 extern "C" {
#endif

extern I2C_HandleTypeDef hi2c1;
extern DMA_HandleTypeDef hdma_i2c1_rx;
extern DMA_HandleTypeDef hdma_i2c1_tx;
extern I2C_HandleTypeDef hi2c1;
extern __IO uint8_t I2C1_Tx_Flag;//I2C1���ݷ�����ɱ�־λ
extern __IO uint8_t I2C1_Rx_Flag;//I2C1���ݽ�����ɱ�־λ

void MX_I2C1_Init(void);

#ifdef __cplusplus
}
#endif

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

#include "mpu6050.h"
#include "ShareWare.h"

/*-----------------------------------------------------------
函数功能: MPU6050初始化函数
输入参数: None
返 回 值: None
说    明: None
 -----------------------------------------------------------*/
void MPU6050_Init(MPU6050_Struct *MPU6050) 
{
	uint8_t I2c1_SenData;
	
	HAL_Delay(100);//等待模块上电启动完成
	
	I2c1_SenData = 0x02;
	I2C1_Tx_Flag = 0;
	HAL_I2C_Mem_Write_IT(&hi2c1, MPU6050_DevAddr, MPU6050_RA_PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &I2c1_SenData, 1);//设置时钟
	while(!I2C1_Tx_Flag){};

	I2c1_SenData = 0x18;
	I2C1_Tx_Flag = 0;
	HAL_I2C_Mem_Write_IT(&hi2c1, MPU6050_DevAddr, MPU6050_RA_GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT, &I2c1_SenData, 1);//陀螺仪最大量程 +-2000度每秒
	while(!I2C1_Tx_Flag){};
		
	I2c1_SenData = 0x00;
	I2C1_Tx_Flag = 0;
	HAL_I2C_Mem_Write_IT(&hi2c1, MPU6050_DevAddr, MPU6050_RA_ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, &I2c1_SenData, 1);//加速度度最大量程 +-2g
	while(!I2C1_Tx_Flag){};
		
	I2c1_SenData = 0x02;
	I2C1_Tx_Flag = 0;
	HAL_I2C_Mem_Write_IT(&hi2c1, MPU6050_DevAddr, MPU6050_RA_PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &I2c1_SenData, 1);//进入工作状态
	while(!I2C1_Tx_Flag){};
		
	MPU6050->Accel_XRaw = 0;//加速度计X轴计原始数值
	MPU6050->Accel_YRaw = 0;//加速度计Y轴计原始数值
	MPU6050->Accel_ZRaw = 0;//加速度计Z轴计原始数值
	MPU6050->TemperatureRaw = 0;//传感器温度原始数值
	MPU6050->Gyro_XRaw = 0;//陀螺仪X轴计原始数值
	MPU6050->Gyro_YRaw = 0;//陀螺仪Y轴计原始数值
	MPU6050->Gyro_ZRaw = 0;//陀螺仪Z轴计原始数值
	
	MPU6050->Accel_X = 0;//加速度计X轴加速度 g
	MPU6050->Accel_Y = 0;//加速度计Y轴加速度 g
	MPU6050->Accel_Z = 0;//加速度计Z轴加速度 g
	
	MPU6050->Gyro_X = 0;//陀螺仪X轴角速度值 rad
	MPU6050->Gyro_Y = 0;//陀螺仪Y轴角速度值 rad
	MPU6050->Gyro_Z = 0;//陀螺仪Z轴角速度值 rad

	MPU6050->Temperature = 0;				//温度值 ℃
}


/*-----------------------------------------------------------
函数功能: 更新MPU原始数值函数
输入参数: MPU6050结构体参数
返 回 值: None
说    明: None
 -----------------------------------------------------------*/
void MPU6050_Update(MPU6050_Struct *MPU6050)
{
	MPU6050->Accel_XRaw = (MPU6050->Buf[0]<<8) + MPU6050->Buf[1];//加速度计X轴计原始数值
	MPU6050->Accel_YRaw = (MPU6050->Buf[2]<<8) + MPU6050->Buf[3];//加速度计X轴计原始数值
	MPU6050->Accel_ZRaw = (MPU6050->Buf[4]<<8) + MPU6050->Buf[5];//加速度计Z轴计原始数值
	MPU6050->TemperatureRaw = (MPU6050->Buf[6]<<8) + MPU6050->Buf[7];//传感器温度原始数值
	MPU6050->Temperature = 36.53 + (float)MPU6050->TemperatureRaw / 340;//传感器温度值
	MPU6050->Gyro_XRaw = (MPU6050->Buf[8]<<8) + MPU6050->Buf[9];	//陀螺仪X轴计原始数值
	MPU6050->Gyro_YRaw = (MPU6050->Buf[10]<<8) + MPU6050->Buf[11];//陀螺仪Y轴计原始数值
	MPU6050->Gyro_ZRaw = (MPU6050->Buf[12]<<8) + MPU6050->Buf[13];//陀螺仪Z轴计原始数值
}

/*-----------------------------------------------------------
函数功能: 更新MPU三轴加速度值函数
输入参数: MPU6050结构体参数
返 回 值: None
说    明: None
 -----------------------------------------------------------*/
void MPU6050_UpdateAccel(MPU6050_Struct *MPU6050)
{
	MPU6050->Accel_X = (float)MPU6050->Accel_XRaw / 1638.375f;//加速度计X轴加速度 m/s^2
	MPU6050->Accel_Y = (float)MPU6050->Accel_YRaw / 1638.375f;//加速度计X轴加速度 m/s^2
	MPU6050->Accel_Z = (float)MPU6050->Accel_ZRaw / 1638.375f;//加速度计X轴加速度 m/s^2
}

/*-----------------------------------------------------------
函数功能: 更新MPU三轴角速度值函数
输入参数: MPU6050结构体参数
返 回 值: None
说    明: None
 -----------------------------------------------------------*/
void MPU6050_UpdateGyro(MPU6050_Struct *MPU6050)
{	
	MPU6050->Gyro_X = (float)MPU6050->Gyro_XRaw / 938.72f;//陀螺仪X轴角速度值 rad
	MPU6050->Gyro_Y = (float)MPU6050->Gyro_YRaw / 938.72f;//陀螺仪Y轴角速度值 rad
	MPU6050->Gyro_Z = (float)MPU6050->Gyro_ZRaw / 938.72f;//陀螺仪Z轴角速度值 rad
}


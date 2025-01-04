#include "encoder.h"
#include <string.h>
#include "main.h"

#ifndef ON
#define ON (1)
#endif
	
#ifndef OFF
#define OFF (0)
#endif


void encoder_Init(volatile Encoder_Class_t *encoder)
{
	memset((void *)encoder,0,sizeof(Encoder_Class_t)); // 初始化编码器
}

/**
* @brief 在中断中回调此函数
*/
void encoderA_Callback(volatile Encoder_Class_t *encoder)
{
	static uint8_t count = 0;
	count++;
	if(encoder->flag.EN_B == OFF)
	{
		encoder->flag.EN_A = ON;
		
		
		if(count % 2 == 0&& encoder->value++ >= ENCODER_MAX)
		{
			count = 0;
			encoder->value = ENCODER_MAX;
		}
	}
	
}

/**
* @brief 在中断中回调此函数
*/
void encoderB_Callback(volatile Encoder_Class_t *encoder)
{
	static uint8_t count = 0;
	count++;
	if(encoder->flag.EN_A == OFF)
	{
		encoder->flag.EN_B = ON;
		
		if(count % 2 == 0 && encoder->value-- <= ENCODER_MAIN)
		{
			count = 0;
			encoder->value = ENCODER_MAIN;
		}
	}
}
/**
*@brief 在主循环中调用此函数
*/
void encoderLoop(volatile Encoder_Class_t *encoder)
{
	if(HAL_GPIO_ReadPin(ENCODER_A_PORT,ENCODER_A_PIN) == RESET 
	   == HAL_GPIO_ReadPin(ENCODER_B_PORT,ENCODER_B_PIN) == RESET)
	{
//		HAL_Delay(20);
//		if(HAL_GPIO_ReadPin(ENCODER_A_PORT,ENCODER_A_PIN) == RESET 
//			&& HAL_GPIO_ReadPin(ENCODER_B_PORT,ENCODER_B_PIN) == RESET)
				memset((void*)&encoder->flag,0,sizeof(encoder_Flag_t));
	}
}

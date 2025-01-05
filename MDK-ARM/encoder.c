#include "encoder.h"
#include <string.h>
// #include "main.h"

#ifndef ON
#define ON (1)
#endif

#ifndef OFF
#define OFF (0)
#endif

/**
 * @brief 初始化编码器
 *
 */
void encoder_Init(volatile Encoder_Class_t *encoder)
{
	memset((void *)&encoder->flag, 0, sizeof(encoder_Flag_t));
//	memset((void *)&encoder->value, 0, sizeof(encoder->value));
	encoder->value = encoder->Range.min;
}

/**
 * @brief 在中断中回调此函数
 */
void encoderA_Callback(volatile Encoder_Class_t *encoder)
{
	static uint8_t count = 0;
	count++;
	encoder->flag.Tigger = ON;
	if (encoder->flag.EN_B == OFF)
	{
		encoder->flag.EN_A = ON;
		encoder->value += encoder->Hardware.Amplitude;
		if (count % 2 == 0 && encoder->value >= encoder->Range.max)
		{
			count = 0;
			encoder->value = encoder->Range.max;
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
	encoder->flag.Tigger = ON;
	if (encoder->flag.EN_A == OFF)
	{
		encoder->flag.EN_B = ON;
		encoder->value -= encoder->Hardware.Amplitude;
		if (count % 2 == 0 && encoder->value <= encoder->Range.min)
		{
			count = 0;
			encoder->value = encoder->Range.min;
		}
	}
}
/**
 *@brief 在主循环中调用此函数
 */
void encoderLoop(volatile Encoder_Class_t *encoder)
{
	uint8_t OK_buff = encoder->flag.EN_OK;
	uint8_t Tigger_buff = encoder->flag.Tigger;
	if ((HAL_GPIO_ReadPin(encoder->Hardware.A.Port, encoder->Hardware.A.Pin) == RESET) == (HAL_GPIO_ReadPin(encoder->Hardware.B.Port, encoder->Hardware.B.Pin) == RESET))
	{
		memset((void *)&encoder->flag, 0, sizeof(encoder_Flag_t));
		encoder->flag.EN_OK = OK_buff;		// 还原C脚状态
		encoder->flag.Tigger = Tigger_buff; // 还原触发状态
	}
}

/**
 * @brief 在C端口中断中回调此函数
 *
 * @param encoder
 */
void encoderOK_Callback(volatile Encoder_Class_t *encoder)
{
	encoder->flag.EN_OK = ON;
}

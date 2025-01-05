#ifndef ENCODER_H
#define ENCODER_H

/**
 * @file encoder.h
 * @brief 旋转编码器驱动 支持多个旋转编码器共存
 *
 * 本文件提供了旋转编码器的驱动接口，用于获取编码器的转动信息。
 * 编码器A、B引脚配置为无上下拉电阻，双边沿触发模式。
 *
 * @author xfp23 (@github.com/xfp23)
 * @note 此驱动支持旋转编码器的A\B\C三个引脚，计数范围在 0x00~0xFFFF 之间可调
 *
 * @date 2025-01-04
 *
 * @version 2.0.1
 *
 * @copyright (c) 2025 xfp23. All rights reserved.
 */

#include <stdint.h>
#include <stdbool.h>
#include "main.h" // 根据自己的芯片选型更改HAL头文件
#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct
	{
		GPIO_TypeDef *Port;
		uint16_t Pin;
	} encoder_Hardware_t;

	typedef struct
	{
		uint16_t max;  // 编码器最大值
		uint16_t min;  // 编码器最小值
	} encoder_Range_t; // 编码器范围

	typedef struct
	{
		uint8_t EN_A : 1;		 // A边
		uint8_t EN_B : 1;		 // 编码器B边
		uint8_t EN_OK : 1;		 // 编码器C脚
		uint8_t Tigger : 1;		 // 编码器A\B边触发标志
		uint8_t Reserve_bit : 4; // 保留位
	} encoder_Flag_t;

	typedef enum
	{
		AMPITUDE_1X = 0X01,
		AMPITUDE_2X = 0X02,
		AMPITUDE_3X = 0X03,
		AMPITUDE_4X = 0X04,
		AMPITUDE_8X = 0X08,
		AMPITUDE_16X = 0X10,
		AMPITUDE_32X = 0X20,
		AMPITUDE_64X = 0X40,
	} encoder_Amplitude_t; // 编码器增益

	typedef struct
	{
		struct
		{
			const encoder_Hardware_t A; // A边硬件
			const encoder_Hardware_t B; // B边硬件
			uint8_t Amplitude;			// 增益
		} Hardware;						// 此结构体用于保存编码器的硬件信息，应该在声明的时候就初始化它
		encoder_Range_t Range;			// 编码器范围
		volatile encoder_Flag_t flag;	// 标志
		volatile uint16_t value;		// 编码器数值

	} Encoder_Class_t;

	/**
	 *@brief 初始化编码器
	 *@note 初始化之前一定要先给对象的硬件信息赋值
	 */
	extern void encoder_Init(volatile Encoder_Class_t *encoder);

	/**
	 *@brief 编码器A边回调，请在对应外部中断中调用
	 */
	extern void encoderA_Callback(volatile Encoder_Class_t *encoder);

	/**
	 *@brief 编码器B边回调，请在对应外部中断中调用
	 */
	extern void encoderB_Callback(volatile Encoder_Class_t *encoder);

	/**
	 *@brief 编码器主循环回调，请在主循环调用
	 */
	extern void encoderLoop(volatile Encoder_Class_t *encoder);

	/**
	 * @brief 在C端口中断中回调此函数
	 */
	extern void encoderOK_Callback(volatile Encoder_Class_t *encoder);
#ifdef __cplusplus
}
#endif

#endif

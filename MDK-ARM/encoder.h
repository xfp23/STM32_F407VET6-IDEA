#ifndef ENCODER_H
#define ENCODER_H

/**
*旋转编码器驱动
*/

#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C"
{
#endif



#define ENCODER_MAX 98 // 编码器最大值
#define ENCODER_MAIN 0 // 编码器最小值	

#define ENCODER_A_PIN ENCODE_A_Pin // 此处更改A边编码器引脚
#define ENCODER_B_PIN ENCODE_B_Pin // 此处更改B边编码器引脚
	
#define ENCODER_A_PORT  GPIOB // 此处更改A边编码器引脚端口
#define ENCODER_B_PORT GPIOB // 此处更改B边编码器引脚端口

typedef struct 
{
	uint8_t EN_A :1; // A边
	uint8_t EN_B :1; // 编码器B边
	uint8_t Reserve_bit :6; // 保留位
}encoder_Flag_t;
	
	
typedef struct {
	encoder_Flag_t flag; // 标志
	uint16_t value; // 编码器数值
}Encoder_Class_t;
	
/**
*@brief 初始化编码器
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


#ifdef __cplusplus
}
#endif

#endif

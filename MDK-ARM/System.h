#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <stdbool.h>
#include "encoder.h"

typedef struct {
	uint8_t UART_buff[64];
	const uint8_t BUFF_SIZE;
	bool UART_FLAG;
}System_Class;

extern System_Tim_Flag systemTim;
extern void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle);
extern  Encoder_Class_t encoder;

extern System_Class System;

extern void init_system(void);
extern void DealWith_UART(void);
#endif


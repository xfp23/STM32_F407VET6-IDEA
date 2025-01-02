#include "System.h"
#include <string.h>
#include <stdio.h>
#include "usart.h"
 System_Class System = {
	.BUFF_SIZE = 64
};
/**
*@brief 系统初始化
*/
void init_system()
{
	
	memset((void *)System.UART_buff,0,64);
	System.UART_FLAG = false;
}

/**
*@brief 处理串口的逻辑
*/
void DealWith_UART()
{
	if(System.UART_FLAG == true)
	{
		//HAL_Delay(100);
		
		//printf("%s",System.UART_buff);
		
		HAL_UART_Transmit(&huart1,System.UART_buff,strlen((char *)System.UART_buff),HAL_MAX_DELAY);
		HAL_GPIO_TogglePin(USER_LED_GPIO_Port,USER_LED_Pin);
		memset((void *)System.UART_buff,0,System.BUFF_SIZE);
		System.UART_FLAG = false;
	}
}



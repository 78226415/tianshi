/***********************************************************************
文件名称：
功    能：
编写时间：
编 写 人：
注    意：
***********************************************************************/
#include "led.h"   
#include "SCI.h"
#include "NVIC.h"
#include "yidaosensor.h"
#include "adc.h"
/*
 * 功能：
 *       板级初始化
 * 参数：
 *       无
 * 返回：
 *       无
 * 说明：
 *       可用与模块中初始化的尽量使用模块初始化
 */
void BSP_Init(void)
{
	LED_Configuration();
	Sensor_Init();
	//USART_485_Configuration();	
	NVIC_Configuration();
	//RS485_DMA_Init();
	USART_232_Configuration();	
	//RS232_DMA_Init();
	//CAN1_Configuration();
	//CAN2_Configuration();
	Adc_Init();
	qj005_uart_init();
}


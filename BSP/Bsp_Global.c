/***********************************************************************
�ļ����ƣ�
��    �ܣ�
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/
#include "led.h"   
#include "SCI.h"
#include "NVIC.h"
#include "yidaosensor.h"
#include "adc.h"
/*
 * ���ܣ�
 *       �弶��ʼ��
 * ������
 *       ��
 * ���أ�
 *       ��
 * ˵����
 *       ������ģ���г�ʼ���ľ���ʹ��ģ���ʼ��
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


/***********************************************************************
文件名称：SCI.h
功    能：
编写时间：2012.11.22
编 写 人：
注    意：
***********************************************************************/
#include "stdint.h"
#include "stm32f4xx.h"	

#ifndef  _SCI_H_
#define  _SCI_H_

#define RS485_REC_BUFF_SIZE				1024
#define RS_485_RX_EN 	GPIO_ResetBits(GPIOD , GPIO_Pin_7)	//接收使能
#define RS_485_TX_EN 	GPIO_SetBits(GPIOD , GPIO_Pin_7)  	//发送使能

extern volatile unsigned char RS485_REC_Flag ;
extern volatile unsigned char RS485_buff[RS485_REC_BUFF_SIZE] ;//用于接收数据
extern volatile unsigned int RS485_rec_counter ;//用于RS485接收计数

extern unsigned short RS485_send_data_length;

#define RS232_REC_BUFF_SIZE				1024

extern volatile unsigned char RS232_REC_Flag ;
extern volatile unsigned char RS232_buff[RS232_REC_BUFF_SIZE] ;//用于接收数据
extern volatile unsigned int RS232_rec_counter ;//用于RS232接收计数

extern unsigned short RS232_send_data_length;
void RS485_Send_Data(unsigned char *send_buff,unsigned int length);
void RS485_DMA_Send(unsigned char *send_buff,unsigned int length);
void USART_485_Configuration(void);
static void RS485_Delay(uint32_t nCount);

void RS232_Send_Data(unsigned char *send_buff,unsigned int length);
void RS232_DMA_Send(unsigned char *send_buff,unsigned int length);
void USART_232_Configuration(void);
static void RS232_Delay(uint32_t nCount);

#endif




void qj005_send_data(char send_buff[]);//void qj005_send_data(unsigned char *send_buff,unsigned int length);
void qj005_uart_init(void);
void send_mp3_command(u8 comand, char* file_name);

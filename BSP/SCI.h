/***********************************************************************
�ļ����ƣ�SCI.h
��    �ܣ�
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
***********************************************************************/
#include "stdint.h"
#include "stm32f4xx.h"	

#ifndef  _SCI_H_
#define  _SCI_H_

#define RS485_REC_BUFF_SIZE				1024
#define RS_485_RX_EN 	GPIO_ResetBits(GPIOD , GPIO_Pin_7)	//����ʹ��
#define RS_485_TX_EN 	GPIO_SetBits(GPIOD , GPIO_Pin_7)  	//����ʹ��

extern volatile unsigned char RS485_REC_Flag ;
extern volatile unsigned char RS485_buff[RS485_REC_BUFF_SIZE] ;//���ڽ�������
extern volatile unsigned int RS485_rec_counter ;//����RS485���ռ���

extern unsigned short RS485_send_data_length;

#define RS232_REC_BUFF_SIZE				1024

extern volatile unsigned char RS232_REC_Flag ;
extern volatile unsigned char RS232_buff[RS232_REC_BUFF_SIZE] ;//���ڽ�������
extern volatile unsigned int RS232_rec_counter ;//����RS232���ռ���

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

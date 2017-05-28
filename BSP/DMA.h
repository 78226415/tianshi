/***********************************************************************
�ļ����ƣ�DMA.H
��    �ܣ�
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/
#ifndef _DMA_H_
#define _DMA_H_


extern volatile unsigned char RS232_dma_send_flag;
extern volatile unsigned char RS485_dma_send_flag;
void RS232_DMA_Init(void);
void DMA_RS232_Send_Configuration(unsigned char *send_buff,unsigned int send_size);
void RS485_DMA_Init(void);
void DMA_RS485_Send_Configuration(unsigned char *send_buff,unsigned int send_size);
#endif
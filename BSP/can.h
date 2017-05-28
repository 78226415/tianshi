/***********************************************************************
�ļ����ƣ�CAN.H
��    �ܣ�
��дʱ�䣺2013.4.25
�� д �ˣ�
ע    �⣺
***********************************************************************/
#ifndef _CAN_H_
#define _CAN_H_

#define CAN_BAUD_NUM    18		//�������ò����ʸ���

extern unsigned char CAN1_data[8];
extern unsigned char can1_rec_flag;
extern unsigned char CAN2_data[8];
extern unsigned char can2_rec_flag;

void CAN1_Configuration(void);
void CAN2_Configuration(void);
void CAN1_WriteData(unsigned int ID);
void CAN2_WriteData(unsigned int ID);
void CAN_Baud_Process(unsigned int Baud,CAN_InitTypeDef *CAN_InitStructure);
#endif

/***********************************************************************
�ļ����ƣ�
��    �ܣ�
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/
 
#ifndef _MAIN_H_
#define _MAIN_H_


//��ӱ�Ҫ��ͷ�ļ�
#include "M_Type_P.h"
#include "Bsp_Global.h"
#include "M_Global.h"
#include "Task_Startup.h"
#include "Task_Test.h"
/*
#include "M_Type_P.h"
#include "M_CMSIS_P.h" 


#include "led.h"   
#include "SCI.h"
#include "DMA.h"
#include "NVIC.h"
#include "yidaosensor.h"
*/
//ET Module�汾��
#define M_VERSION	100


//1��Ƭ������ 

#define M_DEV_MCU   1

//ȫ�ֳ�ʼ����������
void M_Global_init(void);


//////////////////////////////////////////////////////////////////////////
/////////////////////////���°�����ͬģ���ͷ�ļ�/////////////////////////
//////////////////////////////////////////////////////////////////////////

//����ʱ����
#include "M_Delay_P.h"




#endif

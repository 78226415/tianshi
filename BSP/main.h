/***********************************************************************
文件名称：
功    能：
编写时间：
编 写 人：
注    意：
***********************************************************************/
 
#ifndef _MAIN_H_
#define _MAIN_H_


//添加必要的头文件
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
//ET Module版本号
#define M_VERSION	100


//1单片机环境 

#define M_DEV_MCU   1

//全局初始化函数声明
void M_Global_init(void);


//////////////////////////////////////////////////////////////////////////
/////////////////////////以下包含不同模块的头文件/////////////////////////
//////////////////////////////////////////////////////////////////////////

//软延时函数
#include "M_Delay_P.h"




#endif

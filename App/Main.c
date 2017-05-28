/***********************************************************************
文件名称：main.C
功    能：
编写时间：
编 写 人：
注    意：
***********************************************************************/
#include "main.h"


int main(void)
{
	//初始化板子
	BSP_Init();
	//初始化系统
	OSInit();
	//创建启动任务
	OSTaskCreate(	Task_StartUp,               		    				//指向任务代码的指针
                  	(void *) 0,												//任务开始执行时，传递给任务的参数的指针
					(OS_STK *)&Stk_TaskStartUp[TASK_STARTUP_STK_SIZE - 1],	//分配给任务的堆栈的栈顶指针   从顶向下递减
					(INT8U) OS_USER_PRIO_LOWEST);							//分配给任务的优先级  

	//节拍计数器清0  
	OSTimeSet(0);

	//启动UCOS-II内核
	OSStart();
	while (1);
	return 0;
}
//启动任务堆栈
OS_STK Stk_TaskStartUp[TASK_STARTUP_STK_SIZE];
/*
 * 功能：
 *       启动任务
 * 参数：
 *       void *pdata 任务额外参数
 * 返回：
 *       无
 * 说明：
 *       无
 */
void Task_StartUp(void *pdata)
{

	//初始化UCOS时钟
	//OS_TICKS_PER_SEC 为 UCOS-II 每秒嘀嗒数
	SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC - 1);

	//优先级说明，使用OS_USER_PRIO_GET(n)宏来获取
	//OS_USER_PRIO_GET(0)最高,OS_USER_PRIO_GET(1)次之，依次类推
	//OS_USER_PRIO_GET(0)：最高的优先级，主要用于在处理紧急事务，需要将优先处理的任务设置为最高这个优先级  

	//创建任务时，请将测试任务A和B删除
	//并将每个任务放于App文件夹中并以Task_Xxx.c和Task_Xxx.h文件命名
	//将任务的头文件统一添加至App/App_Inc.h文件

	//OSTaskCreate(	Task_Xxx,               		    					//指向任务代码的指针
    //              (void *)0,												//任务开始执行时，传递给任务的参数的指针
	//				(OS_STK *)&Stk_TaskXxx[TASK_XXX_STK_SIZE - 1],			//分配给任务的堆栈的栈顶指针   从顶向下递减
	//				(INT8U) OS_USER_PRIO_GET(N));							//分配给任务的优先级  
	
	//建立两个测试任务
	
	OSTaskCreate(Task_RS232, (void *)0, &Stk_Task_RS232[TASK_TEST_RS232_STK_SIZE-1], OS_USER_PRIO_GET(3));
	OSTaskCreate(Task_SenSor, (void *)0, &Stk_sensor[TASK_TEST_CAN2_STK_SIZE-1], OS_USER_PRIO_GET(4));
  OSTaskCreate(Task_LED, (void *)0, &Stk_Task_LED[TASK_TEST_LED_STK_SIZE-1], OS_USER_PRIO_GET(5));    					  
	while (1)
	{
		//循环看守程序执行情况
		//通常情况下这里使一个系统状态灯闪烁，表示系统正在运行
		OSTimeDlyHMSM(0, 0, 1, 0);//1000ms
	}
}

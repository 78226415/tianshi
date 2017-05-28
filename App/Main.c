/***********************************************************************
�ļ����ƣ�main.C
��    �ܣ�
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/
#include "main.h"


int main(void)
{
	//��ʼ������
	BSP_Init();
	//��ʼ��ϵͳ
	OSInit();
	//������������
	OSTaskCreate(	Task_StartUp,               		    				//ָ����������ָ��
                  	(void *) 0,												//����ʼִ��ʱ�����ݸ�����Ĳ�����ָ��
					(OS_STK *)&Stk_TaskStartUp[TASK_STARTUP_STK_SIZE - 1],	//���������Ķ�ջ��ջ��ָ��   �Ӷ����µݼ�
					(INT8U) OS_USER_PRIO_LOWEST);							//�������������ȼ�  

	//���ļ�������0  
	OSTimeSet(0);

	//����UCOS-II�ں�
	OSStart();
	while (1);
	return 0;
}
//���������ջ
OS_STK Stk_TaskStartUp[TASK_STARTUP_STK_SIZE];
/*
 * ���ܣ�
 *       ��������
 * ������
 *       void *pdata ����������
 * ���أ�
 *       ��
 * ˵����
 *       ��
 */
void Task_StartUp(void *pdata)
{

	//��ʼ��UCOSʱ��
	//OS_TICKS_PER_SEC Ϊ UCOS-II ÿ�������
	SysTick_Config(SystemCoreClock/OS_TICKS_PER_SEC - 1);

	//���ȼ�˵����ʹ��OS_USER_PRIO_GET(n)������ȡ
	//OS_USER_PRIO_GET(0)���,OS_USER_PRIO_GET(1)��֮����������
	//OS_USER_PRIO_GET(0)����ߵ����ȼ�����Ҫ�����ڴ������������Ҫ�����ȴ������������Ϊ���������ȼ�  

	//��������ʱ���뽫��������A��Bɾ��
	//����ÿ���������App�ļ����в���Task_Xxx.c��Task_Xxx.h�ļ�����
	//�������ͷ�ļ�ͳһ�����App/App_Inc.h�ļ�

	//OSTaskCreate(	Task_Xxx,               		    					//ָ����������ָ��
    //              (void *)0,												//����ʼִ��ʱ�����ݸ�����Ĳ�����ָ��
	//				(OS_STK *)&Stk_TaskXxx[TASK_XXX_STK_SIZE - 1],			//���������Ķ�ջ��ջ��ָ��   �Ӷ����µݼ�
	//				(INT8U) OS_USER_PRIO_GET(N));							//�������������ȼ�  
	
	//����������������
	
	OSTaskCreate(Task_RS232, (void *)0, &Stk_Task_RS232[TASK_TEST_RS232_STK_SIZE-1], OS_USER_PRIO_GET(3));
	OSTaskCreate(Task_SenSor, (void *)0, &Stk_sensor[TASK_TEST_CAN2_STK_SIZE-1], OS_USER_PRIO_GET(4));
  OSTaskCreate(Task_LED, (void *)0, &Stk_Task_LED[TASK_TEST_LED_STK_SIZE-1], OS_USER_PRIO_GET(5));    					  
	while (1)
	{
		//ѭ�����س���ִ�����
		//ͨ�����������ʹһ��ϵͳ״̬����˸����ʾϵͳ��������
		OSTimeDlyHMSM(0, 0, 1, 0);//1000ms
	}
}

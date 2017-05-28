/***********************************************************************
�ļ����ƣ�
��    �ܣ�
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/
#ifndef _APP_TASK_TEST_H_
#define _APP_TASK_TEST_H_

#define TASK_TEST_LED_STK_SIZE	400
#define TASK_TEST_RS485_STK_SIZE	400
extern OS_EVENT  *sem_RS485_rec_flag;			//RS485������һ�������ź�������

extern OS_STK Stk_Task_LED[TASK_TEST_LED_STK_SIZE];
extern OS_STK Stk_Task_RS485[TASK_TEST_RS485_STK_SIZE];


#define TASK_TEST_LED_STK_SIZE	400
#define TASK_TEST_RS232_STK_SIZE	400
extern OS_EVENT  *sem_RS232_rec_flag;			//RS232������һ�������ź�������

extern OS_STK Stk_Task_LED[TASK_TEST_LED_STK_SIZE];
extern OS_STK Stk_Task_RS232[TASK_TEST_RS232_STK_SIZE];


#define TASK_TEST_CAN1_STK_SIZE	400
#define TASK_TEST_CAN2_STK_SIZE	400



extern OS_STK Stk_sensor[TASK_TEST_CAN2_STK_SIZE];

extern OS_EVENT  *sem_CAN1_rec_flag;			//CAN1������һ�������ź�������
extern OS_EVENT  *sem_CAN2_rec_flag;			//CAN2������һ�������ź�������

extern OS_STK Stk_Task_CAN1[TASK_TEST_CAN1_STK_SIZE];
extern OS_STK Stk_Task_CAN2[TASK_TEST_CAN2_STK_SIZE];
extern OS_EVENT  *sem_CAN1_rec_flag;			//CAN1������һ�������ź�������
extern OS_EVENT  *sem_CAN2_rec_flag;			//CAN2������һ�������ź�������


void Task_LED(void *pdata);
void Task_RS232(void *pdata);
void Task_LED(void *pdata);
void Task_RS485(void *pdata);
void Task_CAN1(void *pdata);
void Task_CAN2(void *pdata);
void Task_SenSor(void *pdata);
#endif

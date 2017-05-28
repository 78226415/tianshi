/***********************************************************************
�ļ����ƣ�
��    �ܣ�
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/

#include "M_Global.h"
#include "Task_Test.h"
#include "led.h"   
#include "SCI.h"
#include "yidaosensor.h"
#include "adc.h"
#include <stdio.h>
#include <stdlib.h> //
#include <time.h>

#define random(x) (rand()%x)
extern u8 qj005_play_state;
u8 is_play_end = 0;
OS_STK Stk_Task_LED[TASK_TEST_LED_STK_SIZE];
//OS_STK Stk_Task_RS485[TASK_TEST_RS485_STK_SIZE];
//OS_EVENT  *sem_RS485_rec_flag;			//RS485������һ�������ź�������
OS_STK Stk_Task_RS232[TASK_TEST_RS232_STK_SIZE];
//OS_EVENT  *sem_RS232_rec_flag;			//RS232������һ�������ź�������
OS_EVENT   *sqSendMsg;
//OS_STK Stk_Task_CAN1[TASK_TEST_CAN1_STK_SIZE];
OS_STK Stk_sensor[TASK_TEST_CAN2_STK_SIZE];

u8 play_level_type = 100; //
//OS_EVENT  *sem_CAN1_rec_flag;			//CAN1������һ�������ź�������
//OS_EVENT  *sem_CAN2_rec_flag;			//CAN2������һ�������ź�������

/***********************************************************************
�������ƣ�void Task_LED(void *pdata)
��    �ܣ�
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/
void Task_LED(void *pdata)
{		 
    while(1)
	{
		OSTimeDlyHMSM(0, 0, 0, 100);//
		GPIO_ToggleBits(LED1);
		OSTimeDlyHMSM(0, 0, 0, 100);//
		GPIO_ToggleBits(LED2);
		OSTimeDlyHMSM(0, 0, 0, 100);//
		GPIO_ToggleBits(LED3);
		OSTimeDlyHMSM(0, 0, 0, 100);//
		GPIO_ToggleBits(LED4);
	}
}

void play_mp3(u8 play_level, char *file_name)
{
	if(play_level_type > play_level && play_level_type > 100)
	{
		if(qj005_play_state == 1)
		{
			char stop_cmd_buf[] = {0x7E, 0x03, 0x15, 0x18, 0xEF};//
			qj005_send_data(stop_cmd_buf);
			//�˴�Ϊֹͣ���ű������
			OSTimeDlyHMSM(0, 0, 0, 50);//50ms
		}
			
		play_level_type = play_level;
		send_mp3_command(0x44, file_name);
		is_play_end = 0;
		//�˴����ű������
	}
}

/***********************************************************************
�������ƣ�void Task_RS485(void *pdata)
��    �ܣ�
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/
void Task_RS232(void *pdata)
{		 
   unsigned  char  os_err;
	YindaoSensor *sensorv;
	unsigned char Rs232buf[9];
	Rs232buf[0]='A';
	Rs232buf[8]='B';
	sqSendMsg=OSMboxCreate(0);
	
	uint64_t sex_go_on_seconds = 0;//
	int sex_go_gap_remain_seconds = 0;//
	int sex_go_gap_seconds = 60;//
	int cunt_depth_last = 0;//
	int cunt_depth_current = 0;//
	int max_cunt_depth = 4;//
	int screaming_cooling_remain_seconds = 0;//
	int screaming_cooling_seconds = 30;//
	int orgasm_cooling_remain_seconds = 0;//
	int orgasm_cooling_seconds = 90;//
	int loop_rate = 20;//ÿ����ѭ���˶��ٴ�
	int sex_start_segment_seconds = 60;//
	u8 play_end_count = 0;//��¼����mp3�������ʱ�䣬�����¼����mp3����2����л��������ֻ�����
	u8 mouth_play_count = 0;//��Ͷ���ִ�е�������
	u8 eyelids_play_count = 60;//�۾�����ִ�е�������
	//srand(time(0));//srand((unsigned)time(NULL));
	
	while(1)
	{
		sensorv=OSMboxPend(sqSendMsg,0,&os_err);	 //�����ȴ�sqSendMsg�ź�����Ч	
		{
			/*
			if (sensorv->cunt_pro_touch==Bit_SET) Rs232buf[1]='0'; else Rs232buf[1]='1';
			Rs232buf[2]=';';
			
			if (sensorv->cunt_vot1_touch==Bit_SET) Rs232buf[3]='0'; else Rs232buf[3]='1';
			Rs232buf[4]=';';
			
			if (sensorv->cunt_vot2_touch==Bit_SET) Rs232buf[5]='0'; else Rs232buf[5]='1';
			Rs232buf[6]=';';
			
			if (sensorv->cunt_vot3_touch==Bit_SET) Rs232buf[7]='0'; else Rs232buf[7]='1';

			RS232_Send_Data(Rs232buf,9); 	//�����յ������ݷ��ͳ�ȥ
			*/
			if(eyelids_play_count > 0)
			{
				eyelids_play_count -= 1;
			}
			
			if(play_level_type == 50)
			{
				mouth_play_count += 1;
			}
			//��������ź�ʱ��Ϊ500����
			if(mouth_play_count >= 10 && play_level_type == 50)
			{
				play_level_type = 100;
			}
			
			if(is_play_end == 1)
			{
				play_end_count += 1;
			}
			//2����л���Ƶ�ź�
			if(play_end_count >= 40)
			{
				is_play_end = 0;
				//�˴�Ϊ����Ƶ�ź��л����ֻ�����
			}
			
			if(qj005_play_state == 2)
			{
				play_level_type = 100;
				qj005_play_state = 0;
				is_play_end = 1;
				play_end_count = 0;
			}
			
			if(sensorv->cunt_pro_touch > 0)
			{
				cunt_depth_current = 1;
			}
			
			if(sensorv->cunt_vot1_touch > 0)
			{
				cunt_depth_current = 2;
			}
			
			if(sensorv->cunt_vot2_touch > 0)
			{
				cunt_depth_current = 3;
			}
			
			if(sensorv->cunt_vot3_touch > 0)
			{
				cunt_depth_current = 4;
			}
			
			if(cunt_depth_current > 0)
			{
				sex_go_gap_remain_seconds = sex_go_gap_seconds * loop_rate;
			}
			
			//
			if(cunt_depth_last != cunt_depth_current && cunt_depth_current == max_cunt_depth && orgasm_cooling_remain_seconds == 0 && sex_go_on_seconds > sex_start_segment_seconds * loop_rate)
			{
				if(play_level_type > 8)
				{
					orgasm_cooling_remain_seconds = orgasm_cooling_seconds * loop_rate;
					play_level_type = 8;
					play_mp3(play_level_type, "sextop-out");//������Чsex/top-out.mp3
					//���ű���
				}
			}
			else if(cunt_depth_last != cunt_depth_current && cunt_depth_current == max_cunt_depth && screaming_cooling_remain_seconds == 0) //
			{
				if(play_level_type > 9)
				{
					screaming_cooling_remain_seconds = screaming_cooling_seconds * loop_rate;
					play_level_type = 9;
					u8 r = (random(9) + 1);
					char rand_string[20];
					sprintf(rand_string,"%d",r);
					char* mp3_file = {"sextop-depth-"};
					strcat(mp3_file, rand_string);
					play_mp3(play_level_type, mp3_file);//���������Чsex/top-depth-.mp3
					//���ű���
				}
			}
			else if(sensorv->cunt_pro_touch_frec >= 4 || sensorv->cunt_vot1_touch_frec >= 4 || sensorv->cunt_vot2_touch_frec >= 4 || sensorv->cunt_vot3_touch_frec >= 4)//
			{
				if(play_level_type > 10)
				{
					play_level_type = 10;
					u8 r = (random(32) + 1);
					char rand_string[20];
					sprintf(rand_string,"%d",r);
					char* mp3_file = {"sexfrequency-"};
					strcat(mp3_file, rand_string);
					play_mp3(play_level_type, mp3_file);//���������Чfrequency-.mp3
					//���ű���
				}
			}
			else if(sensorv->cunt_pro_touch_frec > 0 || sensorv->cunt_vot1_touch_frec > 0 || sensorv->cunt_vot2_touch_frec > 0 || sensorv->cunt_vot3_touch_frec > 0)
			{
				if(sex_go_on_seconds < sex_start_segment_seconds * loop_rate)
				{
					if(play_level_type > 10)
					{
						play_level_type = 10;
						u8 r = (random(13) + 1);
						char rand_string[20];
						sprintf(rand_string,"%d",r);
						char* mp3_file = {"sexstart-"};
						strcat(mp3_file, rand_string);
						play_mp3(play_level_type, mp3_file);//���������Чstart-.mp3
						//���ű���
					}
				}
				else
				{
					if(play_level_type > 10)
					{
						play_level_type = 10;
						u8 r = (random(73) + 1);
						char rand_string[20];
						sprintf(rand_string,"%d",r);
						char* mp3_file = {"sexhigh-"};
						strcat(mp3_file, rand_string);
						play_mp3(play_level_type, mp3_file);//���������Чhigh-.mp3
						//���ű���
					}
				}
			}
			else if(sensorv->boob_left_vot_touch == 1 || sensorv->boob_right_vot_touch == 1)//
			{
				if(play_level_type > 10)
				{
					play_level_type = 10;
					u8 r = (random(7) + 1);
					char rand_string[20];
					sprintf(rand_string,"%d",r);
					char* mp3_file = {"sexgroan-high-"};
					strcat(mp3_file, rand_string);
					play_mp3(play_level_type, mp3_file);//���������Чgroan-high-.mp3
					//���ű���
				}
			}
			else if(sensorv->boob_left_pro_touch == 1 || sensorv->boob_right_pro_touch == 1)//
			{
				if(play_level_type > 10)
				{
					play_level_type = 10;
					u8 r = (random(7) + 1);
					char rand_string[20];
					sprintf(rand_string,"%d",r);
					char* mp3_file = {"sexgroan-"};
					strcat(mp3_file, rand_string);
					play_mp3(play_level_type, mp3_file);//���������Чgroan-.mp3
					//���ű���
				}
			}
			
			if(play_level_type == 100 && sensorv->voice > 1000)
			{
				play_level_type = 50;
				mouth_play_count = 0;
				//��Ͷ���
			}
			
			if(eyelids_play_count == 0 && play_level_type >= 50)
			{
				//գ�۶���
				
				if(play_level_type == 100)
				{
					eyelids_play_count = (random(6) + 1) * 20;//��ʱ��1-6��գ��һ��
				}
				else if(play_level_type == 50)
				{
					eyelids_play_count = (random(3) + 1) * 20;//���죺1-3��գ��һ��
				}
			}
			

			cunt_depth_last = cunt_depth_current;
		}
		
		//
		if(sex_go_gap_remain_seconds > 0)
		{
			sex_go_on_seconds += 1;
			//
			if(sex_go_on_seconds > sex_start_segment_seconds * loop_rate && orgasm_cooling_remain_seconds == 0  
				&& sex_go_gap_remain_seconds == sex_go_gap_seconds * loop_rate - 1)
			{
				if(play_level_type > 8)
				{
					orgasm_cooling_remain_seconds = orgasm_cooling_seconds * loop_rate;
					play_level_type = 8;
					play_mp3(play_level_type, "sextop-out");//������Чsex/top-out.mp3
					//���ű���
				}
			}
			
			sex_go_gap_remain_seconds -= 1;
			//
			if(sex_go_gap_remain_seconds == 0)
			{
				sex_go_on_seconds = 0;
			}
		}
		//
		if(screaming_cooling_remain_seconds > 0)
		{
			screaming_cooling_remain_seconds -= 1;
		}
		//
		if(orgasm_cooling_remain_seconds > 0)
		{
			orgasm_cooling_remain_seconds -= 1;
		}
	}
}

/***********************************************************************
�������ƣ�void Task_SenSor(void *pdata)
��    �ܣ�
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺
***********************************************************************/
void Task_SenSor(void *pdata)
{		 
    //unsigned  char  os_err;
	YindaoSensor sensorv;
	memset(&sensorv,0,sizeof(sensorv));
	while(1)
	{  
		GetSensorV(&sensorv);
		OSMboxPost(sqSendMsg,&sensorv);
		OSTimeDlyHMSM(0, 0, 0, 50);//50ms
	}
}

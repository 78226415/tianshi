#include "stdio.h"	
#include "stm32f4xx_conf.h"

u8 play_state = 0;//����״̬��1�����ڲ��ţ�2�����Ž���
void qj005_send_data(unsigned char *send_buff,unsigned int length);
void qj005_uart_init();



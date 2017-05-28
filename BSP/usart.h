#include "stdio.h"	
#include "stm32f4xx_conf.h"

u8 play_state = 0;//播放状态，1：正在播放，2：播放结束
void qj005_send_data(unsigned char *send_buff,unsigned int length);
void qj005_uart_init();




/***********************************************************************
文件名称：SCI.C
功    能：完成对usart1和usart2的操作
编写时间：2012.11.22
编 写 人：
注    意：
***********************************************************************/

#include "M_Global.h"
#include "SCI.h"
#include "DMA.h"

volatile unsigned char RS485_REC_Flag = 0;
volatile unsigned char RS485_buff[RS485_REC_BUFF_SIZE];//用于接收数据
volatile unsigned int RS485_rec_counter = 0;//用于RS485接收计数

unsigned short RS485_send_data_length = 0;

volatile unsigned char RS232_REC_Flag = 0;
volatile unsigned char RS232_buff[RS232_REC_BUFF_SIZE];//用于接收数据
volatile unsigned int RS232_rec_counter = 0;//用于RS232接收计数

unsigned short RS232_send_data_length = 0;

/***********************************************************************
函数名称：void USART_232_Configuration(void) 
功    能：
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：RS232用的是USART1
***********************************************************************/
void USART_232_Configuration(void)
{ 
  
	GPIO_InitTypeDef GPIO_InitStructure;//定义GPIO_InitTypeDef类型的结构体成员GPIO_InitStructure

	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	//使能需要用到的GPIO管脚时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOD, ENABLE);
	//使能USART1 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	///复位串口1
	USART_DeInit(USART1);
	
	USART_StructInit(&USART_InitStructure);//载入默认USART参数
	USART_ClockStructInit(&USART_ClockInitStruct);//载入默认USART参数        
	//配置串口1的管脚 PA8 USART1_EN PA9 USART1_TX PA10 USART1_RX    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    //复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);        //管脚PA9复用为USART1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;        
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                                                                                                 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	USART_ClockInit(USART1,&USART_ClockInitStruct);


	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	//USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Mode =  USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure); 
	
//	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);  
//	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);
// 	USART_ITConfig(USART1, USART_IT_TC, ENABLE);// 
	
// 	//采用DMA方式发送  
// 	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  
	//采用DMA方式接收  
//	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE); 
	
	
	USART_Cmd(USART1, ENABLE); 
//	USART_ClearITPendingBit(USART1, USART_IT_TC);//清除中断TC位	

}
/***********************************************************************
函数名称：void USART_485_Configuration(void) 
功    能：
输入参数：
输出参数：
编写时间：
编 写 人：
注    意：RS485用的是USART2
***********************************************************************/
void USART_485_Configuration(void)
{ 
  
	GPIO_InitTypeDef GPIO_InitStructure;//定义GPIO_InitTypeDef类型的结构体成员GPIO_InitStructure
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	//使能需要用到的GPIO管脚时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);
	USART_DeInit(USART2);	//USART2为RS232
	USART_StructInit(&USART_InitStructure);//载入默认USART参数
	USART_ClockStructInit(&USART_ClockInitStruct);//载入默认USART参数        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    //复用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);        //管脚PA9复用为USART1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;        
	GPIO_Init(GPIOD, &GPIO_InitStructure);                                                                                                                 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
	
	USART_ClockInit(USART2,&USART_ClockInitStruct);


	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_9b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_Even;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2,&USART_InitStructure); 

	USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);  
	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);
// 	USART_ITConfig(USART2, USART_IT_TC, ENABLE);// 
	
// 	//采用DMA方式发送  
// 	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);  
	//采用DMA方式接收  
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); 
	
	
	USART_Cmd(USART2, ENABLE); 
	USART_ClearITPendingBit(USART2, USART_IT_TC);//清除中断TC位	
	
/***********************************GPIO_Pin_7，RS485方向控制******************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
/***********************************************************************
函数名称：void USART1_IRQHandler(void) 
功    能：完成SCI的数据的接收，并做标识
输入参数：
输出参数：
编写时间：2012.11.22
编 写 人：
注    意：RS232用的是USART1
***********************************************************************/
void USART1_IRQHandler(void)  
{

	unsigned char temp = 0;
	INT8U err;
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL();    // 关中断                               
    OSIntNesting++;	   		//中断嵌套层数，通知ucos
    OS_EXIT_CRITICAL();	   	//开中断
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{	
		temp = USART1->SR;  
		temp = USART1->DR; 												//清USART_IT_IDLE标志 
		/*
		RS232_REC_Flag = 1;	   											//DMA接收标志
		err = OSSemPost(sem_RS232_rec_flag);  //抛出一个信号量表示RS232已经接收完成一帧数据
		DMA_Cmd(DMA2_Stream5, DISABLE); 							  	//读取数据长度先关闭DMA 
		RS232_rec_counter = RS232_REC_BUFF_SIZE - DMA_GetCurrDataCounter(DMA2_Stream5);//获取DMA接收的数据长度，
		
		DMA_SetCurrDataCounter(DMA2_Stream5,RS232_REC_BUFF_SIZE);		//设置传输数据长度    
		DMA_Cmd(DMA2_Stream5, ENABLE);
		*/
	}
	if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)					//串口发送中断
	{
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		//RS232_dma_send_flag = 0;										//允许再次发送
	}	
	OSIntExit();//中断退出，通知ucos，（该句必须加）	
}

/***********************************************************************
函数名称：RS232_DMA_Send(unsigned char *send_buff,unsigned int length)
功    能：RS232  DMA方式发送字符串
输入参数：send_buff:待发送的数据指针；length：发送的数据长度（字符个数）
输出参数：
编写时间：2012.11.22
编 写 人：
注    意：
***********************************************************************/
void RS232_DMA_Send(unsigned char *send_buff,unsigned int length)
{
	
	unsigned int counter_232 = 0;
	while(RS232_dma_send_flag != 0)					//等待上次的DMA传输完成
	{
		counter_232 ++;
		if(counter_232 >= 0xffff)
		{
			break;
		}
	}						 
	RS232_dma_send_flag = 1;
	DMA2_Stream7 -> M0AR = (u32)send_buff;
	DMA_SetCurrDataCounter(DMA2_Stream7,length);  	//设置传输长度
	DMA_Cmd(DMA2_Stream7,ENABLE);					//启动DMA传输
}

/***********************************************************************
函数名称：RS232_Send_Data(unsigned char *send_buff,unsigned int length)
功    能：RS232发送字符串
输入参数：send_buff:待发送的数据指针；length：发送的数据长度（字符个数）
输出参数：
编写时间：2012.11.22
编 写 人：
注    意：
***********************************************************************/
void RS232_Send_Data(unsigned char *send_buff,unsigned int length)
{
 	unsigned int i = 0;
	for(i = 0;i < length;i ++)
	{			
		USART1->DR = send_buff[i];
		while((USART1->SR&0X40)==0);	
	}
}
/***********************************************************************
函数名称：RS485_DMA_Send(unsigned char *send_buff,unsigned int length)
功    能：RS485  DMA方式发送字符串
输入参数：send_buff:待发送的数据指针；length：发送的数据长度（字符个数）
输出参数：
编写时间：2012.11.22
编 写 人：
注    意：
***********************************************************************/
void RS485_DMA_Send(unsigned char *send_buff,unsigned int length)
{
	
	unsigned int counter_485 = 0;
	RS_485_TX_EN;		//485发送使能
	while(RS485_dma_send_flag != 0)					//等待上次的DMA传输完成
	{
		counter_485 ++;
		if(counter_485 >= 0xffff)
		{
			break;
		}
	}						 
	RS485_dma_send_flag = 1;
	DMA1_Stream6 -> M0AR = (u32)send_buff;
	DMA_SetCurrDataCounter(DMA1_Stream6,length);  	//设置传输长度
	DMA_Cmd(DMA1_Stream6,ENABLE);					//启动DMA传输
}

/***********************************************************************
函数名称：RS485_Send_Data(unsigned char *send_buff,unsigned int length)
功    能：RS485发送字符串
输入参数：send_buff:待发送的数据指针；length：发送的数据长度（字符个数）
输出参数：
编写时间：2012.11.22
编 写 人：
注    意：
***********************************************************************/
void RS485_Send_Data(unsigned char *send_buff,unsigned int length)
{
 	unsigned int i = 0;
	RS_485_TX_EN;		//485发送使能
	RS485_Delay(300);		//稍作延时，注意延时的长短根据波特率来定，波特率越小，延时应该越长
	for(i = 0;i < length;i ++)
	{			
		USART2->DR = send_buff[i];
		while((USART2->SR&0X40)==0);	
	}
	RS485_Delay(50); 		//稍作延时，注意延时的长短根据波特率来定，波特率越小，延时应该越长
	RS_485_RX_EN;  		//485接收使能
}

/***********************************************************************
函数名称：void RS485_Delay(uint32_t nCount)
功    能：RS485收发延时函数
输入参数：
输出参数：
编写时间：2012.11.22
编 写 人：
注    意：
***********************************************************************/
static void RS485_Delay(uint32_t nCount)
{ 
  while(nCount > 0)
  { 
  	  nCount --;   
  }
}


//初始化IO 串口1 
//bound:波特率
void qj005_uart_init(void){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //使能GPIOD时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
 
	//串口2对应引脚复用映射
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2); //GPIOD5复用为USART2
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2); //GPIOD6复用为USART2
	
	//USART2端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; //GPIOD5与GPIOD6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOD,&GPIO_InitStructure); //初始化PD5，PD6

   //USART2 初始化设置
	USART_InitStructure.USART_BaudRate = 9600;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART2, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART2, ENABLE);  //使能串口2 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

	
}

u8 qj005_play_state = 0;//播放状态，0:空状态, 1:正在播放，2:播放结束
u8 is_data_start = 0;
u8 data_index = 0;
//7E 04 51 55 30 30 31 ef    TF/SD 的曲目S001播放完
void USART2_IRQHandler(void)                	//串口2中断服务程序
{
	unsigned char temp = 0;
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL();    // 关中断                               
	OSIntNesting++;	   		//中断嵌套层数，通知ucos
	OS_EXIT_CRITICAL();	   	//开中断   

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  
	{
		temp = USART_ReceiveData(USART2);//读取接收到的数据
		
		if(is_data_start == 1)
		{
			data_index += 1;
		}
		
		if((temp) == 0x7E)//接收开始
		{
			is_data_start = 1;
			data_index = 0;
		}
		
		if((temp) != 0x04 && data_index == 1)//接收到的第二个字符不是04，则清空
		{
			is_data_start = 0;
			data_index = 0;
		}
		
		if((temp) != 0x51 && data_index == 2)//接收到的第三个字符不是51，则清空
		{
			is_data_start = 0;
			data_index = 0;
		}
		
		if((temp) == 0xef && data_index > 2)//接收到结束符ef
		{
			qj005_play_state = 2;
			is_data_start = 0;
			data_index = 0;
		}
  } 

	OSIntExit();//中断退出，通知ucos，（该句必须加）
}

void qj005_send_data(char send_buff[])
{
 	unsigned int i = 0;
	u8 command_length = strlen(send_buff);
	
	for(i = 0;i < command_length; i++)
	{			
		USART_SendData(USART2, send_buff[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET);	
	}
}
/*
void send_char(unsigned char c)
{
 	USART_SendData(USART2, c);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET);	
}
*/
void send_mp3_command(u8 comand, char* file_name)
{
	u8 file_length = strlen(file_name);
	u8 length = 3 + file_length;
	uint32_t sum = length + comand;
	
	for(int i = 0; i < file_length; i++)
	{
		sum += file_name[i];
	}
	
	u8 check_sum = sum % 256;
	char check_sum_string[1] = {check_sum};
	//char send_buff[] = {0x7e, length, comand, file_name[0], 0xef};
	char command_end[1] = {0xef};
	char send_buff[] = {0x7e, length, comand};
	strcat(send_buff, file_name);
	strcat(send_buff, check_sum_string);
	strcat(send_buff, command_end);
	qj005_send_data(send_buff);
}


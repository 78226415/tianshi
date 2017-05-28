#include "usart.h"	
#include "M_Global.h"
	

//初始化IO 串口1 
//bound:波特率
void qj005_uart_init(){
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
			play_state = 2;
			is_data_start = 0;
			data_index = 0;
		}
  } 

	OSIntExit();//中断退出，通知ucos，（该句必须加）
}

void qj005_send_data(unsigned char *send_buff,unsigned int length)
{
 	unsigned int i = 0;

	for(i = 0;i < length; i++)
	{			
		USART_SendData(USART2, send_buff[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != SET);	
	}
}
 




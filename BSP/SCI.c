
/***********************************************************************
�ļ����ƣ�SCI.C
��    �ܣ���ɶ�usart1��usart2�Ĳ���
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
***********************************************************************/

#include "M_Global.h"
#include "SCI.h"
#include "DMA.h"

volatile unsigned char RS485_REC_Flag = 0;
volatile unsigned char RS485_buff[RS485_REC_BUFF_SIZE];//���ڽ�������
volatile unsigned int RS485_rec_counter = 0;//����RS485���ռ���

unsigned short RS485_send_data_length = 0;

volatile unsigned char RS232_REC_Flag = 0;
volatile unsigned char RS232_buff[RS232_REC_BUFF_SIZE];//���ڽ�������
volatile unsigned int RS232_rec_counter = 0;//����RS232���ռ���

unsigned short RS232_send_data_length = 0;

/***********************************************************************
�������ƣ�void USART_232_Configuration(void) 
��    �ܣ�
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺RS232�õ���USART1
***********************************************************************/
void USART_232_Configuration(void)
{ 
  
	GPIO_InitTypeDef GPIO_InitStructure;//����GPIO_InitTypeDef���͵Ľṹ���ԱGPIO_InitStructure

	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	//ʹ����Ҫ�õ���GPIO�ܽ�ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOD, ENABLE);
	//ʹ��USART1 ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	///��λ����1
	USART_DeInit(USART1);
	
	USART_StructInit(&USART_InitStructure);//����Ĭ��USART����
	USART_ClockStructInit(&USART_ClockInitStruct);//����Ĭ��USART����        
	//���ô���1�Ĺܽ� PA8 USART1_EN PA9 USART1_TX PA10 USART1_RX    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    //����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);        //�ܽ�PA9����ΪUSART1
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
	
// 	//����DMA��ʽ����  
// 	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  
	//����DMA��ʽ����  
//	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE); 
	
	
	USART_Cmd(USART1, ENABLE); 
//	USART_ClearITPendingBit(USART1, USART_IT_TC);//����ж�TCλ	

}
/***********************************************************************
�������ƣ�void USART_485_Configuration(void) 
��    �ܣ�
���������
���������
��дʱ�䣺
�� д �ˣ�
ע    �⣺RS485�õ���USART2
***********************************************************************/
void USART_485_Configuration(void)
{ 
  
	GPIO_InitTypeDef GPIO_InitStructure;//����GPIO_InitTypeDef���͵Ľṹ���ԱGPIO_InitStructure
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	//ʹ����Ҫ�õ���GPIO�ܽ�ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);
	USART_DeInit(USART2);	//USART2ΪRS232
	USART_StructInit(&USART_InitStructure);//����Ĭ��USART����
	USART_ClockStructInit(&USART_ClockInitStruct);//����Ĭ��USART����        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    //����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);        //�ܽ�PA9����ΪUSART1
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
	
// 	//����DMA��ʽ����  
// 	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);  
	//����DMA��ʽ����  
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); 
	
	
	USART_Cmd(USART2, ENABLE); 
	USART_ClearITPendingBit(USART2, USART_IT_TC);//����ж�TCλ	
	
/***********************************GPIO_Pin_7��RS485�������******************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
/***********************************************************************
�������ƣ�void USART1_IRQHandler(void) 
��    �ܣ����SCI�����ݵĽ��գ�������ʶ
���������
���������
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺RS232�õ���USART1
***********************************************************************/
void USART1_IRQHandler(void)  
{

	unsigned char temp = 0;
	INT8U err;
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL();    // ���ж�                               
    OSIntNesting++;	   		//�ж�Ƕ�ײ�����֪ͨucos
    OS_EXIT_CRITICAL();	   	//���ж�
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{	
		temp = USART1->SR;  
		temp = USART1->DR; 												//��USART_IT_IDLE��־ 
		/*
		RS232_REC_Flag = 1;	   											//DMA���ձ�־
		err = OSSemPost(sem_RS232_rec_flag);  //�׳�һ���ź�����ʾRS232�Ѿ��������һ֡����
		DMA_Cmd(DMA2_Stream5, DISABLE); 							  	//��ȡ���ݳ����ȹر�DMA 
		RS232_rec_counter = RS232_REC_BUFF_SIZE - DMA_GetCurrDataCounter(DMA2_Stream5);//��ȡDMA���յ����ݳ��ȣ�
		
		DMA_SetCurrDataCounter(DMA2_Stream5,RS232_REC_BUFF_SIZE);		//���ô������ݳ���    
		DMA_Cmd(DMA2_Stream5, ENABLE);
		*/
	}
	if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)					//���ڷ����ж�
	{
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		//RS232_dma_send_flag = 0;										//�����ٴη���
	}	
	OSIntExit();//�ж��˳���֪ͨucos�����þ����ӣ�	
}

/***********************************************************************
�������ƣ�RS232_DMA_Send(unsigned char *send_buff,unsigned int length)
��    �ܣ�RS232  DMA��ʽ�����ַ���
���������send_buff:�����͵�����ָ�룻length�����͵����ݳ��ȣ��ַ�������
���������
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
***********************************************************************/
void RS232_DMA_Send(unsigned char *send_buff,unsigned int length)
{
	
	unsigned int counter_232 = 0;
	while(RS232_dma_send_flag != 0)					//�ȴ��ϴε�DMA�������
	{
		counter_232 ++;
		if(counter_232 >= 0xffff)
		{
			break;
		}
	}						 
	RS232_dma_send_flag = 1;
	DMA2_Stream7 -> M0AR = (u32)send_buff;
	DMA_SetCurrDataCounter(DMA2_Stream7,length);  	//���ô��䳤��
	DMA_Cmd(DMA2_Stream7,ENABLE);					//����DMA����
}

/***********************************************************************
�������ƣ�RS232_Send_Data(unsigned char *send_buff,unsigned int length)
��    �ܣ�RS232�����ַ���
���������send_buff:�����͵�����ָ�룻length�����͵����ݳ��ȣ��ַ�������
���������
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
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
�������ƣ�RS485_DMA_Send(unsigned char *send_buff,unsigned int length)
��    �ܣ�RS485  DMA��ʽ�����ַ���
���������send_buff:�����͵�����ָ�룻length�����͵����ݳ��ȣ��ַ�������
���������
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
***********************************************************************/
void RS485_DMA_Send(unsigned char *send_buff,unsigned int length)
{
	
	unsigned int counter_485 = 0;
	RS_485_TX_EN;		//485����ʹ��
	while(RS485_dma_send_flag != 0)					//�ȴ��ϴε�DMA�������
	{
		counter_485 ++;
		if(counter_485 >= 0xffff)
		{
			break;
		}
	}						 
	RS485_dma_send_flag = 1;
	DMA1_Stream6 -> M0AR = (u32)send_buff;
	DMA_SetCurrDataCounter(DMA1_Stream6,length);  	//���ô��䳤��
	DMA_Cmd(DMA1_Stream6,ENABLE);					//����DMA����
}

/***********************************************************************
�������ƣ�RS485_Send_Data(unsigned char *send_buff,unsigned int length)
��    �ܣ�RS485�����ַ���
���������send_buff:�����͵�����ָ�룻length�����͵����ݳ��ȣ��ַ�������
���������
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
***********************************************************************/
void RS485_Send_Data(unsigned char *send_buff,unsigned int length)
{
 	unsigned int i = 0;
	RS_485_TX_EN;		//485����ʹ��
	RS485_Delay(300);		//������ʱ��ע����ʱ�ĳ��̸��ݲ�����������������ԽС����ʱӦ��Խ��
	for(i = 0;i < length;i ++)
	{			
		USART2->DR = send_buff[i];
		while((USART2->SR&0X40)==0);	
	}
	RS485_Delay(50); 		//������ʱ��ע����ʱ�ĳ��̸��ݲ�����������������ԽС����ʱӦ��Խ��
	RS_485_RX_EN;  		//485����ʹ��
}

/***********************************************************************
�������ƣ�void RS485_Delay(uint32_t nCount)
��    �ܣ�RS485�շ���ʱ����
���������
���������
��дʱ�䣺2012.11.22
�� д �ˣ�
ע    �⣺
***********************************************************************/
static void RS485_Delay(uint32_t nCount)
{ 
  while(nCount > 0)
  { 
  	  nCount --;   
  }
}


//��ʼ��IO ����1 
//bound:������
void qj005_uart_init(void){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIODʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
 
	//����2��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2); //GPIOD5����ΪUSART2
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2); //GPIOD6����ΪUSART2
	
	//USART2�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; //GPIOD5��GPIOD6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOD,&GPIO_InitStructure); //��ʼ��PD5��PD6

   //USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = 9600;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

	
}

u8 qj005_play_state = 0;//����״̬��0:��״̬, 1:���ڲ��ţ�2:���Ž���
u8 is_data_start = 0;
u8 data_index = 0;
//7E 04 51 55 30 30 31 ef    TF/SD ����ĿS001������
void USART2_IRQHandler(void)                	//����2�жϷ������
{
	unsigned char temp = 0;
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL();    // ���ж�                               
	OSIntNesting++;	   		//�ж�Ƕ�ײ�����֪ͨucos
	OS_EXIT_CRITICAL();	   	//���ж�   

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  
	{
		temp = USART_ReceiveData(USART2);//��ȡ���յ�������
		
		if(is_data_start == 1)
		{
			data_index += 1;
		}
		
		if((temp) == 0x7E)//���տ�ʼ
		{
			is_data_start = 1;
			data_index = 0;
		}
		
		if((temp) != 0x04 && data_index == 1)//���յ��ĵڶ����ַ�����04�������
		{
			is_data_start = 0;
			data_index = 0;
		}
		
		if((temp) != 0x51 && data_index == 2)//���յ��ĵ������ַ�����51�������
		{
			is_data_start = 0;
			data_index = 0;
		}
		
		if((temp) == 0xef && data_index > 2)//���յ�������ef
		{
			qj005_play_state = 2;
			is_data_start = 0;
			data_index = 0;
		}
  } 

	OSIntExit();//�ж��˳���֪ͨucos�����þ����ӣ�
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


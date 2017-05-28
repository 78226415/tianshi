#include "usart.h"	
#include "M_Global.h"
	

//��ʼ��IO ����1 
//bound:������
void qj005_uart_init(){
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
			play_state = 2;
			is_data_start = 0;
			data_index = 0;
		}
  } 

	OSIntExit();//�ж��˳���֪ͨucos�����þ����ӣ�
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
 




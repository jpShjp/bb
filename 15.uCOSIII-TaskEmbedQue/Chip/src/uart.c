#include "uart.h"
#include "stdio.h"
#include "includes.h"					//ucos ʹ��	  
#include "task.h"


u8 Uart3_Recv_Buffer[20];
u8 Uart3_Recv_Count = 0;
u8 Uart3_Recv_STA = 0;


void Uart3_init(void)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3��GPIOBʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//USART3_TX   GPIOB.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.10
   
  //USART3_RX	  GPIOB.11��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart3 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = 9600;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART3, &USART_InitStructure); //��ʼ������3
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3
	
	
//	BSP_IntVectSet(BSP_INT_ID_USART3,(CPU_FNCT_VOID)Recv_Protocol);
//	BSP_IntPrioSet(BSP_INT_ID_USART3,1);   
//	BSP_IntEn(BSP_INT_ID_USART3); 
}



void USART3_IRQHandler(void)
{
	
	if(0 == OSRunning)
		return ;
	OSIntEnter();
	//BSP_IntHandlerUSART3();
	Recv_Protocol();
	OSIntExit();
}

void Recv_Protocol(void)
{
	u8 ch;
	OS_ERR err;
	static u8 temp_flag = 0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
	{
		ch =USART_ReceiveData(USART3);
		if(ch == Hekr_Frame_Header)
		{
			temp_flag = 1;
			Uart3_Recv_Count = 0;
		}
		if(temp_flag)
		{
			Uart3_Recv_Buffer[Uart3_Recv_Count++] = ch;
			if(Uart3_Recv_Count > 4 && Uart3_Recv_Count >= Uart3_Recv_Buffer[1])
			{
				//Uart3_Recv_STA = 1;
				OSTaskSemPost(&ProtocolTaskTCB,OS_OPT_POST_NONE,&err);
				temp_flag = 0;
				Uart3_Recv_Count = 0;
			}
//			if(Uart3_Recv_Count > 15)
//			{
//				temp_flag = 0;
//				Uart3_Recv_Count = 0;
//			}
		}
	}	
}

void UART3_SendChar(u8 ch)
{
	while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
    USART3->DR = (u8) ch; 
}

int fputc(int ch, FILE *f)
{
	UART3_SendChar(ch);
	return ch;
}

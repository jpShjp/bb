#include "protocol_task.h"
#include "task.h"
#include "uart.h"
#include "led.h"

//������ƿ�
OS_TCB ProtocolTaskTCB;
//�����ջ	
CPU_STK Protocol_TASK_STK[Protocol_STK_SIZE];

	
void protocol_task(void *p_arg)
{
	OS_ERR err;
	static uint8_t Date_Handle_Flag = 0;
	uint8_t temp = 0;
	p_arg = p_arg;
	while(1)
	{
		
		OSTaskSemPend(0,OS_OPT_PEND_BLOCKING,0,&err);	
		if( !Date_Handle_Flag)  //Uart3_Recv_STA &&
		{
			Date_Handle_Flag = 1;
			//Uart3_Recv_STA = 0;
		}
		if(Date_Handle_Flag)
		{
			temp = Hekr_RecvData_Handle(Uart3_Recv_Buffer);
			if(Valid_Data_Update == temp)
			{
				//���յ����ݱ����� Valid_Data ������
				//User Code
				if(Valid_Data[0] == 0x01)
				{

				}
				else
				{

				}
				if(Valid_Data[1] == 0x01)
				{


				}
				else
				{


				}
			}
			if(Hekr_Module_State_Update == temp)
			{
				//���յ����ݱ����� Module_Status ������
				//User Code
			}
			Date_Handle_Flag = 0;		
		}
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ10ms
	}
}

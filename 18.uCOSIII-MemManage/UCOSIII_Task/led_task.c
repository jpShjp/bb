#include "led_task.h"
#include "LED.h"
#include "sys.h"
#include "task.h"


//������ƿ�
OS_TCB Led0TaskTCB;
//�����ջ	
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];

//led0������
void led0_task(void *p_arg)
{
	OS_ERR err;
	CPU_INT08U *buf;
	p_arg = p_arg;
	while(1)
	{
		buf = OSMemGet((OS_MEM*)&my_mem,
								      (OS_ERR*)&err);
		if(err == OS_ERR_NONE) //�ڴ�����ɹ�
		{
			printf("led0 task get mem \n\r");
		}
		
		if(err == OS_ERR_MEM_NO_FREE_BLKS) //�ڴ�����ɹ�
		{
			printf("No Free Mem \n\r");
		}	
					
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ1s	
		OSMemPut((OS_MEM*	)&my_mem,		//�ͷ��ڴ�
					 (void*		)buf,
					 (OS_ERR* 	)&err);
		printf("buf�ڴ��ͷ�֮��ĵ�ַΪ:%#x\r\n",(u32)(buf));
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ1s	
	
	}
}



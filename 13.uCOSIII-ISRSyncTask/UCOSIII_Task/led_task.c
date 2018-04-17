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
	p_arg = p_arg;
	while(1)
	{

		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ1s	
		// �����ź���
		printf("led0 task task sem.\r\n");
		OSTaskSemPost(&FloatTaskTCB,OS_OPT_POST_NONE,&err);
	}
}

#include "float_task.h"
#include "delay.h"
#include "uart.h"
#include "task.h"

//������ƿ�
OS_TCB	FloatTaskTCB;
//�����ջ
__align(8) CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];

//�����������
void float_task(void *p_arg)
{
	OS_ERR err;
	//CPU_SR_ALLOC();
	while(1)
	{
		printf("float task use share_data, prio : %d\n\r",FLOAT_TASK_PRIO);
		sprintf((char*)share_data,"float task write.\n\r");
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ300ms
		
		printf("float task : %s",share_data);
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ300ms	
	}
}

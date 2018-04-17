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
		printf("float task wait Mutex Sem to Sync. \n\r");
		// �����ź���
		//OSMutexPend(&Mutex_Sem,0,OS_OPT_PEND_BLOCKING,0,&err);
		OSSemPend(&SYNC_SEM,0,OS_OPT_PEND_BLOCKING,0,&err); //�����ź���
		
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ300ms	
		printf("float task get sem \n\r");
		//OSMutexPost(&Mutex_Sem,OS_OPT_POST_ALL,&err);
	}
}

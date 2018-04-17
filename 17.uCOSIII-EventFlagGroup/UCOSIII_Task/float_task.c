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
	while(1)
	{
		
		OSFlagPend((OS_FLAG_GRP*)&event_flag,
				   (OS_FLAGS	)FLAG_BIT(0)|FLAG_BIT(1),
		     	  (OS_TICK     )0,
				   (OS_OPT	    )OS_OPT_PEND_FLAG_SET_ANY+OS_OPT_PEND_FLAG_CONSUME,
				   (CPU_TS*     )0,
				   (OS_ERR*	    )&err);
		printf("float task get the flag \n\r");
		
		OSTimeDlyHMSM(0,0,0,800,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ800ms	
	}
}

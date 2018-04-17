#include "float_task.h"
#include "delay.h"
#include "uart.h"
#include "led_task.h"

//������ƿ�
OS_TCB	FloatTaskTCB;
//�����ջ
__align(8) CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];

//�����������
void float_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	static float float_num = 0.01;
	//uint32_t temp = &float_num;
	while(1)
	{
		float_num+=0.01f;
		OS_CRITICAL_ENTER();	//�����ٽ���
		printf("float_num��ֵΪ: %.4f\r\n",float_num);
		OS_CRITICAL_EXIT();		//�˳��ٽ���
		if(float_num > 0.901f && float_num < 0.919f)
		{
				OSTaskDel((OS_TCB*)&Led0TaskTCB,&err);
				printf("ɾ��LED����\n\r");
		}
		if(float_num > 1.991f && float_num < 2.001f)
		{
				OS_CRITICAL_ENTER();	//�����ٽ���
				OSTaskCreate((OS_TCB 	* )&Led0TaskTCB,		
					(CPU_CHAR	* )"led0 task", 		
							 (OS_TASK_PTR )led0_task, 			
							 (void		* )0,					
							 (OS_PRIO	  )LED0_TASK_PRIO,     
							 (CPU_STK   * )&LED0_TASK_STK[0],	
							 (CPU_STK_SIZE)LED0_STK_SIZE/10,	
							 (CPU_STK_SIZE)LED0_STK_SIZE,		
							 (OS_MSG_QTY  )0,					
							 (OS_TICK	  )0,					
							 (void   	* )0,					
							 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
							 (OS_ERR 	* )&err);	
				printf("����LED����\n\r");
				OS_CRITICAL_EXIT();		//�˳��ٽ���
				float_num = 0.0f;
		}
		OSTimeDlyHMSM(0,0,0,300,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ300ms
		
	}
}

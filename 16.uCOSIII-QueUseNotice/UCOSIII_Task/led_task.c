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
	u8 test[20];
	u8 test1[20] = "abcde";
	u8 test2[20] = "12345";
	u8 test3[20] = "45678";
	
	u8 times = 0;
	CPU_SR_ALLOC();
	u8 temp;	
	p_arg = p_arg;
	while(1)
	{
		OS_CRITICAL_ENTER();
		temp = FloatTaskTCB.MsgQ.NbrEntriesSize - FloatTaskTCB.MsgQ.NbrEntries;
		printf("que remain %d.\r\n",temp);
		OS_CRITICAL_EXIT();	
		sprintf((char *)test,"led_send_que %d",times++);
		printf("led0 task send que.\r\n");
		//��Ϣ���д��͵��ǵ�ַ �Ҳ���������ݿ���
		//ͬһ��ַ�����ٶȱȴ�������� �ᵼ�����ݱ����� ������ݶ�ʧ
		//��Ϣ���д��͵�����Ҫ��ȡĳ����ַ�Ĵ���
		OSTaskQPost((OS_TCB*	)&FloatTaskTCB,	//������Msgdis������Ϣ
					(void*		)test,
          (OS_MSG_SIZE)20,
          (OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);
		OSTaskQPost((OS_TCB*	)&FloatTaskTCB,	//������Msgdis������Ϣ
					(void*		)&test1,
          (OS_MSG_SIZE)20,
          (OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);
		OSTaskQPost((OS_TCB*	)&FloatTaskTCB,	//������Msgdis������Ϣ
					(void*		)&test2,
          (OS_MSG_SIZE)20,
          (OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);
		OSTaskQPost((OS_TCB*	)&FloatTaskTCB,	//������Msgdis������Ϣ
					(void*		)&test3,
          (OS_MSG_SIZE)20,
          (OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);					
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ1s	
			
	}
}


//		OS_CRITICAL_ENTER();
//		temp = isr_que.MsgQ.NbrEntriesSize - isr_que.MsgQ.NbrEntries;
//		printf("que remain %d.\r\n",temp);
//		OS_CRITICAL_EXIT();	
//		if(times == 5)
//		{
//			OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ1s
//			//printf("led0 task wait que .\r\n");
//			continue;
//		}
//		sprintf((char *)test,"led_send_que %d",times++);
//		printf("led0 task send que.\r\n");
//		OSQPost((OS_Q*		)&isr_que,		
//				(void*		)test,
//				(OS_MSG_SIZE)20,
//				(OS_OPT		)OS_OPT_POST_FIFO,
//				(OS_ERR*	)&err);
//				
//		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ1s	


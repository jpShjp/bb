#ifndef _PROTOCOL_TASK_H_
#define _PROTOCOL_TASK_H_

#include "includes.h"

//�������ȼ�
#define Protocol_TASK_PRIO		4u
//�����ջ��С	
#define Protocol_STK_SIZE 		128u
//������ƿ�
extern OS_TCB ProtocolTaskTCB;
//�����ջ	
extern CPU_STK Protocol_TASK_STK[Protocol_STK_SIZE];

void protocol_task(void *p_arg);


#endif


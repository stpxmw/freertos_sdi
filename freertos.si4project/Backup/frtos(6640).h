#ifndef _frtos_c_
#define _frtos_c_

#include "FreeRTOS.h"
#include "task.h"

#define ENABLE_PROJ 1
#define DISABLE_PROJ 0

#if ENABLE_PROJ
#define INTERRUPT_TASK_PRIO 2 //�������ȼ�
#define INTERRUPT_STK_SIZE 256 //�����ջ��С
TaskHandle_t INTERRUPTTask_Handler; //������
void interrupt_task(void *p_arg); //������


#endif











#endif


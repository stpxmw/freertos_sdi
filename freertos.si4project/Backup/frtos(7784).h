#ifndef _frtos_c_
#define _frtos_c_

#define ENABLE_PROJ 1
#define DISABLE_PROJ 0

#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"


#if 1
#define INTERRUPT_TASK_PRIO 2 //�������ȼ�
#define INTERRUPT_STK_SIZE 256 //�����ջ��С
TaskHandle_t INTERRUPTTask_Handler; //������
//void interrupt_task(void *p_arg); //������


//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		256  
//������
TaskHandle_t StartTask_Handler;
//������
//void start_task(void *pvParameters);



#endif











#endif


#ifndef _FRTOS_H_
#define _FRTOS_H_

#define ENABLE_PROJ 1
#define DISABLE_PROJ 0

#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		256  





//�������ȼ�
#define LED0_TASK_PRIO		2
//�����ջ��С	
#define LED0_STK_SIZE 		50  

//������
void led0_task(void *pvParameters);



//�������ȼ�
#define LED1_TASK_PRIO		3
//�����ջ��С	
#define LED1_STK_SIZE 		50  

//������
void led1_task(void *pvParameters);



#if 1
#define INTERRUPT_TASK_PRIO 2 //�������ȼ�
#define INTERRUPT_STK_SIZE 256 //�����ջ��С
void interrupt_task(void *p_arg); //������


//������




//������
void start_task(void *pvParameters);
void enter_main(void);



#endif




#endif

#ifndef _FRTOS_H_
#define _FRTOS_H_

#define ENABLE_PROJ 1
#define DISABLE_PROJ 0

#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		256  





//任务优先级
#define LED0_TASK_PRIO		2
//任务堆栈大小	
#define LED0_STK_SIZE 		50  

//任务函数
void led0_task(void *pvParameters);



//任务优先级
#define LED1_TASK_PRIO		3
//任务堆栈大小	
#define LED1_STK_SIZE 		50  

//任务函数
void led1_task(void *pvParameters);



#if 1
#define INTERRUPT_TASK_PRIO 2 //任务优先级
#define INTERRUPT_STK_SIZE 256 //任务堆栈大小
void interrupt_task(void *p_arg); //任务函数


//任务句柄




//任务函数
void start_task(void *pvParameters);
void enter_main(void);



#endif




#endif

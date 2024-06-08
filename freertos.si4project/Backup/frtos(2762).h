#ifndef _frtos_c_
#define _frtos_c_

#define ENABLE_PROJ 1
#define DISABLE_PROJ 0

#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"


#if 1
#define INTERRUPT_TASK_PRIO 2 //任务优先级
#define INTERRUPT_STK_SIZE 256 //任务堆栈大小
void interrupt_task(void *p_arg); //任务函数


//任务句柄




//任务函数
void start_task(void *pvParameters);



#endif











#endif


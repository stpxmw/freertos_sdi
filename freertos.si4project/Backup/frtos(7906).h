#ifndef _frtos_c_
#define _frtos_c_

#define ENABLE_PROJ 1
#define DISABLE_PROJ 0

#if ENABLE_PROJ
#define INTERRUPT_TASK_PRIO 2 //任务优先级
#define INTERRUPT_STK_SIZE 256 //任务堆栈大小
TaskHandle_t INTERRUPTTask_Handler; //任务句柄
void interrupt_task(void *p_arg); //任务函数





#endif











#endif


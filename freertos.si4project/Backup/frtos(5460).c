#include "frtos.h"


#if 0
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    //创建LED0任务
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
    //创建LED1任务
    xTaskCreate((TaskFunction_t )led1_task,     
                (const char*    )"led1_task",   
                (uint16_t       )LED1_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED1_TASK_PRIO,
                (TaskHandle_t*  )&LED1Task_Handler);         
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}
#endif


void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    //创建中断测试任务
     xTaskCreate((TaskFunction_t )interrupt_task, //任务函数 (1)
     (const char* )"interrupt_task", //任务名称
     (uint16_t )INTERRUPT_STK_SIZE, //任务堆栈大小
     (void* )NULL, //传递给任务函数的参数
     (UBaseType_t )INTERRUPT_TASK_PRIO, //任务优先级
     (TaskHandle_t* )&INTERRUPTTask_Handler); //任务句柄
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}




void interrupt_task(void * p_arg)
{


	static u32		total_num = 0;

	while (1)
		{
		total_num			+= 1;

		if (total_num == 5)
			(2)
				{
				printf("关闭中断.............\r\n");
				portDISABLE_INTERRUPTS();			//关闭中断 (3)
				delay_xms(5000);					//延时 5s (4)
				printf("打开中断.............\r\n"); //打开中断
				portENABLE_INTERRUPTS();
				(5)
				}

		LED0				= ~LED0;
		vTaskDelay(1000);
		}



}





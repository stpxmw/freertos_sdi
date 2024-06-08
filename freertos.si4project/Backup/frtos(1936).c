
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timer.h"
#include "frtos.h"

//extern void TIM3_Int_Init(u16 arr,u16 psc);
//extern void TIM5_Int_Init(u16 arr,u16 psc);



TaskHandle_t INTERRUPTTask_Handler; //任务句柄

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




void interrupt_task(void * p_arg)
{
	static u32		total_num = 0;

	while (1)
	{
		total_num			+= 1;

		if (total_num == 5)
		{
			printf("关闭中断.............\r\n");
			portDISABLE_INTERRUPTS();				//关闭中断 (3)
			delay_xms(5000);						//延时 5s (4)
			printf("打开中断.............\r\n"); //打开中断
			portENABLE_INTERRUPTS();
		}

		LED0				= ~LED0;
		vTaskDelay(1000);
	}



}


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



//LED0任务函数 
void led0_task(void *pvParameters)
{
    while(1)
    {
        LED0=~LED0;
        vTaskDelay(500);
    }
}   

//LED1任务函数
void led1_task(void *pvParameters)
{
    while(1)
    {
        LED1=0;
        vTaskDelay(200);
        LED1=1;
        vTaskDelay(800);
    }
}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName ){
    
}

void enter_main(void)
{

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //设置系统中断优先级分组4	  
	delay_init();									//延时函数初始化   
	uart_init(115200);								//初始化串口
	LED_Init(); 									//初始化LED

	TIM3_Int_Init(10000 - 1, 7200 - 1); 			//初始化定时器 3，定时器周期 1S
	TIM5_Int_Init(10000 - 1, 7200 - 1); 			//初始化定时器 5，定时器周期 1S


	//创建开始任务
	xTaskCreate((TaskFunction_t) start_task,		//任务函数
	(const char *) "start_task",					//任务名称
	(uint16_t) START_STK_SIZE,						//任务堆栈大小
	(void *) NULL,									//传递给任务函数的参数
	(UBaseType_t) START_TASK_PRIO,					//任务优先级
	(TaskHandle_t *) &StartTask_Handler);			//任务句柄				
	vTaskStartScheduler();							//开启任务调度

}















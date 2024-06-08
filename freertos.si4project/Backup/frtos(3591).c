
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
//#include "timer.h"
#include "frtos.h"
#include "gki_log.h"





TaskHandle_t StartTask_Handler;

TaskHandle_t INTERRUPTTask_Handler; //任务句柄
//任务句柄
TaskHandle_t LED0Task_Handler;
//任务句柄
TaskHandle_t LED1Task_Handler;

extern void TIM3_Int_Init(u16 arr,u16 psc);
extern void TIM5_Int_Init(u16 arr,u16 psc);



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

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;  //先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	
	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}

void TIM5_Int_Init(u16 arr,u16 psc)
{
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //时钟使能
//定时器 TIM5 初始化
TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载值
TIM_TimeBaseStructure.TIM_Prescaler =psc; //定时器分频
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 
TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); //使能指定的 TIM5 中断,允许更新中断
//中断优先级 NVIC 设置
NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; //TIM5 中断
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5; //先占优先级 5 级 (2)
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //从优先级 0 级
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ 通道被使能
NVIC_Init(&NVIC_InitStructure); //初始化 NVIC 寄存器
TIM_Cmd(TIM5, ENABLE); //使能 TIM5
}



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
			delay_xms(50000);						//延时 5s (4)
			printf("打开中断.............\r\n"); //打开中断
			portENABLE_INTERRUPTS();
		}

		//LED0				= ~LED0;
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















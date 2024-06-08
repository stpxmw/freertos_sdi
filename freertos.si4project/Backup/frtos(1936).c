
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timer.h"
#include "frtos.h"

//extern void TIM3_Int_Init(u16 arr,u16 psc);
//extern void TIM5_Int_Init(u16 arr,u16 psc);



TaskHandle_t INTERRUPTTask_Handler; //������

#if 0
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //����LED0����
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
    //����LED1����
    xTaskCreate((TaskFunction_t )led1_task,     
                (const char*    )"led1_task",   
                (uint16_t       )LED1_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED1_TASK_PRIO,
                (TaskHandle_t*  )&LED1Task_Handler);         
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
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
			printf("�ر��ж�.............\r\n");
			portDISABLE_INTERRUPTS();				//�ر��ж� (3)
			delay_xms(5000);						//��ʱ 5s (4)
			printf("���ж�.............\r\n"); //���ж�
			portENABLE_INTERRUPTS();
		}

		LED0				= ~LED0;
		vTaskDelay(1000);
	}



}


void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //�����жϲ�������
     xTaskCreate((TaskFunction_t )interrupt_task, //������ (1)
     (const char* )"interrupt_task", //��������
     (uint16_t )INTERRUPT_STK_SIZE, //�����ջ��С
     (void* )NULL, //���ݸ��������Ĳ���
     (UBaseType_t )INTERRUPT_TASK_PRIO, //�������ȼ�
     (TaskHandle_t* )&INTERRUPTTask_Handler); //������
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}



//LED0������ 
void led0_task(void *pvParameters)
{
    while(1)
    {
        LED0=~LED0;
        vTaskDelay(500);
    }
}   

//LED1������
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

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //����ϵͳ�ж����ȼ�����4	  
	delay_init();									//��ʱ������ʼ��   
	uart_init(115200);								//��ʼ������
	LED_Init(); 									//��ʼ��LED

	TIM3_Int_Init(10000 - 1, 7200 - 1); 			//��ʼ����ʱ�� 3����ʱ������ 1S
	TIM5_Int_Init(10000 - 1, 7200 - 1); 			//��ʼ����ʱ�� 5����ʱ������ 1S


	//������ʼ����
	xTaskCreate((TaskFunction_t) start_task,		//������
	(const char *) "start_task",					//��������
	(uint16_t) START_STK_SIZE,						//�����ջ��С
	(void *) NULL,									//���ݸ��������Ĳ���
	(UBaseType_t) START_TASK_PRIO,					//�������ȼ�
	(TaskHandle_t *) &StartTask_Handler);			//������				
	vTaskStartScheduler();							//�����������

}















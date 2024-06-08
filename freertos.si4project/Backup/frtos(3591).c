
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
//#include "timer.h"
#include "frtos.h"
#include "gki_log.h"





TaskHandle_t StartTask_Handler;

TaskHandle_t INTERRUPTTask_Handler; //������
//������
TaskHandle_t LED0Task_Handler;
//������
TaskHandle_t LED1Task_Handler;

extern void TIM3_Int_Init(u16 arr,u16 psc);
extern void TIM5_Int_Init(u16 arr,u16 psc);



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

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;  //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}

void TIM5_Int_Init(u16 arr,u16 psc)
{
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʱ��ʹ��
//��ʱ�� TIM5 ��ʼ��
TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ��ֵ
TIM_TimeBaseStructure.TIM_Prescaler =psc; //��ʱ����Ƶ
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 
TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); //ʹ��ָ���� TIM5 �ж�,��������ж�
//�ж����ȼ� NVIC ����
NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; //TIM5 �ж�
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5; //��ռ���ȼ� 5 �� (2)
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ� 0 ��
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ ͨ����ʹ��
NVIC_Init(&NVIC_InitStructure); //��ʼ�� NVIC �Ĵ���
TIM_Cmd(TIM5, ENABLE); //ʹ�� TIM5
}



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
			delay_xms(50000);						//��ʱ 5s (4)
			printf("���ж�.............\r\n"); //���ж�
			portENABLE_INTERRUPTS();
		}

		//LED0				= ~LED0;
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















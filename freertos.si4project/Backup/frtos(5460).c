#include "frtos.h"


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




void interrupt_task(void * p_arg)
{


	static u32		total_num = 0;

	while (1)
		{
		total_num			+= 1;

		if (total_num == 5)
			(2)
				{
				printf("�ر��ж�.............\r\n");
				portDISABLE_INTERRUPTS();			//�ر��ж� (3)
				delay_xms(5000);					//��ʱ 5s (4)
				printf("���ж�.............\r\n"); //���ж�
				portENABLE_INTERRUPTS();
				(5)
				}

		LED0				= ~LED0;
		vTaskDelay(1000);
		}



}





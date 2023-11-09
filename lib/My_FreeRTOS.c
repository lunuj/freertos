#include "main.h"

void My_FreeRTOS_Init()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

}

//Static
/*

#define START_TASK_PRIO 1
#define START_STK_SIZE 	128
StackType_t StartTaskStack[START_STK_SIZE];
StaticTask_t StartTaskTCB;
TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters);
void led1_task(void *pvParameters);
void led2_task(void *pvParameters);
//创建开始任务
StartTask_Handler=xTaskCreateStatic((TaskFunction_t	)start_task,		//任务函数
                                    (const char* 	)"start_task",		//任务名称
                                    (uint32_t 		)START_STK_SIZE,	//任务堆栈大小
                                    (void* 		  	)NULL,				//传递给任务函数的参数
                                    (UBaseType_t 	)START_TASK_PRIO, 	//任务优先级
                                    (StackType_t*   )StartTaskStack,	//任务堆栈
                                    (StaticTask_t*  )&StartTaskTCB);	//任务控制块              
vTaskStartScheduler();          //开启任务调度


void start_task(void *pvParameters){
	OLED_ShowString(2,1,"task1");
	taskENTER_CRITICAL();

	LED1Task_Handler = xTaskCreateStatic(
		(TaskFunction_t	)led1_task,
		(const char*	)"led1_task",
		(u16			)LED1_STK_SIZE,
		(void *			)NULL,
		(UBaseType_t	)LED1_TASK_PRIO,
		(StackType_t*   )Task1TaskStack,	
		(StaticTask_t*  )&Task1TaskTCB);	
	
	LED2Task_Handler = xTaskCreateStatic(
		(TaskFunction_t	)led2_task,
		(const char*	)"led2_task",
		(u16			)LED1_STK_SIZE,
		(void *			)NULL,
		(UBaseType_t	)LED1_TASK_PRIO,
		(StackType_t*   )Task2TaskStack,	
		(StaticTask_t*  )&Task2TaskTCB);

	vTaskDelete(StartTask_Handler);
	taskEXIT_CRITICAL();
}


void led1_task(void *pvParameters){
	while (1)
	{
	}
}

void led2_task(void *pvParameters){
	while (1)
	{
	}
}
*/

//dymatic
/*
TaskHandle_t Task1_Handler;
TaskHandle_t Task2_Handler;
void led1_task(void *pvParameters);
void led2_task(void *pvParameters);

xTaskCreate(
    (TaskFunction_t)	led2_task,
    (const char *)		"led2_task",
    (uint16_t)			128,
    (void *)			NULL,
    (UBaseType_t)		3,
    (TaskHandle_t)		&Task1_Handler);
xTaskCreate(
    (TaskFunction_t)	led1_task,
    (const char *)		"led1_task",
    (uint16_t)			128,
    (void *)			NULL,
    (UBaseType_t)		3,
    (TaskHandle_t)		&Task2_Handler);

void led1_task(void *pvParameters){
	while (1)
	{
	}
}

void led2_task(void *pvParameters){
	while (1)
	{
	}
}
*/



#if (configSUPPORT_STATIC_ALLOCATION == 1)
/* 空闲任务任务堆栈 */
static StackType_t Idle_Task_Stack[configMINIMAL_STACK_SIZE];
/* 定时器任务堆栈 */
static StackType_t Timer_Task_Stack[configTIMER_TASK_STACK_DEPTH];

/* 空闲任务控制块 */
static StaticTask_t Idle_Task_TCB;
/* 定时器任务控制块 */
static StaticTask_t Timer_Task_TCB;

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer   = &Idle_Task_TCB;
    *ppxIdleTaskStackBuffer = Idle_Task_Stack;
    *pulIdleTaskStackSize   = configMINIMAL_STACK_SIZE;
}

// 获取定时器任务的任务堆栈和任务控制块内存
// ppxTimerTaskTCBBuffer	:		任务控制块内存
// ppxTimerTaskStackBuffer:	任务堆栈内存
// pulTimerTaskStackSize	:		任务堆栈大小
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
    *ppxTimerTaskTCBBuffer   = &Timer_Task_TCB;              /* 任务控制块内存 */
    *ppxTimerTaskStackBuffer = Timer_Task_Stack;             /* 任务堆栈内存 */
    *pulTimerTaskStackSize   = configTIMER_TASK_STACK_DEPTH; /* 任务堆栈大小 */
}
#endif /* SUPPORT_STATIC_ALLOCATION */

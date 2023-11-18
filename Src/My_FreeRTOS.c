#include "My_FreeRTOS.h"
#include "Serial.h"

/**
 * @brief MyFreeRTOS初始化
 * @return [无]
 */
void My_FreeRTOS_Init()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

}

/**
 * @brief 检测当前任务信息,并输出重定向至串口
 * @return [无]
 */
void Monitor_Task()
{
    char *buf = NULL;
    buf = pvPortMalloc(128);
    vTaskList(buf);                                       /* 获取所有任务的信息 */
    Serial_Printf("任务名 \t \t状态 \t优先级 \t剩余栈 \t任务序号\r\n");
    Serial_Printf("%s\r\n", buf);
    vPortFree(buf);
}

#if (configSUPPORT_STATIC_ALLOCATION == 1)

static StackType_t Idle_Task_Stack[configMINIMAL_STACK_SIZE];
static StackType_t Timer_Task_Stack[configTIMER_TASK_STACK_DEPTH];

static StaticTask_t Idle_Task_TCB;
static StaticTask_t Timer_Task_TCB;

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer   = &Idle_Task_TCB;
    *ppxIdleTaskStackBuffer = Idle_Task_Stack;
    *pulIdleTaskStackSize   = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
    *ppxTimerTaskTCBBuffer   = &Timer_Task_TCB;              /* 任务控制块内存 */
    *ppxTimerTaskStackBuffer = Timer_Task_Stack;             /* 任务堆栈内存 */
    *pulTimerTaskStackSize   = configTIMER_TASK_STACK_DEPTH; /* 任务堆栈大小 */
}
#endif /* SUPPORT_STATIC_ALLOCATION */

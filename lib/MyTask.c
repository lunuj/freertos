#include "main.h"

TaskHandle_t LedTask_Handler;

TaskHandle_t OledTask_Handler;

TaskHandle_t KeyTask_Handler;

TaskHandle_t SendTask_Handler;

TaskHandle_t ReceiveTask_Handler;

QueueHandle_t Test_Queue = NULL;

void MyTask_Init()
{
    Test_Queue = xQueueCreate((UBaseType_t)4, (UBaseType_t)4);

    xTaskCreate(
        (TaskFunction_t)led_task,
        (const char *)"led_task",
        (uint16_t)64,
        (void *)NULL,
        (UBaseType_t)3,
        (TaskHandle_t *)&LedTask_Handler);

    xTaskCreate(
        (TaskFunction_t)oled_task,
        (const char *)"oled_task",
        (uint16_t)64,
        (void *)NULL,
        (UBaseType_t)3,
        (TaskHandle_t *)&OledTask_Handler);
    xTaskCreate(
        (TaskFunction_t)key_task,
        (const char *)"key_task",
        (uint16_t)64,
        (void *)NULL,
        (UBaseType_t)5,
        (TaskHandle_t *)&KeyTask_Handler);
    xTaskCreate(
        (TaskFunction_t)receive_task,
        (const char *)"receive_task",
        (uint16_t)128,
        (void *)NULL,
        (UBaseType_t)4,
        (TaskHandle_t *)&ReceiveTask_Handler);

    // 创建发送任务
    xTaskCreate(
        (TaskFunction_t)send_task,
        (const char *)"send_task",
        (uint16_t)128,
        (void *)NULL,
        (UBaseType_t)5,
        (TaskHandle_t *)&SendTask_Handler);

    vTaskSuspend(SendTask_Handler);
    vTaskSuspend(ReceiveTask_Handler);
}

void led_task(void *pvParameters)
{
    while (1) {
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)!GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13));
        FreeRTOS_delay_ms(500);
    }
}

void oled_task(void *pvParameters)
{
    int i = 0;
    while (1) {
        OLED_ShowNum(2, 1, i++, 4);
        FreeRTOS_delay_ms(500);
        OLED_ShowString(2, 1, "    ");
        FreeRTOS_delay_ms(500);
    }
}

void key_task(void *pvParameters)
{

    while (1) {
        if (Key_GetNum(Key_0) == 1) {
            vTaskResume(SendTask_Handler);
            vTaskResume(ReceiveTask_Handler);
        }
        FreeRTOS_delay_ms(20);
    }
}

void send_task(void *pvParamaters)
{
    BaseType_t xSend = pdPASS;
    u32 s_queue      = 'A';
    u8 type          = 1;
    while (1) {
        if (type == 0) {
            xSend = xQueueSend(Test_Queue, &s_queue, 0);
            s_queue++;
            if (xSend == pdPASS) {
                OLED_ShowString(3, 1, "SendQueOK");

            } else {
                OLED_ShowString(3, 1, "SendQueER");
            }
        } else {
            Serial_Printf("%c\r\n", s_queue);
            OLED_ShowString(3, 1, "SendUsaOK");
        }

        vTaskSuspend(NULL);
    }
}

void receive_task(void *pvParamaters)
{
    BaseType_t xReceive = pdTRUE;
    u8 type             = 1;
    u8 r_quque;
    while (1) {
        if (type == 0) {
            xReceive = xQueueReceive(Test_Queue, &r_quque, portMAX_DELAY);
            if (xReceive == pdTRUE) {
                OLED_ShowString(4, 1, "ReceQueOK");
                OLED_ShowHexNum(4, 11, r_quque, 2);
            } else {
                OLED_ShowString(4, 1, "ReceQueER");
            }
        } else {
            if (Serial_GetRxFlag()) {
                OLED_ShowString(4, 1, "ReceUsaOK");
                char String[100];
                sprintf(String, "%s",Serial_GetRxCach());
                OLED_ShowString(4,11,String);
                Serial_Printf("%s\r\t", String);
            }
        }
        vTaskSuspend(NULL);
    }
}
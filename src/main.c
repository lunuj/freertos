/*
 * @Author: lunuj
 * @Date: 2023-10-29 23:38:03
 * @LastEditTime: 2023-11-13 01:40:20
 * @FilePath: \freertos\src\main.c
 * @Description:
 *
 * Copyright (c) 2023 by lunuj, All Rights Reserved.
 */
#include "main.h"
TaskHandle_t LedTask_Handler;
void led_task(void *pvParameters);

TaskHandle_t OledTask_Handler;
void oled_task(void *pvParameters);

TaskHandle_t KeyTask_Handler;
void key_task(void *pvParameters);
int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_SetBits(GPIOC, GPIO_Pin_13);

    GPIO_Init(GPIOC, &GPIO_InitStructure);
    Key_Init();
    OLED_Init();
    OLED_ShowString(1, 1, "STM32 Start");

    xTaskCreate(
        (TaskFunction_t)led_task,
        (const char *)"led_task",
        (uint16_t)50,
        (void *)NULL,
        (UBaseType_t)3,
        (TaskHandle_t)&LedTask_Handler);

    xTaskCreate(
        (TaskFunction_t)oled_task,
        (const char *)"oled_task",
        (uint16_t)50,
        (void *)NULL,
        (UBaseType_t)3,
        (TaskHandle_t)&OledTask_Handler);

    xTaskCreate(
        (TaskFunction_t)key_task,
        (const char *)"key_task",
        (uint16_t)128,
        (void *)NULL,
        (UBaseType_t)3,
        (TaskHandle_t)&KeyTask_Handler);

    vTaskStartScheduler();
}

void led_task(void *pvParameters)
{
    while (1) {
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)!GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13));
        FreeRTOS_delay_ms(50);
    }
}

void oled_task(void *pvParameters)
{
    int i = 0;
    while (1) {
        OLED_ShowNum(2, 1, i++, 1);
        FreeRTOS_delay_ms(500);
        OLED_ShowString(2, 1, " ");
        FreeRTOS_delay_ms(500);
    }
}

void key_task(void *pvParameters)
{
    int state = 1;
    while (1) {

        if (state == 1 && (Key_GetNum(Key_0) == 1)) {
            vTaskSuspend(LedTask_Handler);
            state = 0;
            FreeRTOS_delay_ms(20);
        } else if (state == 0 && (Key_GetNum(Key_0) == 1)) {
            vTaskResume(LedTask_Handler);
            state = 1;
            FreeRTOS_delay_ms(20);
        }
    }
}
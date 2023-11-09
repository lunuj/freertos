/*
 * @Author: lunuj
 * @Date: 2023-10-29 23:38:03
 * @LastEditTime: 2023-11-10 01:10:28
 * @FilePath: \freertos\src\main.c
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */
#include "main.h"
TaskHandle_t Task_Handler;
void led_task(void *pvParameters);


int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_SetBits(GPIOC, GPIO_Pin_13);

	GPIO_Init(GPIOC, &GPIO_InitStructure);

	OLED_Init();
	OLED_ShowString(1,1,"Running");

	xTaskCreate(
    (TaskFunction_t)	led_task,
    (const char *)		"led_task",
    (uint16_t)			128,
    (void *)			NULL,
    (UBaseType_t)		3,
    (TaskHandle_t)		&Task_Handler);

	vTaskStartScheduler();
}

void led_task(void *pvParameters){
	while (1)
	{
		GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)!GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_13));
		FreeRTOS_delay_ms(500);
	}
}
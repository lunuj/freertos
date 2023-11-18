#ifndef __MYTASK_H__
#define __MYTASK_H__

#include "stm32f10x.h"

#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Serial.h"

#include "FreeRTOS.h"
#include "Queue.h"
#include "task.h"

void MyTask_Init();

void led_task(void *pvParameters);

void oled_task(void *pvParameters);

void key_task(void *pvParameters);

void send_task(void *pvParameters);

void receive_task(void *pvParameters);



#endif // __MYTASK_H__
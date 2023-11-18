#ifndef __MY_FREERTOS_H__
#define __MY_FREERTOS_H__
#include "stm32f10x.h"
#include "Serial.h"

#include "FreeRTOS.h"
#include "Queue.h"
#include "task.h"
void My_FreeRTOS_Init();

void Monitor_Task();

#endif // __MY_FREERTOS_H__
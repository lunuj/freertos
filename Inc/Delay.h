#ifndef __DELAY_H
#define __DELAY_H
#define FreeRTOS_ms 
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "Queue.h"
#include "task.h"

void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);

void FreeRTOS_delay_ms(u32 ms);

#endif

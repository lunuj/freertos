/*
 * @Author: lunuj
 * @Date: 2023-10-29 23:38:03
 * @LastEditTime: 2023-10-30 00:02:02
 * @FilePath: \freertos\src\main.c
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */
#include "main.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	while (1)
	{
		
	}
}

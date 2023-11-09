/*
 * @Author: lunuj
 * @Date: 2023-09-18 16:09:25
 * @LastEditTime: 2023-09-20 01:10:20
 * @FilePath: \test\Hardware\Key.c
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */


#include "stm32f10x.h"
#include "Key.h"
#include "Delay.h"

/**
 * @description: 初始化按键
 * @return {*}
 */
void Key_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = Key_0 | Key_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/**
 * @description: 
 * @param {u16} key:输入的端口
 * @return {u8}:返回当前端口状态
 */
u8 Key_GetNum(u16 key){
    u8 KeyNum = 0;
    if (GPIO_ReadInputDataBit(GPIOA, key) == 0)
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(GPIOA, key) == 0);
        Delay_ms(20);
        KeyNum = 1;
    }
    
    return KeyNum;
}
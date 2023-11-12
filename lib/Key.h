/*
 * @Author: lunuj
 * @Date: 2023-09-18 15:46:45
 * @LastEditTime: 2023-11-13 00:10:17
 * @FilePath: \freertos\lib\Key.h
 * @Description: led头文件
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */

#ifndef __KEY_H
#define __KEY_H

#define Key_Port GPIOC
#define Key_Periph RCC_APB2Periph_GPIOA
#define Key_0 GPIO_Pin_14
#define Key_1 GPIO_Pin_6

void Key_Init(void);
u8 Key_GetNum(u16 key);

#endif
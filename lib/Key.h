/*
 * @Author: lunuj
 * @Date: 2023-09-18 15:46:45
 * @LastEditTime: 2023-09-20 01:05:42
 * @FilePath: \test\Hardware\Key.h
 * @Description: led头文件
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */

#ifndef __KEY_H
#define __KEY_H

#define Key_0 GPIO_Pin_5
#define Key_1 GPIO_Pin_6

void Key_Init(void);
u8 Key_GetNum(u16 key);

#endif
/*
 * @Author: lunuj
 * @Date: 2023-09-18 22:22:06
 * @LastEditTime: 2023-09-19 22:33:44
 * @FilePath: \test\Hardware\OLED.h
 * @Description: 
 * 
 * Copyright (c) 2023 by lunuj, All Rights Reserved. 
 */
#ifndef __OLED_H
#define __OLED_H

#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction)(x))

void OLED_Init(void);
void OLED_Clear(void);
void OLED_I2C_Stop(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);


#endif
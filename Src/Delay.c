#include "Delay.h"

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = SystemCoreClock/1000000 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 


void FreeRTOS_delay_ms(u32 ms){
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//系统已经运行
	{		
		if(ms>=1000/configTICK_RATE_HZ)						//延时的时间大于OS的最少时间周期 
		{ 
   			vTaskDelay(ms*configTICK_RATE_HZ/1000);	 		//FreeRTOS延时
		}
		ms = (ms*configTICK_RATE_HZ) % (1000);						//OS已经无法提供这么小的延时了,采用普通方式延时    
	}
	// Delay_us((u32)(ms*1000));				//普通方式延时
}
#include "systick.h"

// static Systick_cback  FunPtr_Arr[Max_callback];

void Dir_SysTick_Init(void)
{
    /* 1. 配置时钟源  1=AHB(72MHz) 0=AHB/8 */
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;

    SysTick->CTRL |= SysTick_CTRL_TICKINT; // 1产生中断（异常）

    SysTick->LOAD = 72000; // 1ms 产生一次中断

    SysTick->CTRL |= SysTick_CTRL_ENABLE; // 打开定时器使能

    for (u8 i = 0; i < Max_callback; i++)
    {
    }
}

__weak void Systick_CBack(void) {}

void SysTick_Handler(void)
{
    static uint16_t cnt = 0;
    cnt++;
    if (cnt > 1000)
    {
        cnt = 0;
        Systick_CBack();
    }
}

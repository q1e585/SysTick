#include "Usart.h"

#include "string.h"



uint8_t StrArr[100];
uint8_t len = 0;

void Dri_Usart_Init()
{
    RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN);

    // PA9 Tx cnf 10 mode 11
    GPIOA->CRH |= (GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1);
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;

    // PA10 Rx cnf 10 mode 00 输入
    GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10_0);
    GPIOA->CRH |= GPIO_CRH_CNF10_1;

    NVIC_SetPriorityGrouping(3);      // 设置优先级组 011 4个抢占优先 0个响应优先
    NVIC_SetPriority(USART1_IRQn, 5); // 设置usart1的优先级
    NVIC_EnableIRQ(USART1_IRQn);      // 使能中断

    USART1->BRR = 0x271; // 设置波特率为115200（没有误差）  时钟/16/brr/=115200;

    USART1->CR1 |= USART_CR1_TE;     // 发送使能
    USART1->CR1 |= USART_CR1_RE;     // 接受使能
    USART1->CR1 |= USART_CR1_RXNEIE; // 接收缓冲区非空中断使能 (RXNE interrupt enable)
    USART1->CR1 |= USART_CR1_IDLEIE; // IDLE中断使能 (IDLE interrupt enable)

    USART1->CR1 &= ~USART_CR1_M;   // 设置字长：0：一个起始位，8个数据位，n个停止位；1：一个起始位，9个数据位，n个停止位。
    USART1->CR1 &= ~USART_CR1_PCE; // 禁止校验

    USART1->CR2 &= ~USART_CR2_STOP; // 00 一个停止位

    USART1->CR1 |= USART_CR1_UE; // usart使能
}

void Dri_Usart_SendChr(uint8_t chr)
{
    while (!(USART1->SR & USART_SR_TXE))
        ;
    USART1->DR = chr;
}

void Dri_Usart_SendStr(uint8_t *str)
{
    uint8_t i = 0;
    while (str[i] != '\0')
    {
        Dri_Usart_SendChr(str[i]);
        i++;
    }
}

// uint8_t Dir_Usart_ReciveChr(void)
// {
//     while (!(USART1->SR & USART_SR_RXNE))
//         ;
//     return USART1->DR;
// }

// void Dir_Usart_ReciveStr(void)
// {
//     uint8_t i = 0;
//     while (1)
//     {
//         while (!(USART1->SR & USART_SR_RXNE))
//         {
//             if (USART1->SR & USART_SR_IDLE)
//             {
//                 return;
//             }
//         }
//         StrArr[i] = USART1->DR;
//         i++;
//     }
// }

void USART1_IRQHandler(void)
{

    if (USART1->SR & USART_SR_RXNE)
    {
        StrArr[len] = USART1->DR;
        len++;
    }
    if (USART1->SR & USART_SR_IDLE)
    {

        // 清除标志位
        USART1->SR;
        USART1->DR;

        
        Dri_Usart_SendStr(StrArr); // 验证是否接收到
        //清除数组
        len = 0;
        memset(StrArr, 0, sizeof(StrArr));
    }
}


int fputc(int ch, FILE *f)
{
    
    Dri_Usart_SendChr((uint8_t)ch);
    
    return ch;
}


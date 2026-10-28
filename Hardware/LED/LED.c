#include "LED.h"
#include "delay.h"


uint32_t leds[3] = {
    LED1, LED2, LED3};

void Int_Led_OffAll(void)
{
    GPIOA->ODR |= (LED1 | LED2 | LED3);
}
void Int_Led_Init(void)
{
    // 1.打开rcc apb2enr pa使能
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // 设置工作模式
    GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1 | GPIO_CRL_MODE0 | GPIO_CRL_CNF1);
    GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
    // cnf 00 推挽   mode 11; 高速
    GPIOA->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1);
    GPIOA->CRH |= GPIO_CRH_MODE8;
    Int_Led_OffAll();
}

void Int_Led_Off(uint32_t i)
{
    GPIOA->ODR |= leds[i];
}

void Int_Led_On(uint32_t i)
{
    GPIOA->ODR &= ~leds[i];
}

void Int_Led_Run(uint8_t speed)
{
   static  uint8_t i =0;
   Int_Led_On(i);
   Delay_ms(speed*10);
   Int_Led_Off(i);
   i++;
   if(i==3) i=0;
}

void Int_Led_toggle(uint32_t i){
    GPIOA->ODR ^= leds[i];
}





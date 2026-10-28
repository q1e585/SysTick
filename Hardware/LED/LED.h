#ifndef _LED_H
#define _LED_H

#include<stm32f10x.h>

#define LED1 GPIO_ODR_ODR0
#define LED2 GPIO_ODR_ODR1
#define LED3 GPIO_ODR_ODR8


void Int_Led_Init(void);

void Int_Led_OffAll(void);

void Int_Led_Off(uint32_t i);

void Int_Led_On(uint32_t i);

void Int_Led_Run(uint8_t speed);


void Int_Led_toggle(uint32_t i);

#endif /* _LED_H */


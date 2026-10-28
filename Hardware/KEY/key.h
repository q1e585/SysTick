#ifndef _KEY_H
#define _KEY_H

#include <stm32f10x.h>

// #define SW5 GPIO_IDR_IDR10


void Int_key_Init(void);

void Exti_callback(void);

#endif /* _KEY_H */

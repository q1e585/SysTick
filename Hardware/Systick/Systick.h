#ifndef _SYSTICK_H
#define _SYSTICK_H

#define Max_callback 5
#define u8 uint8_t

#include "stm32f10x.h"


// typedef void(*Systick_cback(u8 parm)); 

void Dir_SysTick_Init(void);


void Systick_CBack(void);

// void RegistCallBackFun(Systick_cback);


#endif /* _SYSTICK_H */


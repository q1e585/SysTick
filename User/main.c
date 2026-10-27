#include "stm32f10x.h" 

#include "Systick.h"
#include "led.h"

#include "USART.h"


void Systick_CBack(void) {
    Int_Led_toggle(2);  
}

int main(void)
{
	Dri_Usart_Init();

	Int_Led_Init();
	 
	Dir_SysTick_Init();
	
	
	while (1)
	{
	}
}



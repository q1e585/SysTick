#include "stm32f10x.h"

#include "Systick.h"
#include "led.h"
#include "key.h"
#include "USART.h"
#include "eeprom.h"
#include "string.h"

uint8_t speed = 100;


void Exti_callback()
{
	speed = 10;
	 
	 Int_Eeprom_Writebyte(speed, 0x00);
	
}

int main(void)
{

	Dri_Usart_Init();
	Int_key_Init();
	Int_Led_Init();
	Dir_SysTick_Init();
	Int_Eeprom_Init();

	printf("%d\r\n",speed);

	speed = Int_Eeprom_Readbyte(0x00);

	printf("%d\r",speed);
	while (1)
	{
		//  Int_Led_Run(speed);
	}
}

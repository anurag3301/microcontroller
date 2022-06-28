#include "stm32f4xx.h"
#define GPIOAEN			(1U<<0)
#define PIN5			(1U<<5) // set to 0U to turn off
#define LED_PIN			PIN5


int main(void)
{

	RCC->AHB1ENR |=GPIOAEN;

	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

    GPIOA->ODR |=LED_PIN;
}

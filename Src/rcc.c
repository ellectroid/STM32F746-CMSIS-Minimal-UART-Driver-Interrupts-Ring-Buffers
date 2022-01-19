#include "rcc.h"

/*
 * Private functions
 */
void rcc_usart1();
void rcc_gpio_porta();
void rcc_gpio_portb();

void rcc_setup() {
	rcc_usart1();
	rcc_gpio_porta();
	rcc_gpio_portb();
}

void rcc_usart1() {
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
}

void rcc_gpio_porta() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}

void rcc_gpio_portb() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
}

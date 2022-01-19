#include "gpio.h"

/*
 * Private functions
 */

void gpio_setup_porta();
void gpio_setup_portb();

void gpio_setup() {
	gpio_setup_porta();
	gpio_setup_portb();
}

void gpio_setup_porta() {
	/*
	 * PA9 USART1 TX
	 */
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER9_0)) | GPIO_MODER_MODER9_1; //PA9 set to alternate function
	GPIOA->AFR[1] = (GPIOA->AFR[1] & ~(1U << 7)) | (0x07 << 4); //PA9 to AF7
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT9; //PA9 output push-pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR9; //PA9 output speed very high
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9; //PA9 no pull-up no pull-down

}
void gpio_setup_portb() {
	/*
	 * PB7 USART1 RX
	 */
	GPIOB->MODER = (GPIOB->MODER & ~(GPIO_MODER_MODER7_0)) | (GPIO_MODER_MODER7_1); //PB7 set to alternate function
	GPIOB->AFR[0] = (GPIOB->AFR[0] & ~(1U << 31)) | (0x07 << 28); //PB7 to AF7
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_7); //PB7 output push-pull
	GPIOB->OSPEEDR |= (GPIO_OSPEEDR_OSPEEDR7); //PB7 output speed very high
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR7); //PB7 no pull-up no pull-down

}

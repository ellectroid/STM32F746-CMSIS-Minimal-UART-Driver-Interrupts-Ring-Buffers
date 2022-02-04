#include "nvic.h"

void nvic_setup(void) {
	NVIC->IP[USART1_IRQn] = (uint8_t) (16U << 4U); //USART1 interrupt priority to 16 (lowest)
	NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void) {
	NVIC_ClearPendingIRQ(USART1_IRQn); //clear pending flag
	if (USART1->ISR & USART_ISR_RTOF) { //if receiver timeout

	} else if (USART1->ISR & USART_ISR_TXE) { //if send register empty
		uart1_tx_buffer_current_element_pointer = (uart1_tx_buffer_current_element_pointer + 1U) % UART_TX_BUFFER_LENGTH; //increment pointer to current element in ring
		USART1->TDR = uart1_tx_buffer[uart1_tx_buffer_current_element_pointer];
		if (uart1_tx_buffer_current_element_pointer == uart1_tx_buffer_last_element_pointer) {
			USART1->CR1 &= ~USART_CR1_TXEIE;
		}

	} else if (USART1->ISR & USART_ISR_RXNE) { //if receive register not empty

	} else if (USART1->ISR & USART_ISR_ORE) { //if overrun error

	} else if (USART1->ISR & (USART_ISR_FE | USART_ISR_NE)) { //if frame error or noise

	}
//determine what caused the interrupt
}

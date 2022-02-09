#include "nvic.h"

void nvic_setup(void) {
	NVIC->IP[USART1_IRQn] = (uint8_t) (16U << 4U); //USART1 interrupt priority to 16 (lowest)
	NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void) {
	NVIC_ClearPendingIRQ(USART1_IRQn); //clear pending flag
	if ((usartpointer1->ISR & USART_ISR_TXE) && (usartpointer1->CR1 & USART_CR1_TXEIE)) { //if send register empty
		uart1_tx_buffer_current_element_pointer = (uart1_tx_buffer_current_element_pointer + 1U) % UART_TX_BUFFER_LENGTH; //increment pointer to current element in ring & there was data to send
		usartpointer1->TDR = uart1_tx_buffer[uart1_tx_buffer_current_element_pointer];
		if (uart1_tx_buffer_current_element_pointer == uart1_tx_buffer_last_element_pointer) {
			usartpointer1->CR1 &= ~USART_CR1_TXEIE;
		}

	}
	if ((usartpointer1->ISR & USART_ISR_RXNE) && (usartpointer1->CR1 & USART_CR1_RXNEIE)) { //if receive register not empty & we were expecting data
		uart1_rx_buffer_current_element_pointer++; //increment pointer
		uart1_rx_buffer_current_element_pointer %= uart1_rx_buffer_length; //if pointer overflow, reset
		*(uart1_rx_buffer_memory_address + uart1_rx_buffer_current_element_pointer) = usartpointer1->RDR;
		if ((uart1_rx_buffer_current_element_pointer == (uart1_rx_buffer_length - 1U)) && (uart1_rx_mode == UART_IT_RX_BUFFER_SINGLE)) {
			usartpointer1->CR1 &= ~USART_CR1_RXNEIE; //if single buffer mode and wrote the last element, stop interrupts (reception ended)
		}

	}
}

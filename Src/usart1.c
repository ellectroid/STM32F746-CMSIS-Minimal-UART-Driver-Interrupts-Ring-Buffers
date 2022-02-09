#include "usart1.h"

void usart_enable(USART_TypeDef *USART) {
	USART->CR1 |= USART_CR1_UE; //USART1 Enable
}
void usart_disable(USART_TypeDef *USART) {
	USART1->CR1 &= ~USART_CR1_UE; //USART1 Disable
}
void usart_enable_tx(USART_TypeDef *USART) {
	USART1->CR1 |= USART_CR1_TE; // USART Transmitter enabled
}
void usart_disable_tx(USART_TypeDef *USART) {
	USART1->CR1 &= ~USART_CR1_TE; //USART Transmitter disabled
}
void usart_enable_rx(USART_TypeDef *USART) {
	USART1->CR1 |= USART_CR1_RE; //USART Receiver enabled
}
void usart_disable_rx(USART_TypeDef *USART) {
	USART1->CR1 &= ~USART_CR1_RE; //USART Receiver disabled
}


void usart_it_setup(USART_TypeDef *USART) {
	//Set all configs to Reset Value
	USART->CR1 = 0x00;
	USART->CR2 = 0x00;
	USART->CR3 = 0x00;
	USART->BRR = 0x00;
	USART->GTPR = 0x00;
	USART->RQR = 0x00;
	USART->ISR = 0x020000C0;

	USART->CR1 &= ~(USART_CR1_M); //Set word length 8;
	USART->CR3 |= USART_CR3_OVRDIS; //disable receiver overrun error
	USART->BRR = 0x683; //Set baudrate to 9600 (Fck = 16MHz)

	for (uint32_t i = 0; i < UART_TX_BUFFER_LENGTH; i++) {
		uart1_tx_buffer[i] = 'a'; //make sure data buffer is cleared
	}

	uart1_tx_buffer_last_element_pointer = 0;
	uart1_tx_buffer_current_element_pointer = 0;
	uart1_rx_buffer_current_element_pointer = 0;
	usartpointer1 = USART;
	//not activating transmission interrupts, activate on demand
}

uint32_t usart_it_sendArray(USART_TypeDef *USART, uint8_t data[], uint32_t length) {
	//returns number of elements put into buffer array
	if (length <= 0)
		return (uint32_t) 0; //idiot-proofing
	uint32_t bytesPut = 0;

	//stop TXE interrupts so that pointers don't move while we do math
	USART->CR1 &= ~USART_CR1_TXEIE;

	//Determine how much free space the ring buffer has (how much available to overwrite; from after last pointer around the ring and including current element)
	uint32_t max_free_space_tx_buffer = uart1_it_tx_getBufferFreeSpace();

	//for as long as there is something to put and enough room, write data into buffer

	if (USART->ISR & USART_ISR_TC)
		uart1_tx_buffer_last_element_pointer--; //compensating if no communication happening, will increment in while loop

	while (bytesPut < length && bytesPut < max_free_space_tx_buffer) {
		uart1_tx_buffer_last_element_pointer = (uart1_tx_buffer_last_element_pointer + 1U) % UART_TX_BUFFER_LENGTH; //increment last element pointer in the ring
		uart1_tx_buffer[uart1_tx_buffer_last_element_pointer] = data[bytesPut];
		bytesPut++;
	}

	if (USART->ISR & USART_ISR_TC) { //if no transmission, load the first element
		USART->TDR = uart1_tx_buffer[uart1_tx_buffer_current_element_pointer];
	}

	USART->CR1 |= USART_CR1_TXEIE; //activate interrupts again

	return bytesPut; //return how many bytes were written to buffer array
}
uint32_t uart1_it_tx_getBufferFreeSpace(void) {
	if (uart1_tx_buffer_last_element_pointer > uart1_tx_buffer_current_element_pointer) {
		return (UART_TX_BUFFER_LENGTH - (uart1_tx_buffer_last_element_pointer - uart1_tx_buffer_current_element_pointer));
	} else if (uart1_tx_buffer_last_element_pointer < uart1_tx_buffer_current_element_pointer) {
		return ((uart1_tx_buffer_current_element_pointer - uart1_tx_buffer_last_element_pointer));
	}
	return (UART_TX_BUFFER_LENGTH);

}

void usart_it_receiveArray(USART_TypeDef *USART, uint8_t data[], uint32_t length, uint8_t mode) {
	if (length <= 0 || mode > 1 || mode < 0)
		return; //idiotproofing
	uart1_rx_buffer_current_element_pointer = -1U; //will be turned to 0 on reception
	uart1_rx_buffer_length = length;
	uart1_rx_buffer_memory_address = data;
	uart1_rx_mode = mode;
	if (USART->ISR & USART_ISR_RXNE) {
		USART->RQR |= USART_RQR_RXFRQ; //if RDR is not empty, we need to flush it & clear RXNE flag

	}
	USART->CR1 |= USART_CR1_RXNEIE; //activate interrupt on byte received
}

void usart_it_stopReceiveArray(USART_TypeDef *USART) {
	USART->CR1 &= ~USART_CR1_RXNEIE; //disable reception interrupt

}

#include "usart1.h"

void uart1_setup() {
	//Set all configs to Reset Value
	USART1->CR1 = 0x00;
	USART1->CR2 = 0x00;
	USART1->CR3 = 0x00;
	USART1->BRR = 0x00;
	USART1->GTPR = 0x00;
	USART1->RQR = 0x00;
	USART1->ISR = 0x020000C0;

	USART1->CR1 &= ~(USART_CR1_M); //Set word length 8

	USART1->CR2 |= USART_CR2_RTOEN; //enable receiver timeout
	USART1->RTOR = 0x01; //receiver times out after one full bit without next start bit

	USART1->BRR = 0x683; //Set baudrate to 9600 (Fck = 16MHz)
}

void uart1_enable() {
	USART1->CR1 |= USART_CR1_UE; //USART1 Enable
}
void uart1_disable() {
	USART1->CR1 &= ~USART_CR1_UE; //USART1 Disable
}
void uart1_enable_tx() {
	USART1->CR1 |= USART_CR1_TE; // USART Transmitter enabled
}
void uart1_disable_tx() {
	USART1->CR1 &= ~USART_CR1_TE; //USART Transmitter disabled
}
void uart1_enable_rx() {
	USART1->CR1 |= USART_CR1_RE; //USART Receiver enabled
}
void uart1_disable_rx() {
	USART1->CR1 &= ~USART_CR1_RE; //USART Receiver disabled
}

void uart1_sendByte(uint8_t data) {
	uart1_sendArray(&data, 1U);
}
void uart1_sendArray(uint8_t data[], uint32_t length) {
	USART1->ICR &= USART_ICR_TCCF; //clear transfer complete flag
	uint32_t pointer = 0; // what array element to send
	while (1) {
		if (data[pointer] != '\0' && pointer < length) { //check if not string termination character or end of array
			while (!(USART1->ISR & USART_ISR_TXE)); //wait while data is sent out to shift register
			USART1->TDR = data[pointer];
			pointer++;
		} else
			break;
	}
	while (!(USART1->ISR & USART_ISR_TC)); //Wait while Transfer Complete flag is set
	USART1->ICR &= USART_ICR_TCCF; //clear transfer complete flag
}

void uart1_receiveByte(uint8_t *data) {

	uart1_receiveArray(data, 1U);

}
void uart1_receiveArray(uint8_t *arraypointer, uint32_t length) {
	uint8_t *currentpointer = arraypointer;
	for (uint32_t k = 0; k < length; k++) { //fill the buffer with nulls so that it doesn't retain data from previous transmissions
		*(arraypointer + k) = '\0';
	}
	while (!(USART1->ISR & USART_ISR_RXNE)); //wait indefinitely for the beginning of the transmission
	USART1->ICR |= USART_ICR_RTOCF; //make sure receiver timeout flag is cleared
	while (!(USART1->ISR & USART_ISR_RTOF)) { //while not receiver timeout
		if (((USART1->ISR & USART_ISR_RXNE)) && (currentpointer < arraypointer + length)) { //if buffer is not full yet and there is new data
			*currentpointer = USART1->RDR;
			currentpointer++;
			USART1->RQR |= USART_RQR_RXFRQ; //clear RXNE data received flag
		}
	}
	USART1->RQR |= USART_RQR_RXFRQ; //clear RXNE data received flag for buffer overflow data
	USART1->ICR |= USART_ICR_ORECF; //clear receiver overrun flag for buffer array overflow
	USART1->ICR |= USART_ICR_RTOCF; //when receiver timed out and we're done, clear the flag
}

void uart1_it_setup() {
	//Set all configs to Reset Value
	USART1->CR1 = 0x00;
	USART1->CR2 = 0x00;
	USART1->CR3 = 0x00;
	USART1->BRR = 0x00;
	USART1->GTPR = 0x00;
	USART1->RQR = 0x00;
	USART1->ISR = 0x020000C0;

	//Set word length 8;
	USART1->CR1 &= ~(USART_CR1_M);
	USART1->CR2 |= USART_CR2_RTOEN; //enable receiver timeout
	USART1->CR3 |= USART_CR3_EIE; //Enable frame error, overrun error, noise flag error
	USART1->RTOR = 0x01; //receiver times out after one full bit without next start bit

	USART1->BRR = 0x683; //Set baudrate to 9600 (Fck = 16MHz)

	for (uint32_t i = 0; i < UART_TX_BUFFER_LENGTH; i++) {
		uart1_tx_buffer[i] = 'a'; //make sure data buffer is cleared
	}

	uart1_tx_buffer_last_element_pointer = 0;
	uart1_tx_buffer_current_element_pointer = 0;

	//not activating transmission interrupts, activate on demand
}

uint32_t uart1_it_sendArray(uint8_t data[], uint32_t length, uint8_t include_string_terminator) {

	if (length <= 0)
		return (uint32_t) 0; //idiot-proofing
	if (!include_string_terminator)
		length--;
	if (length <= 0)
		return (uint32_t) 0; //idiot-proofing
	uint32_t bytesPut = 0;

	//stop TXE interrupts so that pointers don't move while we do math
	USART1->CR1 &= ~USART_CR1_TXEIE;

	//Determine how much free space the ring buffer has (how much available to overwrite; from after last pointer around the ring and including current element)
	uint32_t max_free_space_tx_buffer = uart1_it_tx_getBufferFreeSpace();

	//for as long as there is something to put and enough room, write data into buffer

	if (USART1->ISR & USART_ISR_TC)
		uart1_tx_buffer_last_element_pointer--; //compensating if no communication happening, will increment in while loop

	while (bytesPut < length && bytesPut < max_free_space_tx_buffer) {
		uart1_tx_buffer_last_element_pointer = (uart1_tx_buffer_last_element_pointer + 1U) % UART_TX_BUFFER_LENGTH; //increment last element pointer in the ring
		uart1_tx_buffer[uart1_tx_buffer_last_element_pointer] = data[bytesPut];
		bytesPut++;
	}

	if (USART1->ISR & USART_ISR_TC) { //if no transmission, load the first element
		USART1->TDR = uart1_tx_buffer[uart1_tx_buffer_current_element_pointer];
	}

	USART1->CR1 |= USART_CR1_TXEIE; //activate interrupts again

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

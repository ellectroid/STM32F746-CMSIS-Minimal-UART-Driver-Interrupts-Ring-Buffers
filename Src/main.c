#include "main.h"

int main(void) {

	/*
	 * HARDWARE SETUP
	 * */
	rcc_setup(); //clock for peripheral, clock will not be altered; therefore default HSI 16MHz clock even with external oscillator connected
	gpio_setup(); //set pin modes and functions
	usart_it_setup(USART1); //set control registers and settings for uart1
	usart_enable(USART1); //enable uart1
	usart_enable_tx(USART1); //enable tx line (wrapper)
	usart_enable_rx(USART1); //enable rx line (wrapper)
	nvic_setup(); //set interrupts and their priorities


	uint8_t message1[] = "Hello! Enter a line into circular buffer of length 8. "; //20 symbols
	uint8_t message2[] = "If element [3] is not 0, it will print the buffer back\r\n";

	//Welcome message using ring TX buffer
	usart_it_sendArray(USART1, message1, sizeof(message1) - 1U); // size-1 because I want no end of line char (returns number of elements put in buffer array)
	while (uart1_it_tx_getBufferFreeSpace() < (sizeof(message2) - 1U)); //wait while TX ring buffer has just enough space for the second line (but not fully empty)
	usart_it_sendArray(USART1, message2, sizeof(message2) - 1U); // size-1 because I want no end of line char

	uint8_t myReceiveBuffer[8] = { '0', '0', '0', '0', '0', '0', '0', '0' }; //setting up default values character '0'
	usart_it_receiveArray(USART1, myReceiveBuffer, 8, UART_IT_RX_BUFFER_CIRCULAR); //activate circular buffer reception, alternative is UART_IT_RX_BUFFER_SINGLE
	blink_ld1(); //LED will blink immediately as the program starts, showing this line is executed even before data is received
	while (myReceiveBuffer[3] == '0'); //keep waiting until myReceiveBuffer[3] is not '0', then print the entire buffer
	usart_it_sendArray(USART1, myReceiveBuffer, 8); //send array by putting its data into ring buffer
	usart_it_stopReceiveArray(USART1); //if you want to stop receiving data into buffer array, call this function; for UART_IT_RX_BUFFER_SINGLE reception is stopped automatically when buffer is full

	while (1) {

	}
	return 0;
}

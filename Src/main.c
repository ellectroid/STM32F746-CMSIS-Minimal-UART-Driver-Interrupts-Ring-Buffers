#include "main.h"

int main(void) {
	rcc_setup();
	gpio_setup();
	uart1_setup();
	uart1_enable();
	uart1_enable_tx();
	uart1_enable_rx();
	while (1) {
		uint8_t buffer[10];
		uint8_t x;
		uart1_sendByte('\r');uart1_sendByte('\n');

		uart1_sendByte('H');uart1_sendByte('i');

		uart1_sendByte('\r');uart1_sendByte('\n');

		uint8_t message[] = "Enter a string (10 chars max) and a digit to be sent to you:\r\n";
		uart1_sendArray(message, sizeof(message)/sizeof(message[0]));

		uart1_receiveArray(buffer, 10);
		uart1_sendArray(buffer, 10);

		uart1_sendByte('\r');
		uart1_sendByte('\n');

		uart1_receiveByte(&x);
		uart1_sendByte(x);
	}
	return 0;
}


#include "main.h"

int main(void) {
	rcc_setup();
	gpio_setup();
	uart1_setup();
	uart1_enable();
	uart1_enable_tx();
	uart1_enable_rx();
	while (1) {
		uint8_t buffer[8];
		uart1_receiveArray(buffer, 8);
		uart1_sendArray(buffer);
	}
	return 0;
}


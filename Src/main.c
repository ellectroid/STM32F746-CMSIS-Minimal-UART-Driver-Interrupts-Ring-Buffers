#include "main.h"

int main(void) {
	rcc_setup();
	gpio_setup();
	//uart1_setup();
	uart1_it_setup();
	uart1_enable();
	uart1_enable_tx();
	uart1_enable_rx();
	nvic_setup();
	uint8_t message1[] = "veryverylongmessage1"; //20 symbols
	uint8_t message2[] = "shortmessage";
	uint8_t message3[] = "NEW LINE!!!\r\n";
	uart1_it_sendArray(message1, sizeof(message1) / sizeof(message1[0]), 0U);
	uart1_it_sendArray(message1, sizeof(message1) / sizeof(message1[0]), 0U);
	uart1_it_sendArray(message1, sizeof(message1) / sizeof(message1[0]), 0U);
	blink_ld1();
	//while(uart1_it_tx_getBufferFreeSpace()<20);
	uart1_it_sendArray(message1, sizeof(message1) / sizeof(message1[0]), 0U);
	//uart1_it_sendArray(message2, sizeof(message2) / sizeof(message2[0]));
	//uart1_it_sendArray(message3, sizeof(message3) / sizeof(message3[0]));
	blink_ld1();
	//uart1_it_sendArray(message1, sizeof(message1) / sizeof(message1[0]));
	//uart1_it_sendArray(message2, sizeof(message2) / sizeof(message2[0]));
	//uart1_it_sendArray(message3, sizeof(message3) / sizeof(message3[0]));
	while (1) {

	}
	return 0;
}


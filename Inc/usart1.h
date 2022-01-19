#ifndef USART1_H_
#define USART1_H_
#include "stm32f746xx.h"

void uart1_setup();

void uart1_enable();
void uart1_disable();
void uart1_enable_tx();
void uart1_disnable_tx();
void uart1_enable_rx();
void uart1_disable_tx();

void uart1_sendByte(uint8_t data);
void uart1_sendArray(uint8_t data[], uint32_t length);

void uart1_receiveByte(uint8_t *data);
void uart1_receiveArray(uint8_t *arraypointer, uint32_t length);


#endif /* USART1_H_ */

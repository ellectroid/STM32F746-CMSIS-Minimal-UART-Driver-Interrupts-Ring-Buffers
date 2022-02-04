#ifndef USART1_H_
#define USART1_H_
#include "stm32f746xx.h"

#define UART_TX_BUFFER_LENGTH (64U)
#define UART_RX_BUFFER_LENGTH (64U)

uint8_t uart1_tx_buffer[UART_TX_BUFFER_LENGTH];
uint8_t uart1_rx_buffer[UART_RX_BUFFER_LENGTH];

uint32_t uart1_tx_buffer_last_element_pointer;
uint32_t uart1_tx_buffer_current_element_pointer;

void uart1_setup();
void uart1_it_setup(void);

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

uint32_t uart1_it_sendArray(uint8_t data[], uint32_t length, uint8_t include_string_terminator);

uint32_t uart1_it_tx_getBufferFreeSpace(void);
#endif /* USART1_H_ */

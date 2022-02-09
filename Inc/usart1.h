#ifndef USART1_H_
#define USART1_H_
#include "stm32f746xx.h"

#define UART_TX_BUFFER_LENGTH (64U)

uint8_t uart1_tx_buffer[UART_TX_BUFFER_LENGTH];

uint32_t uart1_tx_buffer_last_element_pointer;
uint32_t uart1_tx_buffer_current_element_pointer;

uint32_t uart1_rx_buffer_current_element_pointer;
uint8_t *uart1_rx_buffer_memory_address;
uint32_t uart1_rx_buffer_length;
uint8_t uart1_rx_mode;

USART_TypeDef *usartpointer1;

enum uart1_it_rx_mode{
	UART_IT_RX_BUFFER_SINGLE = 0,
	UART_IT_RX_BUFFER_CIRCULAR = 1
};

void usart_it_setup(USART_TypeDef *USART);

void usart_enable(USART_TypeDef *USART);
void usart_disable(USART_TypeDef *USART);
void usart_enable_tx(USART_TypeDef *USART);
void usart_disnable_tx(USART_TypeDef *USART);
void usart_enable_rx(USART_TypeDef *USART);
void usart_disable_tx(USART_TypeDef *USART);


uint32_t usart_it_sendArray(USART_TypeDef *USART, uint8_t data[], uint32_t length);
void usart_it_receiveArray(USART_TypeDef *USART, uint8_t data[], uint32_t length, uint8_t mode);
void usart_it_stopReceiveArray(USART_TypeDef *USART);
uint32_t uart1_it_tx_getBufferFreeSpace(void);
#endif /* USART1_H_ */

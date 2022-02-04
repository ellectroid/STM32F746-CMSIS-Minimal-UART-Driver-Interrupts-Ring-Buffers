#ifndef NVIC_H_
#define NVIC_H_
#include "stm32f746xx.h"
#include "core_cm7.h"
#include "usart1.h"

/*
extern uint8_t uart1_tx_pending;
extern uint8_t uart1_tx_buffer_pointer;
extern uint8_t uart1_tx_buffer[UART_TX_BUFFER_LENGTH];
extern uint32_t uart1_tx_message_length;
*/
void nvic_setup(void);

#endif /* NVIC_H_ */

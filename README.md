# STM32F469-Minimal-UART-Driver-Interrupts-Ring-Buffer
Minimalist Interrupt-based UART driver with ring buffers for STM32F746-Disco UART1 ST-Link COM Port

Clock: default, no changes (16MHz HSI).<br>
USART1 is the USART connected to ST-Link that makes virtual COM port on PC.<br><br>

This project is a proof of concept (that I can).<br>

Might be useful for someone who wants to figure out how the stuff works.<br>
I commented almost every line to make it simple to understand.<br><br>

Hardware:<br>
STM32F746 Disco board, Windows PC <br><br>

Software:<br>
STM32CubeIDE, Putty for UART communication;<br>
No libraries used except for CMSIS register definitions.

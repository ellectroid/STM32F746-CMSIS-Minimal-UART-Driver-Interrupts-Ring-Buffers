# STM32F746-Minimal-Blocking-Uart-Driver
Minimalist blocking UART driver for STM32F746-Disco UART1 ST-Link COM Port

Clock: default, no changes (must be 16MHz HSI).<br>
Only activate GPIO, set them to Alternate Function USART1, Very High Speed.<br>
USART1 is the USART connected to ST-Link that makes virtual COM port on PC.<br><br>

This project is a proof of concept (not of UART, but of me - that I can).<br>
It's not as modular as it could be, but it's not intended to be perfect. Might be useful for someone who wants to figure out how the stuff works.<br>
I commented everything to make it simple to understand.<br><br>

Hardware:<br>
STM32F746 Disco board, Windows PC <br><br>

Software:<br>
STM32CubeIDE v1.7.0, Putty for UART communication;<br>
No libraries used except for CMSIS register definitions.

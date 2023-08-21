#pragma once

void uart_init(void);

void uart_putchar(char c);

void USART_TransmitString(const char* str);

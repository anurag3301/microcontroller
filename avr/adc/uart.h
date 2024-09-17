#pragma once
#include "stdio.h"
#include <stdbool.h>

void uart_init(void);

void uart_putchar(char c, FILE *stream);

char uart_getchar(FILE *steam);

void uart_transmit(char data);

char uart_receive(void);

bool uart_is_data_avaiable();

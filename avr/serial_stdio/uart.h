#pragma once
#include "stdio.h"

void uart_init(void);

void uart_putchar(char c, FILE *stream);

char uart_getchar(FILE *steam);

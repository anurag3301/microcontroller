#define F_CPU 16000000
#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <stdio.h>
#include "uart.h"

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
FILE uart_io = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);


int main(void){

    uart_init();

    stdout = &uart_output;
    stdin = &uart_input;
    char input[100] = {0};

    while (1) {
        puts("Enter a word and press ENTER: ");
        scanf("%s", input);
        printf("You entered %s\n", input);
    }
    return 0;
    
}

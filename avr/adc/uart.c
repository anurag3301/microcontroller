#define F_CPU 8000000
#define BAUD 9600

#include <avr/io.h>
#include <util/setbaud.h>
#include "uart.h"
#include "stdio.h"
#include <stdbool.h>


void uart_init(void){
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;

    UCSRB = _BV(RXEN) | _BV(TXEN) | _BV(RXCIE);

    UCSRC = _BV(URSEL) | _BV(UCSZ0) | _BV(UCSZ1);
}

void uart_putchar(char c, FILE *stream) {
    if(c == '\n'){
        uart_putchar('\r', stream);
    }

    loop_until_bit_is_set(UCSRA, UDRE);
    UDR = c;
}

char uart_getchar(FILE *steam){
    loop_until_bit_is_set(UCSRA, RXC);
    char read = UDR;
    uart_putchar(read, steam);
    return read;
}

void uart_transmit(char data) {
    while (!(UCSRA & (1 << UDRE)));
    UDR = data;
    while (!(UCSRA & (1 << TXC)));
}

char uart_receive(void) {
    return UDR;
}

bool uart_is_data_avaiable(){
    return UCSRA & (1 << RXC);
}

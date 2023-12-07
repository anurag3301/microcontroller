
#define F_CPU 16000000
#define BAUD 9600

#include <avr/io.h>
#include <util/setbaud.h>
#include "uart.h"
#include "stdio.h"


void uart_init(void){
    // UBRR (UART Baud Rate Register) is a 16 bit resiter thats why
    // we have L and H. It store the calcuted baud using BAUD, UBRR._VALUE
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    // USCR stands for UART Control and Status Register
    // _BV just does shift operation eg. _BV(3) -> 0b00001000
    // But not recommened to use as its not standerdiesd
#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); // set the frame
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}

void uart_putchar(char c, FILE *stream) {
    if(c == '\n'){
        uart_putchar('\r', stream);
    }

    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

char uart_getchar(FILE *steam){
    loop_until_bit_is_set(UCSR0A, RXC0);
    char read = UDR0;
    uart_putchar(read, steam);
    return read;
}


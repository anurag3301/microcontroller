
#define F_CPU 16000000
#define BAUD 9600

#include <avr/io.h>
#include <util/setbaud.h>
#include "uart.h"


void uart_init(void){
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}

void uart_putchar(char c) {
    while (!(UCSR0A & (1 << UDRE0))); 
    UDR0 = c;
}

void USART_TransmitString(const char* str) {
    for (uint8_t i = 0; str[i] != '\0'; i++) {
        uart_putchar(str[i]);
    }
}


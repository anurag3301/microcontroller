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
#define BLINK_DELAY_MS 1000

int main(void){
    uart_init();
    stdout = &uart_output;
    stdin = &uart_input;
    
    DDRB |= 1<<PB5;

    while(1){
        PORTB |= 1<<PB5;
        printf("Trun on %x\n", PINB);
        _delay_ms(BLINK_DELAY_MS);

        PORTB &= ~(1<<PB5);
        printf("Trun off %x\n", PINB);
        _delay_ms(BLINK_DELAY_MS);

    }
    
    return 0;
    
}

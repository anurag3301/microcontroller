#define F_CPU 8000000
#define BAUD 9600
#define CHECK_BIT(byte, bitnum) ((byte >> bitnum) & 1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "uart.h"

volatile uint16_t adc_result = 0;

void ADC_ISR_Init(uint8_t channel) {
    ADMUX = _BV(REFS0) | (channel & 0x0F);
    ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
    ADCSRA |= (1 << ADSC);
}

ISR (ADC_vect){
    adc_result = ADC;
    ADCSRA |= (1 << ADSC);
}

int main(void){
    stdout = fdevopen((int (*)(char, FILE *))uart_putchar, NULL);
    stdin = fdevopen(NULL, (int (*)(FILE *))uart_getchar);

    uart_init();
    ADC_ISR_Init(0);
    sei();
    while (1) {
        printf("%d\n\r", adc_result);
        _delay_ms(100);
    }
    return 0;
    
}

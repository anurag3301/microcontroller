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

void ADC_Init(void) {
    ADMUX = _BV(REFS0); // source AVCC
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
}

uint16_t ADC_Read(uint8_t channel){
    ADMUX |= _BV(REFS0) | (channel & 0x0F);
    ADCSRA |= _BV(ADSC);
    while(CHECK_BIT(ADCSRA, ADSC) == 1);

    // Manually calculate ADC value
    /* uint16_t adc_value = ADCL; */
    /* adc_value |= (ADCH << 8); */
    /* return adc_value; */

    return ADC;
}

int main(void){
    stdout = fdevopen((int (*)(char, FILE *))uart_putchar, NULL);
    stdin = fdevopen(NULL, (int (*)(FILE *))uart_getchar);

    uart_init();
    ADC_Init();

    while (1) {
        printf("%d\n\r", ADC_Read(0));
        _delay_ms(100);
    }
    return 0;
    
}

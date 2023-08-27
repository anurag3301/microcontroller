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

void adc_init(void){
    // Set the division factor
    ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
    ADCSRA |= (1<<ADEN);    // Enable ADC module
    ADMUX = (1<<REFS0);     // Set the volage reference for ADC to VCC
}

uint16_t read_adc(uint8_t channel){
    // Keep the exising setting and set the passed channel
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
    /* ADMUX = (ADMUX & 0b11111000) | (channel & 0b00000111); */

    ADCSRA |= (1<<ADSC);        // Start conversion
    while(ADCSRA & (1<<ADSC));  // Wait for conversion
    return ADC;
}



int main(void){

    uart_init();

    stdout = &uart_output;
    stdin = &uart_input;
    
    adc_init();
    
    int adc_value;
    while (1) {
        adc_value = read_adc(0); 
        printf("%d\n", adc_value);
        _delay_ms(100);
    }
    return 0;
    
}

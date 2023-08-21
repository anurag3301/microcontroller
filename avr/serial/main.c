#define F_CPU 16000000
#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <stdio.h>
#include "uart.h"


int main(void){
    char str[100] = {0};

    uart_init();

    uint64_t i = 0;

    while (1) {
        sprintf(str, "Num: %lu\r\n", i++); 
        USART_TransmitString(str);
        _delay_ms(100);
    }
    
}

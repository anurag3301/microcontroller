#define F_CPU 16000000
#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include "uart.h"


int main(void){
    uart_init();
    while (1) {
        USART_TransmitString("Hello, AVR!\r\n");
        _delay_ms(1000);
    }
    
}

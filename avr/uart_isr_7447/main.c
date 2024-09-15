#define F_CPU 8000000
#define BAUD 9600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "uart.h"
#include "7447.h"


char buf[100] = {0};
int pos = 0;

ISR(USART_RXC_vect){
    char c = uart_receive();
    uart_transmit(c);
    buf[pos++] = c;
}

bool isalldigit(const char* str){
    for(int i=0; str[i]!='\0'; i++){
        if(!isdigit(str[i])) return false;
    }
    return true;
}

int main(void){
    stdout = fdevopen((int (*)(char, FILE *))uart_putchar, NULL);
    stdin = fdevopen(NULL, (int (*)(FILE *))uart_getchar);
    Handel_7447 han = {
        .a = {&PORTA, PA1},
        .b = {&PORTA, PA2},
        .c = {&PORTA, PA3},
        .d = {&PORTA, PA4},
        .dec = {&PORTA, PA0}
    };

    init7447(&han);
    uart_init();
    sei();

    display7447(&han, 0xFF);

    char numbuf[100] = {0};
    int numpos = 0;

    printf("Enter a number to display: ");
    while (1) {
        if(buf[pos-1] == '\r' || buf[pos-1]=='\n'){
            buf[pos-1] = '\0';
            if(isalldigit(buf)){
                printf("\n\rDisplaying number: %s\n\r", buf);
                strcpy(numbuf, buf); 
                numpos = 0;
            }else
                printf("\n\rSorry only digits allowed\n\r");
            printf("Enter a number to display: ");
            pos = 0;
        }
        if(numbuf[numpos] == '\0'){
            display7447(&han, 0xFF);
            numpos = 0;
        }
        else{
            display7447(&han, 0xFF);
            _delay_ms(50);
            display7447(&han, numbuf[numpos++]-'0');
        }
        _delay_ms(1000);
    }
    return 0;
    
}

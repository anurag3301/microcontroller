#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 100


int main(void){
    DDRB |= 0B100000;

    while(1){
        PORTB |= 0B100000;
        _delay_ms(BLINK_DELAY_MS);

        PORTB &= ~0B100000;
        _delay_ms(BLINK_DELAY_MS);

    }
}

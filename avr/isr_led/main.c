#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define CHECK_BIT(byte, bitnum) ((byte >> bitnum) & 1)

ISR(INT0_vect){
    PORTA ^= _BV(0);
    _delay_ms(200);
}

ISR(INT1_vect){
    PORTA ^= _BV(1);
    _delay_ms(200);
}

ISR(INT2_vect){
    PORTA ^= _BV(2);
    _delay_ms(200);
}

int main() {
    DDRA |= _BV(0) | _BV(1) | _BV(2);
    DDRD &= ~(_BV(2) | _BV(3));
    DDRB &= ~(_BV(2));

    PORTD |= _BV(2) | _BV(3);
    PORTB |= _BV(2);

    GICR = 0xE0; MCUCR = 0x07; MCUCSR = 0x00;

    sei();

    while(1);
}

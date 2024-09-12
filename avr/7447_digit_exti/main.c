#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define CHECK_BIT(byte, bitnum) ((byte >> bitnum) & 1)
#define _BV(bit) (1 << (bit))

typedef struct {
    volatile uint8_t *port;
    uint8_t pin;
} Pin;

typedef struct {
    Pin a;
    Pin b;
    Pin c;
    Pin d;
    Pin dec;
} Handel_7447;

void pin_write(Pin p, uint8_t state);
void init7447(Handel_7447 *handle);
void display7447(Handel_7447 *handle, uint8_t num);

uint8_t num = 0;

ISR(INT0_vect){
    num++;
    num %= 10;
}

int main(void) {
    Handel_7447 han = {
        .a = {&PORTA, PA1},
        .b = {&PORTA, PA2},
        .c = {&PORTA, PA3},
        .d = {&PORTA, PA4},
        .dec = {&PORTA, PA0}
    };

    init7447(&han);

    DDRD |= _BV(PD2); PORTD |= _BV(PD2);

    GICR |= _BV(INT0);
    MCUCR |= 0x02;
    
    sei();
    while (1) {
        display7447(&han, num);
    }
}




void pin_write(Pin p, uint8_t state) {
    if (state) *p.port |= _BV(p.pin);
    else *p.port &= ~(_BV(p.pin));
}

void init7447(Handel_7447 *handle) {
    *(handle->a.port - 1) |= _BV(handle->a.pin);
    *(handle->b.port - 1) |= _BV(handle->b.pin);
    *(handle->c.port - 1) |= _BV(handle->c.pin);
    *(handle->d.port - 1) |= _BV(handle->d.pin);
    *(handle->dec.port - 1) |= _BV(handle->dec.pin);

    *handle->a.port &= ~(_BV(handle->a.pin));
    *handle->b.port &= ~(_BV(handle->b.pin));
    *handle->c.port &= ~(_BV(handle->c.pin));
    *handle->d.port &= ~(_BV(handle->d.pin));
    *handle->dec.port &= ~(_BV(handle->dec.pin));
}

void display7447(Handel_7447 *handle, uint8_t num) {
    pin_write(handle->a, CHECK_BIT(num, 0));
    pin_write(handle->b, CHECK_BIT(num, 1));
    pin_write(handle->c, CHECK_BIT(num, 2));
    pin_write(handle->d, CHECK_BIT(num, 3));
    pin_write(handle->dec, 1);
}

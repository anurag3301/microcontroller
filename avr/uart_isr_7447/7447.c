#include "7447.h"
#include <avr/io.h>
#define CHECK_BIT(byte, bitnum) ((byte >> bitnum) & 1)


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

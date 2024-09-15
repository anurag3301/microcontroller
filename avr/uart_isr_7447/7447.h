#ifndef _7447_H
#define _7447_H
#include <stdint.h>

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

#endif

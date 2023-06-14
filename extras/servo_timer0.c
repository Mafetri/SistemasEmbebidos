#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "myutils.h"

typedef struct {
    uint8_t tccr0a;
    uint8_t tccr0b;
    uint8_t tccr0;
    uint8_t ocr0a;
    uint8_t ocr0b;
} volatile timer0_t;

volatile timer0_t *timer0 = (timer0_t *)(0x44);
volatile unsigned char *timer0_timsk0 = (unsigned char *)(0x6E);

timer0_init() {
    // Configurar el pin OC0A (pin 6 en Arduino Nano) como salida
    PORTD |= (1 << 6);
    PORTB |= 1 << 5;
    DDRB |= 1 << 5;

    // Configurar Timer0 para generar una señal PWM en el pin OC0A
    timer0->ocr0a |= (1 << 1) | (1 << 0); 
    timer0->ocr0b |= (1 << 2); // Preescalador de 256, (4Mhz / 256 * 256 = 61hz)
    timer0->tccr0a = 200;   // Con dicho prescaler son 15.625 ticks por segundo o 1,5625 ticks cada 100us 
}

void set_servo_angle(int angle) {
    // Minimo 1ms = 1.000us = (con prescalar de 8) 2.000 ticks
    int pulse_with = 750;

    OCR0A = angle;
    delay_ms(500);
}

int main(void) {
    timer0_init();
    sei();
    // set_servo_angle(100);

    while(1){
        // nothing
    }
}

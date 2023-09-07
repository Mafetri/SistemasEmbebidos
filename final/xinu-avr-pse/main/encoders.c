#include <xinu.h>
#include <avr/interrupt.h>

// Global Variables
extern unsigned int left_wheel_ticks;
extern unsigned int right_wheel_ticks;
extern volatile unsigned char * PIN_D;

#define INT0 0
#define INT1 1
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

// Enalbes the interrupts of the D2 and D3 ports on rising edge
void encoder_init() {
    EIMSK |= (1 << INT0) | (1 << INT1);
    EICRA |= (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC00);
    sei();
}

ISR(INT0_vect) {
    right_wheel_ticks++;
}

ISR(INT1_vect) {
    left_wheel_ticks++;
}


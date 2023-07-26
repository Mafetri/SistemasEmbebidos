#include <xinu.h>

#define PORT_RIGHT_INPUT 2
#define PORT_LEFT_INPUT 3

// Global Variables
extern unsigned int left_wheel_ticks;
extern unsigned int right_wheel_ticks;
extern volatile unsigned char * PIN_D;

// Wheel Reader
// Reads the ticks of each wheel
int wheel_reader(void)
{
    // Local Variables
    unsigned char current_right_state = 0;
    unsigned char previous_right_state = 0;
    unsigned char current_left_state = 0;
    unsigned char previous_left_state = 0;

	while (1) {
        current_right_state = *PIN_D & (1 << PORT_RIGHT_INPUT);
        current_left_state = *PIN_D & (1 << PORT_LEFT_INPUT);

        if (current_right_state != previous_right_state) {
            right_wheel_ticks++;
        }

        if (current_left_state != previous_left_state) {
            left_wheel_ticks++;
        }

        previous_left_state = current_left_state;
        previous_right_state = current_right_state;

        sleepms(20);
	}
}

/*
Code for interruptions:
#include <avr/interrupt.h>

#define INT0 0
#define INT1 1
#define ISC10 2
#define ISC11 3


EIMSK |= (1 << INT0) | (1 << INT1);
EICRA |= (0 << ISC11) | (1 << ISC10);
sei();

ISR(INT0_vect) {
    current_right_state = *PIN_D & (1 << PORT_RIGHT_INPUT);
    if (current_right_state != previous_right_state) {
        right_wheel++;
    }
    previous_right_state = current_right_state;
}

ISR(INT1_vect) {
    current_left_state = *PIN_D & (1 << PORT_LEFT_INPUT);
    if (current_left_state != previous_left_state) {
        left_wheel++;
    }
    previous_left_state = current_left_state;
}
*/

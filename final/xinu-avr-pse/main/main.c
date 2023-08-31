#include <xinu.h>
#include <avr/interrupt.h>
#include "serial.h"
#include "mat.h"
#include "timer1.h"
#include "data_structures.h"

// Process with external code
extern int serial_output(void);
extern int rtc(void);
// extern int wheel_reader(void);
extern void encoder_init(void);
extern int locator(void);
extern int controller(void);

// Global Variables
unsigned int left_wheel_ticks;
unsigned int right_wheel_ticks;
unsigned long rtc_miliseconds;
float car_x = 0.0;
float car_y = 0.0;
float car_angle = 0.0;
volatile queue targets;

// Ports
volatile unsigned char *DDR_B = 0x24;
volatile unsigned char *PORT_B = 0x25;
volatile unsigned char *PIN_B = 0x23;
volatile unsigned char *DDR_D = 0x2A;
volatile unsigned char *PORT_D = 0x2B;
volatile unsigned char *PIN_D = 0x29;

// Main process
int main(void)
{
	serial_init();
	init_timer1();
	encoder_init();
	queue_init(&targets);
	queue_enqueue_values(&targets, 60.0, 0.0);
	queue_enqueue_values(&targets, 60.0, 60.0);
	queue_enqueue_values(&targets, 0.0, 60.0);
	queue_enqueue_values(&targets, 0.0, 0.0);

	// Create and run process
	resume(create(locator, 192, 19, "loc", 0));
	resume(create(serial_output, 128, 19, "s_o", 0));
	resume(create(controller, 192, 19, "con", 0));

	*DDR_B |= 1 << 5;
	while (1)
	{
		sleepms(200);
		*PORT_B |= 1 << 5; // high
		sleepms(200);
		*PORT_B ^= 1 << 5; // low
	}

	return 0;
}

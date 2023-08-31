#include <xinu.h>
#include <avr/interrupt.h>
#include "serial.h"
#include "mat.h"
#include "timer1.h"

// Process with external code
extern int serial_output(void);
extern int rtc(void);
extern int wheel_reader(void);
extern int locator(void);
extern int controller(void);

// Global Variables
unsigned int left_wheel_ticks;
unsigned int right_wheel_ticks;
unsigned long rtc_miliseconds;
float car_x = 0.0;
float car_y = 0.0;
float car_angle = 0.0;
unsigned int total_targets = 4;
unsigned int next_target = 0;
float targets[4][2] = {{60.0, 0.0}, {60.0, 60.0}, {0.0, 60.0}, {0.0, 0.0}};

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

	// Create and run process
	resume(create(locator, 258, 19, "loc", 0));
	resume(create(wheel_reader, 64, 20, "w_r", 0));
	resume(create(controller, 128, 19, "con", 0));
	resume(create(serial_output, 128, 19, "s_o", 0));

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
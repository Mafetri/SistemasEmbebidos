#include <xinu.h>
#include <avr/interrupt.h>
#include "serial.h"
#include "mat.h"

// Process with external code
extern int led_placa(void);
extern int serial_output(void);
extern int rtc(void);
extern int wheel_reader(void);
extern int locator(void);

// Global Variables
unsigned int left_wheel_ticks;
unsigned int right_wheel_ticks;
unsigned long rtc_miliseconds;
float car_x = 0.0;
float car_y = 0.0;
float car_angle = 0.0;

// Ports
volatile unsigned char * DDR_B = 0x24;
volatile unsigned char * PORT_B = 0x25;
volatile unsigned char * PIN_B = 0x23;

volatile unsigned char * DDR_D = 0x2A;
volatile unsigned char * PORT_D = 0x2B;
volatile unsigned char * PIN_D = 0x29;

// Main process
int main(void)
{
	serial_init();
	
	// Create and run process
	resume(create(locator, 258, 19, "loc", 0));
	resume(create(wheel_reader, 64, 20, "w_r", 0));
	resume(create(serial_output, 128, 19, "s_o", 0));
	// resume(create(rtc, 64, 20, "rtc", 0));

	led_placa();

	return 0;
}


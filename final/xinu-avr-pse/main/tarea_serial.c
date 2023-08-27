#include <xinu.h>
#include "serial.h"
#include "math.h"

// Global Variables
extern unsigned int left_wheel_ticks;
extern unsigned int right_wheel_ticks;
extern float car_x;
extern float car_y;
extern float car_angle;

// Another Process
int serial_output(void)
{
	while (1)
	{
		serial_put_str("(");
		serial_put_double(car_x, 3);
		serial_put_str(", ");
		serial_put_double(car_y, 3);
		serial_put_str(") Angle: ");
		serial_put_double(car_angle, 3);
		serial_put_new_line();

		sleepms(500);
	}
}

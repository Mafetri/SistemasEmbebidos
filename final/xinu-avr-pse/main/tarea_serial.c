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
		// serial_put_str("(");
		// serial_put_int((int)car_x, 3);
		// serial_put_str(", ");
		// serial_put_int((int)car_y, 3);
		// serial_put_str(") Angle: ");
		// serial_put_int((int)car_angle, 3);
		// serial_put_int((int)cos(0.2), 1);
		serial_put_str("\n\r");
		// serial_put_str("Rueda derecha:");
		// serial_put_int(right_wheel_ticks, 3);
		// serial_put_str("\n\r");
		// serial_put_str("Rueda izquierda:");
		// serial_put_int(left_wheel_ticks, 3);
		// serial_put_str("\n\r");
		// serial_put_str("======================");
		// serial_put_str("\n\r");
		sleepms(200);
	}
}

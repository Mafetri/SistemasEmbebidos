#include <xinu.h>
#include <math.h>

#define WHEEL_RADIUS 6
#define WHEEL_SEPARATION 19.5
#define ENCODER_RES 20
#define PI 3.14159265359

// Global Variables
extern unsigned int left_wheel_ticks;
extern unsigned int right_wheel_ticks;
extern float car_x;
extern float car_y;
extern float car_angle;

// Locator
// Using the ticks of each wheel, calculates the position of the robot
int locator(void)
{
	// Local Variables
	unsigned int left_ticks = 0;
	unsigned int right_ticks = 0;
	float left_distance = 0.0;
	float right_distance = 0.0;
	float center_distance = 0.0;

	while (1) {
		// Read the wheel tick counts from last measurement
		left_ticks = left_wheel_ticks - left_ticks;
		right_ticks = right_wheel_ticks - right_ticks;

		// Calculate wheel odometry
		left_distance = (2.0 * PI * WHEEL_RADIUS * left_ticks) / ENCODER_RES;
		right_distance = (2.0 * PI * WHEEL_RADIUS * right_ticks) / ENCODER_RES;
		center_distance = (left_distance + right_distance) / 2.0;

		// Update robot position and angle
		// car_x += center_distance * (float)cos((double)car_angle);
		// car_y += center_distance * (float)sin((double)car_angle);
		car_angle += (left_distance + right_distance) / WHEEL_SEPARATION;

        sleepms(50);
	}
}
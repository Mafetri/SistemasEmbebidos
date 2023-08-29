#include <xinu.h>
#include <mat.h>

#define WHEEL_DIAMETER 3
#define WHEEL_SEPARATION 19.44
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
	unsigned int delta_left_ticks = 0;
	unsigned int last_left_ticks = 0;
	unsigned int delta_right_ticks = 0;
	unsigned int last_right_ticks = 0;
	float left_distance = 0.0;
	float right_distance = 0.0;
	float center_distance = 0.0;

	while (1)
	{
		// Read the wheel tick counts from last measurement
		delta_left_ticks = left_wheel_ticks - last_left_ticks;
		delta_right_ticks = right_wheel_ticks - last_right_ticks;
		last_left_ticks = left_wheel_ticks;
		last_right_ticks = right_wheel_ticks;

		// Calculate wheel odometry
		left_distance = (PI * WHEEL_DIAMETER / ENCODER_RES) * delta_left_ticks;
		right_distance = (PI * WHEEL_DIAMETER / ENCODER_RES) * delta_right_ticks;
		center_distance = (left_distance + right_distance) / 2.0;

		// Update robot position and angle
		car_x += center_distance * cos(car_angle);
		car_y += center_distance * sin(car_angle);
		car_angle += (right_distance - left_distance) / WHEEL_SEPARATION;

		sleepms(100);
	}
}
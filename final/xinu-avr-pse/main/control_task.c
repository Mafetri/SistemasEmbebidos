#include <xinu.h>
#include "mat.h"
#include "timer1.h"

// Definitions
#define LW_FWD_PORT 4
#define LW_REV_PORT 5
#define RW_FWD_PORT 6
#define RW_REV_PORT 7
#define LW_SPEED_PORT 1
#define LW_SPEED_PORT 2

// Car Configuration
#define WHEEL_RADIUS 3
#define WHEEL_SEPARATION 19.44

// The min speed for the motors to move, higher -> imprecise, lower -> can't move
#define MIN_SPEED 0.3

// Global Variables
extern volatile unsigned char *DDR_D;
extern volatile unsigned char *PORT_D;
extern volatile unsigned char *PIN_D;
extern float car_x;
extern float car_y;
extern float car_angle;
extern float targets[4][2];
unsigned int next_target;
unsigned int total_targets;

// Constants for PID control
#define Kp 0.5
#define Ki 0.01
#define Kd 0.5
#define dT 100

// Move Wheel
// Sets the speed and direction of a wheel
void move_wheel(char side, char direction, double speed)
{
    if (side == 'L')
    {
        if (direction == 'F')
        {
            *(PORT_D) |= 1 << LW_FWD_PORT;
        }
        else if (direction == 'R')
        {
            *(PORT_D) |= 1 << LW_REV_PORT;
        }
        set_timer1_ocr1a_dutycycle(speed);
    }
    else if (side == 'R')
    {
        if (direction == 'F')
        {
            *(PORT_D) |= 1 << RW_FWD_PORT;
        }
        else if (direction == 'R')
        {
            *(PORT_D) |= 1 << RW_REV_PORT;
        }
        set_timer1_ocr1b_dutycycle(speed);
    }
}

// Controller
// Using the position, moves the wheels
int controller(void)
{
    // Local Variables
    double angle_to_target;
    double error_angle;
    double error_x;
    double error_y;
    double proportional;
    double integral = 0.0;
    double derivate = 0.0;
    double pid;
    double left_speed;
    double right_speed;
    double target_x = targets[next_target][0]; // Target X coordinate
    double target_y = targets[next_target][1]; // Target Y coordinate

    // Sets the Left Wheel pins to output
    *(DDR_D) |= (1 << LW_FWD_PORT) | (1 << LW_REV_PORT);
    // Sets the Right Wheel pins to output
    *(DDR_D) |= (1 << RW_FWD_PORT) | (1 << RW_REV_PORT);

    while(1)
    {
        // Error in x, y and the angle to the target
        error_x = target_x - car_x;
        error_y = target_y - car_y;

        // If its near the target
        if (error_x < 0.1 && error_y < 0.1)
        {
            // If there are no more targets, stops
            if(next_target >= total_targets) {
                move_wheel('L', 'F', 0);
                move_wheel('R', 'F', 0);
                break;
            } else {
                target_x = targets[next_target][0];
                target_y = targets[next_target][1];
                next_target++;

                error_x = target_x - car_x;
                error_y = target_y - car_y;
            }
        }

        // Calculates the direct angle to the target 
        angle_to_target = atan2(error_y, error_x);

        // Error between the actual angle and the angle needed
        error_angle = angle_to_target - car_angle;
        error_angle = atan2(sin(error_angle), cos(error_angle));

        // Proportional 
        proportional = error_angle;

        // Integral
        integral = integral + error_angle;

        // Derivative
        derivate = (error_angle - derivate);

        // Gets the total PID
        pid = Kp * proportional + Ki * integral + Kd * derivate;

        // Saves the derivate for the next run
        derivate = error_angle;

        right_speed = (2 * 0.05 + pid * WHEEL_SEPARATION) / (2 * WHEEL_RADIUS);
        left_speed = (2 * 0.05 - pid * WHEEL_SEPARATION) / (2 * WHEEL_RADIUS);
        if (left_speed > 0 && left_speed < MIN_SPEED) {
            left_speed = MIN_SPEED;
        }
        if (right_speed > 0 && right_speed < MIN_SPEED) {
            right_speed = MIN_SPEED;
        }

        // Move the wheels according to the PID outputs
        move_wheel('L', 'F', left_speed);
        move_wheel('R', 'F', right_speed);

        sleepms(dT);
    }
}
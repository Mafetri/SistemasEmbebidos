#include <xinu.h>
#include "mat.h"
#include "timer1.h"
#include "data_structures.h"

// Definitions
#define LW_FWD_PORT 4
#define LW_REV_PORT 5
#define RW_FWD_PORT 6
#define RW_REV_PORT 7
#define LW_SPEED_PORT 1
#define LW_SPEED_PORT 2

// Car Configuration
#define WHEEL_RADIUS 6
#define WHEEL_SEPARATION 19.44

// The min speed for the motors to move, higher -> imprecise, lower -> can't move
#define MIN_SPEED 0.8

// Global Variables
extern volatile car_position car;
extern volatile unsigned char *DDR_D;
extern volatile unsigned char *PORT_D;
extern volatile unsigned char *PIN_D;
extern volatile queue targets;

// Constants for PID control
#define Kp 0.1
#define Ki 0.01
#define Kd 0.1
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

double abs2(double x)
{
    if (x < 0)
    {
        return -x;
    }
    else
    {
        return x;
    }
}

// Planner
// Using the position, moves the wheels
int planner(void)
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
    double next_target[2];
    queue_dequeue(&targets, &next_target);

    // Sets the Left Wheel pins to output
    *(DDR_D) |= (1 << LW_FWD_PORT) | (1 << LW_REV_PORT);
    // Sets the Right Wheel pins to output
    *(DDR_D) |= (1 << RW_FWD_PORT) | (1 << RW_REV_PORT);

    while(1)
    {
        // Error in x, y and the angle to the target
        error_x = next_target[0] - car.x;
        error_y = next_target[1] - car.y;

        if (abs2(error_x) < 1 && abs2(error_y) < 1)
        {
            // If there are more targets, jumps to another iteration
            if(queue_dequeue(&targets, &next_target) == 1) {
                continue;
            } else {
                // If not, stops
                move_wheel('L', 'F', 0);
                move_wheel('R', 'F', 0);
                break;
            }
        }

        // Calculates the direct angle to the target 
        angle_to_target = atan2(error_y, error_x);

        // Error between the actual angle and the angle needed
        error_angle = angle_to_target - car.angle;
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
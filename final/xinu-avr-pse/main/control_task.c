#include <xinu.h>
#include "mat.h"

// Definitions
#define LW_FWD_PORT 4
#define LW_REV_PORT 5
#define RW_FWD_PORT 6
#define RW_REV_PORT 7
#define LW_SPEED_PORT 1
#define LW_SPEED_PORT 2
#define WHEEL_DIAMETER 3
#define WHEEL_SEPARATION 55.6
#define MIN_SPEED 0.2

// Global Variables
extern volatile unsigned char *DDR_D;
extern volatile unsigned char *PORT_D;
extern volatile unsigned char *PIN_D;
extern float car_x;
extern float car_y;
extern float car_angle;

#define target_x 80 // Target X coordinate
#define target_y 80 // Target Y coordinate

// Constants for PID control
#define Kp 1.5
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
    double integral;
    double derivate;
    double pid;
    double left_speed;
    double right_speed;

    // Sets the Left Wheel pins to output
    *(DDR_D) |= (1 << LW_FWD_PORT) | (1 << LW_REV_PORT);
    // Sets the Right Wheel pins to output
    *(DDR_D) |= (1 << RW_FWD_PORT) | (1 << RW_REV_PORT);

    while(1)
    {
        // Error in x, y and the angle to the target
        error_x = target_x - car_x;
        error_y = target_y - car_y;

        if (error_x < 0.3 && error_x < 0.3)
        {
            move_wheel('L', 'F', 0);
            move_wheel('R', 'F', 0);
            break;
        }

        angle_to_target = atan2(error_y, error_x);

        // Error between the actual angle and the angle needed
        error_angle = angle_to_target - car_angle;
        error_angle = atan2(sin(error_angle), cos(error_angle));

        // Proportional 
        proportional = error_angle;

        // Integral
        integral = integral + error_angle * dT;

        // Derivative
        derivate = (error_angle - derivate) / dT;

        pid = Kp * proportional + Ki * integral + Kd * derivate;

        right_speed = (2 * MIN_SPEED + pid * WHEEL_SEPARATION) / (2 * WHEEL_DIAMETER);
        left_speed = (2 * MIN_SPEED - pid * WHEEL_SEPARATION) / (2 * WHEEL_DIAMETER);

        // if (left_speed > right_speed) {
        //     left_speed = left_speed/left_speed;
        //     right_speed = right_speed/left_speed;
        // } else {
        //     left_speed = left_speed/right_speed;
        //     right_speed = right_speed/right_speed;
        // }

        // Move the wheels according to the PID outputs
        move_wheel('L', 'F', left_speed);
        move_wheel('R', 'F', right_speed);

        sleepms(dT);
    }
}
#include <xinu.h>

// Global Variables
extern volatile unsigned char * DDR_D;
extern volatile unsigned char * PORT_D;
extern volatile unsigned char * PIN_D;

#define LW_FWD_PORT 4
#define LW_REV_PORT 5
#define RW_FWD_PORT 6
#define RW_REV_PORT 7
#define LW_SPEED_PORT 1
#define LW_SPEED_PORT 2

// Controller
// Using the position, moves the wheels
int controller(void)
{
	// Local Variables

    // Sets the Left Wheel pins to output
    *(DDR_D) |= (1 << LW_FWD_PORT) | (1 << LW_REV_PORT);
    // Sets the Right Wheel pins to output
    *(DDR_D) |= (1 << RW_FWD_PORT) | (1 << RW_REV_PORT);

    move_wheel('L', 'R', 0.3);
    move_wheel('R', 'F', 0.9);

	while (1)
	{
		sleepms(100);
	}
}

void move_wheel(char side, char direction, double speed) {
    if(side == 'L') {
        if(direction == 'F') {
            *(PORT_D) |= 1 << LW_FWD_PORT;
        } else {
            *(PORT_D) |= 1 << LW_REV_PORT;
        }
        set_timer1_ocr1a_dutycycle(speed);
    } else if (side == 'R') {
        if(direction == 'F') {
            *(PORT_D) |= 1 << RW_FWD_PORT;
        } else {
            *(PORT_D) |= 1 << RW_REV_PORT;
        }
        set_timer1_ocr1b_dutycycle(speed);
    }
}
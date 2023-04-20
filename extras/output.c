#include "myutils.h"

int main() {
    volatile unsigned char * DDR_B = 0x24;
    volatile unsigned char * PORT_B = 0x25;
    volatile unsigned char * PIN_B = 0x23;

    // Sets the DDR_B port 0 to output
    *(DDR_B) |= 1 << 0;
    // Sets the PORT_B 1 to input
    *(PORT_B) |= 1 << 1;

    while(1) {
        *(PORT_B) ^= 1 << 0;
        sleep_10_us();
        *(PORT_B) ^= 1 << 0;

        int time = 0;
        while(*(PIN_B) ^ (1 << 1)) {
            time++;
            sleep_10_us();
        }

        int cm = time / 58;
        
    }

    return 0;
}
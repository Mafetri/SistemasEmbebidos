#include "timer.h"
#include <avr/interrupt.h>

void send_char(char c, int port_number, volatile unsigned char* port) {
    // Sets to low the light to start transmission
    *(port) ^= (1 << port_number);
    timer0_wait(100);

    // Sends the bits
    for (int i = 0; i < 8; i++) {
        // If the bit of the i position
        if ((c >> i) & 1) {
            *(port) |= 1 << port_number; // Is 1, high
        } else {
            *(port) ^= 1 << port_number; // Is 0, low
        }
        timer0_wait(100);
    }

    *(port) ^= 1 << port_number; // Sets to high again
}

/*
For the arduino receptionist:

char receive_char(int port){
    while(adc_get(port) > 700);
    timer0_wait(50);

    char received_char;
    for(int i=0; i < 8; i++){
        received_char |= (adc_get(port) > 700) ? (1 << i) : 0;
        timer0_wait(100);
    }

    while(adc_get(2) < 700);
    
    return receive_char;
}
*/

int main(void) {
    volatile unsigned char * DDR_D = 0x2A;
    volatile unsigned char * PORT_D = 0x2B;

    int laser_port = 2;
    (*PORT_D) = 1 << laser_port;
    *(DDR_D) = 1 << laser_port;

    timer0_init();
    sei();

    while(1) {
        timer0_wait(1000);
        send_char('a', laser_port, DDR_D);
    }
}
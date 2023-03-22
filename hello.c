void delay(long delay) {
    volatile long i;
    for(i = 0; i < delay; i++){
    }
}

void toggle_led(int port_number, char* port) {
    *(port) ^= 1 << port_number; 
}

int main(void) {
    volatile unsigned char * DDR_B = 0x24;
    volatile unsigned char * PORT_B = 0x25;

    // Sets the DDR_B port 5 to output
    *(DDR_B) = 0b00100000;

    while(1) {
        // LED on (toggles the 5th bit of PortB)
        toggle_led(5, PORT_B);
        delay(100000);

        //LED off (toggles the 5th bit of PortB)
        toggle_led(5, PORT_B);
        delay(100000);
    }

    return 0;
}

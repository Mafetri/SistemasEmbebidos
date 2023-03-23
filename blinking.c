void delay(long delay) {
    volatile long i;
    for(i = 0; i < delay; i++){
    }
}

void toggle_led(int port_number, volatile char* port) {
    *(port) ^= 1 << port_number; 
}

void blink(int times, int port_number, volatile char* port) {
    int i;
    for(i = 0; i < times; i++){
        // LED on (toggles the 5th bit of PortB)
        toggle_led(port_number, port);
        delay(30000);

        //LED off (toggles the 5th bit of PortB)
        toggle_led(port_number, port);
        delay(30000);
    }
}

int main(void) {
    volatile unsigned char * DDR_B = 0x24;
    volatile unsigned char * PORT_B = 0x25;
    int port_number = 5;
    int num = 3;

    // Sets the DDR_B port 5 to output
    *(DDR_B) ^= 1 << port_number;

    while(1) {
        // LED on (toggles the 5th bit of PortB)
        blink(num, port_number, PORT_B);
        delay(200000);
    }

    return 0;
}
void delay(long delay) {
    volatile long i;
    for(i = 0; i < delay; i++){
    }
}

void toggle_led(int port_number, volatile char* port) {
    *(port) ^= 1 << port_number; 
}

int main(void) {
    volatile unsigned char * DDR_B = 0x24;
    volatile unsigned char * PORT_B = 0x25;
    int port_number = 5;

    // Sets the DDR_B port 5 to output
    *(DDR_B) ^= 1 << port_number;

    while(1) {
        // LED on (toggles the port_number bit of PortB)
        toggle_led(port_number, PORT_B);
        delay(100000);

        //LED off (toggles the port_number bit of PortB)
        toggle_led(port_number, PORT_B);
        delay(100000);
    }

    return 0;
}
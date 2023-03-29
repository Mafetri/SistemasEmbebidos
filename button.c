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

void lightbar (int ports, volatile char* port) {
    int lights = 0;
    int op = 1;
    while(1) {
        *(port) = 1 << lights;
        if(lights == ports) {
            op = -1;
        }
        if(lights == 0) {
            op = 1;
        }
        lights = (lights + op) % ports;
        delay(10000);
    }
}

int main(void) {
    volatile unsigned char * DDR_B = 0x24;
    volatile unsigned char * PORT_B = 0x25;
    volatile unsigned char * PIN_B = 0x23;
    volatile unsigned char * DDR_D = 0x2A;
    volatile unsigned char * PORT_D = 0x2B;
    int portInput = 4;
    int portOutput = 5;
    *(PORT_B) |= 1 << portInput;
    *(DDR_B) |= 1 << portOutput;
    *(PIN_B) |= 1 << portInput;

    while(1) {
        if((*(PIN_B) & (1 << portInput)) == 0) {
            delay(10000);
            if((*(PIN_B) & (1 << portInput)) == 0) {
                *(PORT_B) ^= 1 << portOutput;
                delay(100000);
            }
        }
    }

    return 0;
}
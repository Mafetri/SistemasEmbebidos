int delay(long delay) {
    volatile long i;
    for(i = 0; i < delay; i++){
    }
    return 0;
}

int main(void) {
    volatile unsigned char * DDR_B = 0x24;
    volatile unsigned char * PORT_B = 0x25;

    // Sets the DDR_B port 5 to output
    *(DDR_B) = 0b00100000;

    while(1) {
        // LED on (sets the port B number 5 to 1)
        *(PORT_B) = 0b00100000;
        delay(100000);

        //LED off (sets the port B number 5 to 0)
        *(PORT_B) = 0b00000000;
        delay(100000);
    }

    return 0;
}

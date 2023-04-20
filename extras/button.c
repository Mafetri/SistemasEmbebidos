void delay(long delay) {
    volatile long i;
    for(i = 0; i < delay; i++){
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
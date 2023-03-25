void delay(long delay) {
    volatile long i;
    for(i = 0; i < delay; i++){
    }
}

void show_number(int num, volatile char* PORT_D, volatile char* PORT_B) {
    int segment_7[10] = {
        0b1000000,
        0b1111001,
        0b0100100,
        0b0110000,
        0b0011001,
        0b0010010,
        0b0000010,
        0b1111000,
        0b0000000,
        0b0010000
    };

    // Sets the first 6 bits and keeps the 2 less significant of the PORT intact
    *(PORT_D) = (*(PORT_D) & 0b11) | segment_7[num] << 2;
    // Keeps the first 7 bits of the PORT intact and sets the last bit
    *(PORT_B) = (*(PORT_B) & 0b11111110) | segment_7[num] >> 6;
}

int main(void) {
    volatile unsigned char * DDR_B = 0x24;
    volatile unsigned char * DDR_D = 0x2A;
    volatile unsigned char * PORT_D = 0x2B;
    volatile unsigned char * PORT_B = 0x25;
    int num = 0;

    // Sets the first 6 bits of the port to output and keeps untouched the least 2
    *(DDR_D) |= 0b11111100;
    // Sets the last bit of the port to output and keeps untouched the first 7
    *(DDR_B) |= 0b00000001;

    while(1) {
        show_number(num, PORT_D, PORT_B);
        delay(200000);
        num = (num + 1) % 10;
    }

    return 0;
}
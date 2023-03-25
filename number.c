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

    *(PORT_D) = segment_7[num] << 2;
    *(PORT_B) = segment_7[num] >> 6;
}

int main(void) {
    volatile unsigned char * DDR_B = 0x24;
    volatile unsigned char * DDR_D = 0x2A;
    volatile unsigned char * PORT_D = 0x2B;
    volatile unsigned char * PORT_B = 0x25;
    int num = 0;

    *(DDR_D) = 0b11111100;
    *(DDR_B) = 0b00000001;

    while(1) {
        show_number(num, PORT_D, PORT_B);
        delay(200000);
        num = (num + 1) % 10;
    }

    return 0;
}
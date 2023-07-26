#include <xinu.h>

extern volatile unsigned char * DDR_B;
extern volatile unsigned char * PORT_B;

int led_placa(void)
{
    *DDR_B |= 0x20; // control: salida.

    while (1){
        sleepms(200);
        *PORT_B |= 0x20; // high
        sleepms(200);
        *PORT_B = (*PORT_B & (~0x20)); // low
    }

}


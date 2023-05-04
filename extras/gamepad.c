// #include "serial.h"
// #include "myutils.h"

/*
Bash code to play:
cat /dev/ttyUSB0 | 
while read -n 1 tecla;
    do xdotool key $tecla;
done
*/

int main(void)
{
    volatile unsigned char * DDR_D = 0x2A;
    volatile unsigned char * PORT_D = 0x2B;
    volatile unsigned char * PIN_D = 0x29;

    // Serial
    serial_init();
    serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');
    serial_put_char('\n');
    serial_put_char('\r');

    // Buttons
    int rightButton = 2;
    int leftButton = 3;
    *(PORT_D) |= 1 << rightButton;
    *(PORT_D) |= 1 << leftButton;

    while (1) {
        if((*(PIN_D) & (1 << rightButton)) == 0) {
            delay_ms(1);
            if((*(PIN_D) & (1 << rightButton)) == 0) {
                serial_put_char('D');
                delay_ms(50);
            }
        }

        if((*(PIN_D) & (1 << leftButton)) == 0) {
            delay_ms(1);
            if((*(PIN_D) & (1 << leftButton)) == 0) {
                serial_put_char('A');
                delay_ms(50);
            }
        }
    }

    return 0;
}
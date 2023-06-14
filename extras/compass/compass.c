#include "HMC5883l.h"
#include "serial.h"
#include "myutils.h"

int main(void) {
    serial_init();
    while(1) {
        float angulo = HMC5883l_getHeadingDegrees();
        // serial_put_int((int)angulo, 3);
        // serial_put_new_line();
        delay_ms(500);
    }
    return 0;
}
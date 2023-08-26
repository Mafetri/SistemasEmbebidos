/**********************************************************************
 *
 * Filename:    serial.h
 * 
 * API para la aplicacion embebida 
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#ifndef _SERIAL_H
#define _SERIAL_H

void serial_init(void);
void serial_put_char(char);
char serial_get_char(void);
void serial_put_str(char *);
void serial_put_int (int, int);
void serial_put_double(double, int);
void serial_put_new_line(void);

#endif /* _SERIAL_H */

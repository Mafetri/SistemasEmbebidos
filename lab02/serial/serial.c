
/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */

typedef struct
{
    uint8_t status_control_a;   // ucsr0a USART Control and Status A
    uint8_t status_control_b;   // ucsr0b USART Control and Status B 
    uint8_t status_control_c;   // ucsr0c USART Control and Status C
    uint8_t reserved;           // unused space to align registers with structure
    uint8_t baud_rate_l;        // ucsr0l baud rate low 
    uint8_t baud_rate_h;        // ucsr0h baud rate high 

    uint8_t data_es;            // udr0 i/o data
} volatile uart_t;

// Pointer to peripheral register data structure
uart_t *serial_port = (uart_t *) (0xc0);

#define F_CPU 4000000UL
#define USART_BAUDRATE 2400
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
/*
7:6 Asynchronous (00)
5:4 Even Parity (10)
3   1 stop bit (0)
2:1 8-bit size (11)
0   Falling Edge (0)
*/ 
#define USART_INIT 0b00100110
#define ENABLE_RX_TX (0b11 << 3)
#define UDREn 1 << 5

void serial_init() {
	// Configure High and Low registers with BAUD_PRESCALE
    serial_port->baud_rate_h = (unsigned char) (BAUD_PRESCALE >> 8);
    serial_port->baud_rate_l = (unsigned char) (BAUD_PRESCALE);

	// Configure 8-bits frame, parity and 1-bit stop
    serial_port->status_control_c = (unsigned char) (USART_INIT);

    // Enables the Rx and Tx
    serial_port->status_control_b = (unsigned char) (ENABLE_RX_TX);
}

void serial_put_char (char c) {
    // Wait until the transmitter is ready for the next character.
    while (!(serial_port->status_control_a & UDREn));

    // Send the character via the serial port.
    serial_port->data_es = c;
}


char serial_get_char(void)
{

}
#ifndef UART_H
#define UART_H

#include <stdio.h>

/**
 * @brief Initializes the UART serial port and redirects stdin/stdout to it.
 * 
 * @param baudrate The baud rate for serial communication (e.g., 9600).
 */
void uart_init(unsigned long baudrate);

/**
 * @brief Reads a line of text from the serial port, supporting backspace.
 * 
 * @param dest The destination buffer.
 * @param max_len The maximum length of characters to read.
 */
void read_line(char* dest, int max_len);

/**
 * @brief Reads an integer from the serial port, supporting backspace.
 * 
 * @return The parsed integer value.
 */
int read_int(void);

/**
 * @brief Reads a single character from the serial port.
 * 
 * @return The character read.
 */
char read_char(void);

#endif /* UART_H */


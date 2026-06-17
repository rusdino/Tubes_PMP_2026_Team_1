#include "uart.h"
#include <avr/io.h>
#include <stdio.h>

volatile uint8_t uart_echo_enabled = 1;

// Function to transmit a character over UART
static int uart_putchar(char c, FILE *stream) {
    // Convert \n to \r\n for serial terminals to render new lines correctly
    if (c == '\n') {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = '\r';
    }
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
    return 0;
}

// Function to receive a character from UART
static int uart_getchar(FILE *stream) {
    static char last_char = 0;
    char c;
    while (1) {
        while (!(UCSR0A & (1 << RXC0)));
        c = UDR0;
        
        // Handle Backspace / Delete
        if (c == '\b' || c == 127) {
            if (uart_echo_enabled) {
                // Send backspace, space, backspace to erase character visually
                uart_putchar('\b', stream);
                uart_putchar(' ', stream);
                uart_putchar('\b', stream);
            }
            return '\b';
        }
        
        // Handle \r\n line endings: skip \n if it immediately follows \r
        if (c == '\n' && last_char == '\r') {
            last_char = c;
            continue;
        }
        
        last_char = c;
        if (c == '\r') {
            c = '\n';
        }
        
        // Echo back character if enabled
        if (uart_echo_enabled) {
            uart_putchar(c, stream);
        }
        return c;
    }
}

// Create file streams for stdout and stdin
static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
static FILE uart_stdin  = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

void uart_init(unsigned long baudrate) {
    // Calculate UBRR value with rounding
    unsigned int ubrr = (unsigned int)((F_CPU + 8UL * baudrate) / (16UL * baudrate) - 1);
    
    // Set baud rate registers
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    
    // Set frame format: 8 data bits, 1 stop bit, no parity (8N1)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    
    // Redirect standard I/O streams
    stdout = &uart_stdout;
    stdin  = &uart_stdin;
}

#include <stdlib.h>

void read_line(char* dest, int max_len) {
    int i = 0;
    while (i < max_len - 1) {
        int c = getchar();
        if (c == EOF || c == '\n') {
            break;
        }
        if (c == '\b' || c == 127) { // Backspace
            if (i > 0) {
                i--;
            }
        } else {
            dest[i++] = c;
        }
    }
    dest[i] = '\0';
}

int read_int(void) {
    char buf[16];
    read_line(buf, sizeof(buf));
    return atoi(buf);
}

char read_char(void) {
    char buf[8];
    read_line(buf, sizeof(buf));
    int idx = 0;
    while (buf[idx] == ' ' || buf[idx] == '\t' || buf[idx] == '\r' || buf[idx] == '\n') {
        idx++;
    }
    return buf[idx];
}


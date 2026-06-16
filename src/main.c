#include <stddef.h>
#include <avr/pgmspace.h>
#include "menu.h"
#include "delete.h"
#include "uart.h"

int main() {
    // Initialize serial communication
    uart_init(9600);

    dataset* database = NULL;
    
    // Seed initial mock data
    seed_data(&database);
    
    // Enter the interactive CLI loop
    menu_loop(&database);
    
    // Clean up allocated memory before program exit
    free_database(&database);
    
    return 0;
}

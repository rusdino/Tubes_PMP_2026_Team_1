#include <stddef.h>
#include "menu.h"
#include "delete.h"

int main() {
    dataset* database = NULL;
    
    // Seed initial mock data
    seed_data(&database);
    
    // Enter the interactive CLI loop
    menu_loop(&database);
    
    // Clean up allocated memory before program exit
    free_database(&database);
    
    return 0;
}

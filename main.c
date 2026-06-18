#include <stddef.h>
#include "menu.h"
#include "delete.h"

int main() {
    dataset* database = NULL;
    
    seed_data(&database);
    menu_loop(&database);
    free_database(&database);
    
    return 0;
}

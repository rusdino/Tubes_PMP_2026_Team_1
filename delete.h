#ifndef DELETE_H
#define DELETE_H

#include "dataset.h"

void delete_item(dataset** list, int id);
void delete_item_from_input(dataset** head);
void free_database(dataset** head);

#endif
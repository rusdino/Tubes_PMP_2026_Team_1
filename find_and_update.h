#ifndef FIND_AND_UPDATE_H
#define FIND_AND_UPDATE_H
#include "dataset.h"

void find(dataset* list, int id, dataset** node);
void find_item_from_input(dataset* head);

void update_status(dataset** list, int id, int tersedia, int dipinjam, int rusak);
void update_status_from_input(dataset** head);

void update_stock(dataset** list, int id, int amount, char mode);
void update_stock_from_input(dataset** head);

#endif

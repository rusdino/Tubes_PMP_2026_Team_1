#ifndef FIND_AND_UPDATE_H
#define FIND_AND_UPDATE_H
#include "dataset.h"

void find(dataset* list, int id, dataset** node);

void update_status(dataset** list, int id, int tersedia, int dipinjam, int rusak);

void update_stock(dataset** list, int id, int amount, char mode);

#endif

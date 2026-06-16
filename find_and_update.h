#ifndef FIND_AND_UPDATE_H
#define FIND_AND_UPDATE_H
#include "dataset.h"

void find(dataset* list, int id, dataset** node);

void update_status(dataset** list, int id, char status[]);

void update_stock(dataset** list, int id, int amount, char mode);

#endif

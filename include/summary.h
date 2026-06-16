#ifndef SUMMARY_H
#define SUMMARY_H

#include "dataset.h"

/**
 * @brief Displays a summary of the inventory data, including total items,
 * total stock, counts by status, and category statistics.
 * 
 * @param list Pointer to the head of the dataset linked list.
 */
void show_summary(dataset* list);

#endif

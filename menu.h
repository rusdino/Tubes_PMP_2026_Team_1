#ifndef MENU_H
#define MENU_H

#include "dataset.h"

/**
 * @brief Seeds initial mock data into the database linked list.
 * 
 * @param head Pointer to the head pointer of the linked list.
 */
void seed_data(dataset** head);

/**
 * @brief Clears the stdin input buffer.
 */
void clear_buffer();

/**
 * @brief Runs the main menu interactive CLI loop.
 * 
 * @param head Pointer to the head pointer of the linked list.
 */
void menu_loop(dataset** head);

#endif

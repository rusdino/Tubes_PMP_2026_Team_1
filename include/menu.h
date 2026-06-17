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

/**
 * @brief Reads semicolon-separated database lines from serial and adds them.
 * 
 * @param head Pointer to the head pointer of the linked list.
 */
void load_database_from_serial(dataset** head);

/**
 * @brief Traverses the database and prints items in semicolon-separated format to serial.
 * 
 * @param head Pointer to the head of the linked list.
 */
void dump_database_to_serial(dataset* head);

#endif


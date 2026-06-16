#ifndef ADD_H
#define ADD_H

#include "dataset.h"

/**
 * @brief Adds an inventory item directly using arguments.
 * 
 * @param head Pointer to the head pointer of the linked list.
 * @param id Unique ID of the item.
 * @param nama Name of the component.
 * @param kategori Category of the component.
 * @param jumlah_stok Stock quantity.
 * @param lokasi_penyimpanan Storage location.
 * @param status Status (Tersedia, Dipinjam, Rusak, Habis).
 * @param pemilik Owner of the item.
 * @param pic Person in Charge.
 */
void add_item(dataset** head, int id, const char nama[], const char kategori[], int jumlah_stok, const char lokasi_penyimpanan[], int tersedia, int dipinjam, int rusak, const char pemilik[], const char pic[]);

/**
 * @brief Prompts user via serial monitor / terminal for item fields, performs validation,
 * and adds the item to the dataset linked list.
 * 
 * @param head Pointer to the head pointer of the linked list.
 */
void add_item_from_input(dataset** head);

#endif

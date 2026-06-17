#include "delete.h"
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "uart.h"

void delete_item(dataset** head, int id){
    if (*head == NULL){
        printf_P(PSTR("[ERROR] List empty\n"));
        return;
    }
    dataset** curr = head;
    while (*curr != NULL && (*curr)->id != id) {
        curr = &((*curr)->next);
    }
    if (*curr != NULL) {
        dataset* temp = *curr;
        *curr = (*curr)->next;
        free(temp);
        printf_P(PSTR("[SUCCESS] Barang dengan ID %d berhasil dihapus.\n"), id);
    }
    else {
        printf_P(PSTR("[ERROR] ID %d tidak ditemukan.\n"), id);
    }
}

void delete_item_from_input(dataset** head) {
    if (*head == NULL) {
        printf_P(PSTR("[ERROR] List kosong. Tidak ada barang yang bisa dihapus.\n"));
        return;
    }
    int id;
    printf_P(PSTR("Masukkan ID Barang yang akan dihapus: "));
    id = read_int();
    delete_item(head, id);
}

void free_database(dataset** head) {
    if (head == NULL || *head == NULL) {
        return;
    }
    dataset* curr = *head;
    while (curr != NULL) {
        dataset* temp = curr;
        curr = curr->next;
        free(temp);
    }
    *head = NULL;
}
#include "delete.h"
#include <stdlib.h>
#include <stdio.h>

static void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void delete_item(dataset** head, int id){
    if (*head == NULL){
        printf("[ERROR] List empty\n");
        return;
    }
    
    if ((*head)->id == id){
        dataset* temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("[SUCCESS] Barang dengan ID %d berhasil dihapus.\n", id);
    }
    else {
        dataset* prev = *head;
        dataset* now = (*head)->next;
        while (now != NULL && now->id != id){
            now = now->next;
            prev = prev->next;
        }
        if (now != NULL){
            prev->next = now->next;
            free(now);
            printf("[SUCCESS] Barang dengan ID %d berhasil dihapus.\n", id);
        }
        else {
            printf("[ERROR] ID %d tidak ditemukan.\n", id);
        }
    }
}

void delete_item_from_input(dataset** head) {
    if (*head == NULL) {
        printf("[ERROR] List kosong. Tidak ada barang yang bisa dihapus.\n");
        return;
    }
    int id;
    printf("Masukkan ID Barang yang akan dihapus: ");
    if (scanf("%d", &id) != 1) {
        printf("[ERROR] ID tidak valid.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
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
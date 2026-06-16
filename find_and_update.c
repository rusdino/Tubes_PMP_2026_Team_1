#include "find_and_update.h"
#include <stdio.h>
#include <string.h>

void find(dataset* list, int id, dataset** node){
    dataset* temp = list;
    while (temp != NULL && temp->id != id){
        temp = temp->next;
    }
    *node = temp;
    return;
}

void update_status(dataset** list, int id, int tersedia, int dipinjam, int rusak){
    if (*list != NULL){
        dataset* updated_node;
        find(*list, id, &updated_node);
        if (tersedia + dipinjam + rusak != updated_node->jumlah_stok){
            printf("[ERROR] Total status (%d) tidak sama dengan jumlah stok saat ini (%d)!\n", (tersedia + dipinjam + rusak), updated_node->jumlah_stok);
        }
        else {
            if (updated_node != NULL){
                updated_node->status.dipinjam = dipinjam;
                updated_node->status.tersedia = tersedia;
                updated_node->status.rusak = rusak;
            }
            else {
                printf("ID not found\n");
            }
        }
    }
    else {
        printf("List empty\n");
    }
}

void update_stock(dataset** list, int id, int amount, char mode){
    if (*list != NULL){
        dataset* updated_node;
        find(*list, id, &updated_node);
        if (updated_node != NULL){
            if (mode == '-'){
                if (updated_node->status.rusak - amount < 0){
                    printf("Rejected: Jumlah barang rusak yang ingin dikurangi (%d) melebihi catatan (%d).\n", amount, updated_node->status.rusak);
                }
                else if (updated_node->jumlah_stok - amount < 0){
                    printf("Requirement amount not available\n");
                    printf("Available total stock %d\n", updated_node->jumlah_stok);
                }
                else {
                    updated_node->jumlah_stok -= amount;
                    updated_node->status.rusak -= amount;
                    printf("Stock updated (Pengurangan/Pembuangan).\n");
                    printf("Current total stock: %d | Barang Rusak tersisa: %d\n", 
                           updated_node->jumlah_stok, updated_node->status.rusak);
                }
            }
            else if (mode == '+'){
                updated_node->jumlah_stok += amount;
                updated_node->status.tersedia += amount;
                printf("Stock updated (Penambahan).\n");
                printf("Current total stock: %d | Barang Tersedia menjadi: %d\n", 
                       updated_node->jumlah_stok, updated_node->status.tersedia);
            }
            else {
                printf("Mode tidak valid. Gunakan '+' atau '-'.\n");
            }
        }
        else {
            printf("ID not found\n");
        }
    }
    else {
        printf("List empty\n");
    }
}

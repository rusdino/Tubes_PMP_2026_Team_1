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

static void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void find_item_from_input(dataset* head) {
    if (head == NULL) {
        printf("[ERROR] List kosong. Tidak ada data untuk dicari.\n");
        return;
    }
    int id;
    printf("Masukkan ID Barang yang dicari: ");
    if (scanf("%d", &id) != 1) {
        printf("[ERROR] ID tidak valid.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    
    dataset* found_node = NULL;
    find(head, id, &found_node);
    if (found_node != NULL) {
        printf("\n--- Data Ditemukan ---\n");
        printf("ID      : %d\n", found_node->id);
        printf("Nama    : %s\n", found_node->nama);
        printf("Kategori: %s\n", found_node->kategori);
        printf("Stok    : %d\n", found_node->jumlah_stok);
        printf("Lokasi  : %s\n", found_node->lokasi_penyimpanan);
        printf("Status (T/D/R): %d/%d/%d\n", found_node->status.tersedia, found_node->status.dipinjam, found_node->status.rusak);
        printf("Pemilik : %s\n", found_node->pemilik);
        printf("PIC     : %s\n", found_node->pic);
    } else {
        printf("[ERROR] ID %d tidak ditemukan.\n", id);
    }
}

void update_status(dataset** list, int id, int tersedia, int dipinjam, int rusak){
    if (*list != NULL){
        dataset* updated_node;
        find(*list, id, &updated_node);
        if (updated_node == NULL){
            printf("ID not found\n");
            return;
        }
        if (tersedia + dipinjam + rusak != updated_node->jumlah_stok){
            printf("[ERROR] Total status (%d) tidak sama dengan jumlah stok saat ini (%d)!\n", (tersedia + dipinjam + rusak), updated_node->jumlah_stok);
        }
        else {
            updated_node->status.dipinjam = dipinjam;
            updated_node->status.tersedia = tersedia;
            updated_node->status.rusak = rusak;
        }
    }
    else {
        printf("List empty\n");
    }
}

void update_status_from_input(dataset** head) {
    if (*head == NULL) {
        printf("[ERROR] List kosong. Tidak ada data untuk diperbarui.\n");
        return;
    }
    int id;
    int tersedia, dipinjam, rusak;
    printf("Masukkan ID Barang: ");
    if (scanf("%d", &id) != 1) {
        printf("[ERROR] ID tidak valid.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    dataset* found_node = NULL;
    find(*head, id, &found_node);
    if (found_node == NULL) {
        printf("[ERROR] ID %d tidak ditemukan.\n", id);
        return;
    }

    printf("Masukkan Jumlah Tersedia Baru: ");
    if (scanf("%d", &tersedia) != 1 || tersedia < 0) {
        printf("[ERROR] Jumlah tidak valid.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("Masukkan Jumlah Dipinjam Baru: ");
    if (scanf("%d", &dipinjam) != 1 || dipinjam < 0) {
        printf("[ERROR] Jumlah tidak valid.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("Masukkan Jumlah Rusak Baru: ");
    if (scanf("%d", &rusak) != 1 || rusak < 0) {
        printf("[ERROR] Jumlah tidak valid.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (tersedia + dipinjam + rusak != found_node->jumlah_stok) {
        printf("[ERROR] Total status (%d) tidak sama dengan jumlah stok saat ini (%d)!\n", 
               (tersedia + dipinjam + rusak), found_node->jumlah_stok);
        return;
    }

    update_status(head, id, tersedia, dipinjam, rusak);
    printf("[SUCCESS] Status barang berhasil diperbarui.\n");
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

void update_stock_from_input(dataset** head) {
    if (*head == NULL) {
        printf("[ERROR] List kosong. Tidak ada data untuk diperbarui.\n");
        return;
    }
    int id, amount;
    char mode;
    printf("Masukkan ID Barang: ");
    if (scanf("%d", &id) != 1) {
        printf("[ERROR] ID tidak valid.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    dataset* found_node = NULL;
    find(*head, id, &found_node);
    if (found_node == NULL) {
        printf("[ERROR] ID %d tidak ditemukan.\n", id);
        return;
    }

    printf("Masukkan mode perbaruan (+ untuk menambah, - untuk mengurangi): ");
    if (scanf(" %c", &mode) != 1 || (mode != '+' && mode != '-')) {
        printf("[ERROR] Mode tidak valid.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("Masukkan jumlah stok yang akan diubah: ");
    if (scanf("%d", &amount) != 1 || amount < 0) {
        printf("[ERROR] Jumlah tidak valid.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    update_stock(head, id, amount, mode);
}

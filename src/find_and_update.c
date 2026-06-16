#include "find_and_update.h"
#include <stdio.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "uart.h"

void find(dataset* list, int id, dataset** node){
    dataset* temp = list;
    while (temp != NULL && temp->id != id){
        temp = temp->next;
    }
    *node = temp;
    return;
}


void find_item_from_input(dataset* head) {
    if (head == NULL) {
        printf_P(PSTR("[ERROR] List kosong. Tidak ada data untuk dicari.\n"));
        return;
    }
    int id;
    printf_P(PSTR("Masukkan ID Barang yang dicari: "));
    id = read_int();
    
    dataset* found_node = NULL;
    find(head, id, &found_node);
    if (found_node != NULL) {
        printf_P(PSTR("\n--- Data Ditemukan ---\n"));
        printf_P(PSTR("ID      : %d\n"), found_node->id);
        printf_P(PSTR("Nama    : %s\n"), found_node->nama);
        printf_P(PSTR("Kategori: %s\n"), found_node->kategori);
        printf_P(PSTR("Stok    : %d\n"), found_node->jumlah_stok);
        printf_P(PSTR("Lokasi  : %s\n"), found_node->lokasi_penyimpanan);
        printf_P(PSTR("Status (T/D/R): %d/%d/%d\n"), found_node->status.tersedia, found_node->status.dipinjam, found_node->status.rusak);
        printf_P(PSTR("Pemilik : %s\n"), found_node->pemilik);
        printf_P(PSTR("PIC     : %s\n"), found_node->pic);
    } else {
        printf_P(PSTR("[ERROR] ID %d tidak ditemukan.\n"), id);
    }
}

void update_status(dataset** list, int id, int tersedia, int dipinjam, int rusak){
    if (*list != NULL){
        dataset* updated_node;
        find(*list, id, &updated_node);
        if (updated_node == NULL){
            printf_P(PSTR("ID not found\n"));
            return;
        }
        if (tersedia + dipinjam + rusak != updated_node->jumlah_stok){
            printf_P(PSTR("[ERROR] Total status (%d) tidak sama dengan jumlah stok saat ini (%d)!\n"), (tersedia + dipinjam + rusak), updated_node->jumlah_stok);
        }
        else {
            updated_node->status.dipinjam = dipinjam;
            updated_node->status.tersedia = tersedia;
            updated_node->status.rusak = rusak;
        }
    }
    else {
        printf_P(PSTR("List empty\n"));
    }
}

void update_status_from_input(dataset** head) {
    if (*head == NULL) {
        printf_P(PSTR("[ERROR] List kosong. Tidak ada data untuk diperbarui.\n"));
        return;
    }
    int id;
    int tersedia, dipinjam, rusak;
    printf_P(PSTR("Masukkan ID Barang: "));
    id = read_int();

    dataset* found_node = NULL;
    find(*head, id, &found_node);
    if (found_node == NULL) {
        printf_P(PSTR("[ERROR] ID %d tidak ditemukan.\n"), id);
        return;
    }

    printf_P(PSTR("Masukkan Jumlah Tersedia Baru: "));
    tersedia = read_int();
    if (tersedia < 0) {
        printf_P(PSTR("[ERROR] Jumlah tidak valid.\n"));
        return;
    }

    printf_P(PSTR("Masukkan Jumlah Dipinjam Baru: "));
    dipinjam = read_int();
    if (dipinjam < 0) {
        printf_P(PSTR("[ERROR] Jumlah tidak valid.\n"));
        return;
    }

    printf_P(PSTR("Masukkan Jumlah Rusak Baru: "));
    rusak = read_int();
    if (rusak < 0) {
        printf_P(PSTR("[ERROR] Jumlah tidak valid.\n"));
        return;
    }

    if (tersedia + dipinjam + rusak != found_node->jumlah_stok) {
        printf_P(PSTR("[ERROR] Total status (%d) tidak sama dengan jumlah stok saat ini (%d)!\n"), 
               (tersedia + dipinjam + rusak), found_node->jumlah_stok);
        return;
    }

    update_status(head, id, tersedia, dipinjam, rusak);
    printf_P(PSTR("[SUCCESS] Status barang berhasil diperbarui.\n"));
}

void update_stock(dataset** list, int id, int amount, char mode){
    if (*list != NULL){
        dataset* updated_node;
        find(*list, id, &updated_node);
        if (updated_node != NULL){
            if (mode == '-'){
                if (updated_node->status.rusak - amount < 0){
                    printf_P(PSTR("Rejected: Jumlah barang rusak yang ingin dikurangi (%d) melebihi catatan (%d).\n"), amount, updated_node->status.rusak);
                }
                else if (updated_node->jumlah_stok - amount < 0){
                    printf_P(PSTR("Requirement amount not available\n"));
                    printf_P(PSTR("Available total stock %d\n"), updated_node->jumlah_stok);
                }
                else {
                    updated_node->jumlah_stok -= amount;
                    updated_node->status.rusak -= amount;
                    printf_P(PSTR("Stock updated (Pengurangan/Pembuangan).\n"));
                    printf_P(PSTR("Current total stock: %d | Barang Rusak tersisa: %d\n"), 
                           updated_node->jumlah_stok, updated_node->status.rusak);
                }
            }
            else if (mode == '+'){
                updated_node->jumlah_stok += amount;
                updated_node->status.tersedia += amount;
                printf_P(PSTR("Stock updated (Penambahan).\n"));
                printf_P(PSTR("Current total stock: %d | Barang Tersedia menjadi: %d\n"), 
                       updated_node->jumlah_stok, updated_node->status.tersedia);
            }
            else {
                printf_P(PSTR("Mode tidak valid. Gunakan '+' atau '-'.\n"));
            }
        }
        else {
            printf_P(PSTR("ID not found\n"));
        }
    }
    else {
        printf_P(PSTR("List empty\n"));
    }
}

void update_stock_from_input(dataset** head) {
    if (*head == NULL) {
        printf_P(PSTR("[ERROR] List kosong. Tidak ada data untuk diperbarui.\n"));
        return;
    }
    int id, amount;
    char mode;
    printf_P(PSTR("Masukkan ID Barang: "));
    id = read_int();

    dataset* found_node = NULL;
    find(*head, id, &found_node);
    if (found_node == NULL) {
        printf_P(PSTR("[ERROR] ID %d tidak ditemukan.\n"), id);
        return;
    }

    printf_P(PSTR("Masukkan mode perbaruan (+ untuk menambah, - untuk mengurangi): "));
    mode = read_char();
    if (mode != '+' && mode != '-') {
        printf_P(PSTR("[ERROR] Mode tidak valid.\n"));
        return;
    }

    printf_P(PSTR("Masukkan jumlah stok yang akan diubah: "));
    amount = read_int();
    if (amount < 0) {
        printf_P(PSTR("[ERROR] Jumlah tidak valid.\n"));
        return;
    }

    update_stock(head, id, amount, mode);
}

#include "add.h"
#include <stdio.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <string.h>
#include "uart.h"

void add_item(dataset** head, int id, const char nama[], const char kategori[], int jumlah_stok, const char lokasi_penyimpanan[], int tersedia, int dipinjam, int rusak, const char pemilik[], const char pic[]) {
    // 1. Check for duplicate ID
    dataset* temp = *head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf_P(PSTR("[ERROR] ID %d sudah digunakan (duplikat)!\n"), id);
            return;
        }
        temp = temp->next;
    }

    // 2. Allocate memory for new node
    dataset* new_node = (dataset*)malloc(sizeof(dataset));
    if (new_node == NULL) {
        printf_P(PSTR("[ERROR] Memori hampir habis / Alokasi memori gagal!\n"));
        return;
    }

    // 3. Populate data and ensure proper null-termination
    new_node->id = id;
    
    strncpy(new_node->nama, nama, sizeof(new_node->nama) - 1);
    new_node->nama[sizeof(new_node->nama) - 1] = '\0';

    strncpy(new_node->kategori, kategori, sizeof(new_node->kategori) - 1);
    new_node->kategori[sizeof(new_node->kategori) - 1] = '\0';

    new_node->jumlah_stok = jumlah_stok;

    strncpy(new_node->lokasi_penyimpanan, lokasi_penyimpanan, sizeof(new_node->lokasi_penyimpanan) - 1);
    new_node->lokasi_penyimpanan[sizeof(new_node->lokasi_penyimpanan) - 1] = '\0';

    new_node->status.tersedia = tersedia;
    new_node->status.dipinjam = dipinjam;
    new_node->status.rusak = rusak;

    strncpy(new_node->pemilik, pemilik, sizeof(new_node->pemilik) - 1);
    new_node->pemilik[sizeof(new_node->pemilik) - 1] = '\0';

    strncpy(new_node->pic, pic, sizeof(new_node->pic) - 1);
    new_node->pic[sizeof(new_node->pic) - 1] = '\0';

    new_node->next = NULL;

    // 4. Append to linked list
    if (*head == NULL) {
        *head = new_node;
    } else {
        dataset* curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
    printf_P(PSTR("[SUCCESS] Data dengan ID %d berhasil ditambahkan.\n"), id);
}

void add_item_from_input(dataset** head) {
    int id;
    char nama[21];
    char kategori[15];
    int jumlah_stok;
    char lokasi_penyimpanan[13];
    int tersedia;
    int dipinjam;
    int rusak;
    char pemilik[13];
    char pic[6];


    printf_P(PSTR("\n=== TAMBAH DATA INVENTARIS BARU ===\n"));
    
    printf_P(PSTR("Masukkan ID Barang (angka): "));
    id = read_int();

    printf_P(PSTR("Masukkan Nama Komponen: "));
    read_line(nama, sizeof(nama));

    printf_P(PSTR("Masukkan Kategori Barang: "));
    read_line(kategori, sizeof(kategori));

    printf_P(PSTR("Masukkan Jumlah Stok: "));
    jumlah_stok = read_int();

    printf_P(PSTR("Masukkan Lokasi Penyimpanan: "));
    read_line(lokasi_penyimpanan, sizeof(lokasi_penyimpanan));

    printf_P(PSTR("Masukkan Jumlah Tersedia: "));
    tersedia = read_int();
    if (tersedia < 0) {
        printf_P(PSTR("[ERROR] Input Jumlah Tersedia tidak valid.\n"));
        return;
    }

    printf_P(PSTR("Masukkan Jumlah Dipinjam: "));
    dipinjam = read_int();
    if (dipinjam < 0) {
        printf_P(PSTR("[ERROR] Input Jumlah Dipinjam tidak valid.\n"));
        return;
    }

    printf_P(PSTR("Masukkan Jumlah Rusak: "));
    rusak = read_int();
    if (rusak < 0) {
        printf_P(PSTR("[ERROR] Input Jumlah Rusak tidak valid.\n"));
        return;
    }

    if (tersedia + dipinjam + rusak != jumlah_stok) {
        printf_P(PSTR("[ERROR] Jumlah stok (%d) tidak sesuai dengan jumlah status Tersedia (%d) + Dipinjam (%d) + Rusak (%d)!\n"), jumlah_stok, tersedia, dipinjam, rusak);
        return;
    }

    printf_P(PSTR("Masukkan Pemilik Barang: "));
    read_line(pemilik, sizeof(pemilik));

    printf_P(PSTR("Masukkan PIC Barang: "));
    read_line(pic, sizeof(pic));

    // Call add_item to perform insertion logic
    add_item(head, id, nama, kategori, jumlah_stok, lokasi_penyimpanan, tersedia, dipinjam, rusak, pemilik, pic);
}


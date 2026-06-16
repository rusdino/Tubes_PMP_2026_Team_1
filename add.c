#include "add.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Clears the stdin input buffer.
 */
static void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Reads a line of text from stdin up to max_len.
 * 
 * @param dest Destination buffer.
 * @param max_len Maximum length of characters to read.
 */
static void read_line(char* dest, int max_len) {
    if (fgets(dest, max_len, stdin) != NULL) {
        size_t len = strlen(dest);
        if (len > 0 && dest[len - 1] == '\n') {
            dest[len - 1] = '\0';
        }
    }
}

void add_item(dataset** head, int id, const char nama[], const char kategori[], int jumlah_stok, const char lokasi_penyimpanan[], const char status[], const char pemilik[], const char pic[]) {
    // 1. Check for duplicate ID
    dataset* temp = *head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("[ERROR] ID %d sudah digunakan (duplikat)!\n", id);
            return;
        }
        temp = temp->next;
    }

    // 2. Allocate memory for new node
    dataset* new_node = (dataset*)malloc(sizeof(dataset));
    if (new_node == NULL) {
        printf("[ERROR] Memori hampir habis / Alokasi memori gagal!\n");
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

    strncpy(new_node->status, status, sizeof(new_node->status) - 1);
    new_node->status[sizeof(new_node->status) - 1] = '\0';

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
    printf("[SUCCESS] Data dengan ID %d berhasil ditambahkan.\n", id);
}

void add_item_from_input(dataset** head) {
    int id;
    char nama[50];
    char kategori[20];
    int jumlah_stok;
    char lokasi_penyimpanan[20];
    char status[20];
    char pemilik[50];
    char pic[50];

    printf("\n=== TAMBAH DATA INVENTARIS BARU ===\n");
    
    printf("Masukkan ID Barang (angka): ");
    if (scanf("%d", &id) != 1) {
        printf("[ERROR] Input ID tidak valid.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer(); // clear newline left in stream

    printf("Masukkan Nama Komponen: ");
    read_line(nama, sizeof(nama));

    printf("Masukkan Kategori Barang: ");
    read_line(kategori, sizeof(kategori));

    printf("Masukkan Jumlah Stok: ");
    if (scanf("%d", &jumlah_stok) != 1) {
        printf("[ERROR] Input Stok tidak valid.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer(); // clear newline left in stream

    printf("Masukkan Lokasi Penyimpanan: ");
    read_line(lokasi_penyimpanan, sizeof(lokasi_penyimpanan));

    printf("Masukkan Status Barang (Tersedia/Dipinjam/Rusak/Habis): ");
    read_line(status, sizeof(status));

    printf("Masukkan Pemilik Barang: ");
    read_line(pemilik, sizeof(pemilik));

    printf("Masukkan PIC Barang: ");
    read_line(pic, sizeof(pic));

    // Call add_item to perform insertion logic
    add_item(head, id, nama, kategori, jumlah_stok, lokasi_penyimpanan, status, pemilik, pic);
}

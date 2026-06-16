#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"
#include "add.h"
#include "delete.h"
#include "find_and_update.h"
#include "show.h"
#include "summary.h"

/**
 * @brief Seeds initial mock data into the database linked list.
 * 
 * @param head Pointer to the head pointer of the linked list.
 */
static void seed_data(dataset** head) {
    add_item(head, 101, "Arduino Uno R3", "Mikrokontroler", 15, "Rak A1", 15, 0, 0, "Laboratorium", "Ahmad");
    add_item(head, 102, "Sensor Ultrasonik HC-SR04", "Sensor", 20, "Kotak B2", 20, 0, 0, "Laboratorium", "Budi");
    add_item(head, 103, "Raspberry Pi 4", "SBC", 5, "Rak A2", 0, 5, 0, "Laboratorium", "Cici");
    add_item(head, 104, "Motor Servo SG90", "Actuator", 0, "Kotak C1", 0, 0, 0, "Laboratorium", "Dodi");
}

/**
 * @brief Clears the stdin input buffer.
 */
static void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Runs the main menu interactive CLI loop.
 * 
 * @param head Pointer to the head pointer of the linked list.
 */
static void menu_loop(dataset** head) {
    int pilihan;
    int running = 1;

    while (running) {
        printf("\n==================================================\n");
        printf("   SISTEM INVENTARISASI EMBEDDED SYSTEMS LAB     \n");
        printf("==================================================\n");
        printf("1. Tambah Data Barang Baru\n");
        printf("2. Hapus Data Barang\n");
        printf("3. Cari Data Barang Berdasarkan ID\n");
        printf("4. Perbarui Jumlah Stok Barang\n");
        printf("5. Perbarui Status Barang\n");
        printf("6. Tampilkan Seluruh Data Inventaris\n");
        printf("7. Tampilkan Ringkasan Statistik\n");
        printf("8. Keluar\n");
        printf("==================================================\n");
        printf("Pilih Menu (1-8): ");

        if (scanf("%d", &pilihan) != 1) {
            printf("[ERROR] Masukan tidak valid.\n");
            clear_buffer();
            continue;
        }
        clear_buffer();

        switch (pilihan) {
            case 1:
                add_item_from_input(head);
                break;
            case 2: {
                int id;
                printf("Masukkan ID Barang yang akan dihapus: ");
                if (scanf("%d", &id) != 1) {
                    printf("[ERROR] ID tidak valid.\n");
                    clear_buffer();
                } else {
                    clear_buffer();
                    delete_item(head, id);
                }
                break;
            }
            case 3: {
                int id;
                printf("Masukkan ID Barang yang dicari: ");
                if (scanf("%d", &id) != 1) {
                    printf("[ERROR] ID tidak valid.\n");
                    clear_buffer();
                } else {
                    clear_buffer();
                    dataset* found_node = NULL;
                    find(*head, id, &found_node);
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
                break;
            }
            case 4: {
                int id, amount;
                char mode;
                printf("Masukkan ID Barang: ");
                if (scanf("%d", &id) != 1) {
                    printf("[ERROR] ID tidak valid.\n");
                    clear_buffer();
                    break;
                }
                clear_buffer();
                
                printf("Masukkan mode perbaruan (+ untuk menambah, - untuk mengurangi): ");
                if (scanf(" %c", &mode) != 1 || (mode != '+' && mode != '-')) {
                    printf("[ERROR] Mode tidak valid.\n");
                    clear_buffer();
                    break;
                }
                clear_buffer();

                printf("Masukkan jumlah stok yang akan diubah: ");
                if (scanf("%d", &amount) != 1 || amount < 0) {
                    printf("[ERROR] Jumlah tidak valid.\n");
                    clear_buffer();
                    break;
                }
                clear_buffer();

                update_stock(head, id, amount, mode);
                break;
            }
            case 5: {
                int id;
                int tersedia, dipinjam, rusak;
                printf("Masukkan ID Barang: ");
                if (scanf("%d", &id) != 1) {
                    printf("[ERROR] ID tidak valid.\n");
                    clear_buffer();
                    break;
                }
                clear_buffer();

                dataset* found_node = NULL;
                find(*head, id, &found_node);
                if (found_node == NULL) {
                    printf("[ERROR] ID %d tidak ditemukan.\n", id);
                    break;
                }

                printf("Masukkan Jumlah Tersedia Baru: ");
                if (scanf("%d", &tersedia) != 1 || tersedia < 0) {
                    printf("[ERROR] Jumlah tidak valid.\n");
                    clear_buffer();
                    break;
                }
                clear_buffer();

                printf("Masukkan Jumlah Dipinjam Baru: ");
                if (scanf("%d", &dipinjam) != 1 || dipinjam < 0) {
                    printf("[ERROR] Jumlah tidak valid.\n");
                    clear_buffer();
                    break;
                }
                clear_buffer();

                printf("Masukkan Jumlah Rusak Baru: ");
                if (scanf("%d", &rusak) != 1 || rusak < 0) {
                    printf("[ERROR] Jumlah tidak valid.\n");
                    clear_buffer();
                    break;
                }
                clear_buffer();

                if (tersedia + dipinjam + rusak != found_node->jumlah_stok) {
                    printf("[ERROR] Total status (%d) tidak sama dengan jumlah stok saat ini (%d)!\n", 
                           (tersedia + dipinjam + rusak), found_node->jumlah_stok);
                    break;
                }

                update_status(head, id, tersedia, dipinjam, rusak);
                printf("[SUCCESS] Status barang berhasil diperbarui.\n");
                break;
            }
            case 6:
                show(*head);
                break;
            case 7:
                show_summary(*head);
                break;
            case 8:
                printf("Keluar dari program. Sampai jumpa!\n");
                running = 0;
                break;
            default:
                printf("[ERROR] Pilihan menu tidak valid.\n");
        }
    }
}

int main() {
    dataset* database = NULL;
    
    // Seed initial mock data
    seed_data(&database);
    
    // Enter the interactive CLI loop
    menu_loop(&database);
    
    // Clean up allocated memory before program exit
    dataset* curr = database;
    while (curr != NULL) {
        dataset* temp = curr;
        curr = curr->next;
        free(temp);
    }
    return 0;
}

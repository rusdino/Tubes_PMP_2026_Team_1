#include "menu.h"
#include <stdio.h>
#include "add.h"
#include "delete.h"
#include "find_and_update.h"
#include "show.h"
#include "summary.h"

void seed_data(dataset** head) {
    add_item(head, 101, "Arduino Uno R3", "Mikrokontroler", 15, "Rak A1", 15, 0, 0, "Laboratorium", "Ahmad");
    add_item(head, 102, "Sensor Ultrasonik HC-SR04", "Sensor", 20, "Kotak B2", 20, 0, 0, "Laboratorium", "Budi");
    add_item(head, 103, "Raspberry Pi 4", "SBC", 5, "Rak A2", 0, 5, 0, "Laboratorium", "Cici");
    add_item(head, 104, "Motor Servo SG90", "Actuator", 0, "Kotak C1", 0, 0, 0, "Laboratorium", "Dodi");
}

static void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menu_loop(dataset** head) {
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
            case 2:
                delete_item_from_input(head);
                break;
            case 3:
                find_item_from_input(*head);
                break;
            case 4:
                update_stock_from_input(head);
                break;
            case 5:
                update_status_from_input(head);
                break;
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

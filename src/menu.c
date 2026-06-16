#include "menu.h"
#include <stdio.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <string.h>
#include "add.h"
#include "delete.h"
#include "find_and_update.h"
#include "show.h"
#include "summary.h"
#include "uart.h"

void seed_data(dataset** head) {
    add_item(head, 101, "Arduino Uno R3", "Mikrokontroler", 15, "Rak A1", 15, 0, 0, "Laboratorium", "Ahmad");
    add_item(head, 102, "Sensor Ultrasonik HC-SR04", "Sensor", 20, "Kotak B2", 20, 0, 0, "Laboratorium", "Budi");
    add_item(head, 103, "Raspberry Pi 4", "SBC", 5, "Rak A2", 0, 5, 0, "Laboratorium", "Cici");
    add_item(head, 104, "Motor Servo SG90", "Actuator", 0, "Kotak C1", 0, 0, 0, "Laboratorium", "Dodi");
}

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menu_loop(dataset** head) {
    int pilihan;
    int running = 1;

    while (running) {
        printf_P(PSTR("\n==================================================\n"));
        printf_P(PSTR("   SISTEM INVENTARISASI EMBEDDED SYSTEMS LAB     \n"));
        printf_P(PSTR("==================================================\n"));
        printf_P(PSTR("1. Tambah Data Barang Baru\n"));
        printf_P(PSTR("2. Hapus Data Barang\n"));
        printf_P(PSTR("3. Cari Data Barang Berdasarkan ID\n"));
        printf_P(PSTR("4. Perbarui Jumlah Stok Barang\n"));
        printf_P(PSTR("5. Perbarui Status Barang\n"));
        printf_P(PSTR("6. Tampilkan Seluruh Data Inventaris\n"));
        printf_P(PSTR("7. Tampilkan Ringkasan Statistik\n"));
        printf_P(PSTR("8. Keluar\n"));
        printf_P(PSTR("==================================================\n"));
        printf_P(PSTR("Pilih Menu (1-8): "));

        pilihan = read_int();


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
                printf_P(PSTR("Keluar dari program. Sampai jumpa!\n"));
                running = 0;
                break;
            default:
                printf_P(PSTR("[ERROR] Pilihan menu tidak valid.\n"));
        }
    }
}

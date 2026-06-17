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
    char nama[21];
    char kategori[15];
    char lokasi[13];
    char pemilik[13];
    char pic[6];

    strcpy_P(nama, PSTR("Arduino Uno R3"));
    strcpy_P(kategori, PSTR("Mikrokontroler"));
    strcpy_P(lokasi, PSTR("Rak A1"));
    strcpy_P(pemilik, PSTR("Laboratorium"));
    strcpy_P(pic, PSTR("Ahmad"));
    add_item(head, 101, nama, kategori, 15, lokasi, 15, 0, 0, pemilik, pic);

    strcpy_P(nama, PSTR("Sensor Ultrasonik"));
    strcpy_P(kategori, PSTR("Sensor"));
    strcpy_P(lokasi, PSTR("Kotak B2"));
    strcpy_P(pemilik, PSTR("Laboratorium"));
    strcpy_P(pic, PSTR("Budi"));
    add_item(head, 102, nama, kategori, 20, lokasi, 20, 0, 0, pemilik, pic);

    strcpy_P(nama, PSTR("Raspberry Pi 4"));
    strcpy_P(kategori, PSTR("SBC"));
    strcpy_P(lokasi, PSTR("Rak A2"));
    strcpy_P(pemilik, PSTR("Laboratorium"));
    strcpy_P(pic, PSTR("Cici"));
    add_item(head, 103, nama, kategori, 5, lokasi, 0, 5, 0, pemilik, pic);

    strcpy_P(nama, PSTR("Motor Servo SG90"));
    strcpy_P(kategori, PSTR("Actuator"));
    strcpy_P(lokasi, PSTR("Kotak C1"));
    strcpy_P(pemilik, PSTR("Laboratorium"));
    strcpy_P(pic, PSTR("Dodi"));
    add_item(head, 104, nama, kategori, 0, lokasi, 0, 0, 0, pemilik, pic);
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
        printf_P(PSTR("8. Muat Seed dari Serial\n"));
        printf_P(PSTR("9. Simpan Database ke Serial\n"));
        printf_P(PSTR("10. Keluar\n"));
        printf_P(PSTR("==================================================\n"));
        printf_P(PSTR("Pilih Menu (1-10): "));

        pilihan = read_int();

        if (pilihan <= 0) {
            continue;
        }

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
                load_database_from_serial(head);
                break;
            case 9:
                dump_database_to_serial(*head);
                break;
            case 10:
                printf_P(PSTR("Keluar dari program. Sampai jumpa!\n"));
                running = 0;
                break;
            default:
                printf_P(PSTR("[ERROR] Pilihan menu tidak valid.\n"));
        }
    }
}

void load_database_from_serial(dataset** head) {
    uart_echo_enabled = 0; // Disable echo during automated load
    printf_P(PSTR("[READY] Kirim data database/seed. Ketik 'END' untuk selesai.\n"));
    char line[100];
    while (1) {
        read_line(line, sizeof(line));
        if (strcmp(line, "END") == 0) {
            break;
        }
        if (strlen(line) == 0) {
            continue;
        }
        
        char* token = strtok(line, ";");
        if (!token) {
            printf_P(PSTR("[ERROR] Format data tidak valid (ID kosong).\n"));
            continue;
        }
        int id = atoi(token);
        
        char* nama = strtok(NULL, ";");
        if (!nama) {
            printf_P(PSTR("[ERROR] Format data tidak valid (Nama kosong).\n"));
            continue;
        }
        
        char* kategori = strtok(NULL, ";");
        if (!kategori) {
            printf_P(PSTR("[ERROR] Format data tidak valid (Kategori kosong).\n"));
            continue;
        }
        
        token = strtok(NULL, ";");
        if (!token) {
            printf_P(PSTR("[ERROR] Format data tidak valid (Stok kosong).\n"));
            continue;
        }
        int stok = atoi(token);
        
        token = strtok(NULL, ";");
        if (!token) {
            printf_P(PSTR("[ERROR] Format data tidak valid (Tersedia kosong).\n"));
            continue;
        }
        int tersedia = atoi(token);
        
        token = strtok(NULL, ";");
        if (!token) {
            printf_P(PSTR("[ERROR] Format data tidak valid (Dipinjam kosong).\n"));
            continue;
        }
        int dipinjam = atoi(token);
        
        token = strtok(NULL, ";");
        if (!token) {
            printf_P(PSTR("[ERROR] Format data tidak valid (Rusak kosong).\n"));
            continue;
        }
        int rusak = atoi(token);
        
        char* lokasi = strtok(NULL, ";");
        if (!lokasi) {
            printf_P(PSTR("[ERROR] Format data tidak valid (Lokasi kosong).\n"));
            continue;
        }
        
        char* pemilik = strtok(NULL, ";");
        if (!pemilik) {
            printf_P(PSTR("[ERROR] Format data tidak valid (Pemilik kosong).\n"));
            continue;
        }
        
        char* pic = strtok(NULL, ";");
        if (!pic) {
            printf_P(PSTR("[ERROR] Format data tidak valid (PIC kosong).\n"));
            continue;
        }
        
        add_item(head, id, nama, kategori, stok, lokasi, tersedia, dipinjam, rusak, pemilik, pic);
    }
    uart_echo_enabled = 1; // Re-enable echo for interactive mode
    printf_P(PSTR("[SUCCESS] Proses pemuatan database dari serial selesai.\n"));
}


void dump_database_to_serial(dataset* head) {
    if (head == NULL) {
        printf_P(PSTR("[WARNING] List kosong. Tidak ada data untuk diekspor.\n"));
        return;
    }
    printf_P(PSTR("[START_DUMP]\n"));
    dataset* temp = head;
    while (temp != NULL) {
        printf_P(PSTR("%d;%s;%s;%d;%d;%d;%d;%s;%s;%s\n"),
                 temp->id, temp->nama, temp->kategori, temp->jumlah_stok,
                 temp->status.tersedia, temp->status.dipinjam, temp->status.rusak,
                 temp->lokasi_penyimpanan, temp->pemilik, temp->pic);
        temp = temp->next;
    }
    printf_P(PSTR("[END_DUMP]\n"));
}


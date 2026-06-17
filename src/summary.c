#include "summary.h"
#include <stdio.h>
#include <avr/pgmspace.h>
#include <string.h>

void show_summary(dataset* list) {
    if (list == NULL) {
        printf_P(PSTR("[WARNING] List Empty. Tidak ada ringkasan statistik.\n"));
        return;
    }

    int total_jenis_barang = 0;
    int total_stok = 0;
    int total_rusak = 0;
    int total_dipinjam = 0;
    int total_tersedia = 0;
    int total_habis = 0;

    // For counting categories (max 15 categories to suit Arduino Uno SRAM limits)
    char categories[15][15];
    int category_counts[15] = {0};
    int unique_categories = 0;

    dataset* temp = list;
    while (temp != NULL) {
        total_jenis_barang++;
        total_stok += temp->jumlah_stok;

        total_tersedia += temp->status.tersedia;
        total_dipinjam += temp->status.dipinjam;
        total_rusak += temp->status.rusak;
        if (temp->jumlah_stok == 0) {
            total_habis++;
        }

        // Count category
        int found = 0;
        for (int i = 0; i < unique_categories; i++) {
            if (strcmp(categories[i], temp->kategori) == 0) {
                category_counts[i]++;
                found = 1;
                break;
            }
        }
        if (!found && unique_categories < 15) {
            strncpy(categories[unique_categories], temp->kategori, sizeof(categories[unique_categories]) - 1);
            categories[unique_categories][sizeof(categories[unique_categories]) - 1] = '\0';
            category_counts[unique_categories] = 1;
            unique_categories++;
        }

        temp = temp->next;
    }

    printf_P(PSTR("\n==================================================\n"));
    printf_P(PSTR("               RINGKASAN INVENTARIS               \n"));
    printf_P(PSTR("==================================================\n"));
    printf_P(PSTR("Total Jenis Komponen: %d\n"), total_jenis_barang);
    printf_P(PSTR("Total Jumlah Stok   : %d\n"), total_stok);
    printf_P(PSTR("--------------------------------------------------\n"));
    printf_P(PSTR("Status Barang:\n"));
    printf_P(PSTR("  - Tersedia : %d\n"), total_tersedia);
    printf_P(PSTR("  - Dipinjam : %d\n"), total_dipinjam);
    printf_P(PSTR("  - Rusak    : %d\n"), total_rusak);
    printf_P(PSTR("  - Habis    : %d\n"), total_habis);
    printf_P(PSTR("--------------------------------------------------\n"));
    printf_P(PSTR("Statistik per Kategori:\n"));
    for (int i = 0; i < unique_categories; i++) {
        printf_P(PSTR("  - %-15s: %d jenis\n"), categories[i], category_counts[i]);
    }
    printf_P(PSTR("==================================================\n"));
}

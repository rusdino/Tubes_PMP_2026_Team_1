#include "summary.h"
#include <stdio.h>
#include <string.h>

void show_summary(dataset* list) {
    if (list == NULL) {
        printf("[WARNING] List Empty. Tidak ada ringkasan statistik.\n");
        return;
    }

    int total_jenis_barang = 0;
    int total_stok = 0;
    int total_rusak = 0;
    int total_dipinjam = 0;
    int total_tersedia = 0;
    int total_habis = 0;

    // For counting categories (max 20 categories to suit Arduino Uno SRAM limits)
    char categories[20][20];
    int category_counts[20] = {0};
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
        if (!found && unique_categories < 20) {
            strncpy(categories[unique_categories], temp->kategori, sizeof(categories[unique_categories]) - 1);
            categories[unique_categories][sizeof(categories[unique_categories]) - 1] = '\0';
            category_counts[unique_categories] = 1;
            unique_categories++;
        }

        temp = temp->next;
    }

    printf("\n==================================================\n");
    printf("               RINGKASAN INVENTARIS               \n");
    printf("==================================================\n");
    printf("Total Jenis Komponen: %d\n", total_jenis_barang);
    printf("Total Jumlah Stok   : %d\n", total_stok);
    printf("--------------------------------------------------\n");
    printf("Status Barang:\n");
    printf("  - Tersedia : %d\n", total_tersedia);
    printf("  - Dipinjam : %d\n", total_dipinjam);
    printf("  - Rusak    : %d\n", total_rusak);
    printf("  - Habis    : %d\n", total_habis);
    printf("--------------------------------------------------\n");
    printf("Statistik per Kategori:\n");
    for (int i = 0; i < unique_categories; i++) {
        printf("  - %-15s: %d jenis\n", categories[i], category_counts[i]);
    }
    printf("==================================================\n");
}

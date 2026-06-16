#include "show.h"
#include <stdio.h>

static void print_line(int length) {
    for (int i = 0; i < length; i++) {
        putchar('-');
    }
    putchar('\n');
}

void show(dataset* list){
    dataset* temp = list;
    
    if (temp == NULL){
        printf ("List Empty\n");
        return;
    }
    
    int table_width = 139;
    
    print_line(table_width);
    printf ("%*s\n", (table_width + 8) / 2, "DATABASE");
    print_line(table_width);
    printf ("%-5s | %-25s | %-15s | %-5s | %-13s | %-15s | %-20s | %-20s\n", "ID", "NAMA", "KATEGORI", "STOK", "STATUS(T/D/R)", "LOKASI", "PEMILIK", "PIC");
    print_line(table_width);
    
    while (temp != NULL){
        char status_str[20];
        snprintf(status_str, sizeof(status_str), "%d/%d/%d", temp->status.tersedia, temp->status.dipinjam, temp->status.rusak);
        printf ("%-5d | %-25s | %-15s | %-5d | %-13s | %-15s | %-20s | %-20s\n", temp->id, temp->nama, temp->kategori, temp->jumlah_stok, status_str, temp->lokasi_penyimpanan, temp->pemilik, temp->pic);        
        temp = temp->next;
    }
    print_line(table_width);
    return;
}


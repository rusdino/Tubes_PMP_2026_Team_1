#include "show.h"
#include <stdio.h>

void show(dataset* list){
    dataset* temp = list;
    if (temp == NULL){
        printf ("List Empty\n");
        return;
    }
    printf ("________________________________________________________________DATABASE______________________________________________________________\n");
    printf ("______________________________________________________________________________________________________________________________________\n");
    printf ("%-5s | %-25s | %-15s | %-5s | %-15s | %-15s | %-20s | %-20s\n", "ID", "NAMA", "KATEGORI", "STOK", "LOKASI", "STATUS", "PEMILIK", "PIC");
    printf ("______________________________________________________________________________________________________________________________________\n");
    while (temp != NULL){
        printf ("%-5d | %-25s | %-15s | %-5d | %-15s | %-15s | %-20s | %-20s\n", temp->id, temp->nama, temp->kategori, temp->jumlah_stok, temp->lokasi_penyimpanan, temp->status, temp->pemilik, temp->pic);
        temp = temp->next;
    }
    return;
}
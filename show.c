#include "show.h"
#include <stdio.h>

void show(dataset* list){
    dataset* temp = list;
    
    if (temp == NULL){
        printf ("List Empty\n");
        return;
    }
    
    printf ("______________________________________________________________________________________________________________________________________________________\n");
    printf ("                                                                        DATABASE                                                                      \n");
    printf ("______________________________________________________________________________________________________________________________________________________\n");
    printf ("%-5s | %-25s | %-15s | %-5s | %-13s | %-15s | %-20s | %-20s\n", "ID", "NAMA", "KATEGORI", "STOK", "STATUS(T/D/R)", "LOKASI", "PEMILIK", "PIC");
    printf ("______________________________________________________________________________________________________________________________________________________\n");
    
    while (temp != NULL){
        char status_str[20];
        sprintf(status_str, "%d/%d/%d", temp->status.tersedia, temp->status.dipinjam, temp->status.rusak);
        printf ("%-5d | %-25s | %-15s | %-5d | %-13s | %-15s | %-20s | %-20s\n", temp->id, temp->nama, temp->kategori, temp->jumlah_stok, status_str, temp->lokasi_penyimpanan, temp->pemilik, temp->pic);        
        temp = temp->next;
    }
    return;
}

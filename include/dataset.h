#ifndef DATASET_H
#define DATASET_H

#include <stdint.h>

typedef struct property{
    uint8_t tersedia;
    uint8_t dipinjam;
    uint8_t rusak;
}property;

typedef struct dataset{
    int id;
    char nama[19];
    char kategori[15];
    uint8_t jumlah_stok;
    property status;
    char lokasi_penyimpanan[10];
    char pemilik[13];
    char pic[6];
    struct dataset* next;
}dataset;

#endif


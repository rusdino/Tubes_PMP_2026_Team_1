#ifndef DATASET_H
#define DATASET_H

typedef struct property{
    int tersedia;
    int dipinjam;
    int rusak;
}property;

typedef struct dataset{
    int id;
    char nama[50];
    char kategori[20];
    int jumlah_stok;
    property status;
    char lokasi_penyimpanan[20];
    char pemilik[50];
    char pic[50];
    struct dataset* next;
}dataset;

#endif

# Tubes_PMP_2026_Team_1
sebuah sistem inventarisasi sederhana akan dibuat berbasis Arduino Uno. Setiap komponen/peralatan laboratorium diberi ID unik yang akan direpresentasikan dalam bentuk QR code. QR code tersebut akan ditempelkan pada komponen, kotak penyimpanan, atau rak alat.
# Sistem Inventarisasi Laboratorium Embedded Systems

Proyek ini adalah perangkat lunak sistem inventarisasi barang laboratorium berbasis Arduino Uno, dikembangkan untuk memenuhi Tugas Besar Pemecahan Masalah dengan Pemrograman (EL2008). Sistem ini dirancang untuk mendigitalisasi pencatatan manual yang menggunakan logbook atau spreadsheet.

## Deskripsi Sistem

Setiap komponen laboratorium direpresentasikan dengan ID unik berbasis QR code. Sistem membaca ID ini melalui pemindai QR dan menjadikannya kata kunci untuk mengakses data. Mengingat keterbatasan sumber daya dan memori pada Arduino Uno, proyek ini tidak menggunakan sistem database eksternal, melainkan diimplementasikan sepenuhnya menggunakan struktur data Linked List di dalam memori mikrokontroler.

## Fitur Utama

Sistem beroperasi melalui Serial Monitor dan mendukung fitur berikut:
- Menambah data barang baru.
- Menghapus data barang.
- Mencari data barang berdasarkan ID.
- Memperbarui jumlah stok barang.
- Memperbarui status barang.
- Menampilkan seluruh data inventaris.
- Menampilkan ringkasan inventaris.

## Struktur Data

Data inventaris yang disimpan memuat informasi:
- ID Barang
- Nama Komponen/Peralatan
- Kategori Barang
- Jumlah Stok
- Lokasi Penyimpanan
- Status Barang (Tersedia / Dipinjam / Rusak / Habis)
- Pemilik Barang
- PIC (Person in Charge)

## Penanganan Masalah (Error Handling)

Sistem dilengkapi penanganan error untuk skenario berikut:
- Input ID duplikat.
- Pencarian ID yang tidak ditemukan.
- Pengurangan stok melebihi batas.
- Operasi sistem saat data masih kosong.
- Peringatan batas kapasitas memori.
- Validasi penghapusan node pertama, tengah, dan akhir pada Linked List.

## Arsitektur Program

Program ditulis dalam Bahasa C dengan pendekatan modular (file `.c` dan `.h`). Mematuhi batasan spesifikasi tugas, fungsi `main()` murni berperan sebagai pemanggil fungsi, dan seluruh fungsi operasional menggunakan tipe data `void`.

## Anggota Kelompok

- [Nama/NIM 1] - Struktur Data & Manajemen Memori
- [Nama/NIM 2] - Operasi CRUD Linked List
- [Nama/NIM 3] - Antarmuka & Pembaruan Data
- [Nama/NIM 4] - Penanganan Error & Dokumentasi

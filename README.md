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

## 👥 Pembagian Tugas Tim: Sistem Inventarisasi Laboratorium

Sistem ini diimplementasikan menggunakan struktur data **Linked List** murni dalam Bahasa C pada Arduino Uno. Karena keterbatasan SRAM memori (hanya 2KB), manajemen memori sangat krusial. 

Setiap *node* pada Linked List akan memuat data berikut:
1. ID Barang (Unik)
2. Nama Komponen
3. Kategori Barang
4. Jumlah Stok
5. Lokasi Penyimpanan
6. Status Barang (Tersedia, Dipinjam, Rusak, Habis)
7. Pemilik Barang
8. PIC

Berikut adalah pembagian tugas substansial untuk 4 orang:

### 1. The Core Allocator (Manajemen Memori & Registrasi Data)
**Fokus:** Mengatur struktur data dasar dan alokasi memori dinamis.
* **Tugas Utama:**
  * Mendefinisikan tipe data `struct` yang paling efisien memori (misalnya menggunakan *array of char* alih-alih tipe data dinamis berat).
  * **Fungsi 1 (Menambah Data):** Membuat logika registrasi barang baru.
* **Edge Cases & Error Handling:**
  * Menangani **ID duplikat** (memastikan tidak ada ID yang sama masuk ke sistem).
  * Mendeteksi dan menangani kondisi **memori hampir habis** (menangkap *return* `NULL` dari fungsi alokasi `malloc()`).

### 2. The Surgeon (Operasi Penghapusan & Integritas Data)
**Fokus:** Manipulasi sambungan *pointer* pada Linked List agar tidak terjadi kebocoran memori (*memory leak*).
* **Tugas Utama:**
  * **Fungsi 2 (Menghapus Data):** Mengatur logika pelepasan *node* dari memori menggunakan `free()`.
  * **Fungsi 6 (Menampilkan Seluruh Data):** Melakukan iterasi dari awal hingga akhir *node* untuk mencetak data.
* **Edge Cases & Error Handling:**
  * Memastikan program tidak *crash* saat melakukan penghapusan pada **node awal (head)**, **tengah**, maupun **akhir (tail)**.
  * Menangani peringatan saat mencoba menghapus atau menampilkan dari **data kosong**.
  * Menangani input pencarian **ID tidak ditemukan** saat proses penghapusan.

### 3. The Search & Update Specialist (Navigasi & Modifikasi Data)
**Fokus:** Membuat mesin pencari yang menjadi tulang punggung untuk fitur pembaruan.
* **Tugas Utama:**
  * **Fungsi 3 (Mencari Data):** Menelusuri Linked List dan mengembalikan *pointer* ke *node* yang sesuai dengan ID.
  * **Fungsi 4 (Memperbarui Stok):** Memodifikasi variabel stok pada *node* yang ditemukan.
  * **Fungsi 5 (Memperbarui Status):** Memodifikasi variabel status (tersedia/dipinjam/dsb).
* **Edge Cases & Error Handling:**
  * Menangani peringatan saat memanipulasi stok/status pada **data kosong** atau **ID tidak ditemukan**.
  * Menangani logika penolakan jika pembaruan pengurangan membuat **stok tidak mencukupi** (misal stok sisa 2, tapi dikurangi 5).

### 4. The Aggregator & Integrator (Arsitektur Utama & I/O)
**Fokus:** Menyatukan seluruh modul C, mengelola antarmuka (I/O) komunikasi serial murni, dan kalkulasi rekapitulasi.
* **Tugas Utama:**
  * **Fungsi 7 (Menampilkan Ringkasan):** Melakukan iterasi perhitungan statistik (total barang, total per kategori, jumlah barang rusak/dipinjam).
  * **Integrasi `main()`:** Memastikan aturan spesifikasi terpenuhi (fungsi `main` hanya sebagai pemanggil, semua fungsi operasi bertipe `void`).
  * Mengatur *wrapper* komunikasi serial (menggunakan register UART murni seperti `printf/scanf` standar C, bukan bawaan C++ `Serial.print`).
* **Edge Cases & Error Handling:**
  * Menangani perhitungan ringkasan saat kondisi **database masih kosong**.
  * Memastikan *input/output* Serial Monitor berjalan responsif dan tidak *blocking*.

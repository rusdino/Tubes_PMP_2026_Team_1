# Sistem Inventarisasi Laboratorium Embedded Systems

Proyek ini adalah implementasi perangkat lunak untuk sistem inventarisasi komponen dan peralatan laboratorium berbasis **Arduino Uno R3 (ATmega328P)**. Sistem ini dikembangkan untuk memenuhi Tugas Besar Pemecahan Masalah dengan Pemrograman (EL2008) dengan menggunakan **Bahasa C murni (modular)** dan berkomunikasi langsung melalui **Serial Monitor** tanpa pustaka C++ bawaan Arduino (`Serial.print`).

---

## 📌 Fitur Utama

Sistem ini beroperasi secara interaktif via Serial Monitor dan mendukung fungsi-fungsi inventarisasi berikut:
1. **Tambah Data Barang Baru**: Mendaftarkan barang baru ke dalam memori dinamis (*linked list*).
2. **Hapus Data Barang**: Menghapus data barang tertentu berdasarkan ID barang, mendukung penanganan penghapusan di awal (*head*), tengah (*middle*), maupun akhir (*tail*) list secara aman tanpa kebocoran memori.
3. **Cari Data Barang**: Mencari komponen spesifik berdasarkan ID uniknya dan menampilkan detail data secara lengkap.
4. **Perbarui Stok Barang**: Melakukan penambahan stok baru (+) atau pengurangan/pembuangan stok rusak (-) secara dinamis.
5. **Perbarui Status Barang**: Mengubah proporsi status komponen (Tersedia, Dipinjam, Rusak, Habis) secara langsung.
6. **Tampilkan Database**: Menampilkan seluruh data inventaris yang tersimpan dalam format tabel yang rapi di Serial Monitor.
7. **Ringkasan Inventaris**: Menghitung statistik global seperti total jenis komponen, jumlah total unit fisik, pengelompokan berdasarkan kategori, dan status barang.

---

## ⚙️ Spesifikasi Teknis & Optimasi Memori

* **Mikrokontroler**: Arduino Uno R3 (ATmega328P) — **SRAM: 2 KB**, **Flash: 32 KB**.
* **Komunikasi Serial**: UART register-level murni (Baud rate **9600**, format 8N1). standard I/O streams C (`stdin`/`stdout`) langsung diarahkan ke register UART mikrokontroler.
* **Struktur Data**: Singly Linked List murni dengan alokasi memori dinamis (`malloc` & `free`).
* **Optimasi SRAM (PROGMEM)**:
  Karena keterbatasan SRAM Arduino Uno yang hanya 2KB, proyek ini menggunakan optimasi memori Flash (`pgmspace.h`). Semua string literal, menu CLI, dan string format cetakan disimpan langsung di dalam Flash (menggunakan `printf_P` dan `PSTR`), sehingga konsumsi SRAM statis berkurang dari **155% menjadi hanya 11.2% (229 byte)**.

---

## 📁 Struktur Berkas Proyek

Proyek ini menggunakan struktur modular C dengan pemisahan berkas `.c` dan `.h` yang terstandarisasi:

```text
Tubes_PMP_2026_Team_1/
├── include/                   # Berkas Header (.h)
│   ├── dataset.h              # Definisi struktur data komponen (Linked List)
│   ├── uart.h                 # Driver UART register-level dan fungsi input aman
│   ├── menu.h                 # Loop menu dan fungsi seeding mock data
│   ├── add.h                  # Fungsi tambah barang ke database
│   ├── delete.h               # Fungsi hapus barang dan free memory
│   ├── find_and_update.h      # Fungsi pencarian, update stok, dan update status
│   ├── show.h                 # Fungsi mencetak tabel database
│   └── summary.h              # Fungsi analisis data & rekapitulasi statistik
├── src/                       # Berkas Source Code (.c)
│   ├── main.c                 # Entry point utama program
│   ├── uart.c                 # Implementasi driver UART register-level dan input helper
│   ├── menu.c                 # Logika loop interaksi menu utama
│   ├── add.c                  # Logika registrasi data baru
│   ├── delete.c               # Logika pelepasan node linked list
│   ├── find_and_update.c      # Logika pencarian data dan modifikasi stok/status
│   ├── show.c                 # Logika rendering tabel
│   └── summary.c              # Logika kalkulator agregasi data
├── Makefile                   # Otomatisasi pio build, upload, dan monitor
├── platformio.ini             # Konfigurasi PlatformIO untuk target Board Arduino Uno
└── README.md                  # Dokumentasi proyek
```

---

## 🛠️ Persiapan Lingkungan (Setup Environment)

Untuk mengompilasi dan mengunggah kode ke Arduino Uno, Anda memerlukan **PlatformIO Core (CLI)**.

### Langkah 1: Instalasi PlatformIO Core
Jika Anda menggunakan VS Code, instal ekstensi **PlatformIO IDE**. Ekstensi ini secara otomatis akan memasang PlatformIO Core.
Di Windows, executable PlatformIO biasanya berada di lokasi:
```text
C:\Users\<Username>\.platformio\penv\Scripts\
```

### Langkah 2: Menambahkan PlatformIO ke PATH System (Opsional)
Agar dapat memanggil perintah `pio` langsung dari PowerShell/CMD/Terminal:
1. Cari Windows Search: *Environment Variables* (Edit variabel lingkungan sistem).
2. Di bagian *User Variables*, pilih `Path` lalu klik **Edit**.
3. Klik **New** dan masukkan path berikut (sesuaikan `<Username>` Anda):
   ```text
   %USERPROFILE%\.platformio\penv\Scripts
   ```
4. Klik **OK** dan buka kembali terminal baru Anda.

---

## 🚀 Kompilasi, Mengunggah, dan Memonitor

Setelah lingkungan siap dan Arduino Uno terhubung ke port **COM23**, Anda dapat menggunakan terminal atau Makefile.

### 1. Menggunakan Perintah PlatformIO CLI Langsung

Jalankan perintah-perintah berikut di folder root proyek:

* **Kompilasi Proyek (Build):**
  ```powershell
  & "C:\Users\<Username>\.platformio\penv\Scripts\pio.exe" run
  ```
  *(Atau cukup ketik `pio run` jika pio sudah masuk ke PATH).*

* **Unggah ke Arduino Uno (COM23):**
  ```powershell
  & "C:\Users\<Username>\.platformio\penv\Scripts\pio.exe" run -t upload
  ```
  *(PlatformIO akan mendeteksi target COM23 dari file `platformio.ini` dan mem-flash firmware).*

* **Membuka Serial Monitor:**
  ```powershell
  & "C:\Users\<Username>\.platformio\penv\Scripts\pio.exe" device monitor
  ```
  *(Serial Monitor akan terbuka pada baudrate 9600).*

---

### 2. Menggunakan GNU Make (Makefile)

Jika sistem Anda sudah terpasang utilitas `make` (misal via MinGW, Git Bash, WSL, dll), Anda dapat memanfaatkan perintah singkatan berikut:

* **Kompilasi Kode:**
  ```bash
  make build
  ```
* **Mengunggah Firmware:**
  ```bash
  make upload
  ```
* **Membuka Serial Monitor:**
  ```bash
  make monitor
  ```
* **Mengunggah sekaligus Memonitor (Sangat Direkomendasikan):**
  ```bash
  make run
  ```
* **Membersihkan Berkas Sampah Hasil Kompilasi:**
  ```bash
  make clean
  ```

---

## ⚠️ Penanganan Masalah & Error Handling

Program ini dilengkapi dengan deteksi edge cases untuk menjamin kestabilan mikrokontroler:
* **ID Duplikat**: Sistem akan menolak penambahan barang jika ID yang diinput sudah ada di database.
* **Memori Penuh (Null Pointer)**: Sistem akan menangkap kegagalan alokasi `malloc()` dan menampilkan pesan error jika RAM Arduino hampir habis saat penambahan data.
* **Pencarian & Hapus ID Tidak Ditemukan**: Menampilkan pesan error yang ramah dan membatalkan operasi tanpa merusak list.
* **Pengurangan Stok Melebihi Batas**: Mencegah stok menjadi bernilai negatif dan menjaga konsistensi nilai status (Tersedia + Dipinjam + Rusak = Total Stok).
* **Operasi pada Data Kosong**: Menampilkan peringatan khusus jika pengguna mencoba menghapus, mencari, memperbarui, atau menampilkan data pada database yang belum memiliki data.

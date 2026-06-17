# 📦 Sistem Inventarisasi Laboratorium Embedded Systems

![C](https://img.shields.io/badge/language-C-blue.svg)
![Platform](https://img.shields.io/badge/platform-Arduino%20Uno-00979C.svg)
![Memory](https://img.shields.io/badge/optimization-Extreme%20(SRAM%20%3C%205%25)-brightgreen.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

Sistem manajemen inventaris komponen dan peralatan laboratorium interaktif berbasis **Arduino Uno R3 (ATmega328P)**. Proyek ini dikembangkan murni menggunakan **Bahasa C** (*Bare Metal / Register-level UART*) tanpa mengandalkan *library* bawaan Arduino C++ (seperti `Serial.print`). 

Proyek ini dibuat untuk memenuhi Tugas Besar Pemecahan Masalah dengan Pemrograman (EL2008).

---

## 📑 Daftar Isi
- [Fitur Utama](#-fitur-utama)
- [Spesifikasi Teknis & Optimasi](#-spesifikasi-teknis--optimasi)
- [Struktur Direktori](#-struktur-direktori)
- [Persiapan & Instalasi](#-persiapan--instalasi)
- [Cara Penggunaan](#-cara-penggunaan)
- [Pengelolaan Database (Python)](#-pengelolaan-database-python)
- [Troubleshooting](#-troubleshooting)

---

## ✨ Fitur Utama

- **Manajemen Data Dinamis**: Menambahkan, mencari, dan menghapus data alat/komponen berbasis algoritma *Singly Linked List* yang efisien.
- **Kendali Stok & Status**: Memperbarui jumlah stok dan mendistribusikan status barang secara aktual (Tersedia, Dipinjam, Rusak).
- **Tampilan Tabel Serial**: Menampilkan seluruh data inventaris dalam format tabel antarmuka yang rapi secara langsung di Serial Monitor.
- **Ringkasan Cerdas**: Menghitung statistik inventaris global secara otomatis (total unit fisik, rasio jenis komponen, klasifikasi kategori).
- **Manajemen Memori Aman**: Mencegah *Heap Overflow* (`malloc` protection) dan kebocoran memori pada lingkungan *resource-constrained*.

---

## ⚙️ Spesifikasi Teknis & Optimasi

Proyek ini menonjolkan arsitektur yang sangat ramping karena keterbatasan memori pada mikrokontroler.

* **Perangkat Keras**: Arduino Uno R3 (ATmega328P).
* **Komunikasi**: Register-level UART (Baud rate **9600**, format 8N1) yang dipetakan langsung pada standar input/output (`stdin`/`stdout`).
* **Alokasi Memori**: Dinamis menggunakan ruang sempit memori SRAM (total 2 KB).
* **Extreme Memory Optimization**: 
  - Konsumsi RAM ditekan secara ekstrem hingga **~3.1% (63 bytes)** saat *idle*.
  - Pemindahan data statis secara menyeluruh: teks menu peringatan, judul tabel, serta *formatting string* diletakkan ke *Flash Memory* (PROGMEM) memanfaatkan pustaka `<avr/pgmspace.h>`.
  - Optimalisasi bit dan *struct*: Penyesuaian ukuran dan batasan karakter pada masing-masing entri barang (*node*) untuk menghemat *byte-by-byte*.

---

## 📂 Struktur Direktori

Sistem ini menganut standar arsitektur *modular C* dengan pemisahan berkas *header* dan *source* yang jelas:

```text
Tubes_PMP_2026_Team_1/
├── include/                   # Deklarasi fungsi dan struktur data (.h)
│   ├── dataset.h              # Definisi ukuran struct Linked List
│   ├── uart.h                 # Driver UART low-level
│   └── ...                    # Modul-modul fungsional lainnya
├── src/                       # Implementasi logika utama (.c)
│   ├── main.c                 # Entry point dan Main Loop program
│   ├── uart.c                 # Implementasi stream input/output Serial
│   └── ...                    # Logika CRUD & rendering antarmuka
├── lib/                       # Berkas Seed Data inventaris (*.csv)
├── test/                      # Direktori ekspor/backup database (.csv)
├── manage_serial.py           # Skrip pengelola serial/database dinamis
├── platformio.ini             # Konfigurasi PlatformIO & target Board
└── Makefile                   # Sistem otomasi utilitas proyek
```

---

## 🚀 Persiapan & Instalasi

Proyek ini dikelola memanfaatkan **PlatformIO CLI**. Pastikan Anda sudah menginstal platform tersebut melalui ekstensi VS Code atau CLI mandiri.

### 1. Konfigurasi Lingkungan (Windows)
Jika Anda menggunakan terminal Command Prompt / PowerShell murni, pastikan PlatformIO diatur dalam Environment Variables `PATH` sistem Anda:
```text
C:\Users\<Username>\.platformio\penv\Scripts\
```

---

## 💻 Cara Penggunaan

Gunakan terminal atau utilitas *GNU Make* di terminal Anda untuk menjalankan proses build secara instan.

| Perintah Makefile | Perintah PlatformIO (Alternatif) | Deskripsi Tindakan |
| :--- | :--- | :--- |
| `make build` | `pio run` | Mengompilasi seluruh *source code* modular |
| `make upload` | `pio run -t upload` | Melakukan *flash firmware* ke Arduino Uno |
| `make monitor` | `pio device monitor` | Membuka antarmuka Serial Monitor bawaan |
| `make run` | - | Mengompilasi, *upload*, sekaligus membuka monitor |
| `make clean` | `pio run -t clean` | Membersihkan *cache object* kompilasi sebelumnya |

*Catatan: Konfigurasi upload secara spesifik dipetakan ke port **COM23** (lihat `platformio.ini`). Sesuaikan port tersebut bila menggunakan Arduino di komputer yang berbeda.*

---

## 🗄️ Pengelolaan Database (Python)

Program ini menyertakan utilitas eksternal cerdas, `manage_serial.py`, yang mengotomatisasi injeksi (*seeding*) puluhan data inventaris ke memori RAM Arduino, serta pencadangan data (*backup*) ke PC.

1. **Penting**: Tutup semua antarmuka Serial Monitor reguler yang berjalan sebelum mengeksekusi skrip ini.
2. Jalankan utilitas pengelola melalui terminal PC Anda:
   ```bash
   make manage
   # atau
   python manage_serial.py
   ```
3. **Data Seeding**: Ketik angka `8` (opsi `Load Seed`) untuk mendorong puluhan baris data bawaan (dari direktori `lib/`) tanpa perlu mengetik ulang ID dan atribut barang secara manual.
4. **Data Exporting**: Anda dapat menyimpan kondisi operasional inventaris mikrokontroler terakhir sebagai berkas log `.csv` di dalam direktori `test/`.

---

## 🛡️ Troubleshooting

- **Error: Access is denied (COM Port)**
  *Penyebab:* Port serial masih diblokir oleh interaksi yang sedang berjalan (seperti *Terminal Monitor* yang belum dimatikan atau proses Python yang macet).
  *Solusi:* Tutup paksa sesi terminal tersebut sebelum melakukan proses `upload`.
  
- **Serial Monitor *Freeze* atau Terhenti Tiba-tiba**
  *Penyebab:* Penambahan muatan data yang tak terhingga akhirnya menghabiskan sisa memori dinamis 2 KB (SRAM Exhaustion).
  *Solusi:* Sistem kami telah menerapkan mekanisme deteksi limit memori yang ketat (*malloc verification*). Kurangi jumlah muatan data atau pantau notifikasi "Memori Hampir Habis" pada Serial Monitor.

---

*Dipersembahkan untuk Tugas Besar EL2008 © 2026 Team 1*

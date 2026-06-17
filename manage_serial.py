import os
import sys
import time
import glob
import datetime
import threading

# Try to import serial
try:
    import serial
    import serial.tools.list_ports
except ImportError:
    print("[ERROR] Library 'pyserial' belum terinstal. Silakan jalankan 'pip install pyserial' terlebih dahulu.")
    sys.exit(1)

LIB_DIR = "lib"
TEST_DIR = "test"
DEFAULT_PORT = "COM23"
BAUDRATE = 9600

def safe_flush_input(ser):
    """Discard all bytes in the input buffer by reading them, avoiding hardware resets."""
    try:
        time.sleep(0.05)
        while ser.in_waiting > 0:
            ser.read(ser.in_waiting)
            time.sleep(0.01)
    except Exception:
        pass

def list_ports():
    ports = list(serial.tools.list_ports.comports())
    return [p.device for p in ports]

def select_port():
    ports = list_ports()
    print("\n--- DETEKSI PORT SERIAL ---")
    if not ports:
        print(f"[Peringatan] Tidak ada port serial aktif yang terdeteksi.")
        print(f"Menggunakan default port: {DEFAULT_PORT}")
        return DEFAULT_PORT
    
    print("Port serial yang terdeteksi:")
    for idx, p in enumerate(ports):
        print(f"  [{idx + 1}] {p}")
    print(f"  [D] Default Port ({DEFAULT_PORT})")
    
    choice = input("Pilih nomor port atau tekan Enter untuk default: ").strip()
    if not choice or choice.lower() == 'd':
        return DEFAULT_PORT
    try:
        idx = int(choice) - 1
        if 0 <= idx < len(ports):
            return ports[idx]
    except ValueError:
        pass
    print(f"Pilihan tidak valid. Menggunakan default port: {DEFAULT_PORT}")
    return DEFAULT_PORT

def list_seed_files():
    if not os.path.exists(LIB_DIR):
        os.makedirs(LIB_DIR)
    files = glob.glob(os.path.join(LIB_DIR, "*.csv"))
    return sorted(files)

def menu_seed(ser):
    files = list_seed_files()
    if not files:
        print(f"\n[ERROR] Tidak ada berkas seed (.csv) ditemukan di folder '{LIB_DIR}'.")
        return

    print("\n--- BERKAS SEED YANG TERSEDIA DI FOLDER LIB/ ---")
    for idx, f in enumerate(files):
        try:
            with open(f, 'r', encoding='utf-8') as fh:
                items = sum(1 for line in fh if line.strip())
        except Exception:
            items = "?"
        filename = os.path.basename(f)
        print(f"  [{idx + 1}] {filename} ({items} item)")

    choice = input("Pilih berkas seed yang ingin diunggah: ").strip()
    try:
        idx = int(choice) - 1
        if 0 <= idx < len(files):
            selected_file = files[idx]
        else:
            print("[ERROR] Pilihan tidak valid.")
            return
    except ValueError:
        print("[ERROR] Pilihan tidak valid.")
        return

    filename = os.path.basename(selected_file)
    try:
        # Prepare serial communication
        safe_flush_input(ser)

        print("Mengirim perintah '8' (Muat Seed)...")
        ser.write(b"8\n")
        
        # Wait for [READY] signal
        ready = False
        start_time = time.time()
        buffer = ""
        while time.time() - start_time < 5:
            if ser.in_waiting:
                chunk = ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
                buffer += chunk
                if "[READY]" in buffer:
                    ready = True
                    break
            time.sleep(0.01)
        
        if not ready:
            print("[ERROR] Arduino tidak merespon status READY.")
            print(f"Buffer keluaran terakhir:\n{buffer}")
            return

        print(f"Mengunggah data dari {filename}...")
        with open(selected_file, 'r', encoding='utf-8') as fh:
            lines = fh.readlines()

        # Handshake loop: Send line and wait for Arduino verification to prevent packet loss
        for line in lines:
            line_str = line.strip()
            if not line_str:
                continue
            # Transmit line over serial
            print(f" -> Kirim: {line_str}")
            ser.write((line_str + "\n").encode('utf-8'))
            
            # Wait for [SUCCESS] or [ERROR] acknowledgement
            response_received = False
            response_buffer = ""
            start_wait = time.time()
            while time.time() - start_wait < 5:  # 5 seconds timeout per line
                if ser.in_waiting:
                    chunk = ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
                    response_buffer += chunk
                    if "\n" in response_buffer:
                        parts = response_buffer.split("\n")
                        for p in parts[:-1]:
                            p_clean = p.strip()
                            if p_clean:
                                print(f"    [Arduino]: {p_clean}")
                                if "[SUCCESS]" in p_clean or "[ERROR]" in p_clean:
                                    response_received = True
                        response_buffer = parts[-1]
                        if response_received:
                            break
                time.sleep(0.01)

        # Send END command to finish
        print(" -> Kirim: END")
        ser.write(b"END\n")
        
        # Wait for final SUCCESS signal
        success = False
        start_time = time.time()
        buffer = ""
        while time.time() - start_time < 5:
            if ser.in_waiting:
                chunk = ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
                buffer += chunk
                if "[SUCCESS]" in buffer:
                    success = True
                    break
            time.sleep(0.01)
        
        # Print remaining output
        time.sleep(0.3)
        if ser.in_waiting:
            buffer += ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
            
        print("\nKeluaran Arduino:")
        for l in buffer.split('\n'):
            l = l.strip()
            if l:
                print(f"  {l}")
                
    except Exception as e:
        print(f"[ERROR] Terjadi kesalahan: {e}")

def menu_dump(ser):
    try:
        safe_flush_input(ser)

        print("Mengirim perintah '9' (Simpan Database)...")
        ser.write(b"9\n")
        
        # Read output and capture dump
        dump_data = []
        is_dumping = False
        start_time = time.time()
        buffer = ""
        
        while time.time() - start_time < 8:
            if ser.in_waiting:
                chunk = ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
                buffer += chunk
                
                # Check for Start of dump
                if "[START_DUMP]" in buffer and not is_dumping:
                    is_dumping = True
                    buffer = buffer.split("[START_DUMP]")[1]
                    
                # Check for End of dump
                if "[END_DUMP]" in buffer:
                    lines = buffer.split("[END_DUMP]")[0].strip().split('\n')
                    for line in lines:
                        line = line.strip()
                        if line:
                            dump_data.append(line)
                    break
                    
                # If dumping and buffer contains a newline, parse completed lines
                if is_dumping and '\n' in buffer:
                    parts = buffer.split('\n')
                    for p in parts[:-1]:
                        p = p.strip()
                        if p:
                            dump_data.append(p)
                    buffer = parts[-1]
            time.sleep(0.01)
        
        if not dump_data and not is_dumping:
            print("[ERROR] Arduino tidak merespon dumping data atau database kosong.")
            return

        print(f"\nBerhasil menerima {len(dump_data)} data komponen!")
        
        # Create test folder if it does not exist
        if not os.path.exists(TEST_DIR):
            os.makedirs(TEST_DIR)
            
        timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
        default_filename = f"db_backup_{timestamp}.csv"
        
        filename = input(f"Masukkan nama file backup (Default: {default_filename}): ").strip()
        if not filename:
            filename = default_filename
        if not filename.endswith('.csv'):
            filename += '.csv'
            
        filepath = os.path.join(TEST_DIR, filename)
        with open(filepath, 'w', encoding='utf-8') as fh:
            for item in dump_data:
                fh.write(item + "\n")
                
        print(f"[SUCCESS] Database berhasil disimpan di {filepath}")
    except Exception as e:
        print(f"[ERROR] Terjadi kesalahan: {e}")

def monitor_serial(ser):
    try:
        safe_flush_input(ser)
        
        # Trigger the Arduino to redraw the menu silently by sending newline
        ser.write(b"\n")
        
        print("\n--- MONITOR SERIAL AKTIF (Tanpa Reset) ---")
        print("Tekan Ctrl+C untuk kembali ke menu utama.\n")
        
        # Wait a bit for the menu printout to finish transferring completely
        time.sleep(0.6)
        if ser.in_waiting:
            sys.stdout.write(ser.read(ser.in_waiting).decode('utf-8', errors='ignore'))
            sys.stdout.flush()

        stop_thread = False

        # Thread for reading from serial
        def read_loop():
            while not stop_thread:
                try:
                    if ser.in_waiting:
                        text = ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
                        sys.stdout.write(text)
                        sys.stdout.flush()
                except Exception:
                    break
                time.sleep(0.01)

        t = threading.Thread(target=read_loop)
        t.daemon = True
        t.start()

        # Main thread for writing to serial
        while True:
            try:
                line = input()
                ser.write((line + "\n").encode('utf-8'))
            except KeyboardInterrupt:
                break

        stop_thread = True
        t.join(timeout=1)
        print("\n--- MONITOR SERIAL DIHENTIKAN ---")
    except Exception as e:
        print(f"[ERROR] Terjadi kesalahan: {e}")

def main():
    port = select_port()
    print(f"\nMenghubungkan ke Arduino pada {port}...")
    try:
        # Use a constant short timeout (0.1s) throughout to avoid toggling serial state
        ser = serial.Serial(port, BAUDRATE, timeout=0.1)
        # Arduino Uno resets upon first serial connection. Wait for bootloader.
        print("Menunggu Arduino selesai reset (Booting)...")
        time.sleep(2.5)
        safe_flush_input(ser)
        print("Koneksi berhasil dibuka!")
    except Exception as e:
        print(f"[ERROR] Tidak dapat membuka port serial {port}: {e}")
        print("Silakan pastikan kabel USB terhubung dan port serial tidak sedang digunakan oleh program lain (seperti VS Code monitor).")
        sys.exit(1)

    try:
        while True:
            print("\n==================================================")
            print("          PENGELOLA DATABASE & SEED SERIAL        ")
            print("==================================================")
            print("  [1] Muat Seed Database (dari folder lib/)")
            print("  [2] Simpan Database ke Berkas (di folder test/)")
            print("  [3] Jalankan Serial Monitor Interaktif")
            print("  [4] Keluar")
            print("==================================================")
            
            choice = input("Pilih menu (1-4): ").strip()
            if choice == '1':
                menu_seed(ser)
            elif choice == '2':
                menu_dump(ser)
            elif choice == '3':
                monitor_serial(ser)
            elif choice == '4':
                print("Menutup koneksi serial...")
                ser.close()
                print("Sampai jumpa!")
                break
            else:
                print("[ERROR] Pilihan menu tidak valid.")
    except KeyboardInterrupt:
        print("\nMenutup koneksi serial...")
        ser.close()
        print("Sampai jumpa!")

if __name__ == "__main__":
    main()

# ==============================================================================
# Makefile for Sistem Inventarisasi Laboratorium Embedded Systems (EL2008)
# Team 1 - Tubes PMP 2026
# Optimized for Arduino Uno R3 upload and Serial Monitor using PlatformIO CLI
# ==============================================================================

# PlatformIO CLI command detection
ifeq ($(OS),Windows_NT)
    # Check if pio is in system PATH on Windows
    PIO_IN_PATH := $(shell where pio 2>nul)
    ifneq ($(PIO_IN_PATH),)
        PIO = pio
    else
        PIO = "$(USERPROFILE)\.platformio\penv\Scripts\pio.exe"
    endif
else
    # Check if pio is in system PATH on Unix
    PIO_IN_PATH := $(shell which pio 2>/dev/null)
    ifneq ($(PIO_IN_PATH),)
        PIO = pio
    else
        PIO = ~/.platformio/penv/bin/pio
    endif
endif

# Default Target: Build firmware
all: build

# Build the firmware
build:
	@echo "Building firmware using PlatformIO..."
	$(PIO) run

# Upload the firmware to Arduino Uno (COM23 is defined in platformio.ini)
upload:
	@echo "Uploading firmware to Arduino Uno..."
	$(PIO) run -t upload

# Open Serial Monitor
monitor:
	@echo "Opening Serial Monitor..."
	$(PIO) device monitor

# Upload and immediately open Serial Monitor
run:
	@echo "Uploading firmware and starting Serial Monitor..."
	$(PIO) run -t upload
	$(PIO) device monitor

# Clean build files
clean:
	@echo "Cleaning build artifacts..."
	$(PIO) run -t clean

# Run Database and Seed Manager CLI
manage:
	python manage_serial.py

.PHONY: all build upload monitor run clean manage



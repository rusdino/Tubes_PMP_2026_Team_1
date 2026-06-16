# ==============================================================================
# Makefile for Sistem Inventarisasi Laboratorium Embedded Systems (EL2008)
# Team 1 - Tubes PMP 2026
# ==============================================================================

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2

# Target Executable Name
TARGET = inventaris

# Source and Object Files
SRCS = main.c add.c delete.c find_and_update.c show.c summary.c
OBJS = $(SRCS:.c=.o)
HEADERS = add.h dataset.h delete.h find_and_update.h show.h summary.h

# ------------------------------------------------------------------------------
# Platform Detection and Shell Compatibility
# ------------------------------------------------------------------------------
# Detect if we are on Windows (Windows_NT is set by default on Windows OS)
ifeq ($(OS),Windows_NT)
    EXE = $(TARGET).exe
    # Use Windows cmd.exe built-in "del" command to ensure clean command works
    # regardless of the shell Make is running under (CMD, PowerShell, or sh)
    RM = cmd.exe /C del /F /Q
    # Replace forward slashes with backward slashes for cmd.exe compatibility
    CLEAN_TARGETS = $(subst /,$(strip \),$(OBJS)) $(EXE)
    
    # Check if the active shell in GNU Make is sh/bash
    ifeq ($(findstring sh,$(SHELL)),sh)
        RUN_CMD = ./$(EXE)
    else
        RUN_CMD = $(EXE)
    endif
else
    # Linux, macOS, and other Unix-like systems
    EXE = $(TARGET)
    RM = rm -f
    CLEAN_TARGETS = $(OBJS) $(EXE)
    RUN_CMD = ./$(EXE)
endif

# ------------------------------------------------------------------------------
# Build Rules
# ------------------------------------------------------------------------------

# Default Target (Build the executable)
all: $(EXE)

# Link Object Files to Create Executable
$(EXE): $(OBJS)
	@echo Linking object files into $(EXE)...
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo Build successful!

# Compile Source Files to Object Files
# Recompile if any header file changes to maintain code integrity
%.o: %.c $(HEADERS)
	@echo Compiling $<...
	$(CC) $(CFLAGS) -c $< -o $@

# Run the Compiled Program
run: $(EXE)
	@echo Running $(EXE)...
	@$(RUN_CMD)

# Clean Up Build Artifacts (Object files and executable)
clean:
	@echo Cleaning up build artifacts...
	-$(RM) $(CLEAN_TARGETS)
	@echo Clean done!

.PHONY: all run clean

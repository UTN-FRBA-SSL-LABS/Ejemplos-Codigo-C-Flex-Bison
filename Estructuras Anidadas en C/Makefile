CC=gcc
CFLAGS=-std=c89 -Wall -Wextra -pedantic

TARGET=estructuras_anidadas

# Detectar Windows
ifeq ($(OS),Windows_NT)
    TARGET_EXT=.exe
    RM=del /Q
    MKDIR=mkdir
else
    TARGET_EXT=
    RM=rm -f
    MKDIR=mkdir -p
endif

BIN_DIR=bin
TARGET_PATH=$(BIN_DIR)/$(TARGET)$(TARGET_EXT)

all: $(TARGET_PATH)

$(TARGET_PATH): main.c
	$(MKDIR) $(BIN_DIR)
	$(CC) $(CFLAGS) main.c -o $(TARGET_PATH)

run: all
	$(TARGET_PATH)

clean:
	$(RM) $(TARGET_PATH)
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = src/main.c
TARGET = bin/programa

# Regla principal
all: $(TARGET)

# Asegura que exista la carpeta bin antes de compilar
$(TARGET): $(SRC)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
	rmdir bin
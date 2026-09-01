# Makefile — ejemplos de declaraciones y definiciones en C
#
# Uso:
#   make          → compila todo
#   make run      → compila y ejecuta
#   make clean    → elimina los archivos generados

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -pedantic
TARGET  = ejemplo_declaraciones_definiciones
SRCS    = main.c contadores.c datos.c variadico.c

$(TARGET): $(SRCS) globals.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

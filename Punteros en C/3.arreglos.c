#include <stdio.h>
#include <stdlib.h>

#define CANTIDAD_ELEMENTOS 5

void asignar_valores_indice(int *arr, int n);
void imprimir_valores_indice(int *arr, int n);
void asignar_valores_aritmeticamente(int *arr, int n);
void imprimir_valores_aritmeticamente(const int *arr, int n);

int arreglos() {
    // Reservar memoria dinámica
    int *arr = malloc(CANTIDAD_ELEMENTOS * sizeof(int));
    if (arr == NULL) {
        printf("Error al reservar memoria.\n");
        return EXIT_FAILURE;
    }

    // Ejemplo 1: con índice
    printf("\nEjemplo: Utilizando índice\n");
    asignar_valores_indice(arr, CANTIDAD_ELEMENTOS);
    imprimir_valores_indice(arr, CANTIDAD_ELEMENTOS);

    // Ejemplo 2: con aritmética de punteros
    printf("\nEjemplo: Utilizando aritmética de punteros\n");
    asignar_valores_aritmeticamente(arr, CANTIDAD_ELEMENTOS);
    imprimir_valores_aritmeticamente(arr, CANTIDAD_ELEMENTOS);

    // Liberar memoria
    free(arr);
    return EXIT_SUCCESS;
}

void asignar_valores_indice(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
}

void imprimir_valores_indice(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("(Índice) arr[%d] => %d\n", i, arr[i]);
    }
}

void asignar_valores_aritmeticamente(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        *(arr + i) = i + 1;
    }
}

void imprimir_valores_aritmeticamente(const int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("(Aritmética) *(arr + %d) => %d\n", i, *(arr + i));
    }
}

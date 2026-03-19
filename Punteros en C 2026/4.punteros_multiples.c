#include <stdio.h>

int punterosMultiples() {
    int valor = 99;

    int *puntero1 = &valor;
    int **puntero2 = &puntero1;
    int ***puntero3 = &puntero2;

    printf("valor        = %d, Pos: %p\n", valor, &valor);
    printf("*puntero1    = %d, valor: %p, Pos: %p\n", *puntero1, puntero1, &puntero1);
    printf("**puntero2   = %d, valor: %p, Pos: %p\n", **puntero2, puntero2, &puntero2);
    printf("***puntero3  = %d, valor: %p, Pos: %p\n", ***puntero3, puntero3, &puntero3);

    return 0;
}
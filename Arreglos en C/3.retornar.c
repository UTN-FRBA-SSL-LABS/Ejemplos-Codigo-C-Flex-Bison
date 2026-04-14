#include <stdio.h>
#include <stdlib.h>

#define CANT 10

int *obtener_arreglo();

void imprimir_arreglo(int *arreglo);

int retornar()
{
    int *arreglo;

    arreglo = obtener_arreglo();

    imprimir_arreglo(arreglo);

    return 0;
}

int *obtener_arreglo()
{
    static int arreglo[CANT];

    for (int i = 0; i < CANT; i++)
    {
        arreglo[i] = i + 1;
    }

    return arreglo;
}

void imprimir_arreglo(int *arreglo)
{
    for (int i = 0; i < CANT; i++)
    {
        printf("Elemento #%d = %d\n", i, arreglo[i]);
    }
}
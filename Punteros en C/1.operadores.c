#include <stdio.h>
#include <stdlib.h>

int operadores() {
    int variable_entera = 10;
    int  *puntero;

    // ¡PELIGRO! Puntero sin inicializar. Contiene basura.
    printf("\n(1) Dirección INICIAL almacenada en 'puntero': %p\n", puntero);
    // printf("(1) Valor de *puntero: %f\n", *puntero); // ⚠️ Puede dar error.

    // Buena práctica: inicializar punteros
    puntero = NULL;

    printf("(1) Dirección NUEVA almacenada en 'puntero': %p\n", puntero);
    // printf("(1) Valor de *puntero: %f\n", *puntero); // ⚠️ Segmentation Fault

    // Operador & → obtiene dirección de variable
    puntero = (int  *)&variable_entera;

    printf("\n(2) Dirección de 'variable_entera': %p\n", &variable_entera);
    printf("(2) Dirección NUEVA en 'puntero': %p\n", puntero);
    printf("(2) Valor apuntado por puntero: %d\n", *puntero);

    variable_entera = 20;
    printf("\n(3) Valor NUEVO apuntado por puntero: %d\n", *puntero);

    return EXIT_SUCCESS;
}

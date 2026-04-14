#include <stdio.h>      // Biblioteca del sistema
#include "operaciones.h" // Encabezado propio del proyecto

int main() {
    int val1 = 2;
    int val2 = 1;

    printf("--- Ejemplo de Modularización en C ---\n");
    
    // El compilador confía en la declaración del .h para estas llamadas
    printf("Resultado de la suma: %d\n", sumar(val1, val2));
    printf("Resultado de la resta: %d\n", restar(val1, val2));

    return 0;
}
/*
 * variadico.c
 *
 * DEFINE la función variádica sumar_variadico.
 * Declarada en globals.h como: int sumar_variadico(int cantidad, ...);
 */

#include <stdarg.h>   /* va_list, va_start, va_arg, va_end */
#include "globals.h"

/*
 * sumar_variadico — suma una cantidad arbitraria de enteros.
 *
 * Parámetros:
 *   cantidad : cuántos enteros se van a pasar a continuación.
 *   ...      : los enteros a sumar (deben ser todos int).
 *
 * Buena práctica: Se recomienda siempre documentar qué tipo se espera
 * en los argumentos variables, porque el compilador no puede verificarlo.
 *
 * Ejemplo de uso:
 *   sumar_variadico(3, 10, 20, 30);  → 60
 *   sumar_variadico(2, 5, 5);        → 10
 */
int sumar_variadico(int cantidad, ...) {
    va_list args;
    va_start(args, cantidad);   /* Inicializa la lista a partir del último arg fijo */

    int suma = 0;
    for (int i = 0; i < cantidad; i++) {
        suma += va_arg(args, int);  /* Extrae el siguiente argumento como int */
    }

    va_end(args);   /* Siempre llamar va_end antes de retornar */
    return suma;
}

/*
 * datos.c
 *
 * DEFINE los arreglos globales "dias" y "matriz".
 * También DEFINE las funciones imprimir_dias() e imprimir_matriz() que
 * fueron declaradas en globals.h.
 */

#include <stdio.h>
#include "globals.h"

/* ── DEFINICIÓN del arreglo de strings ────────────────────────────────────
 *
 * Buena práctica: Se recomienda usar const char * para literales de cadena,
 * ya que el compilador los ubica en memoria de solo lectura.
 */
const char *dias[] = {
    "Lunes",
    "Martes",
    "Miércoles",
    "Jueves",
    "Viernes"
};

/* ── DEFINICIÓN de la matriz ──────────────────────────────────────────── */
int matriz[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

/* ── Definición de las funciones declaradas en globals.h ──────────────── */

void imprimir_dias(void) {
    printf("\nDías de la semana (definidos en datos.c):\n");
    int n = sizeof(dias) / sizeof(dias[0]);
    for (int i = 0; i < n; i++) {
        printf("  dias[%d] = %s\n", i, dias[i]);
    }
}

void imprimir_matriz(void) {
    printf("\nMatriz 3x3 (definida en datos.c):\n");
    for (int i = 0; i < 3; i++) {
        printf("  ");
        for (int j = 0; j < 3; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

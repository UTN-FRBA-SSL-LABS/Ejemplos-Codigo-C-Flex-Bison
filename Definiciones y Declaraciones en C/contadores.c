/*
 * contadores.c
 *
 * DEFINE la variable global "contador" y las funciones que la manipulan.
 *
 * Aquí está la única definición de "contador" en todo el proyecto.
 * Los demás archivos que necesiten usarla deben incluir globals.h,
 * que contiene: extern int contador;
 */

#include <stdio.h>
#include "globals.h"

/* ── DEFINICIÓN de la variable global ─────────────────────────────────────
 *
 * Esta línea reserva memoria para "contador".
 * Solo debe aparecer en UN archivo .c de todo el proyecto.
 *
 * Si esta línea apareciera también en datos.c o en main.c (sin extern),
 * el linker fallaría: "multiple definition of 'contador'".
 */
int contador = 0;

/* ── Definición de las funciones declaradas en globals.h ──────────────── */

void incrementar(void) {
    contador++;
}

void resetear(void) {
    contador = 0;
}

int obtener_contador(void) {
    return contador;
}

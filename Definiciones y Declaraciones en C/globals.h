/*
 * globals.h
 *
 * Archivo de cabecera compartido por todos los módulos.
 *
 * REGLA DE ORO para .h:
 *   - Acá van las DECLARACIONES  (extern, prototipos de funciones, typedefs, structs)
 *   - Acá NO van las DEFINICIONES (nunca: int x; o int arr[] = {...}; en un .h)
 *
 * ¿Por qué? Porque el .h es incluido por múltiples .c.
 * Si se define una variable en el .h, cada .c que lo incluya tendrá
 * su propia definición -> el linker reportará "multiple definition of x".
 *
 * ERROR TÍPICO EN TPs:
 *   int dias[] = {"Lunes", "Martes"};   <-- NUNCA en un .h
 *
 * CORRECTO:
 *   extern const char *dias[];          <-- declaración en el .h
 *   ... y la definición en exactamente UN archivo .c
 */

#ifndef GLOBALS_H   /* Include guard: evita inclusión múltiple del mismo .h */
#define GLOBALS_H

/* ── Declaraciones de variables globales ───────────────────────────────────
 *
 * "extern" le dice al compilador: "esta variable existe, pero está definida
 * en otro archivo .c". No reserva memoria.
 */

extern int contador;              /* Definida en contadores.c */
extern const char *dias[];        /* Definida en datos.c      */
extern int matriz[3][3];          /* Definida en datos.c      */

/* ── Prototipos de funciones ───────────────────────────────────────────────
 *
 * Los prototipos son declaraciones puras: no reservan memoria,
 * solo informan al compilador la firma de cada función.
 */

void incrementar(void);
void resetear(void);
int  obtener_contador(void);

void imprimir_dias(void);
void imprimir_matriz(void);

int  sumar_variadico(int cantidad, ...);

#endif /* GLOBALS_H */

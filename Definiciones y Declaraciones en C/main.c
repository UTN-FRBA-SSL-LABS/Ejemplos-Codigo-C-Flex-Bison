/*
 * main.c
 *
 * Ejemplos de declaraciones, definiciones e inicialización en C.
 */

#include <stdio.h>
#include <stdlib.h>
#include "globals.h"   /* Incluimos el .h compartido: trae las declaraciones extern */

/* ════════════════════════════════════════════════════════════════════════════
 * 1. DECLARACIÓN vs DEFINICIÓN — variables locales
 * ════════════════════════════════════════════════════════════════════════════ */

void ejemplo_basico(void) {
    printf("\n── 1. Declaración, Definición e Inicialización ──\n");

    /* Definición sin inicialización.
     * Reserva memoria, pero el valor es INDETERMINADO (basura).*/
    int a;
    /* printf("%d\n", a);  <-- NO hacer: comportamiento indefinido */

    /* Buena práctica: Se recomienda siempre inicializar variables locales
     * al momento de definirlas para evitar comportamiento indeterminado. */
    int b = 0;

    /* Definición + inicialización en una sola sentencia */
    int c = 42;

    /* Asignación posterior (no es "inicialización" en sentido estricto) */
    a = 10;

    printf("a (asignado luego):       %d\n", a);
    printf("b (inicializado a 0):     %d\n", b);
    printf("c (inicializado a 42):    %d\n", c);
}

/* ════════════════════════════════════════════════════════════════════════════
 * 2. VARIABLES GLOBALES Y ESTÁTICAS — se inicializan a 0 por defecto
 * ════════════════════════════════════════════════════════════════════════════ */

int global_sin_init;        /* Global: se inicializa a 0 automáticamente */
int global_con_init = 99;   /* Global: inicializada explícitamente        */

void ejemplo_globales(void) {
    printf("\n── 2. Variables globales y estáticas ──\n");

    /* Variable estática local: vive durante toda la ejecución del programa,
     * se inicializa a 0 por defecto y conserva su valor entre llamadas. */
    static int llamadas = 0;
    llamadas++;

    printf("global_sin_init:  %d  (automáticamente 0)\n", global_sin_init);
    printf("global_con_init:  %d\n", global_con_init);
    printf("static llamadas:  %d  (persiste entre llamadas)\n", llamadas);
}

/* ════════════════════════════════════════════════════════════════════════════
 * 3. PUNTERO A ARREGLO vs PUNTERO AL PRIMER ELEMENTO
 * ════════════════════════════════════════════════════════════════════════════ */

void ejemplo_puntero_arreglo(void) {
    printf("\n── 3. Puntero a arreglo vs puntero al elemento ──\n");

    int arr[5] = {10, 20, 30, 40, 50};

    int  *p1   = arr;       /* Apunta al primer elemento: tipo int *       */
    int (*p2)[5] = &arr;    /* Apunta al arreglo completo: tipo int (*)[5] */

    printf("*p1        = %d\n", *p1);         /* 10 */
    printf("*(p1 + 1)  = %d\n", *(p1 + 1));  /* 20 — avanza sizeof(int)    */
    printf("(*p2)[0]   = %d\n", (*p2)[0]);   /* 10 */
    printf("(*p2)[2]   = %d\n", (*p2)[2]);   /* 30 */

    /* La diferencia clave: cuánto avanza cada puntero al hacer +1 */
    printf("\nsizeof(int)      = %zu bytes  → p1+1 avanza esto\n", sizeof(int));
    printf("sizeof(int[5])   = %zu bytes  → p2+1 avanza esto\n", sizeof(int[5]));
}

/* ════════════════════════════════════════════════════════════════════════════
 * 4. ARREGLO DE PUNTEROS A CHAR — strings
 * ════════════════════════════════════════════════════════════════════════════ */

void ejemplo_arreglo_strings(void) {
    printf("\n── 4. Arreglo de punteros a char ──\n");

    /* Buena práctica: Se recomienda usar const char * para literales de cadena,
     * ya que residen en memoria de solo lectura. Intentar modificarlos
     * produce comportamiento indefinido. */
    const char *colores[] = {"Rojo", "Verde", "Azul"};
    int n = sizeof(colores) / sizeof(colores[0]);  /* cantidad de elementos */

    for (int i = 0; i < n; i++) {
        printf("colores[%d] = %s\n", i, colores[i]);
    }

    /* INCORRECTO — no hacer esto:
     *
     *   char *mal = "Hola";
     *   mal[0] = 'h';   <-- comportamiento indefinido: modifica memoria de solo lectura
     */
}

/* ════════════════════════════════════════════════════════════════════════════
 * 5. USO DE VARIABLES EXTERNAS (definidas en otros .c)
 * ════════════════════════════════════════════════════════════════════════════ */

void ejemplo_extern(void) {
    printf("\n── 5. Variables externas (extern) ──\n");

    /* "contador" está DECLARADO en globals.h (extern int contador)
     * y DEFINIDO en contadores.c (int contador = 0).
     * Acá solo lo usamos; el linker conecta los archivos. */

    printf("Contador inicial: %d\n", obtener_contador());
    incrementar();
    incrementar();
    incrementar();
    printf("Contador tras 3 incrementos: %d\n", obtener_contador());
    resetear();
    printf("Contador tras resetear: %d\n", obtener_contador());

    /* El arreglo de días también está definido en datos.c */
    imprimir_dias();

    /* La matriz también */
    imprimir_matriz();
}

/* ════════════════════════════════════════════════════════════════════════════
 * 6. FUNCIÓN VARIÁDICA
 * ════════════════════════════════════════════════════════════════════════════ */

void ejemplo_variadico(void) {
    printf("\n── 6. Función variádica ──\n");

    /* sumar_variadico está definida en variadico.c */
    int r1 = sumar_variadico(3, 10, 20, 30);
    int r2 = sumar_variadico(5, 1, 2, 3, 4, 5);

    printf("sumar(3, 10, 20, 30)     = %d\n", r1);   /* 60  */
    printf("sumar(5, 1, 2, 3, 4, 5) = %d\n", r2);   /* 15  */
}

/* ════════════════════════════════════════════════════════════════════════════
 * main
 * ════════════════════════════════════════════════════════════════════════════ */

static void mostrar_menu(void) {
    printf("\n=== Menu de ejemplos ===\n");
    printf("1. ejemplo basico\n");
    printf("2. ejemplo globales\n");
    printf("3. ejemplo puntero arreglo\n");
    printf("4. ejemplo arreglo strings\n");
    printf("5. ejemplo extern\n");
    printf("6. ejemplo variadico\n");
    printf("0. salir\n");
    printf("Elegir una opcion: ");
}

static int leer_opcion(void) {
    char buffer[32];
    char *fin = NULL;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    long opcion = strtol(buffer, &fin, 10);
    if (fin == buffer) {
        return -1;
    }

    while (*fin == ' ' || *fin == '\t' || *fin == '\n') {
        fin++;
    }

    if (*fin != '\0') {
        return -1;
    }

    return (int)opcion;
}

int main(void) {
    int opcion;

    do {
        mostrar_menu();
        opcion = leer_opcion();

        switch (opcion) {
            case 1:
                ejemplo_basico();
                break;
            case 2:
                ejemplo_globales();
                break;
            case 3:
                ejemplo_puntero_arreglo();
                break;
            case 4:
                ejemplo_arreglo_strings();
                break;
            case 5:
                ejemplo_extern();
                break;
            case 6:
                ejemplo_variadico();
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}

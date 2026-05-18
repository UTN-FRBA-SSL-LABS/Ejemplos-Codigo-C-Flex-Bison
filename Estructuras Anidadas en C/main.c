#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* COLORES */
#define RESET   "\x1b[0m"
#define AZUL    "\x1b[34m"
#define CYAN    "\x1b[36m"
#define VERDE   "\x1b[32m"
#define AMARILLO "\x1b[33m"
#define BLANCO  "\x1b[37m"
#define BOLD    "\x1b[1m"

/* LIMPIAR PANTALLA */
void limpiarPantalla() {
    printf("\x1b[2J\x1b[H");
}

/* HEADER PRINCIPAL */
void mostrarHeader();

struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Persona {
    char *nombre;
    int edad;
    struct Fecha nacimiento;
    int *notas;
    size_t cant_notas;
};

struct PersonaSimple {
    char nombre[50];
    int edad;
    struct Fecha nacimiento;
};

static void pause_enter(void)
{
    printf("\nPresione ENTER para volver al menu...");
    fflush(stdout);
    getchar();
}

static struct Persona *crear_persona(const char *nombre, int edad, struct Fecha nac)
{
    struct Persona *p;

    p = (struct Persona *) malloc(sizeof *p);
    if (!p) {
        return NULL;
    }

    p->nombre = (char *) malloc(strlen(nombre) + 1);
    if (!p->nombre) {
        free(p);
        return NULL;
    }

    strcpy(p->nombre, nombre);
    p->edad = edad;
    p->nacimiento = nac;
    p->notas = NULL;
    p->cant_notas = 0;
    return p;
}

static int agregar_nota(struct Persona *p, int nota)
{
    int *tmp;
    size_t nuevo_len;

    if (!p) {
        return 0;
    }

    nuevo_len = p->cant_notas + 1;
    tmp = (int *) realloc(p->notas, nuevo_len * sizeof *p->notas);
    if (!tmp) {
        return 0;
    }

    p->notas = tmp;
    p->notas[p->cant_notas] = nota;
    p->cant_notas = nuevo_len;
    return 1;
}

static void liberar_persona(struct Persona *p)
{
    if (!p) {
        return;
    }

    free(p->nombre);
    free(p->notas);
    free(p);
}

static void ejemplo_estructuras(void)
{
    struct Fecha f;
    struct PersonaSimple p;

    f.dia = 15;
    f.mes = 6;
    f.anio = 1998;

    strcpy(p.nombre, "Ana");
    p.edad = 25;
    p.nacimiento = f;

    printf("===== ESTRUCTURAS ANIDADAS =====\n");
    printf("Nombre: %s\n", p.nombre);
    printf("Edad: %d\n", p.edad);
    printf("Nacimiento: %d/%d/%d\n", p.nacimiento.dia, p.nacimiento.mes, p.nacimiento.anio);
    printf("Acceso anidado con '.': p.nacimiento.dia\n");
}

static void ejemplo_scope(void)
{
    static int contador = 0;
    int local;

    local = 5;
    contador++;
    local++;

    printf("===== ALCANCE Y STATIC =====\n");
    printf("Variable local: %d\n", local);
    printf("Variable static: %d\n", contador);
    printf("La local existe solo en esta llamada; la static conserva su valor entre llamadas.\n");
}

static void ejemplo_dinamica(void)
{
    struct Fecha f;
    struct Persona *ana;

    f.dia = 15;
    f.mes = 6;
    f.anio = 1998;

    ana = crear_persona("Ana", 25, f);
    if (!ana) {
        printf("No se pudo reservar memoria para la persona.\n");
        return;
    }

    if (!agregar_nota(ana, 9) || !agregar_nota(ana, 7)) {
        printf("No se pudo ampliar el arreglo de notas.\n");
        liberar_persona(ana);
        return;
    }

    printf("===== MEMORIA DINAMICA =====\n");
    printf("Nombre: %s\n", ana->nombre);
    printf("Edad: %d\n", ana->edad);
    printf("Fecha: %d/%d/%d\n", ana->nacimiento.dia, ana->nacimiento.mes, ana->nacimiento.anio);
    printf("Notas:\n");
    printf("  -> %d\n", ana->notas[0]);
    printf("  -> %d\n", ana->notas[1]);
    printf("BUENA_PRACTICA: realloc se asigna primero a un temporal y recien despues se reemplaza el original.\n");

    liberar_persona(ana);
}

static void ejemplo_puntero_pila(void)
{
    printf("===== PUNTERO A PILA =====\n");
    printf("Un puntero puede guardar una direccion valida aunque el objeto al que apunta ya no exista.\n");
    printf("Si una funcion devuelve la direccion de una variable local, esa variable se destruye al salir de la funcion.\n");
    printf("A partir de ese momento, la direccion sigue escrita en el puntero, pero ya no referencia memoria utilizable para ese objeto.\n");
    printf("Usarlo produce comportamiento indefinido: puede parecer correcto, devolver basura o fallar.\n");
    printf("La alternativa correcta es reservar memoria dinamica y transferir la responsabilidad de liberarla.\n");
}

int main(void)
{
    int opcion;

    for (;;) {
        mostrarHeader();
        printf("\n========================================\n");
        printf("Estructuras anidadas y memoria dinamica\n");
        printf("========================================\n");
        printf("1. Estructuras anidadas\n");
        printf("2. Alcance y static\n");
        printf("3. Memoria dinamica\n");
        printf("4. Puntero a pila\n");
        printf("0. Salir\n");
        printf("Opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida.\n");
            return 1;
        }

        getchar();

        switch (opcion) {
            case 1:
                ejemplo_estructuras();
                pause_enter();
                break;
            case 2:
                ejemplo_scope();
                pause_enter();
                break;
            case 3:
                ejemplo_dinamica();
                pause_enter();
                break;
            case 4:
                ejemplo_puntero_pila();
                pause_enter();
                break;
            case 0:
                printf("Saliendo...\n");
                return 0;
            default:
                printf("Opcion no valida.\n");
                break;
        }
    }
}

void mostrarHeader() {

    limpiarPantalla();

    printf(AZUL BOLD);
    printf("========================================================\n");
    printf("\n");

    printf("         ███████╗███████╗██╗     \n");
    printf("         ██╔════╝██╔════╝██║     \n");
    printf("         ███████╗███████╗██║     \n");
    printf("         ╚════██║╚════██║██║     \n");
    printf("         ███████║███████║███████╗\n");
    printf("         ╚══════╝╚══════╝╚══════╝\n");

    printf("\n");
    printf("========================================================\n");
    printf(RESET);

    return;
}
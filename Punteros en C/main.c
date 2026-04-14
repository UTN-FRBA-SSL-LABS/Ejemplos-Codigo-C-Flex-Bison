#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>

void operadores();
void valorYReferencia();
void arreglos();
void punterosMultiples();

void limpiar_pantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int opcion;
    char repetir;

    do {
        limpiar_pantalla();

        printf("=== MENÚ DE PRUEBAS - PUNTEROS EN C ===\n");
        printf("1. Operadores básicos\n");
        printf("2. Pasaje por Valor-Referencia\n");
        printf("3. Uso de arreglos\n");
        printf("3. Uso de punteros múltiples\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        limpiar_pantalla();

        switch (opcion) {
            case 1: operadores(); break;
            case 2: valorYReferencia(); break;
            case 3: arreglos(); break;
            case 4: punterosMultiples(); break;
            case 0: printf("Saliendo...\n"); return 0;
            default: printf("Opción inválida\n"); break;
        }

        printf("\n¿Desea ejecutar otra opción? (s/n): ");
        scanf(" %c", &repetir);

    } while (repetir == 's' || repetir == 'S');

    printf("¡Gracias por usar el programa!\n");
    return 0;
}

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>

void recorrer();
void por_parametro();
void retornar();
void coordenadas();
void por_parametro_2();
void por_parametro_bidimensional();
void puntajes();
void tamanio_del_arreglo();

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

        printf("=== MENÚ DE PRUEBAS - ARREGLOS EN C ===\n");
        printf("1. Recorrer arreglo\n");
        printf("2. Pasar arreglo por parámetro\n");
        printf("3. Retornar arreglo\n");
        printf("4. Coordenadas (arreglo bidimensional)\n");
        printf("5. Pasar arreglo (versión 2)\n");
        printf("6. Pasar arreglo bidimensional\n");
        printf("7. Puntajes\n");
        printf("8. Tamaño del arreglo\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        limpiar_pantalla();

        switch (opcion) {
            case 1: recorrer(); break;
            case 2: por_parametro(); break;
            case 3: retornar(); break;
            case 4: coordenadas(); break;
            case 5: por_parametro_2(); break;
            case 6: por_parametro_bidimensional(); break;
            case 7: puntajes(); break;
            case 8: tamanio_del_arreglo(); break;
            case 0: printf("Saliendo...\n"); return 0;
            default: printf("Opción inválida\n"); break;
        }

        printf("\n¿Desea ejecutar otra opción? (s/n): ");
        scanf(" %c", &repetir);

    } while (repetir == 's' || repetir == 'S');

    printf("¡Gracias por usar el programa!\n");
    return 0;
}

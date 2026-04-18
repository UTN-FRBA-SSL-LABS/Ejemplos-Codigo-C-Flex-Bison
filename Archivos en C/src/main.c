#include <stdio.h>

int main() {
    // Declaramos un puntero a archivo y lo abrimos en modo binario para lectura y escritura
    FILE *archivo = fopen("./datos.bin", "wb+");
    if (archivo == NULL) return 1;

    // Escribimos 3 números enteros (1, 2, 3) en el archivo
    for(int i = 0; i < 3; i++) {
        int numero = i + 1;
        fwrite(&numero, sizeof(int), 1, archivo);
    }

    // Acceso Aleatorio: Vamos al segundo entero (índice 1)
    // El desplazamiento es 1 * sizeof(int)
    fseek(archivo, sizeof(int), SEEK_SET);

    // Modificamos el valor en esa posición (reemplazamos el 10 por el 99)
    int nuevoNumero = 0;
    fwrite(&nuevoNumero, sizeof(int), 1, archivo);

    // Leemos todo el archivo
    fseek(archivo, 0, SEEK_SET); // Volvemos al inicio del archivo
    int leido;
    printf("Contenido del archivo:\n");
    // Mientras podamos leer un entero, lo imprimimos
    while(fread(&leido, sizeof(int), 1, archivo) == 1) {
        printf("%d\n", leido);
    }

    fclose(archivo);
    return 0;
}
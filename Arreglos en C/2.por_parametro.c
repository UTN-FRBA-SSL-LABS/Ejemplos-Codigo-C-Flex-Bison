#include <stdio.h>
#include <stdlib.h>

#define LONG 9

double promedio(int *elementos, int cantidad_elementos);

int por_parametro()
{
    int calificaciones[LONG] = {1, 2, 3, 4, 5, 6, 7, 8, 1};

    double promedio_calificaciones = promedio(calificaciones, LONG);

    printf("El promedio de las calificaciones es: %f\n", promedio_calificaciones);

    return EXIT_SUCCESS;
}

double promedio(int *elementos, int cantidad_elementos)
{
    double sumatoria_elementos = 0;
   
    for (int i = 0; i < cantidad_elementos; i++)
    {
        sumatoria_elementos += elementos[i];
    }

    return sumatoria_elementos / cantidad_elementos;
}
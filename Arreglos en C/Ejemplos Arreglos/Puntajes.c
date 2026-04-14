#include <stdio.h>

int puntajes()
{
    int puntajes[3] = {-5, 0 ,3};
    
    
    int puntaje_martin = puntajes[0];
    int puntaje_santi = puntajes[1];
    int puntaje_juan = puntajes[2];

    int puntaje_nacho = puntajes[3];
    
    printf("El puntaje de martin es: %d\n",puntaje_martin);
    
    printf("El puntaje de santi es: %d\n",puntaje_santi);
    
    printf("El puntaje de juan es: %d\n",puntaje_juan);
    
    printf("El puntaje de nacho es: %d\n",puntaje_nacho);
    
    printf("Tamaño de un entero en este sistema: %zu bytes\n", sizeof(int));
    return 0;
}



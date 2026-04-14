#include <stdio.h>

int tamanio_del_arreglo()
{
    
    int tamanioDelArreglo;
    
    printf("Cuantos valores tendra el arreglo?: ");
    
    scanf("%d",&tamanioDelArreglo);
    
    int primerArray[tamanioDelArreglo];
    
    for (int i = 0; i < tamanioDelArreglo ; i++){
        printf("Inserte el valor %d del arreglo: ",i);
        scanf("%d",&primerArray[i]);
    }
    
    for(int j = 0; j < tamanioDelArreglo ; j++){
        printf("El valor del arreglo en la posicion %d es: %d\n",j, primerArray[j]);
    }
    
    return 0;
}



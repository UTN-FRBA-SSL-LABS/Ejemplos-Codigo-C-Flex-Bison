#include <stdio.h>

int coordenadas()
{
      int coordenadas[2][2] = {
        -5.0, 2.01,
        15.3, 24.9
    };

    double medrano_x = coordenadas[0][0];
    double medrano_y = coordenadas[0][1];
    double campus_x = coordenadas[1][0];
    double campus_y = coordenadas[1][1];

    double ypf_x = coordenadas[2][0];
    double ypf_y = coordenadas[1][2];
    
    printf("Coordenada ypf_x: %f\n", ypf_x);
    printf("Coordenada ypf_y: %f\n",ypf_y);

    return 0;
}



#include <stdio.h>
#include <stdlib.h>

#define FIL 5
#define COL 5

int recorrer()
{
    int tabla_multiplicar[FIL][COL];

    // Inicializar para que tenga las tablas de multiplicar
    for (int i = 0; i < FIL; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            tabla_multiplicar[i][j] = i * j;
        }
    }

    // Imprimir por pantalla los valores
    for (int i = 0; i < FIL; i++)
    {
        printf("\nTabla del %d\n", i);

        for (int j = 0; j < COL; j++)
        {
            printf("%d * %d = %d\n", i, j, tabla_multiplicar[i][j]);
        }
    }

    return EXIT_SUCCESS;
}
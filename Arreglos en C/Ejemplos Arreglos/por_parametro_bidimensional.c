/*Este ejemplo pide al usuario ingresar 9 numeros y los almacena en el arreglo de dos
dimensiones para despues mostrarlo por pantalla como quedo ordenado. Para eso usa
una funcion que recibe por parametro la matriz de dos dimensiones y la cantidad de filas*/

#include <stdio.h>
 
void ImprimirMatriz(int m[][3], int filas);

int por_parametro_bidimensional()
{
 int posicionFila = 0, posicionColumna = 0;
 int matriz[3][3];
 
 printf("Introduzca los valores para la matriz\n");
 for (posicionFila=0; posicionFila<3; ++posicionFila)
     {
      for (posicionColumna=0; posicionColumna<3; ++posicionColumna)
          {
           printf("Valor para el elemento [%d][%d]: ", posicionFila, posicionColumna);
           scanf("%d",&matriz[posicionFila][posicionColumna]);
          }
      printf("\n");
     }
 
 printf("Matriz\n");
 ImprimirMatriz(matriz, 3);
 
 system("pause");

 return 0;
}

void ImprimirMatriz(int m[][3], int filas)
{
 int i=0,j=0;
 
 for (i=0; i<filas; ++i)
     {
      for (j=0; j<3; ++j)
          {
           printf("%d ",m[i][j]);
          }
      printf("\n");
     }
}
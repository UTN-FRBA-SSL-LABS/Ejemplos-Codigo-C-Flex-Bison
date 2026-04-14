/*Este programa le pide al usuario ingresar 10 numeros de tipo int y los guarda en un
arreglo. Despues se le pide al usuario que ingrese un numero para buscar el valor
que esta en esa posicion del arreglo.*/

#include <stdio.h>

int BuscaNumero(int arreglo[], int tamanio, int busqueda);
void MuestraArreglo(int arreglo[], int tamanio);

int por_parametro_2()
{
 int x=0, numero=0, posicion=0;
 int ar_numeros[10] = {0};
 
 printf("Introduzca los 10 numeros enteros que se almacenaran en el arreglo\n");

for (x=0; x<10; ++x)
    {
      printf("Valor para el elemento [%d]: ", x);
      scanf("%d",&ar_numeros[x]);
    }
 printf("\n");
 
 printf("Introduzca el numero que desea buscar en el arreglo\n");
 scanf("%d",&numero);
 printf("\n");
 MuestraArreglo(ar_numeros,10);
 
 posicion=BuscaNumero(ar_numeros,10,numero);
 if (posicion != -1)
     printf("El numero %d esta en la posicion %d del arreglo\n",numero, posicion);
 else
     printf("El numero %d no esta en el arreglo\n",numero);
 
 return 0;
}


/*Esta funcion recibe el arreglo con los 10 valores, el numero de elementos que tiene
el arreglo y la posicion del arreglo que esta buscando. Esta funcion devuelve -1 si
el numero no esta en el arreglo*/ 
int BuscaNumero(int valores[], int tamanio, int busca)
{
int i=0, posicion=-1;
 
do
  {
   if (valores[i]==busca)
       posicion=i;
   else
       ++i;
  }
while(i<tamanio && posicion<0);
 
return posicion;
}
 
void MuestraArreglo(int valores[], int tamanio)
{
 int i=0;
 
 for (i=0; i<tamanio; ++i)
      printf("%d\t",valores[i]);
 printf("\n");
}
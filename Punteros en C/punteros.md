### UTN - FRBA - Sintaxis y Semántica de los Lenguajes - 2025

## 📌 **Punteros en C**

---

### 🔍 ¿Qué se va a realizar en clase?

- Declarar un puntero
- Inicializar un puntero
- Asignar un valor a un puntero
- Acceder a un valor de un puntero
- Pasar por parámetro de una función un puntero
- Aritmética de punteros

---

## 🧠 **Definición formal de un puntero**

Un puntero es una **variable especial** cuyo valor es la **dirección de memoria** de otra variable. Es decir, apunta a una ubicación específica en memoria, donde se encuentra el valor de otra variable.

---

## 📝 **Declarar un puntero**

Para declarar un puntero en C, se debe indicar:

1. El tipo de dato al que apunta.
2. El nivel de indirección (cantidad de `*`).
3. El nombre del puntero.

```c
tipo *nombre_puntero;
```

### ✅ Ejemplos:

```c
int *punteroEntero;
char *punteroChar;
float *punteroFloat;
```

---

### 🔎 **Tipo de un puntero**

El tipo de un puntero hace referencia al **tipo de dato que contiene la dirección de memoria apuntada**.  
Internamente, todos los punteros ocupan el mismo espacio en memoria (una dirección, generalmente 4 u 8 bytes según arquitectura), pero el compilador usa el tipo para interpretar correctamente el contenido.

---

## 🧪 **Inicializar y usar punteros**

```c
int x = 10;
int *puntero = &x;

printf("Valor de x: %d\n", x); 
printf("Dirección de x: %p\n", &x);  
printf("Valor de puntero: %p\n", puntero);
printf("Valor apuntado: %d\n", *puntero);
```

💡 El operador `&` obtiene la dirección de una variable.  
💡 El operador `*` accede al valor contenido en la dirección.

---

## 🔁 **Pasar punteros por parámetro**

Cuando se pasan variables a funciones, se hace por **valor**. Para poder modificar el valor original, se debe pasar un **puntero**.

```c
void duplicar(int *num) {
    *num *= 2;
}

int main() {
    int valor = 5;
    duplicar(&valor);
    printf("%d\n", valor);
}
```

---

## ➕➖ **Aritmética de punteros**

Un puntero contiene una dirección, y se pueden realizar operaciones aritméticas con ella:

Operadores válidos: `++`, `--`, `+`, `-`

```c
int *punteroEntero = (int *)1000;
char *punteroChar = (char *)2000;

punteroEntero++;
punteroChar--;
```

⚠️ Las operaciones se ajustan al tamaño del tipo apuntado. No suman 1 byte, sino 1 * sizeof(tipo).

---

## 🔄 **Indirección múltiple: punteros a punteros**

### 📍 Doble puntero (`**`)

```c
int x = 5;
int *p = &x;
int **pp = &p;

printf("%d\n", x);
printf("%d\n", *p);
printf("%d\n", **pp);
```

### 🧭 ¿Para qué sirve?

- Permite **modificar un puntero dentro de una función**:
```c
void asignar(int **pp) {
    static int x = 42;
    *pp = &x;
}
```

- Es la base de estructuras más complejas como **arrays de punteros**, **listas enlazadas**, **matrices dinámicas**, etc.

# 2. Punteros a Punteros

## Definición

Un puntero a puntero es una variable que almacena la dirección de memoria de otro puntero.

Es decir:

```text
Variable <- Puntero <- Puntero a Puntero
```

---

## Declaración

```c
int numero = 10;

int *ptr = &numero;

int **ptr2 = &ptr;
```

---

## Explicación

| Variable | Contiene |
|---|---|
| `numero` | valor entero |
| `ptr` | dirección de `numero` |
| `ptr2` | dirección de `ptr` |

---

## Representación gráfica

```text
numero = 10

ptr -------> numero

ptr2 ------> ptr ------> numero
```

---

# 3. Acceso a valores

## Acceso simple

```c
*ptr
```

Devuelve:

```text
10
```

---

## Acceso doble

```c
**ptr2
```

También devuelve:

```text
10
```

Porque:

- `ptr2` apunta a `ptr`
- `ptr` apunta a `numero`

---

# 4. Ejemplo completo

```c
#include <stdio.h>

int main() {

    int numero = 25;

    int *ptr = &numero;

    int **ptr2 = &ptr;

    printf("Valor de numero: %d\n", numero);

    printf("Valor usando ptr: %d\n", *ptr);

    printf("Valor usando ptr2: %d\n", **ptr2);

    return 0;
}
```

---

# 5. ¿Para qué se usan los punteros a punteros?

## Casos comunes

### 1. Modificar punteros dentro de funciones

### 2. Manejo de memoria dinámica

### 3. Matrices dinámicas

### 4. Listas enlazadas y árboles

### 5. Simulación de arreglos multidimensionales

---

# 6. Ejemplo práctico: modificar un puntero

## Problema

Queremos reservar memoria dentro de una función.

---

## Incorrecto

```c
void reservarMemoria(int *ptr) {
    ptr = malloc(sizeof(int));
}
```

No funciona correctamente porque se modifica una copia del puntero.

---

## Correcto usando puntero a puntero

```c
#include <stdio.h>
#include <stdlib.h>

void reservarMemoria(int **ptr) {

    *ptr = malloc(sizeof(int));

    **ptr = 50;
}

int main() {

    int *numero = NULL;

    reservarMemoria(&numero);

    printf("%d\n", *numero);

    free(numero);

    return 0;
}
```

---

# 7. Punteros a Funciones

## Definición

Un puntero a función es una variable que almacena la dirección de memoria de una función.

En C, las funciones también ocupan memoria.

Por lo tanto:

```text
Una función tiene dirección de memoria
```

y puede ser apuntada por un puntero.

---

# 8. Sintaxis

## Función normal

```c
int sumar(int a, int b) {
    return a + b;
}
```

---

## Puntero a función

```c
int (*ptrFuncion)(int, int);
```

---

## Explicación de la sintaxis

| Parte | Significado |
|---|---|
| `int` | tipo de retorno |
| `(*ptrFuncion)` | nombre del puntero |
| `(int, int)` | parámetros de la función |

---

# 9. Asignar una función al puntero

```c
ptrFuncion = sumar;
```

o también:

```c
ptrFuncion = &sumar;
```

Ambas formas son válidas.

---

# 10. Invocar una función mediante puntero

```c
int resultado = ptrFuncion(2, 3);
```

o:

```c
int resultado = (*ptrFuncion)(2, 3);
```

---

# 11. Ejemplo completo

```c
#include <stdio.h>

int sumar(int a, int b) {
    return a + b;
}

int main() {

    int (*operacion)(int, int);

    operacion = sumar;

    int resultado = operacion(5, 7);

    printf("Resultado: %d\n", resultado);

    return 0;
}
```

---

# 12. ¿Para qué sirven los punteros a funciones?

## Aplicaciones reales

### 1. Callbacks

Permiten enviar funciones como parámetros.

---

### 2. Menús dinámicos

---

### 3. Programación modular

---

### 4. Sistemas de eventos

---

### 5. Bibliotecas estándar

Por ejemplo:

```c
qsort()
```

usa punteros a funciones.

---

# 13. Ejemplo de callback

```c
#include <stdio.h>

void ejecutar(void (*funcion)()) {
    funcion();
}

void saludar() {
    printf("Hola!\n");
}

int main() {

    ejecutar(saludar);

    return 0;
}
```

---

# 14. Comparación conceptual

| Concepto | Qué almacena |
|---|---|
| `int *p` | dirección de un entero |
| `int **p` | dirección de un puntero |
| `int (*f)(int,int)` | dirección de una función |

---

# 15. Errores comunes

## 1. Confundir paréntesis

Incorrecto:

```c
int *f(int, int);
```

Esto declara una función que retorna puntero.

---

Correcto:

```c
int (*f)(int, int);
```

Esto declara un puntero a función.

---

## 2. Desreferenciar incorrectamente

```c
**ptr
```

requiere que:
- `ptr` sea un puntero a puntero válido

---

## 3. Acceder a memoria no reservada

Siempre validar:

```c
if(ptr != NULL)
```

---

# 16. Conclusión

Los punteros a punteros y punteros a funciones son herramientas fundamentales en C.

Los punteros a punteros permiten:
- manipular memoria dinámicamente
- modificar punteros dentro de funciones
- construir estructuras complejas

Los punteros a funciones permiten:
- programación flexible
- callbacks
- modularidad
- comportamiento dinámico

Comprender estos conceptos es esencial para:
- programación de sistemas
- sistemas operativos
- compiladores
- desarrollo embebido
- y programación avanzada en C.

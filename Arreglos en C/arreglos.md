
### UTN - FRBA - Sintaxis y Semántica de los Lenguajes - 2025

## **Arreglos en C**

---

### Contenido
- [¿Qué se va a realizar en clase?](#qué-se-va-a-realizar-en-clase)
- [Definición formal de un arreglo](#definición-formal-de-un-arreglo)
- [Declarar un arreglo](#declarar-un-arreglo)
- [Inicializar un arreglo](#inicializar-un-arreglo)
- [Acceder a un valor de un arreglo](#acceder-a-un-valor-de-un-arreglo)
- [Recorrer con bucle un arreglo](#recorrer-con-bucle-un-arreglo)
- [Pasar por parámetro de una función un arreglo](#pasar-por-parámetro-de-una-función-un-arreglo)
- [Retornar un arreglo por una función](#retornar-un-arreglo-por-una-función)
- [Errores comunes con arreglos](#errores-comunes-con-arreglos)

---

### ¿Qué se va a realizar en clase?

- Declarar un arreglo
- Inicializar un arreglo
- Asignar un valor a un arreglo
- Acceder a un valor de un arreglo
- Recorrer con bucle un arreglo
- Pasar por parámetro de una función un arreglo
- Retornar un arreglo por una función

---

## **Definición formal de un arreglo**

Los arreglos son una estructura de datos que puede almacenar una colección secuencial de **tamaño fijo** de elementos del mismo tipo. Se utilizan para guardar múltiples valores relacionados, y pueden verse como una colección de variables del mismo tipo agrupadas en un bloque de memoria.

---

### Declarar un arreglo

Para declarar un arreglo en C, se debe especificar:

1. El tipo de los elementos
2. El nombre del arreglo
3. La cantidad de elementos (**debe ser un valor constante entero mayor que 0**)

#### Declarar un arreglo unidimensional

```c
tipo nombre_arreglo[tamanio_arreglo];
```

|     | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|-----|---|---|---|---|---|---|---|
|     | 1 | 2 | 3 | 4 | 5 | 6 | 7 |

#### Declarar un arreglo bidimensional

```c
tipo nombre_arreglo[fila][columna];
```

|     | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|-----|---|---|---|---|---|---|---|
| **0** | 4 | 3 | 4 | 5 | 6 | 7 | 3 |
| **1** | 1 | 2 | 4 | 8 | 3 | 1 | 4 |

#### Declarar un arreglo [...]-dimensional

> Por cada dimensión extra, se agrega un par de `[ ]`.

```c
tipo nombre_arreglo[d1][d2]...[dn];
```

---

### Inicializar un arreglo

#### Inicializar un arreglo unidimensional

```c
// Asignar uno por uno
int puntajes[3];
puntajes[0] = -5;
puntajes[1] = 0;
puntajes[2] = 3;

// Inicializar todo junto
int puntajes[3] = { -5, 0, 3 };

// También válido: tamaño inferido
int puntajes[] = { -5, 0, 3 };
```

#### Inicializar un arreglo bidimensional

```c
// Asignar uno por uno
double coordenadas[2][2];
coordenadas[0][0] = -5.0;
coordenadas[0][1] = 2.01;
coordenadas[1][0] = 15.3;
coordenadas[1][1] = 25.2;

// Inicializar todo junto (correcto)
double coordenadas[2][2] = {
    { -5.0, 2.01 },
    { 15.3, 25.2 }
};

// ❌ Esto NO se puede:
double coordenadas[][] = {
    { -5.0, 2.01 },
    { 15.3, 25.2 }
};
```

---

### Acceder a un valor de un arreglo

#### Unidimensional

```c
int puntajes[3] = { -5, 0, 3 };

int puntaje_martin = puntajes[0];
int puntaje_santi = puntajes[1];
int puntaje_juan = puntajes[2];

int puntaje_iniaki = puntajes[3]; // ❌ Error: índice fuera de rango
```

#### Bidimensional

```c
double coordenadas[2][2] = {
    { -5.0, 2.01 },
    { 15.3, 25.2 }
};

double medrano_x = coordenadas[0][0];
double medrano_y = coordenadas[0][1];
double campus_x = coordenadas[1][0];
double campus_y = coordenadas[1][1];

double ypf_x = coordenadas[2][0]; // ❌ Error
double ypf_y = coordenadas[1][2]; // ❌ Error
```

---

### Recorrer con bucle un arreglo

#### Unidimensional

```c
#include <stdio.h>

int main() {
    int numeros[10];

    // Inicializar
    for (int i = 0; i < 10; i++) {
        numeros[i] = i + 1;
    }

    // Mostrar
    for (int i = 0; i < 10; i++) {
        printf("Elemento #%d: %d\n", i, numeros[i]);
    }

    return 0;
}
```

#### Bidimensional

```c
#include <stdio.h>

#define FIL 5
#define COL 5

int main() {
    int tabla_multiplicar[FIL][COL];

    for (int i = 0; i < FIL; i++) {
        for (int j = 0; j < COL; j++) {
            tabla_multiplicar[i][j] = i * j;
        }
    }

    for (int i = 0; i < FIL; i++) {
        printf("\nTabla del %d\n", i);
        for (int j = 0; j < COL; j++) {
            printf("%d * %d = %d\n", i, j, tabla_multiplicar[i][j]);
        }
    }

    return 0;
}
```

---

### Pasar por parámetro de una función un arreglo

#### Opción 1: como puntero

```c
void funcion(int *parametro) {
   // ...
}
```

#### Opción 2: arreglo con tamaño

```c
void funcion(int parametro[10]) {
   // ...
}
```

#### Opción 3: arreglo sin tamaño

```c
void funcion(int parametro[]) {
   // ...
}
```

## ⚠️ C no verifica los límites del arreglo

En C, cuando accedés a un arreglo con un índice (por ejemplo, `arreglo[i]`), **el compilador no verifica automáticamente si ese índice está dentro del rango válido**. Esto puede generar comportamientos impredecibles o errores muy difíciles de detectar.

### 📌 Ejemplo:

```c
int arreglo[3] = {1, 2, 3};
printf("%d\n", arreglo[5]); // ❌ acceso fuera de rango
```

### 🔥 ¿Qué puede pasar?

- Se puede leer o escribir datos incorrectos ("basura").
- Se pueden pisar variables o estructuras de memoria cercanas.
- El programa puede fallar en tiempo de ejecución (**segmentation fault**).
- El error puede pasar desapercibido, provocando resultados incorrectos.

### SPOILER ALERT - Clasificación del error: Acceso fuera de los límites del arreglo

### ⚠️ Error: `arreglo[5]` cuando el arreglo solo tiene 3 elementos

> Estás accediendo a una posición de memoria que no pertenece al arreglo.

### ❓ ¿Qué tipo de error es?

| Tipo de Error   | ¿Aplica? | Explicación                                                                 |
|-----------------|----------|------------------------------------------------------------------------------|
| **Léxico**      | ❌ No     | El compilador **sí reconoce** la palabra `arreglo`, el número `5` y los `[]`. |
| **Sintáctico**  | ❌ No     | La expresión `arreglo[5]` **es válida sintácticamente** en C.                |
| **Semántico**   | ✅ Sí     | El acceso está **fuera del rango lógico permitido**, aunque la sintaxis sea válida. |
---
### ✅ Buenas prácticas:

- Usá `for (int i = 0; i < TAM; i++)` para evitar pasarte del límite.
- No accedas directamente a `arreglo[i]` si `i` no está controlado.
- Considerá usar constantes o `#define TAM` para manejar tamaños.
---

### Retornar un arreglo por una función

C no permite devolver un arreglo completo, pero sí un **puntero** al arreglo. Requiere declarar el arreglo como `static`.

```c
int* devolver_arreglo() {
    static int datos[3] = { 1, 2, 3 };
    return datos;
}
```

## ⚠️ No se debe devolver la dirección de una variable local

Cuando declarás una variable dentro de una función, esa variable es **local** y su espacio en memoria **se libera automáticamente** al terminar la función. Si devolvés su dirección, vas a apuntar a memoria que **ya no existe**.

### 📌 Ejemplo peligroso:

```c
int* devolver_arreglo() {
    int arreglo[3] = {1, 2, 3};  // ← variable local
    return arreglo;              // ❌ Devuelve dirección inválida
}
```

### 🔥 ¿Qué pasa si usás ese puntero?

- Vas a acceder a memoria "muerta" o reusada.
- Podés obtener basura, errores o crashes.
- El comportamiento es **indefinido** (lo peor en C).

---

## ✅ Soluciones válidas:

### ✔️ Usar `static` (persiste en memoria global)

```c
int* devolver_arreglo() {
    static int arreglo[3] = {1, 2, 3};
    return arreglo; // ✅ válido: no se libera al salir
}
```

### ✔️ Usar memoria dinámica (`malloc`)

```c
#include <stdlib.h>

int* devolver_arreglo() {
    int* arreglo = malloc(sizeof(int) * 3);
    arreglo[0] = 1;
    arreglo[1] = 2;
    arreglo[2] = 3;
    return arreglo;
}
```

> ⚠️ Con `malloc`, vos sos responsable de liberar la memoria con `free()`.

---

### 🧠 Recomendación:

- Siempre que devuelvas arreglos o estructuras grandes, pensá si podés:
    - Usar `static`
    - Usar `malloc`
    - O pasar el arreglo como parámetro en lugar de devolverlo
---

### ❌ Errores comunes con arreglos

- Usar índices fuera del rango (ej: `arr[10]` en un arreglo de tamaño 10)
- No inicializar un arreglo y usar sus valores (puede haber basura de memoria)
- Confundir tamaño con índices válidos (`arr[3]` tiene índices `0`, `1`, `2`)
- Intentar devolver un arreglo sin usar puntero o `static`
- Escribir fuera del arreglo y sobrescribir memoria

---

### ✨ ¡Listo!

Este apunte sirve como referencia rápida para cualquier práctica de arreglos en C.

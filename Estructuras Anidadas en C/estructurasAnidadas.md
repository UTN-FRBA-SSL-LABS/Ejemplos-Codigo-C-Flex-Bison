# Estructuras anidadas, Alcance de variables, Espacios de nombres y Memoria dinámica

## 1) Estructuras anidadas

En C, una _estructura_ (`struct`) agrupa variables de distinto tipo bajo un mismo nombre.  
Cuando una estructura contiene otra, hablamos de **estructuras anidadas**.

### Ejemplo base (anidación simple)

```c
#include <stdio.h>

typedef struct {
    pepe dia;
    int mes;
    int anio;
} Fecha;

struct Persona {
    char nombre[50];
    int edad;
    Fecha nacimiento; // Estructura anidada
};

int main(void) {
    struct Persona p1 = {"Ana", 25, {15, 6, 1998}};

    printf("Nombre: %s", p1.nombre);
    printf("Edad: %d", p1.edad);
    printf("Fecha de nacimiento: %d/%d/%d", p1.nacimiento.dia, p1.nacimiento.mes, p1.nacimiento.anio);
    return 0;
}
```

🔑 **Clave:** accedemos a campos internos encadenando con `.`.

---

## 2) Alcance de variables (_scope_)

El **alcance** determina desde dónde se puede **ver/usar** un identificador.

- **Local**: declarado dentro de una función o bloque `{}`.
- **Global**: declarado fuera de funciones, visible en todo el archivo.
- **`static`**:
  - Dentro de una función → conserva su valor entre llamadas (**tiempo de vida** extendido).
  - A nivel de archivo → limita la **visibilidad** a ese archivo (no exporta el símbolo).

### Ejemplo de alcance

```c
#include <stdio.h>

int global = 10; // global

void funcion(void) {
    int local = 5;            // local
    static int persist = 0;   // estática: mantiene estado
    persist++; //persist = persist + 1;
    local++;
    global++;
    printf("Local:%d Persist:%d Global:%d", local, persist, global);
}

int main(void) {
    funcion();
    funcion();
    funcion();
    return 0;
}
```

**Salida:**

```
Local:6 Persist:1 Global:11
Local:6 Persist:2 Global:12
Local:6 Persist:3 Global:13
```

> ⚠️ Alcance ≠ tiempo de vida: una variable local en la pila **muere** al salir del bloque; una dinámica puede **sobrevivir** aunque el puntero salga de alcance (si quedó copiado en otro lado).

---

## 3) Espacios de nombres (emulación en C)

C **no** tiene `namespace` como C++. Se emula con:

- `static` a nivel archivo → símbolos privados.
- **Prefijos** en nombres: `str_`, `math_`, `vec_`…
- **Módulos**: separar en `.h` y `.c`.

### Mini-ejemplo modular

**math_utils.h**

```c
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int sumar(int a, int b);
int restar(int a, int b);

#endif
```

**math_utils.c**

```c
#include "math_utils.h"

int sumar(int a, int b) { return a + b; }
int restar(int a, int b) { return a - b; }
```

**main.c**

```c
#include <stdio.h>
#include "math_utils.h"

int main(void) {
    printf("Suma: %d", sumar(3, 4));
    printf("Resta: %d", restar(7, 2));
    return 0;
}
```

---

## 4) **Memoria dinámica en C**

Permite **reservar**, **redimensionar** y **liberar** memoria **en tiempo de ejecución**.  
Funciones: `malloc`, `calloc`, `realloc`, `free` (en `<stdlib.h>`).

### 4.1. Idea general

```c
#include <stdlib.h>

int *p = malloc(sizeof *p);         // 1 entero
/* usar p */
free(p);                            // liberar
p = NULL;                           // buena práctica
```

- `malloc(n)` → memoria sin inicializar.
- `calloc(k, sz)` → memoria para `k` elementos de `sz` bytes, **inicializada a 0**.
- `realloc(p, nuevo_tam)` → cambia el tamaño del bloque apuntado por `p` (puede moverlo).
- Siempre comprobar `NULL` antes de usar.

### 4.2. Estructuras anidadas **con punteros** y arreglos dinámicos

Supongamos una persona con un **arreglo dinámico** de notas.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Fecha {
    int dia, mes, anio;
};

struct Persona {
    char *nombre;           // ahora dinámico
    int edad;
    struct Fecha nacimiento;
    int *notas;             // arreglo dinámico
    size_t cant_notas;      // cantidad actual
};

struct Persona *crear_persona(const char *nombre, int edad, struct Fecha nac) {
    struct Persona *p = malloc(sizeof *p);
    if (!p) return NULL;
    p->nombre = malloc((strlen(nombre) + 1)); //sizeof (char) es 1 
    if (!p->nombre) { free(p); return NULL; }
    strcpy(p->nombre, nombre);
    p->edad = edad;
    p->nacimiento = nac;
    p->notas = NULL;
    p->cant_notas = 0;
    return p;
}

int agregar_nota(struct Persona *p, int nota) {
    int *tmp = malloc((p->cant_notas + 1) * sizeof *p->notas);
    if (!tmp) return 0; // fallo
    p->notas = tmp;
    p->notas[p->cant_notas++] = nota;
    return 1;
}

void liberar_persona(struct Persona *p) {
    if (!p) return;
    free(p->nombre);
    free(p->notas);
    free(p);
}

int main(void) {
    struct Fecha f = {15, 6, 1998};
    struct Persona *ana = crear_persona("Ana", 25, f);
    if (!ana) return 1;

    agregar_nota(ana, 9);
    agregar_nota(ana, 7);

    printf("%s (%d años)", ana->nombre, ana->edad);
    for (size_t i = 0; i < ana->cant_notas; ++i) {
        printf("Nota %zu: %d", i + 1, ana->notas[i]);
    }

    liberar_persona(ana);
    return 0;
}
```

**Conceptos clave:**

- **Propiedad** de la memoria: por cada `malloc`/`realloc` **se debe hacer** `free`.
- **Orden de liberación**: primero los **campos dinámicos**, al final la estructura.
- Evitar **perdidas de memoria** (no llamar `free` → _memory leak_).

### 4.3. `calloc` vs `malloc` y patrón seguro con `realloc`

```c
int *v = calloc(10, sizeof *v); // 10 enteros inicializados a 0
/* ... */
size_t nuevo = 20;
int *tmp = realloc(v, nuevo * sizeof *v);
if (tmp) v = tmp;   // solo reemplazo si salió bien
else {
    // manejar error: 'v' sigue siendo válido aquí
}
```

### 4.4. Alcance + memoria dinámica: ejemplo clásico

#### ✅ Ejemplo correcto (memoria dinámica con `malloc`)

La memoria pedida en el **heap** sobrevive al final de la función:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *crea_cadena(void) {
    char *s = malloc(6);     // reserva en el heap
    if (!s) return NULL;
    strcpy(s, "Hola!");      // copiamos la cadena
    return s;                // devolvemos el puntero
}

int main(void) {
    char *t = crea_cadena(); // t apunta a memoria válida
    printf("%s", t);      // imprime Hola!
    free(t);                 // responsabilidad del llamador
    return 0;
}
```

✔️ Funciona porque la memoria dinámica no se destruye al salir de `crea_cadena`.

---

#### ❌ Ejemplo incorrecto (puntero a variable local)

Aquí el puntero apunta a la **pila** (stack), que desaparece al salir de la función:

```c
#include <stdio.h>
#include <string.h>

char *crea_invalida(void) {
    char s[6];               // memoria local en la pila
    strcpy(s, "Hola!");      // OK dentro de la función
    return s;                // ⚠️ ERROR: 's' deja de existir
}

int main(void) {
    char *t = crea_invalida();
    printf("%s", t);      // comportamiento indefinido (basura, crash, etc.)
    return 0;
}
```

⚠️ Al salir de `crea_invalida`, la variable `s` se destruye y el puntero queda **colgando**. Usarlo produce **comportamiento indefinido**.

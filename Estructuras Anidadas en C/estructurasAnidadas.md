# Estructuras anidadas, Alcance de variables, Espacios de nombres y Memoria dinámica

## 1) Estructuras anidadas

En C, una _estructura_ (`struct`) agrupa variables de distinto tipo bajo un mismo nombre.  
Cuando una estructura contiene otra, hablamos de **estructuras anidadas**.

> _Nota: En esta práctica vamos a ser explícitos con `struct Fecha` y `struct Persona` en lugar de ocultar el tipo detrás de `typedef`. `typedef` sirve para crear un alias de tipo y puede mejorar la escritura cuando el tipo se usa muy seguido, pero en material introductorio también puede ocultar el hecho de que estamos trabajando con una estructura concreta._

### Ejemplo base (anidación simple)

```c
#include <stdio.h>

struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Persona {
    char nombre[50];
    int edad;
    struct Fecha nacimiento; /* estructura anidada */
};

int main(void)
{
    struct Persona p1 = {"Ana", 25, {15, 6, 1998}};

    printf("===== PERSONA =====\n");
    printf("Nombre: %s\n", p1.nombre);
    printf("Edad: %d\n", p1.edad);
    printf("Fecha de nacimiento: %d/%d/%d\n",
           p1.nacimiento.dia, p1.nacimiento.mes, p1.nacimiento.anio);
    return 0;
}
```

🔑 **Clave:** accedemos a campos internos encadenando con `.`.

### Ejemplo con memoria dinámica y estructura anidada (C89, manejo seguro):

```c
/* ejemplo_dinamico.c  -- compilar: gcc -std=c89 -Wall ejemplo_dinamico.c -o ejemplo_dinamico */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Persona {
    char *nombre;          /* dinámico: requiere free */
    int edad;
    struct Fecha nacimiento;
    int *notas;            /* arreglo dinámico */
    size_t cant_notas;     /* cantidad válida en 'notas' */
};

/* Crea y devuelve una Persona nueva; el llamador (caller) debe usar free (liberar_persona). */
struct Persona *crear_persona(const char *nombre, int edad, struct Fecha nac)
{
    struct Persona *p;

    p = (struct Persona *) malloc(sizeof *p);
    if (!p) return NULL;

    p->nombre = (char *) malloc(strlen(nombre) + 1);
    if (!p->nombre) {
        free(p);
        return NULL;
    }

    strcpy(p->nombre, nombre);
    p->edad = edad;
    p->nacimiento = nac;
    p->notas = NULL;
    p->cant_notas = 0;
    return p;
}

/* Agrega una nota al arreglo dinámico usando realloc seguro. */
int agregar_nota(struct Persona *p, int nota)
{
    int *tmp;
    size_t nuevo_len;

    if (!p) return 0;

    nuevo_len = p->cant_notas + 1;
    /* BUENA_PRÁCTICA: usar tmp para no perder el bloque original en caso de fallo */
    tmp = (int *) realloc(p->notas, nuevo_len * sizeof *p->notas);
    if (!tmp) {
        return 0; /* realloc falló; 'p->notas' sigue válido */
    }

    p->notas = tmp;
    p->notas[p->cant_notas] = nota;
    p->cant_notas = nuevo_len;
    return 1;
}

void liberar_persona(struct Persona *p)
{
    if (!p) return;
    free(p->nombre); /* liberar campos dinámicos primero */
    free(p->notas);
    free(p);
}

int main(void)
{
    struct Fecha f = {15, 6, 1998};
    struct Persona *ana;

    ana = crear_persona("Ana", 25, f);
    if (!ana) {
        fprintf(stderr, "Error: no se pudo crear persona\n");
        return 1;
    }

    if (!agregar_nota(ana, 9) || !agregar_nota(ana, 7)) {
        fprintf(stderr, "Error: no se pudo agregar nota\n");
        liberar_persona(ana);
        return 1;
    }

    printf("===== PERSONA DINÁMICA =====\n");
    printf("%s (%d años)\n", ana->nombre, ana->edad);
    {
        size_t i;
        for (i = 0; i < ana->cant_notas; ++i) {
            printf("Nota %lu: %d\n", (unsigned long)(i + 1), ana->notas[i]);
        }
    }

    liberar_persona(ana);
    return 0;
}
```

> Nota técnica: cuando `realloc` falla, devuelve `NULL` y el bloque original sigue siendo válido. Por eso se guarda primero en una variable auxiliar. Recién cuando el llamado devuelve un puntero no nulo se reemplaza el anterior.


---

## 2) Alcance (scope) y `static` — notas y ejemplo

El **alcance** determina desde dónde se puede **ver/usar** un identificador.

- **Local**: declarado dentro de una función o bloque `{}`.
- **Global**: declarado fuera de funciones, visible en todo el archivo.
- **`static`**:
    - `static` a nivel de archivo limita la visibilidad del símbolo a ese fichero (encapsulación simple).
    - `static` dentro de una función extiende el tiempo de vida de la variable pero NO su visibilidad fuera de la función.

### Ejemplo de alcance

```c
/* scope_example.c */
#include <stdio.h>

static int archivo_privado = 42; /* visible sólo en este fichero */

void f(void)
{
    static int contador = 0; /* persiste entre llamadas */
    int local = 5;           /* vive sólo durante la llamada */

    contador++;
    archivo_privado++;
    local++;
    printf("local=%d contador=%d archivo_privado=%d\n", local, contador, archivo_privado);
}

int main(void)
{
    f();
    f();
    f();
    return 0;
}
```

**Salida:**

```
local=6 contador=1 archivo_privado=43
local=6 contador=2 archivo_privado=44
local=6 contador=3 archivo_privado=45
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

La corrección conceptual es importante: `s` es un arreglo automático, reservado en la pila de la llamada. Su existencia termina al salir de `crea_invalida`. El puntero devuelto no apunta a un objeto válido después del `return`; conserva una dirección, pero esa dirección ya no referencia memoria utilizable para ese objeto. A partir de ese punto, cualquier acceso a través de ese puntero tiene **comportamiento indefinido:** puede parecer que funciona, puede leer basura o puede provocar un fallo inmediato.

Si se necesita devolver una cadena desde una función, la alternativa correcta es reservar memoria dinámica, copiar el contenido allí y transferir la responsabilidad de liberarla al llamador.

### Recomendaciones prácticas
- Siempre comprobar valores retornados por `malloc`, `calloc` y `realloc`.
- Liberar en orden: primero campos dinámicos dentro de la estructura, luego la estructura en sí.
- Después de `free(ptr);` es buena práctica asignar `ptr = NULL;` si el puntero seguirá en alcance.
- Para `realloc`: usar un `tmp` intermedio y sólo asignar al campo si `tmp != NULL`.

Patrón seguro de `realloc` (resumen):

```c
int *tmp = (int *) realloc(v, nuevo_tam * sizeof *v);
if (tmp) v = tmp; /* OK */
else { /* manejar fallo: 'v' sigue apuntando al bloque original */ }
```

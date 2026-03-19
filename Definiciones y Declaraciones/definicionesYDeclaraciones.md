Declaraciones y Definiciones en C

---

### ¿Qué es una Declaración?

Una **declaración** es una sentencia que introduce un nombre en una unidad de compilación, dándole existencia semántica. Informa al compilador que ese nombre representa una entidad (variable, función, estructura, etc.).

**Ejemplos:**

```c
int x;
int sumar(int, int);
int sumar(int a, int b);
```

**Resumen:**

* Asocia un identificador con un tipo.
* Informa al compilador sobre su uso.
* No necesariamente reserva memoria (a menos que también sea definición).

---

### ¿Qué es una Definición?

Una **definición** es una declaración que además inicia la existencia física del objeto (reserva memoria).

**Ejemplos:**

```c
// Declaración sin definición
extern int x;

// Declaración con definición sin inicialización
int x;

// Declaración con definición e inicialización
int x = 3;
```

**Funciones:**

```c
// Declaración (prototipo)
int sumar(int a, int b);

// Definición
int sumar(int a, int b) {
    return a + b;
}
```

---

### Secuencia vital de un objeto en C

1. **Declarar**: Asociar nombre con tipo.
2. **Iniciar**: Reservar espacio en memoria.
3. **Definir**: Declarar + Iniciar.
4. **Inicializar**: Asignar valor inicial.

---

### Aclaración sobre `extern`

```c
extern int x; // Solo declaración
```

* No reserva memoria.
* Se asume que la definición está en otro lugar.
* Evita confusiones con definiciones repetidas.

---

## Declaraciones avanzadas

### 1. Arreglo de punteros

```c
char *dias[] = {"Lunes", "Martes", "Miercoles"};
```

* `dias` es un arreglo de punteros a `char`.
* Cada elemento apunta a una cadena.

```c
int a = 10, b = 20;
int *ptrs[] = {&a, &b};
```

* `ptrs` es un arreglo de punteros a `int`.

---

### 2. Puntero a un arreglo

```c
int arr[5] = {1, 2, 3, 4, 5};
int (*p)[5] = &arr;
```

* `p` es un puntero a un arreglo de 5 enteros.

---

### 3. Funciones con cantidad variable de argumentos

```c
#include <stdarg.h>

int sumar(int cantidad, ...) {
    va_list args; // Variable que representa la lista de argumentos
    va_start(args, cantidad); // Inicializa la lista con el último argumento fijo
    int suma = 0;
    for (int i = 0; i < cantidad; i++) {
        suma += va_arg(args, int); // Extrae el siguiente argumento de tipo int
    }
    va_end(args); // Finaliza el manejo de argumentos variables
    return suma;
}
```

**Uso:**

```c
int total = sumar(3, 10, 20, 30); // total = 60
```

* Se usa la librería `<stdarg.h>`.
* `va_list` es el tipo de dato que representa la lista de argumentos.
* `va_start` la inicializa, `va_arg` recupera argumentos, y `va_end` libera recursos.
* La función acepta un número variable de argumentos.

---

### Conclusión

| Concepto    | Qué hace                               |
| ----------- | -------------------------------------- |
| Declarar    | Relaciona un identificador con un tipo |
| Iniciar     | Reserva almacenamiento en memoria      |
| Definir     | Declara + Inicia                       |
| Inicializar | Asigna un valor inicial                |

* Las **funciones** se definen al implementar su cuerpo.
* Las **variables** pueden declararse, definirse e inicializarse en una sola sentencia.
* El modificador `extern` permite separar declaración de definición.
* Se pueden declarar estructuras complejas como arreglos de punteros o funciones variádicas.

---

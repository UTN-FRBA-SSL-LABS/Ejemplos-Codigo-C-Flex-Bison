# Declaraciones y Definiciones en C

## ¿Qué es una Declaración?

Una **declaración** es una sentencia que introduce un nombre (identificador) en una unidad de compilación, asociándolo con un tipo. Le informa al compilador qué es ese nombre y cómo usarlo, pero **no necesariamente reserva memoria**.

**Ejemplos:**

```c
int sumar(int, int);      // Declaración de función (prototipo)
int sumar(int a, int b);  // Ídem, con nombres de parámetros (más legible)
extern int x;             // Declaración de variable: existe en otro archivo
```

**Resumen:**

* Asocia un identificador con un tipo.
* Permite al compilador verificar usos correctos del identificador.
* No siempre reserva espacio en memoria.

---

## ¿Qué es una Definición?

Una **definición** es una declaración que además reserva almacenamiento para el objeto. Todo objeto debe tener exactamente una definición en el programa (la llamada *One Definition Rule*).

**Ejemplos:**

```c
extern int x;   // Solo declaración: no reserva memoria,
                // la definición está en otro archivo

int x;          // Declaración + definición: reserva memoria para x
                // (el valor es indeterminado si es variable local — ver nota más abajo)

int x = 3;      // Declaración + definición + inicialización
```

### Funciones

```c
// Declaración (prototipo): le avisa al compilador la firma de la función
int sumar(int a, int b);

// Definición: implementa el cuerpo, aquí sí existe la función
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

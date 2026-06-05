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

## Los tres conceptos clave

| Concepto | Qué hace | Ejemplo |
|---|---|---|
| **Declaración** | Asocia un nombre con un tipo | `extern int x;` |
| **Definición** | Declaración + reserva de almacenamiento | `int x;` |
| **Inicialización** | Asigna un valor en el momento de la definición | `int x = 3;` |

> **Nota importante:** Definición e inicialización son conceptos distintos.
> Definir una variable reserva memoria; inicializarla le da un valor de partida.
> Se pueden hacer juntos o por separado:
>
> ```c
> int x;      // Definición sin inicialización
> x = 5;     // Asignación posterior (no es inicialización)
>
> int y = 5;  // Definición con inicialización
> ```

---

## ⚠️ Variables no inicializadas: comportamiento indeterminado

Este es uno de los errores más comunes y peligrosos en C.

```c
void ejemplo(void) {
    int x;          // Variable local: valor INDETERMINADO (basura de memoria)
    printf("%d\n", x); // Comportamiento indefinido — puede imprimir cualquier cosa
}
```

```c
int global;         // Variable global o estática: se inicializa a 0 automáticamente
static int s;       // Ídem
```

> K&R, Cap. 4: *"External and static variables are initialized to zero by default.
> Automatic variables for which there is no explicit initializer have undefined values."*

```c
/* Buena práctica: Se recomienda siempre inicializar las variables locales
   al momento de definirlas, para evitar comportamiento indeterminado. */
int x = 0;
```

---

## El modificador `extern`

`extern` declara que un identificador existe, pero que su definición está en **otra unidad de compilación** (otro archivo `.c`). No reserva memoria.

```c
// archivo: main.c
extern int contador;    // Declaración: el compilador sabe que existe
                        // pero no reserva memoria aquí

// archivo: utils.c
int contador = 0;       // Definición: aquí sí se reserva memoria
```

> **¿Para qué sirve?** Permite compartir variables globales entre archivos sin
> definirlas múltiples veces. Si se omite `extern` y se pone `int contador;`
> en varios archivos, el linker puede reportar un error de símbolo duplicado.

---

## Declaraciones avanzadas

### 1. Arreglo de punteros

```c
/* Buena práctica: Se recomienda usar const char * al apuntar a literales de cadena,
   ya que modificarlos produce comportamiento indefinido. */
const char *dias[] = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes"};
```

- `dias` es un arreglo de punteros a `char`.
- Cada elemento apunta al inicio de una cadena literal almacenada en memoria de solo lectura.
- **¿Por qué `const`?** Los literales de cadena (`"Lunes"`, etc.) no deben modificarse.
  Usar `char *` en lugar de `const char *` compila, pero es un error latente:

```c
char *mal = "Hola";
mal[0] = 'h';   // Comportamiento indefinido: intento de modificar memoria de solo lectura
```

Con enteros, la misma idea:

```c
int a = 10, b = 20;
int *ptrs[] = {&a, &b};  // Arreglo de punteros a int
```

---

### 2. Puntero a un arreglo

```c
int arr[5] = {1, 2, 3, 4, 5};
int (*p)[5] = &arr;   // p es un puntero a un arreglo de 5 enteros
```

La diferencia con `int *p = arr` es sutil pero importante:

```c
int *p1 = arr;      // Puntero al primer elemento: tipo int *
int (*p2)[5] = &arr; // Puntero al arreglo completo: tipo int (*)[5]

// p1 + 1 avanza sizeof(int) bytes
// p2 + 1 avanza sizeof(int[5]) bytes — salta el arreglo entero
```

> Esto es especialmente relevante al trabajar con arreglos bidimensionales
> y al pasar arreglos a funciones.

---

### 3. Funciones con cantidad variable de argumentos
Cuando una función necesita aceptar un número no fijo de argumentos, C provee
la librería `<stdarg.h>`.

```c
#include <stdarg.h>

int sumar(int cantidad, ...) {
    va_list args;              // Tipo que representa la lista de argumentos variables
    va_start(args, cantidad);  // Inicializa la lista; necesita el último arg fijo

    int suma = 0;
    for (int i = 0; i < cantidad; i++) {
        suma += va_arg(args, int);  // Extrae el siguiente argumento como tipo int
    }

    va_end(args);   // Libera los recursos asociados a va_list
    return suma;
}
```

**Uso:**

```c
int total = sumar(3, 10, 20, 30); // total = 60
```

**Macros de `<stdarg.h>`:**

| Macro | Función |
|---|---|
| `va_list` | Tipo que representa la lista de argumentos |
| `va_start(ap, ultimo)` | Inicializa `ap` usando el último argumento fijo |
| `va_arg(ap, tipo)` | Extrae el siguiente argumento con el tipo indicado |
| `va_end(ap)` | Finaliza el uso de `ap` (siempre llamar antes de retornar) |

> ⚠️ El compilador **no verifica** los tipos de los argumentos variables.
> Si se pasa un `double` y se extrae con `va_arg(args, int)`, el comportamiento
> es indefinido. La responsabilidad del tipo recae en el programador.

```c
/* Buena práctica: Se recomienda siempre incluir un parámetro fijo que indique
   la cantidad o el tipo de los argumentos variables, para poder recorrerlos
   correctamente (como hace printf con el string de formato). */
```

---

## Resumen

| Concepto | Qué hace | Reserva memoria |
|---|---|---|
| **Declaración** | Asocia un identificador con un tipo | No |
| **Definición** | Declaración + reserva almacenamiento | Sí |
| **Inicialización** | Asigna valor en la definición | — |
| `extern` | Declara sin definir (la def. está en otro archivo) | No |

- Las **funciones** se definen al implementar su cuerpo; el prototipo es solo declaración.
- Las **variables globales y estáticas** se inicializan a cero por defecto.
- Las **variables locales** tienen valor indeterminado si no se inicializan explícitamente.
- El modificador `extern` permite compartir variables entre archivos sin duplicar definiciones.
- Declaraciones compuestas como arreglos de punteros o funciones variádicas siguen las mismas reglas, pero requieren atención adicional a los tipos.
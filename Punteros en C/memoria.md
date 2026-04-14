### UTN - FRBA - Sintaxis y Semántica de los Lenguajes - 2025

## 💾 **Manejo de Memoria en C**

---

## 🧰 **Funciones útiles para gestión de memoria dinámica**

### 🧱 `malloc` (Memory ALLOCation)

```c
void* malloc(unsigned numero_de_bytes);
```

Reserva un bloque de memoria de `numero_de_bytes`. Devuelve un puntero genérico (`void*`) al inicio del bloque.

---

### 📦 `calloc` (Contiguous ALLOCation)

```c
void* calloc(unsigned numero_de_elementos, unsigned numero_de_bytes);
```

Reserva memoria para un arreglo de elementos, inicializando todos los bytes a cero (`\0`).

```c
int *arrayEnteros = calloc(5, sizeof(int));
```

Equivalente con `malloc`:

```c
int *arrayEnteros = malloc(5 * sizeof(int));
```

---

### ✂️ `realloc` (RE-ALLOCation)

```c
void* realloc(void *unPuntero, unsigned numero_de_bytes);
```

Redimensiona un bloque de memoria previamente reservado.  
Mantiene los datos si se agranda. Devuelve un nuevo puntero.

---

### 🗑️ `free` (Liberar)

```c
void free(void *unPuntero);
```

Libera un bloque de memoria previamente reservado con `malloc`, `calloc` o `realloc`.

> 🧠 **Regla de oro**:  
> Por cada `malloc()` o `calloc()`, **debe** haber un `free()` correspondiente.  
> No liberar memoria puede provocar **memory leaks** (fugas de memoria).

---

## 🧠 Visualización del uso de memoria

### 📊 Stack vs Heap

```
Memoria (de abajo hacia arriba):

+---------------------+
| Código (text)       |
+---------------------+
| Datos estáticos     |
+---------------------+
| HEAP (malloc, etc.) | ← ← ← Crece hacia arriba
|                     |
|  ← ← ← malloc()     |
+---------------------+
|                     |
| STACK (variables)   | ← ← ← Crece hacia abajo
+---------------------+
```

- 📌 **Stack**: contiene variables locales, parámetros de funciones, y retorna automáticamente al salir de una función.
- 📌 **Heap**: contiene memoria dinámica reservada manualmente con `malloc`, `calloc`, `realloc`. Se libera con `free()`.

---

### 🧪 Ejemplo visual: malloc

```c
int *p = malloc(3 * sizeof(int));
```

```
Antes de malloc:
p → [indefinido]

Después de malloc:
p → dirección 0x1000
       ↓
0x1000: [ ? ]
0x1004: [ ? ]
0x1008: [ ? ]
```

- `p` vive en el stack
- La memoria apuntada vive en el heap
- Los valores son indefinidos hasta que se asignan

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
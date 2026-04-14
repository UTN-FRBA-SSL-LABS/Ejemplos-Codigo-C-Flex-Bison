# 📂 Ficheros en C – Apunte Completo

## 📌 Introducción
En este apunte se desarrollan conceptos fundamentales sobre el manejo de **ficheros (archivos) en C**, con el objetivo de comprender las funciones y operaciones necesarias para su uso en trabajos prácticos.

> ⚠️ Para utilizar las funciones mencionadas, es obligatorio incluir:
```c
#include <stdio.h>
```

---

## 📖 ¿Qué es un fichero/archivo?

Un fichero es una estructura de datos almacenada en memoria secundaria, donde si deseamos guardar, recuperar o utilizar información del mismo, vamos a tener que realizar una serie de pasos u operaciones.

Para trabajar con archivos en C es necesario realizar una serie de operaciones:

1. Declaración del fichero  
2. Apertura  
3. Lectura / Escritura  
4. Cierre  

Antes de poder utilizar un fichero, primero debemos realizar la operación de apertura del mismo. Luego, si queremos almacenar datos en él, tendremos que realizar una operación de escritura y si queremos obtener datos que están en el archivo realizaremos una operación de lectura. Una vez que terminamos de usar el archivo, como último paso, deberíamos realizar una operación de cierre del archivo, para así liberar la memoria que esté ocupando.


---

## 🧩 Declaración de un fichero

```c
FILE *nombre_variable;
```

🔎 Esto declara un **puntero a una estructura `FILE`**, que representa el archivo.

---

## 🔓 Apertura y cierre de ficheros

### 📂 Apertura de un fichero

Se realiza con la función:

```c
FILE *fichero = fopen("nombre_archivo", "modo");
```

Acá utilizamos la función fopen. Esta función nos devuelve un puntero a un fichero, y se lo estamos asignando a la variable “fichero” que declaramos previamente con el mismo tipo de variable.

- Si ocurre un error → devuelve `NULL`

### ✅ Buenas prácticas

```c
FILE *fichero = fopen("datos.txt", "r");

if (fichero == NULL) {
    printf("Error al abrir el archivo\n");
}
```

---

### 🔑 Modos de apertura

El modo nos indica el tipo del fichero (texto o binario) y el uso que le vamos a dar, ya sea para escritura, lectura, solo añadir datos al final, etc.

| Modo | Descripción |
|------|------------|
| `r` | Lectura (error si no existe) |
| `w` | Escritura (crea o sobrescribe) |
| `a` | Agregar al final |
| `+` | Lectura y escritura |
| `b` | Binario |
| `t` | Texto (por defecto) |

🔧 Ejemplos:
- `"rb+"` → lectura y escritura binaria  
- `"wb+"` → crea archivo binario  
- `"a"` → agrega al final  

---

Por ejemplo, para abrir un fichero binario ya existente para lectura y escritura el modo será "rb+"; si el fichero no existe, o aun existiendo se desea crear, el modo será " wb+ ". Si deseamos añadir datos al final de un fichero de texto bastará con poner "a", etc.
Una buena práctica que se puede utilizar con la función fopen es utilizarla dentro de una sentencia condicional (IF) para poder ver si se produjo algún error al intentar abrirlo o si se efectuó con éxito, por ejemplo:

```c

FILE *fichero;

  if((fichero == fopen("nomfichero.dat",r)) == NULL){
     /* control para la apertura */
     printf("Error en la apertura. Es posible que el fichero no exista \n")
}

```

Recordemos que si durante la apertura del fichero, ocurre un error, la función fopen retorna NULL, por lo que la comparación daría verdadero e imprimiría el mensaje que pusimos.
Cuando se termine de utilizar el fichero, es importantísimo cerrarlo para liberar la memoria que se está utilizando. Esto se hace con fclose(fichero);

### 🔒 Cierre de fichero

```c
fclose(fichero);
```

> ⚠️ Es **muy importante** cerrar el archivo para liberar memoria.

---

## ✍️ Lectura y escritura en archivos

Funciones principales:

- `fread`, `fwrite`
- `fgetc`, `fputc`
- `fgets`, `fputs`
- `fscanf`, `fprintf`

---

## 📦 Lectura y escritura por bloques

### 📝 Escritura con `fwrite`

```c
fwrite(direccion, tamaño, cantidad, fichero);
```

### 🔍 Parámetros:

- direccion: es la dirección del dato que se quiere ingresar en el archivo. Si el dato lo asignamos a una variable, podemos colocar la variable con el referenciador &.
- tamaño: acá tenemos que colocar el tamaño que va a necesitar en memoria lo que queremos escribir en el archivo, por ejemplo, si queremos introducir un INT, necesitamos el tamaño que ocupa un INT en memoria. Como hay tantos tipos de datos y la verdad no es necesario acordarse cuanto ocupa cada uno, lo que podemos utilizar allí es la función sizeof(). Esta función lo que devuelve es el espacio que ocupa un tipo de dato. Por lo cual, allí podremos colocar sizeof(Int), y devolverá el espacio que ocupa un int (4 bytes).
- cantidad: Indica la cantidad de datos que vamos a ingresar en el archivo.
- fichero: es el fichero donde queremos escribir el dato.

---

### ✅ Ejemplo

```c
FILE *salida = fopen("salida.txt", "wb");

int numero = 5;
fwrite(&numero, sizeof(numero), 1, salida);

fclose(salida);
```

---

### 📖 Lectura con `fread`

```c
fread(direccion, tamaño, cantidad, fichero);
```

- Guarda los datos leídos en la dirección indicada

---

### ✅ Ejemplo

```c
FILE *entrada = fopen("entrada.txt", "rb");

int numero;
fread(&numero, sizeof(numero), 1, entrada);

fclose(entrada);
```

---

### 📊 Leer múltiples datos

Bueno, lo que hay que entender en este caso, es que cada dato que se lea ocupara un espacio distinto en memoria, por lo cual, si quisiésemos por ejemplo leer 3 datos, requeriríamos que se almacenen en un vector de 4 espacios, como en el siguiente ejemplo:

```c
int vector[3];
fread(vector, sizeof(int), 3, archivo);
```

📌 Los datos se almacenan así:
```
vector[0], vector[1], vector[2]
```

---

## 🔧 Otras funciones útiles

---

### 🖨️ `fprintf`

Escribe texto formateado en un archivo:

```c
fprintf(archivo, "Fin del archivo");
```

---

### 🔡 `fgetc`

Lee un carácter:

```c
char c = fgetc(archivo);
```

- Devuelve `EOF` al final del archivo

---

### ✏️ `fputc`

Escribe un carácter:

```c
fputc('a', archivo);
```

---

### 📜 `fgets`

Lee varios caracteres (string):

```c
fgets(buffer, tamaño, archivo);
```

---

### 📝 `fputs`

Escribe una cadena:

```c
fputs("Practica fputs", archivo);
```

---

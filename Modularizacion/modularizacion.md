# 📂 Modularización y Archivos de Cabecera (.h)

## 📌 Introducción
La **modularización** es la técnica que permite dividir un programa en componentes independientes y funcionales. En C, esto se logra separando la **interfaz** (declaraciones en archivos `.h`) de la **implementación** (definiciones en archivos `.c`). Esta práctica es esencial para organizar el código, facilitar el mantenimiento y permitir el escalado de proyectos.


## ⚙️ El proceso de compilación: Las 4 Etapas
Para comprender la utilidad de los encabezados, es necesario analizar el proceso de transformación del código fuente en un ejecutable:

1.  **Preprocesamiento:** El preprocesador interpreta las directivas como `#include`. Realiza una **sustitución textual**, copiando el contenido del archivo `.h` dentro del archivo `.c` correspondiente.
2.  **Compilación:** El código preprocesado se traduce a **lenguaje ensamblador**. El compilador usa las declaraciones de los `.h` para validar que las funciones y tipos se utilicen correctamente.
3.  **Ensamblado:** El código en ensamblador se convierte en **código objeto** (archivos `.o`), que contiene instrucciones de máquina pero aún tiene referencias pendientes a otros módulos.
4.  **Enlazado (Linking):** El enlazador une todos los archivos objeto. "Conecta" las llamadas a funciones con su lógica real y genera el archivo **ejecutable** final.


## 🔍 Declaración vs. Definición
Es crucial distinguir estos dos conceptos que conviven en la modularización:
* **Declaración (en el `.h`):** Le dice al compilador "esta función existe y tiene este formato", pero no ocupa espacio en memoria ni ejecuta lógica. Es una promesa de que la función estará disponible.
* **Definición (en el `.c`):** Es el código real de la función. Ocupa espacio en el binario y es lo que el enlazador buscará al final para completar el programa.


## 🛡️ Guardas de Inclusión: El mecanismo de "bandera"
Las guardas de inclusión son obligatorias para garantizar que el contenido de un archivo `.h` se procese **exactamente una vez**, evitando errores de redefinición.

### ¿Cómo funciona el `#define` interno?
El identificador utilizado (ej. `OPERACIONES_H`) funciona como una **bandera o testigo**:
* **Consulta (`#ifndef`):** El preprocesador pregunta si la "bandera" ya existe.
* **Marcado (`#define`):** Si no existe, la define. Esto **marca el archivo como "ya procesado"**.
* **Protección:** Si otro archivo intenta incluirlo nuevamente, el preprocesador verá la bandera levantada y saltará el contenido.


## 🔍 Consideraciones Técnicas
Para asegurar una compilación exitosa y un diseño modular correcto, se deben observar las siguientes pautas:

* **Archivos a incluir**: En las directivas `#include` siempre se deben indicar archivos de cabecera (`.h`), **nunca archivos fuente (`.c`)**.
* **Contenido de archivos fuente**: Los archivos `.c` pueden contener tanto declaraciones como definiciones y directivas de preprocesador, pero se reservan principalmente para la lógica ejecutable.
* **Sintaxis del `#include`**: 
    * `#include "archivo.h"`: Se utiliza para encabezados del propio proyecto; el preprocesador inicia la búsqueda en el directorio local.
    * `#include <archivo.h>`: Se reserva para bibliotecas estándar del sistema; el preprocesador busca en las rutas configuradas del compilador.


## 🧱 Estructura del Proyecto
* **`include/operaciones.h`**: Contiene los prototipos (declaraciones) y las guardas de inclusión.
* **`src/operaciones.c`**: Contiene la lógica detallada (definiciones) de las funciones.
* **`src/main.c`**: El programa principal que utiliza el módulo.


## 🚀 Compilación y Ejecución
Para construir un proyecto modular, se deben incluir todos los archivos fuente en el comando:

```bash
# Compilar todas las unidades de traducción
gcc src/main.c src/operaciones.c -Iinclude -o bin/programa

# Ejecutar el programa generado
./bin/programa
```

**Nota**: La bandera -Iinclude le indica al compilador la ruta de la carpeta donde se encuentran nuestros encabezados. A medida que el proyecto crece, este proceso de compilación manual se vuelve complejo y se facilita significativamente mediante el uso de herramientas de automatización como Make.
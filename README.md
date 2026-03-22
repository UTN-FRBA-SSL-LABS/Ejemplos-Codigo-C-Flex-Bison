# 🧠 Ejemplos-Codigo-C-Flex-Bison

## 📌 Descripción
Este repositorio contiene una colección organizada de ejemplos, prácticas y ejercicios desarrollados en el lenguaje **C**, orientados a reforzar conceptos fundamentales de programación, estructuras de datos y herramientas utilizadas en el análisis de lenguajes.

El objetivo principal es servir como material de apoyo tanto para el aprendizaje como para la consulta, abordando temas clave que forman parte de cursos de **Sintaxis y Semántica de Lenguajes**.

---

## 🎯 Objetivos

- Consolidar conceptos fundamentales del lenguaje C  
- Proveer ejemplos claros y reutilizables  
- Facilitar la comprensión de estructuras y manejo de memoria  
- Introducir buenas prácticas de programación  
- Aplicar técnicas básicas de testing  
- Comprender herramientas de análisis léxico y sintáctico  

---

## 📚 Contenidos

El repositorio se encuentra organizado en diferentes módulos temáticos:

---

### 🔢 Arreglos en C
- Declaración e inicialización de arrays  
- Recorrido y manipulación de datos  
- Arreglos multidimensionales  
- Aplicaciones prácticas  

---

### 📍 Punteros en C
- Concepto de puntero y dirección de memoria  
- Operadores `*` y `&`  
- Aritmética de punteros  
- Relación entre punteros y arreglos  
- Manejo dinámico de memoria  

---

### 📂 Archivos en C
- Manejo de archivos con `FILE *`  
- Apertura y cierre (`fopen`, `fclose`)  
- Lectura y escritura (`fread`, `fwrite`, `fprintf`, etc.)  
- Archivos de texto y binarios  
- Buenas prácticas en persistencia de datos  

---

### 🧪 Testing en C
- Introducción al testing en C  
- Casos de prueba  
- Validación de funciones  
- Detección de errores y debugging  
- Estrategias básicas de verificación  

---

### 🧱 Estructuras anidadas en C
- Definición de `struct`  
- Estructuras dentro de estructuras  
- Acceso a datos complejos  
- Aplicaciones en modelado de información  

---

### ⚙️ Flex (Análisis Léxico)
- Definición de analizadores léxicos  
- Uso de expresiones regulares  
- Generación automática de scanners  
- Identificación de tokens  
- Integración con código en C  

---

### 🔗 Bison + Flex (Análisis Sintáctico)
- Integración entre análisis léxico y sintáctico  
- Definición de gramáticas  
- Construcción de parsers  
- Procesamiento estructurado de tokens  
- Aplicaciones en compiladores  

---

### 🤖 Implementación de AFD con TT en C
- Representación de autómatas finitos determinísticos  
- Uso de tablas de transición (TT)  
- Simulación de reconocimiento de cadenas  
- Aplicaciones en análisis léxico  
- Modelado de lenguajes regulares  

---

## 🛠️ Requisitos

Para compilar y ejecutar los programas se recomienda:

- Compilador de C (GCC, Clang, etc.)  
- Sistema operativo compatible (Linux, Windows, macOS)  
- Flex y Bison instalados (para los módulos correspondientes)  

---

## ▶️ Cómo compilar y ejecutar

### 🔹 Programas en C
```bash
gcc programa.c -o programa
./programa
```

### 🔹 Programas con Flex y Bison
```bash
bison -d parser.y
flex scanner.l
gcc lex.yy.c parser.tab.c -o programa
./programa
```

---

## 📁 Estructura del repositorio

```
/arreglos
/punteros
/archivos
/testing
/estructuras-anidadas
/flex
/bison-flex
/afd-tt
```

Cada carpeta contiene ejemplos prácticos y código comentado.

---

## 💡 Buenas prácticas incluidas

- Código claro y legible  
- Uso de nombres descriptivos  
- Comentarios explicativos  
- Modularización de funciones  
- Validación de errores  

---

## 📖 Uso del repositorio

Este repositorio puede utilizarse como:

- 📘 Material de estudio  
- 🧩 Base para trabajos prácticos  
- 🔍 Referencia rápida  
- 🛠️ Ejemplos para proyectos  

---

## 🚀 Autor

Repositorio desarrollado por la cátedra de **Sintaxis y Semántica de los Lenguajes** del profesor **Santiago Ferreiros Cabrera**, con fines educativos para el aprendizaje del lenguaje C y sus conceptos fundamentales.

---

## 📄 Licencia

Este proyecto es de uso libre con fines educativos.

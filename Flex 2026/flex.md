# ⚙️ FLEX – Generador de Analizadores Léxicos

## 📌 ¿Qué es FLEX?

**FLEX (Fast Lexical Analyzer Generator)** es una herramienta que permite generar **analizadores léxicos** a partir de especificaciones basadas en **expresiones regulares**.

Un analizador léxico (scanner) es el primer componente de un compilador o intérprete, encargado de **leer una secuencia de caracteres y agruparlos en unidades significativas llamadas tokens**.

---

## 🎯 Objetivo

El propósito de FLEX es automatizar la construcción de analizadores léxicos, permitiendo:

- Identificar patrones en texto
- Clasificar lexemas en tokens
- Simplificar el desarrollo de compiladores e intérpretes

---

## 🧩 ¿Cómo funciona?

FLEX toma como entrada un archivo de especificación (generalmente con extensión `.l`) que contiene:

1. **Definiciones**
2. **Reglas léxicas (expresiones regulares)**
3. **Código en C asociado a cada patrón**

A partir de este archivo, FLEX genera automáticamente código en C que implementa el analizador léxico.

---

## 📄 Estructura de un archivo FLEX

Un archivo típico de FLEX se divide en tres secciones:

```flex
%{
/* Código en C */
%}

%%
/* Reglas léxicas */
%%

/* Código adicional en C */
```

---

## 🔍 Reglas léxicas

Cada regla está formada por:

```
expresión_regular    acción_en_C
```

Ejemplo:

```flex
[0-9]+      { printf("Numero\n"); }
[a-zA-Z]+   { printf("Identificador\n"); }
```

📌 FLEX evalúa las reglas en orden y ejecuta la acción correspondiente al primer patrón que coincida.

---

## 🧠 Conceptos clave

- **Token**: unidad léxica reconocida (identificadores, números, palabras clave, etc.)
- **Lexema**: secuencia de caracteres que coincide con un patrón
- **Expresión regular (ER)**: forma de describir patrones de texto

---

## 🔄 Flujo de trabajo

1. Escribir el archivo `.l`
2. Ejecutar FLEX:
   ```bash
   flex archivo.l
   ```
3. Compilar el código generado:
   ```bash
   gcc lex.yy.c -o scanner
   ```
4. Ejecutar:
   ```bash
   ./scanner
   ```

---

## 🛠️ Aplicaciones

FLEX se utiliza principalmente en:

- Desarrollo de compiladores
- Intérpretes
- Procesamiento de texto
- Validación de formatos de entrada

---

## 🤝 Integración con otras herramientas

FLEX suele utilizarse junto con **Bison (o Yacc)**:

- **FLEX** → análisis léxico  
- **Bison/Yacc** → análisis sintáctico  

---

## ✅ Ventajas

- Automatiza la generación de analizadores léxicos  
- Reduce errores manuales  
- Permite trabajar con expresiones regulares de forma eficiente  
- Genera código en C portable  

---

## ⚠️ Consideraciones

- El orden de las reglas es importante  
- Siempre se selecciona la coincidencia más larga  
- Requiere conocimientos básicos de C y expresiones regulares  

---

## 📚 Resumen

FLEX es una herramienta fundamental en el desarrollo de compiladores, ya que permite transformar texto en una secuencia estructurada de tokens mediante reglas definidas con expresiones regulares, facilitando el análisis posterior del lenguaje.

---

## 💡 Tip

> Pensá en FLEX como un “traductor” que convierte texto crudo en piezas entendibles para el programa.

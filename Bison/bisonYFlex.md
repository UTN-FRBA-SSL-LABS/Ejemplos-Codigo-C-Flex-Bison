# ⚙️ Bison + Flex – Análisis Léxico y Sintáctico

## 📌 Introducción

**Flex** y **Bison** son herramientas ampliamente utilizadas en el desarrollo de compiladores e intérpretes para implementar las dos primeras etapas del análisis de un lenguaje:

- **Análisis léxico** (Flex)
- **Análisis sintáctico** (Bison)

Trabajando en conjunto, permiten transformar texto de entrada en una estructura organizada que puede ser procesada por un programa.

---

## 🧩 ¿Qué es Flex?

**Flex (Fast Lexical Analyzer Generator)** genera analizadores léxicos a partir de **expresiones regulares**.

Su función es:
- Leer caracteres de entrada
- Agruparlos en **tokens**
- Ignorar elementos irrelevantes (espacios, comentarios, etc.)

---

## 🧠 ¿Qué es Bison?

**Bison** es un generador de analizadores sintácticos basado en **gramáticas independientes de contexto**.

Su función es:
- Recibir tokens desde Flex
- Verificar si la secuencia cumple una **estructura válida**
- Construir una representación estructurada (por ejemplo, un árbol sintáctico)

---

## 🔄 ¿Cómo trabajan juntos?

El flujo típico es el siguiente:

```
Entrada (texto)
   ↓
Flex (análisis léxico)
   ↓
Tokens
   ↓
Bison (análisis sintáctico)
   ↓
Estructura sintáctica
```

📌 Flex identifica los elementos básicos, mientras que Bison valida la estructura del lenguaje.

---

## 📄 Estructura básica

### 🔹 Archivo Flex (`.l`)

Contiene:
- Definiciones
- Reglas con expresiones regulares
- Acciones en C

Ejemplo simplificado:

```flex
[0-9]+      { return NUM; }
"+"         { return PLUS; }
```

---

### 🔹 Archivo Bison (`.y`)

Contiene:
- Declaración de tokens
- Reglas gramaticales
- Acciones semánticas

Ejemplo simplificado:

```bison
expr: expr '+' expr
    | NUM
    ;
```

---

## 🔗 Integración

Para que ambos funcionen juntos:

- Flex devuelve tokens mediante `return`
- Bison define esos tokens con `%token`
- Ambos comparten definiciones mediante archivos de cabecera (`.h`)

---

## ⚙️ Proceso de compilación

```bash
bison -d parser.y
flex scanner.l
gcc lex.yy.c parser.tab.c -o programa
```

---

## 🧠 Conceptos clave

- **Token**: unidad léxica (identificador, número, operador)
- **Gramática**: conjunto de reglas que define la estructura
- **Parser**: componente que analiza la sintaxis
- **Scanner**: componente que analiza el texto

---

## 🛠️ Aplicaciones

- Compiladores
- Intérpretes
- Lenguajes de dominio específico (DSL)
- Validadores de sintaxis

---

## ✅ Ventajas

- Separación clara entre léxico y sintaxis  
- Automatización del análisis de lenguajes  
- Reducción de errores manuales  
- Flexibilidad para definir reglas complejas  

---

## ⚠️ Consideraciones

- Requiere coordinación entre ambos archivos  
- Los tokens deben coincidir en Flex y Bison  
- El orden y diseño de reglas afecta el comportamiento  

---

## 📚 Resumen

Flex y Bison trabajan conjuntamente para analizar un lenguaje:

- **Flex** convierte texto en tokens  
- **Bison** valida la estructura de esos tokens  

Esta combinación permite construir analizadores robustos de manera eficiente, siendo una base fundamental en el desarrollo de compiladores.

---

## 💡 Tip

> Pensá en Flex como quien "lee" el texto, y en Bison como quien "entiende" la estructura.

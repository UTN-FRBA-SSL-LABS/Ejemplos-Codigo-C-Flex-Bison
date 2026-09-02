# 1. Introducción

El análisis semántico es la etapa del compilador que verifica el significado de las construcciones del lenguaje, asegurando que cumplan las reglas definidas por la semántica del lenguaje.

# 2. Conceptos Clave

## 2.1 Semántica Estática

Se evalúa **en tiempo de compilación**. Ejemplos:

- Comprobación de tipos.
- Uso de variables declaradas previamente.
- Correspondencia de número y tipo de argumentos en llamadas a funciones.

## 2.2 Semántica Dinámica

Se evalúa **en tiempo de ejecución**. Ejemplos:

- División por cero.
- Acceso a memoria inválida.
- Desbordamientos de búfer.

| Tipo de Error | Momento de detección | Ejemplo |
|---|---|---|
| Semántico estático | Compilación | `x = a + b;` con `a` no declarado |
| Semántico dinámico | Ejecución | `int a = 5/0;` |

# 3. Tabla de Símbolos (TS)

## 3.1 Definición

Estructura de datos usada para registrar información de identificadores.

## 3.2 Contenido típico

- Nombre del identificador.
- Tipo de dato.
- Ámbito.
- Información adicional (parámetros en funciones, dirección en memoria, etc.).

## 3.3 Ejemplo

| Nombre | Tipo | Clase | Parámetros | Ámbito |
|---|---|---|---|---|
| a | int | var | - | global |
| b | char | var | - | global |
| sumar | int | func | (int, int) | global |
| op1 | int | param | - | sumar |
| op2 | int | param | - | sumar |

# 4. Integración con Bison

Bison permite asociar **acciones semánticas** a reglas gramaticales.

## 4.1 Declaración de funciones en la gramática

```text
TIPO_DATO IDENTIFICADOR '(' lista_param ')' PUNTOYCOMA      {agregarFuncion($1, $2, ptr_lista_param);}
```

## 4.2 Declaración de parámetros

```text
lista_param:
    TIPO_DATO IDENTIFICADOR                         { agregarParametro($1, $2); }
  | lista_param ',' TIPO_DATO IDENTIFICADOR         { agregarParametro($3, $4); }
;
```

# 5. Validaciones Semánticas Comunes

 5.1 Redeclaraciones incompatibles

```text
char a;
int a; // Error
```

 5.2 Uso de variables no declaradas
 
 5.3 Coincidencia de tipos en expresiones

```text
A = b + 5; // Tipo(b) debe coincidir con tipo(5)
```

 5.4 Coincidencia en llamadas a funciones

Número y tipo de argumentos vs. parámetros declarados.

# 6. Conclusiones
-   El análisis semántico asegura que el programa tenga sentido lógico y semántico, no solo sintáctico.
-   La Tabla de Símbolos es fundamental para almacenar y consultar información durante el análisis.
-   Bison facilita integrar la lógica de validación semántica directamente en la gramática.

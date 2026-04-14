### UTN - FRBA - Sintaxis y Semántica de los Lenguajes
# Lenguajes Regulares

## Definir (ER), Producir (GR) y Reconocer (AF) los Lenguajes regulares

## Repaso rápido

¿Qué es un lenguaje regular?

Un conjunto de cadenas que puede describirse mediante:

- Expresiones Regulares (ER): Son una forma compacta y simbólica de describir un lenguaje regular.

```
“Las ER dicen cómo se ven las cadenas válidas.”
```

- Gramáticas Regulares (GR): Son reglas de producción que generan todas las cadenas de un lenguaje.

```
“Las GR muestran cómo se construyen las cadenas.”
```

- Autómatas Finitos (AF): Son modelos computacionales que reconocen lenguajes.

```
“Los AF verifican si una cadena pertenece al lenguaje.”
```

## Relación entre los tres

ER ⇄ GR ⇄ AF

👉 Son equivalentes: distintas formas de representar el mismo lenguaje

# Para pensar...

¿Cómo reconoce un compilador en C si esto es válido?

```c
int _contador1 = 25;
```

👉 Necesitamos una forma de:

- Definir qué es válido
- Generar ejemplos válidos
- Reconocer automáticamente las cadenas válidas

# Un poco de práctica

## Ejercicio 1

Dado el siguiente AF:

![alt text](image-1.png)

- ¿Qué lenguaje reconoce?:
- Dar ejemplos válidos e inválidos:
  - VÁLIDO: aa, ab, ba, bb, abab, abb....
  - INVÁLIDO: cab, a, 0, b
- Escribir una ER equivalente:  
  - (ab)* = Long.Mínima 0 (INVÁLIDA)
  - (a+b).(a+b).(a+b)+ = Long. Mínima 3 (INVÁLIDA)
  - (a+b).(a+b)+ = Long. Mínima 2 (VÁLIDA)
  - (a+b).(a+b).(a+b)* = Long. Mínima 2 (VÁLIDA)

## Ejercicio 2

Dada la ER: (a+b)\*abb

- ¿Qué lenguaje describe?:
- Construir un AF

## Ejercicio 3

Lenguaje: Cadenas de 0 y 1 con cantidad par de 0

- Construir AF
- Dar la ER: 
  - 1 * ( 0 1 * 0 1 * ) *

## Introducción a ERX (Expresiones Regulares Extendidas)

Las Expresiones Regulares Extendidas (ERX) son una versión práctica de las expresiones regulares que se usan en programación y herramientas reales (como validadores, compiladores o buscadores).

¿Por qué ERX? - Las ER formales son correctas desde el punto de vista teórico, pero pueden ser:

- muy largas
- poco legibles
- difíciles de escribir

Las ERX agregan atajos para hacerlas más simples y expresivas.

Diferencia clave
ER (formal)

```
(a|b)(a|b)(a|b)*
```

ERX equivalente

```
[a-b]{2}[a-b]*
```

👉 Ambas describen el mismo lenguaje, pero la ERX es más compacta.


## Principales extensiones

a{0,1} === a?
[abcd] === [a-d]

![alt text](image-2.png)

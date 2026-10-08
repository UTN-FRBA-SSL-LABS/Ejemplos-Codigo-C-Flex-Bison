# Símbolos de Preanálisis: Conjunto Primero y Conjunto Siguiente

> **Sintaxis y Semántica de los Lenguajes** · Análisis Sintáctico
> Bibliografía: Muchnik, *SSL Vol. 2 – Desde el Compilador*, §4.3.3.3 y §4.3.3.4 (págs. 70–73)

---

## 1. El problema: ¿qué producción expando?

Un **parser predictivo** (ASDR, Análisis Sintáctico Descendente Recursivo) recorre la entrada de izquierda a derecha y, cada vez que tiene que expandir un no terminal, debe elegir **qué lado derecho usar**.

Para decidir mira un único token: el **símbolo de preanálisis**, es decir, el próximo token del flujo de entrada. No puede retroceder.

| No terminal a expandir | Símbolo de preanálisis | Producción elegida |
|---|---|---|
| `A` | `id` | `A → id B` (la única que puede empezar con `id`) |

Si con **un solo** símbolo de preanálisis siempre alcanza para decidir, la gramática es **LL(1)**:
**L**eft-to-right, **L**eftmost derivation, **1** símbolo de preanálisis.

Para poder tomar esa decisión necesitamos dos conjuntos: **Primero** y **Siguiente**.

---

## 2. Hacia dónde vamos: la función Predice

```
Predice(A → X1…Xm) =
    si ε ∈ Primero(X1…Xm) entonces
        (Primero(X1…Xm) − {ε}) ∪ Siguiente(A)
    caso contrario
        Primero(X1…Xm)
```

**Condición LL(1):** para un mismo no terminal, los conjuntos Predice de sus producciones tienen que ser **disjuntos**. Si dos producciones comparten un token, el parser no sabe cuál elegir.

Predice usa **siempre** Primero, y usa Siguiente **sólo** cuando el lado derecho puede desaparecer (derivar ε).

---

## 3. Conjunto Primero

### Definición

> Sea la producción `A → X1…Xm`. **Primero(X1…Xm)** es el conjunto de terminales que pueden iniciar cualquier cadena de derivación que se obtenga a partir de `X1…Xm`.
> Si `X1…Xm` puede derivar en ε, entonces Primero también contiene a **ε**.

Pregunta guía: **¿con qué terminal puede empezar esta cadena?**

### Cómo se calcula

1. **Terminal:** si `X1` es terminal, `Primero(X1…Xm) = {X1}`.
2. **No terminal:** si `X1` es no terminal, se calcula Primero de cada lado derecho de las producciones de `X1`.
3. **Anulable:** si `X1` puede generar ε, se agrega `Primero(X1) − {ε}` y se sigue con `X2`; si `X1` y `X2` son anulables, se sigue con `X3`, y así.
4. **Todo anulable:** si **todos** los `Xi` derivan ε, entonces `ε ∈ Primero(X1…Xm)`.

### El efecto cascada

```
B → 1 | 2 | ε        Primero(B) = {1, 2, ε}
C → 3 | ε            Primero(C) = {3, ε}
D → 3 | 4 | ε        Primero(D) = {3, 4, ε}
```

```
Primero(B C D):
  B tiene ε → agrego {1, 2} y sigo con C
  C tiene ε → agrego {3}    y sigo con D
  D tiene ε → agrego {3, 4} y, como todos son anulables, agrego ε

Primero(B C D) = {1, 2, 3, 4, ε}
```

**Regla de corte:** me detengo en el primer símbolo que **no** deriva ε.

> ¿Qué pasaría si fuera `C → 3` (sin ε)? → `Primero(BCD) = {1, 2, 3}`: C corta la cascada, no entra el 4 ni ε.

---

## 4. Conjunto Siguiente

### Definición

> **Siguiente(A)** es el conjunto de terminales que siguen **inmediatamente** al no terminal A en las cadenas de derivación que contienen a A.

Define el **contexto derecho** de A. Pregunta guía: **¿qué terminal puede venir después de A?**

- Sólo se calcula para **no terminales**.
- **Nunca contiene ε.**
- ¿Por qué lo necesitamos? Si A puede desaparecer (derivar ε), el símbolo de preanálisis no lo produce A sino **lo que viene después de A**.

### Cómo se calcula

Se inspecciona la gramática buscando **todas las apariciones de A en los lados derechos**:

| Situación | Forma | Qué se agrega |
|---|---|---|
| 1. A seguido por un terminal | `… A x …` | `x ∈ Siguiente(A)` |
| 2. A seguido por un no terminal | `… A B …` | `Primero(B) − {ε} ⊆ Siguiente(A)`; si B es anulable, se mira también lo que sigue a B |
| 3. A es el último del lado derecho | `T → Y1…Ym A` | `Siguiente(T) ⊆ Siguiente(A)` |

Como un Siguiente puede depender de otro, se repite el recorrido **hasta que ningún conjunto cambie**.

> **Ojo con la diferencia:** para **Primero** miro las producciones **de** X (lado izquierdo). Para **Siguiente** busco las apariciones de A **en** los lados derechos.

> **Sobre el fin de la entrada:** el libro no agrega automáticamente una marca de fin al axioma. Cuando hace falta, el fin de la entrada se modela con un terminal explícito **fdt** (*fin de tokens*) dentro de la gramática.

---

## 5. Ejemplos 10 y 11 del libro

```
S → a S e | B
B → b B e | C
C → c C e | d
```

| No terminal | Primero | Siguiente |
|---|---|---|
| S | { a, b, c, d } | { e } |
| B | { b, c, d } | { e } |
| C | { c, d } | { e } |

- **Primero:** `S → aSe` aporta `a`; `S → B` aporta Primero(B). `B → bBe` aporta `b`; `B → C` aporta Primero(C) = {c, d}.
- **Siguiente:** en `S → a S e`, S está seguido de `e` (situación 1). En `S → B`, B es el último, así que hereda Siguiente(S) (situación 3); además en `B → b B e`, B está seguido de `e`. Lo mismo para C.

---

## 6. Ejemplo del apunte

```
T → A 5
J → A 7
A → B C D
B → 1 | 2 | ε
C → 3 | ε
D → 3 | 4 | ε
```

### Primero

| No terminal | Primero |
|---|---|
| B | { 1, 2, ε } |
| C | { 3, ε } |
| D | { 3, 4, ε } |
| A | { 1, 2, 3, 4, ε } |
| T | { 1, 2, 3, 4, 5 } |
| J | { 1, 2, 3, 4, 7 } |

En `T → A 5`, A es anulable, así que al Primero(A) sin ε se le suma el 5; como 5 es terminal, la cascada corta y T no tiene ε.

### Siguiente(A) y Predice(A → BCD)

1. A aparece en `T → A 5` y en `J → A 7` (situación 1) → `Siguiente(A) = {5, 7}`
2. ¿BCD puede derivar ε? Sí: B, C y D son anulables → `ε ∈ Primero(BCD)`
3. Entonces:

```
Predice(A → BCD) = (Primero(BCD) − {ε}) ∪ Siguiente(A)
                 = {1, 2, 3, 4} ∪ {5, 7}
                 = {1, 2, 3, 4, 5, 7}
```

Si el preanálisis es 5 o 7, igual se elige `A → BCD`: B, C y D desaparecen y el 5 o el 7 lo produce la producción de T o de J.

### ¿Es LL(1)? Miremos C

En `A → B C D`, después de C viene D, que es anulable:

```
Siguiente(C) = (Primero(D) − {ε}) ∪ Siguiente(A)
             = {3, 4} ∪ {5, 7}
             = {3, 4, 5, 7}
```

| Producción | Predice |
|---|---|
| C → 3 | { 3 } |
| C → ε | { 3, 4, 5, 7 } |

**Conflicto:** con preanálisis `3` no se sabe si C produce el 3 o si desaparece y el 3 lo produce D. **La gramática no es LL(1).**

> ¿Qué cambiarían de la gramática para resolverlo?

---

## 7. Ejemplo completo: lista de expresiones (Ejemplo 15 del libro)

```
LE → fdt | E ; LE
E  → T E′
E′ → + T E′ | ε
T  → F T′
T′ → * F T′ | ε
F  → n | ( E )
```

Genera una lista, posiblemente vacía, de expresiones con suma, producto y paréntesis, cada una terminada en `;`. Acá **fdt** es un terminal más: marca el final de la lista.

### Paso 1: Primero

| No terminal | Primero | ¿Por qué? |
|---|---|---|
| F | { n, ( } | `F → n \| ( E )` |
| T′ | { *, ε } | `T′ → * F T′ \| ε` |
| T | { n, ( } | Primero(F), F no es anulable |
| E′ | { +, ε } | `E′ → + T E′ \| ε` |
| E | { n, ( } | Primero(T), T no es anulable |
| LE | { fdt, n, ( } | fdt ∪ Primero(E) |

Orden de cálculo: **de abajo hacia arriba**. F no depende de nadie; T depende de F; E de T; LE de E.

### Paso 2: Siguiente

| No terminal | Siguiente | ¿De dónde sale? |
|---|---|---|
| E | { ;, ) } | `LE → E ; LE` y `F → ( E )` (situación 1) |
| E′ | { ;, ) } | Último en `E → T E′`: hereda Siguiente(E) |
| T | { +, ;, ) } | Primero(E′) − {ε}; E′ anulable → hereda de E y E′ |
| T′ | { +, ;, ) } | Último en `T → F T′`: hereda Siguiente(T) |
| F | { *, +, ;, ) } | Primero(T′) − {ε}; T′ anulable → hereda de T y T′ |

### Paso 3: Predice y decisión LL(1)

| Producción | Predice |
|---|---|
| LE → fdt | { fdt } |
| LE → E ; LE | { n, ( } |
| E → T E′ | { n, ( } |
| E′ → + T E′ | { + } |
| E′ → ε | { ;, ) } |
| T → F T′ | { n, ( } |
| T′ → * F T′ | { * } |
| T′ → ε | { +, ;, ) } |
| F → n | { n } |
| F → ( E ) | { ( } |

- El Predice de una producción ε es exactamente el **Siguiente** del no terminal.
- Para cada no terminal los Predice son disjuntos → **la gramática es LL(1).**

---

## 8. Errores frecuentes

| Error | Cómo evitarlo |
|---|---|
| Poner ε en un Siguiente | ε **nunca** pertenece a un Siguiente. |
| Buscar en el lugar equivocado | Primero mira las producciones **de** X; Siguiente busca a A **en** los lados derechos. |
| Cortar la cascada antes de tiempo | Primero(BCD) **no** es Primero(B) si B es anulable. |
| Hacer una sola pasada | Siguiente tiene dependencias cruzadas: iterar hasta que nada cambie. |

---

## 9. Ejercicio (Ejercicio 26 del libro, ampliado)

```
S → A B c
A → a | ε
B → b | ε
```

1. Calcular **Primero** de cada no terminal.
2. Calcular **Siguiente** de A y de B.
3. Calcular **Predice** de cada producción.
4. Decidir si la gramática es **LL(1)**.

<details>
<summary><b>Ver solución</b></summary>

**Primero**

| No terminal | Primero |
|---|---|
| A | { a, ε } |
| B | { b, ε } |
| S | { a, b, c } |

A y B son anulables, así que la cascada llega hasta `c`; S no tiene ε porque `c` es terminal.

**Siguiente**

| No terminal | Siguiente |
|---|---|
| A | { b, c } (seguido de B, que es anulable, y después `c`) |
| B | { c } |

**Predice**

| Producción | Predice |
|---|---|
| S → A B c | { a, b, c } |
| A → a | { a } |
| A → ε | { b, c } |
| B → b | { b } |
| B → ε | { c } |

Los Predice son disjuntos para cada no terminal → **es LL(1).**

</details>

---

## 10. Resumen: tres preguntas, tres conjuntos

| Conjunto | Pregunta |
|---|---|
| **Primero** | ¿Con qué terminal puede empezar esta cadena? |
| **Siguiente** | ¿Qué terminal puede venir después de este no terminal? |
| **Predice** | ¿Con qué tokens elijo esta producción? |

Si los Predice de cada no terminal son disjuntos, la gramática es **LL(1)** y se puede construir el analizador sintáctico predictivo.

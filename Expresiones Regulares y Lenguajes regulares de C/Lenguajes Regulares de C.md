### UTN - FRBA - Sintaxis y Semántica de los Lenguajes

# Lenguajes Regulares en C

## 1. Identificadores en C

### ✔ Definición

- Empieza con letra o `_`
- Continúa con letras, dígitos o `_`

---

### ✔ Expresión Regular

```regex
[a-zA-Z_][a-zA-Z0-9_]*
```

---

### ✔ Gramática Regular

```
S → letra A | _ A
A → letra A | digito A | _ A | ε
```

---

### ✔ Ejemplos

✔ Válidos:

```
x
_var
temp123
```

❌ Inválidos:

```
1var
#abc
```

---

## 2. Constantes Enteras

### ✔ Ejemplos

```
0
0152
123
4567
0x12F
0XeF4

0158 MAL
154E MAL
0x   MAL

```

---

### ✔ Expresión Regular

```
NOTA: Ver teoria OneNote
```

---

### ✔ Gramática Regular

```
NOTA: Ver teoria OneNote
```

---

### ✔ Autómata Finito

```
NOTA: Ver teoria OneNote
```

---

## 3. Constantes Reales

```
NOTA: Ver teoria OneNote
```

## 4. Literales Cadena

### ✔ Ejemplos

```
"hola"
"texto123"
"abc def"
```

---

### ✔ Expresión Regular

```regex
"[^"]*"
```

---

### ✔ Gramática Regular

```
S → " A "
A → char A | ε
```

(char ≠ ")

---

## Ejercicio

Dado el lenguaje:

- cadenas que empiezan con `a` y terminan con `b` (Universo a y b)

👉 Dar:

- ER: a[ab]*b
- GR:
    S -> aT
    T -> aT | bT | b

- AF:


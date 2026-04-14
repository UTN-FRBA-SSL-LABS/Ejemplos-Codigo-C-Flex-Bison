# Sintácticamente Correcto: BNF + Restricciones

## ¿Qué significa que algo sea sintácticamente correcto?

En el análisis de lenguajes de programación, se dice que una **estructura es sintácticamente correcta** cuando:

1. Es **derivable de la BNF**, y
2. **Cumple con las restricciones adicionales** del lenguaje.

Ambas condiciones son necesarias. Derivar de la BNF por sí solo **no es suficiente** para asegurar que una expresión sea válida en términos de sintaxis.

---

## 1. Derivable de la BNF

La **BNF** define la **gramática formal** de un lenguaje. Si una cadena puede derivarse desde el símbolo inicial mediante las reglas de la BNF, se dice que es **derivable**.

### Ejemplo:
Una expresión como `3 = a;` puede ser derivada desde la BNF de muchos lenguajes, ya que sigue una estructura del tipo:

```
Expresión → Valor = Valor;
```

Pero...

---

## 2. Restricciones del Lenguaje

A pesar de que `3 = a;` es derivable, **viola una restricción semántica del lenguaje**: el lado izquierdo de una asignación debe ser una **l-value** (una ubicación de memoria válida para almacenar un valor), usualmente un **identificador**.

Por lo tanto, `3 = a;` **no es sintácticamente correcta** en ese lenguaje, aunque sea derivable de la BNF.

---

## Relación entre BNF y Sintaxis

Podemos resumirlo así:

- **Derivable de la BNF** → Léxicamente Correcto.
- **Derivable de la BNF + Cumple restricciones** → Sintácticamente Correcto.

### Importante:

- Toda estructura **sintácticamente correcta** es **derivable de la BNF**.
- Pero no toda estructura **derivable de la BNF** es **sintácticamente correcta**.

---

## Diagrama resumen

```
                  Derivable de la BNF
                        |
                        V
    +----------Cumple restricciones?-----------+
    |                                          |
   SI                                          NO 
    |                                          |
    V                                          V
Sintácticamente correcto          Sintácticamente Incorrecto
```

---

## Comparación de errores

| Tipo de error       | Causa                                                  |
|---------------------|--------------------------------------------------------|
| **Léxico**          | Uso de símbolos que no pertenecen al lenguaje regular  |
| **Sintáctico**      | Violación de la BNF o de sus restricciones              |
| **Semántico**       | Errores en el significado: tipos, declaraciones, etc.  |

---

## Conclusión

La corrección sintáctica no se agota en derivar una expresión desde la BNF. También es necesario verificar las **restricciones contextuales** impuestas por el lenguaje. Solo así se puede determinar si una estructura es sintácticamente válida.

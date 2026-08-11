# Bison — Generador de Analizadores Sintácticos

Sintaxis y Semántica de los Lenguajes

---

## Parte 1 — Introducción a Bison

### 1.1 Dónde estamos parados

El análisis de un lenguaje se hace por etapas. Cada una consume la salida de la anterior:

```
Archivo fuente          "int a = 0xF;"
        ↓                                    ← ANÁLISIS LÉXICO   (Flex, TP2)
Secuencia de tokens     TIPO_DATO IDENTIFICADOR OP_ASIG CTE_HEXA PUNTO_Y_COMA
        ↓                                    ← ANÁLISIS SINTÁCTICO (Bison, TP3)
Estructura sintáctica   SENTENCIA_DECLARACION
        ↓                                    ← ANÁLISIS SEMÁNTICO (rutinas en C)
Tabla de símbolos       a | int | 15
```

Dos herramientas, dos formalismos:

| | Flex | Bison |
|---|---|---|
| Genera | Analizador **léxico** (scanner) | Analizador **sintáctico** (parser) |
| Basado en | Expresiones regulares | Gramáticas independientes de contexto |
| Reconoce | Categorías **léxicas** (tokens) | Categorías **sintácticas** |
| Implementa | Un **AFD** (autómata finito determinístico) | Un **AFP** (autómata finito con pila) |
| Función generada | `yylex()` | `yyparse()` |
| Archivo fuente | `*.l` | `*.y` |
| Archivo generado | `lex.yy.c` | `y.tab.c` + `y.tab.h` |

> **Idea clave:** Flex *lee* el texto; Bison *entiende* la estructura.

---

### 1.2 Cómo se comunican Flex y Bison

Esto es lo que más cuesta al principio, así que vale detenerse.

```
                       ┌──────────┐
                       │  main()  │
                       └────┬─────┘
                            │ invoca
                            ▼
   yyerror()  ◄────── ┌───────────┐
   (errores)          │ yyparse() │  PARSER — implementa un AFP
                      └─────┬─────┘
                            │  "dame el siguiente token"
                            │  ◄── devuelve el Nº de token (0 = EOF)
                            ▼
                      ┌───────────┐                    ┌──────────────┐
                      │  yylex()  │ ◄───────────────── │   Archivo    │
                      └───────────┘  lee de a un       │   fuente     │
                       SCANNER — AFD  carácter         └──────────────┘
                            │
                            │ escribe el valor semántico
                            ▼
                      ┌───────────┐
                      │  yylval   │  ← variable GLOBAL compartida
                      └───────────┘
                            ▲
                            │ lo lee el parser en las acciones
```

Puntos a retener:

1. **El parser manda.** `yyparse()` pide los tokens **de a uno**, a medida que los necesita. El scanner no procesa todo el archivo de golpe.
2. `yylex()` devuelve un **entero**: el número que identifica la categoría léxica. Devolver `0` significa fin de archivo.
3. El **valor** asociado al token (el número que se leyó, la cadena del identificador) no viaja por el `return`: se deja en **`yylval`**, una variable global compartida entre ambos.
4. No todo token necesita valor. El token `'+'` no lleva nada; `IDENTIFICADOR` sí.
5. `yyerror()` la define el usuario y la invoca Bison para reportar errores.

**¿Y cómo sabe el scanner qué número tiene cada token?** Bison genera, además del parser, un archivo de cabecera `*.tab.h` con el `typedef union` de `YYSTYPE` y un `#define` por cada token:

```c
typedef union { char* cadena; int numero; } YYSTYPE;
extern YYSTYPE yylval;

#define SI       257
#define ENTONCES 258
#define ID       259
#define NUM      260
```

Por eso el `.l` **debe** incluirlo:

```c
%{
#include "parser.tab.h"
%}
```

Ese archivo es el **nexo** entre ambos: le permite al scanner saber qué nombre y qué número tiene cada token, y qué campo de `yylval` le corresponde. Es lo que garantiza que el `.l` y el `.y` manejen los mismos nombres de tokens.

Además de `yylval` existe **`yylloc`**, una estructura con la ubicación del token (`first_line`, `first_column`, `last_line`, `last_column`). Es de Bison, no de Flex, y se activa con la declaración `%locations`.

---

### 1.3 Estructura de un archivo `.y`

Tres secciones separadas por `%%`, igual que en Flex:

```bison
/* 1. PRÓLOGO — código C copiado tal cual al parser generado */
%{
#include <stdio.h>
extern int yylex(void);
void yyerror(const char*);
%}

/* 2. DECLARACIONES de Bison: %union, %token, %type, precedencias, %start */
%union { ... }
%token <campo> NOMBRE
%left '+' '-'
%start axioma

%%
/* 3. REGLAS de la gramática, con acciones en C opcionales */
noTerminal
    : simb1 simb2 ... simbN   { /* acción */ }
    | otraParteDerecha        { /* acción */ }
    ;
%%

/* 4. EPÍLOGO — main(), yyerror(), rutinas semánticas */
```

Formato de las reglas:

```bison
simboloNoTerminal
    : simb1 simb2 … simbM   { acción }
    | parteDerecha2         { acción }   /* alternativas con | */
    | /* vacío */                        /* producción lambda: se comenta por claridad */
    ;
```

Cada símbolo de la parte derecha es un **no terminal** o un **terminal** (token). Por convención: **tokens en MAYÚSCULAS**, no terminales en minúsculas.

---

### 1.4 Las declaraciones, una por una

#### `%union` — los tipos de los valores semánticos

Por defecto `yylval` es `int`. Pero un identificador necesita una cadena y una constante entera necesita un `int`: son tipos distintos. `%union` declara indirectamente una `union` de C con un campo por cada tipo posible.

```bison
%union {
    char*  cadena;
    int    numero;
}
```

Con eso, el scanner escribe `yylval.cadena = ...` o `yylval.numero = ...` según el caso.

> No hace falta un campo por token. Varios tokens comparten campo, y los que no llevan valor (como un paréntesis) no usan ninguno.

#### `%token` — los terminales de la gramática

```bison
%token NOMBRE_TOKEN                  /* forma simple, sin valor asociado */
%token <campo_union> NOMBRE_TOKEN    /* forma cualificada: usa ese campo de la unión */
```

Reglas prácticas:

- Se pueden **agrupar en una línea** si comparten tipo: `%token <cadena> IDENTIFICADOR PALABRA_RESERVADA`.
- Los tokens de **un solo carácter no se declaran**: ya están declarados implícitamente con su valor ASCII. Desde Flex se devuelven con `return '+';` o `return yytext[0];`.
- Bison asigna a los tokens de usuario números **desde 258**. El token `error` vale 256.
- Operadores como `++`, `>=` o `&&` **sí** hay que declararlos: no son caracteres simples.

#### `%type` — los tipos de los no terminales

Los no terminales también almacenan valores, del mismo modo que los tokens. Se les asigna un campo de la unión con la misma sintaxis que `%token`:

```bison
%type <campo_union> nombre_no_terminal
```

Si un no terminal nunca recibe un valor a través de `$$`, no hace falta declararlo.

#### `%left` / `%right` — asociatividad y precedencia

```bison
%left  '+' '-'
%left  '*' '/'
%right '^'
```

Dos cosas al mismo tiempo:

- **Asociatividad**: `%left` a izquierda, `%right` a derecha.
- **Precedencia**: queda determinada por el **orden de declaración**, de **menor a mayor**. En el ejemplo, `+` y `-` tienen la misma precedencia y menor que `*` y `/`.

⚠️ La exponenciación es asociativa a **derecha**: con `%left '^'`, `2^3^2` daría `(2^3)^2 = 64` en vez de `2^(3^2) = 512`.

Sin estas declaraciones, una gramática como `exp: exp '+' exp` es **ambigua** y genera conflictos *shift/reduce*. Bison los resuelve por defecto haciendo *shift*, o sea asociando a derecha: `3-1-1` se evaluaría como `3-(1-1)`.

#### `%start` — el axioma

```bison
%start input
```

Declara el axioma de la gramática. Si se omite, Bison asume que es el no terminal de la **primera regla**.

---

### 1.5 Pseudovariables: `$$`, `$1`, `$2`…

Dentro de las acciones se accede a los valores semánticos con pseudovariables:

- **`$$`** — el valor del símbolo de la **izquierda** de la producción (lo que la regla *produce*).
- **`$N`** — el valor del símbolo que ocupa la **posición N** de la parte derecha, según el orden de aparición (ordinal).

```bison
exp
    : exp '+' exp   { $$ = $1 + $3; }
    ;
/*     ↑    ↑   ↑
      $1   $2  $3        ($2 es el '+', no se usa)  */
```

Se llaman *pseudo*variables porque **existen solo mientras se ejecuta esa acción**: no se pueden referenciar desde afuera de la regla.

Si el símbolo tiene tipo declarado con `%token <campo>` o `%type <campo>`, alcanza con `$$` y `$1`. Si no lo tiene, hay que indicar el campo explícitamente:

```bison
$<nombre_campo_union>N      /* por ejemplo: $<cadena>1 */
```

En paralelo, `@N` y `@$` dan acceso a la **ubicación** (`@1.first_line`, `@1.first_column`) cuando está activo `%locations`.

⚠️ **Cuidado con guardar punteros a `$N`.** Apuntan a la pila de valores semánticos de Bison, que se reutiliza en las reducciones siguientes. Si necesitás conservar el dato, **copialo**.

#### Acciones a mitad de regla

Una acción puede ir en el medio de la parte derecha, para ejecutar código *antes* de terminar de reconocer la producción:

```bison
sentencia: TIPO_DATO {guardar($1);} listaIdentificadores ';' {…}
/*            $1          $2                $3                $4   */
```

⚠️ La acción intermedia **cuenta como un símbolo** y corre la numeración: `listaIdentificadores` es `$3`, no `$2`.

---

### 1.6 Herramientas de diagnóstico

#### El archivo `.output` (`bison -v`)

Es la radiografía del autómata. Contiene:

**Gramática numerada.** La regla 0 es siempre `$accept: input $end` y la agrega Bison; `$end` es el token de fin de archivo, con valor 0. La regla 0 no se reduce hasta llegar al EOF.

```
0 $accept: input $end
1 input: /* vacío */
2      | input line
5 exp: NUM
6    | exp exp '+'
```

**Terminales y no terminales**, con las reglas donde aparecen. Los caracteres simples muestran su valor ASCII entre paréntesis:

```
$end (0) 0        '+' (43) 6        error (256)       NUM (258) 5
```

**Los estados**, con sus acciones:

```
estado 1
    0 $accept: input . $end
    2 input: input . line

    $end   desplazar e ir al estado 2       ← TERMINALES: consumen token
    NUM    desplazar e ir al estado 3
    line   ir al estado 5                   ← NO TERMINALES: no consumen token
    exp    ir al estado 6

    $default  reduce usando la regla 6 (exp)
```

- **desplazar** (*shift*): se consume el token y se transita de estado.
- **ir al estado** sin desplazar: ocurre al derivar un no terminal desde otro no terminal.
- **reduce**: se reemplaza la parte derecha de una producción por su lado izquierdo, ejecutando la acción en C asociada.

#### Modo debug

Compilando con `YYDEBUG` y poniendo `yydebug = 1;` en el `main`, el parser narra lo que hace:

```
Starting parse
Entering state 0
Reading a token
Next token is token NUM ()          ← recibió un token del scanner
Shifting token NUM ()               ← lo consumió según la tabla de transición
Entering state 3
Reducing stack by rule 4 (line 38): ← REDUCCIÓN
   $1 = nterm exp ()
   $2 = token '\n' ()
-> $$ = nterm line ()
Stack now 0                          ← reglas pendientes en la pila
```

Se lee de derecha a izquierda: en una reducción vamos del lado derecho al lado izquierdo.

---

### 1.7 Manejo de errores

Bison tiene un token predefinido llamado **`error`** (valor 256). **No hay que declararlo con `%token`.** Se usa como símbolo dentro de una producción para marcar un punto de sincronización:

```bison
line
    : '\n'
    | exp '\n'    { printf("%g\n", $1); }
    | error '\n'  { yyerrok; }      /* descarta tokens hasta encontrar '\n' */
    ;
```

Cuando aparece un error, el parser descarta símbolos hasta poder desplazar `error` seguido del símbolo de sincronización (acá, el salto de línea) y continúa con la línea siguiente.

- **`yyerrok`** le avisa a Bison que la recuperación terminó. Sin esto, el parser queda en modo de recuperación y **silencia los errores siguientes** hasta desplazar tres tokens.
- **`YYERROR`** provoca un error desde una acción (útil para errores semánticos, como dividir por cero).
- **`YYACCEPT`** / **`YYABORT`** hacen que `yyparse()` retorne inmediatamente con 0 / 1.
- **`%define parse.error verbose`** hace que los mensajes pasados a `yyerror` sean detallados. (La forma vieja, `%error-verbose`, está obsoleta desde Bison 3.0.)

Valores de retorno de `yyparse()`:

| Valor | Significado |
|---|---|
| `0` | Análisis exitoso (fin de archivo, o invocación de `YYACCEPT`) |
| `1` | Fallo del que no se pudo recuperar, o invocación de `YYABORT` |
| `2` | Fallo por agotamiento de memoria |

---

## Parte 2 — Ejemplos de código en Bison

Los seis ejemplos están en `Bison/` y cada uno agrega **un** concepto nuevo sobre el anterior. Todos se compilan igual:

```bash
make all
make run-example
```

| # | Ejemplo | Concepto que introduce |
|---|---|---|
| 1 | Calculadora Polaca | Estructura mínima de un `.y`, `%union`, `%type`, `%locations` |
| 2 | Calculadora Infija | Precedencias, gramática ambigua, errores semánticos |
| 3 | Declaración de Variables | Acciones a mitad de regla, recuperación de errores |
| 4 | Validación de Tipos | Valor semántico compuesto (struct en la unión) |
| 5 | Calculadora con tabla de símbolos | La tabla de símbolos (TS) la gestiona el **scanner** |
| 6 | Calculadora con tabla de símbolos | La tabla de símbolos (TS) la gestiona el **parser** |

---

### Ejemplo 1 — Calculadora Polaca

📁 `Bison/1. Calculadora Polaca/src/`

Notación polaca inversa: `3 4 +`. La gramática es **postfija**, así que **no es ambigua** y no necesita ninguna declaración de precedencia. Ideal para ver la estructura sin ruido.

**El scanner deja el valor y devuelve el token:**

```lex
{digito}+ {
        yylloc.last_column += yyleng;
        yylval.long_type = (long) strtoul(yytext, NULL, 0);
        return NUM;
    }

"+" { yylloc.last_column += yyleng; return '+'; }
```

Fijate: `'+'` se devuelve como carácter (no se declara), `NUM` sí es un token declarado y **deja su valor en `yylval`**.

**Las declaraciones del parser:**

```bison
%locations                       /* activa el seguimiento de yylloc */

%union {
	long long_type;
}

%token <long_type> NUM           /* el token NUM usa el campo long_type */
%type  <long_type> exp           /* el no terminal exp también */

%start input
```

**La gramática:**

```bison
input
        : /* producción nula */
        | input line             /* recursividad: acepta muchas líneas */
        ;

line
        : '\n'
        | exp '\n'  { printf("El resultado de la expresion es: %ld\n", $1); YYACCEPT; }
        ;

exp
        : NUM             { $$ = $1; }
        | exp exp '+'     { $$ = $1 + $2; }
        | exp exp '-'     { $$ = $1 - $2; }
        | exp exp '*'     { $$ = $1 * $2; }
        ;
```

El par `input`/`line` es un **patrón idiomático** que se repite en los seis ejemplos: `input` acumula líneas por recursividad y arranca con la producción nula.

En `exp exp '+'`, los operandos son `$1` y `$2` porque el operador está al final. Comparalo con el ejemplo 2, donde son `$1` y `$3`.

**Error semántico con `YYERROR`:**

```bison
| exp exp '/'     {
                if($2 == 0)
                {
                        fprintf(stderr, "Bison: %d:%d: Error semantico: No se puede dividir por 0\n",
                                @1.first_line, @1.first_column);
                        YYERROR;
                }
                else $$ = $1 / $2;
        }
```

Acá se ve para qué sirve `%locations`: `@1` da la ubicación del primer símbolo, así el mensaje indica **línea y columna**.

---

### Ejemplo 2 — Calculadora Infija

📁 `Bison/2. Calculadora Infija/src/`

Ahora `3 + 4 * 2`. La notación infija **sí** es ambigua: hay que decirle a Bison cómo desambiguar.

**Precedencias — el corazón del ejemplo:**

```bison
%left  '+' '-'      /* menor precedencia */
%left  '*' '/'
%left  NEG          /* menos unario */
%right '^'          /* mayor precedencia, asociativo a DERECHA */
```

Tres cosas para señalar:

1. El orden va de **menor a mayor** precedencia.
2. `'^'` es `%right`: `2^3^2` debe ser `2^(3^2) = 512`.
3. **`NEG` es un token ficticio.** No lo devuelve nunca el scanner: existe solo para darle precedencia propia al menos unario, que no puede tener la misma que el `-` binario.

```bison
| '-' exp %prec NEG   { $$ = -$2; }
```

`%prec NEG` le dice a la regla: "usá la precedencia de `NEG`, no la del `'-'` que aparece en tu parte derecha".

**Dos campos en la unión, dos tokens numéricos:**

```bison
%union {
	int int_type;
        double double_type;
}

%token <double_type> NUM         /* constantes reales */
%token <int_type>    ENTERO      /* octales y hexadecimales */
%type  <double_type> exp
```

```bison
exp
        : NUM             { $$ = $1; }
	| ENTERO	  { $$ = $<int_type>1; }
```

⚠️ Ojo con la segunda línea. `exp` es `double_type`, así que `$$` no necesita calificarse. Pero `ENTERO` es `int_type`, y como el tipo de `$1` **no coincide** con el de la regla, hay que escribir `$<int_type>1` explícitamente. Es el caso típico donde la forma `$<campo>N` es obligatoria.

**Recuperación de errores:**

```bison
line
        : '\n'
        | exp '\n'   { printf("El resultado de la expresion es: %g \n\n", $1); menu(); }
        | error '\n' { printf("\n"); menu(); yyerrok; }
        ;
```

Una expresión mal formada no aborta el programa: se descarta la línea y se sigue con la siguiente.

---

### Ejemplo 3 — Declaración de Variables

📁 `Bison/3. Declaración de Variables/src/`

Reconoce sentencias como `int a, b = 5, c;`. Es el primero que hace algo más que calcular: **acumula información** a lo largo de la producción.

**El problema y su solución — acción a mitad de regla:**

```bison
%code {
char tipo[LARGO_CADENA];      /* arreglo global: la memoria ya está reservada */
}

%%

sentenciaDeclaracion:
    TIPO_DATO {strcpy(tipo,$1);} listaIdentificadores ';' {…}
/*     $1           $2                    $3               $4  */
```

El tipo de dato se lee **al principio**, pero se necesita **después**, al procesar cada identificador de la lista. La acción intermedia lo guarda en una variable global apenas se reconoce `TIPO_DATO`.

Dos advertencias:

1. La acción intermedia **ocupa una posición**: `listaIdentificadores` es `$3`.
2. Se hace **`strcpy`**, no `tipo = $1`. Guardar un puntero a `$1` sería un error: apunta al slot de la pila de valores semánticos, que se reutiliza en las reducciones siguientes.

Como `tipo` es un **arreglo** y no un puntero, no hay que pedir memoria: los 30 bytes quedan reservados al compilar. Con `char* tipo;` habría que hacer `strdup` y después `free`. Y el `strcpy` es seguro sin verificar longitudes porque `$1` es el campo `cadena` de la unión, un `char[LARGO_CADENA]` que el scanner ya trunca.

**Lista recursiva:**

```bison
listaIdentificadores: 	identificadorA
			| identificadorA ',' listaIdentificadores
;
```

**Errores a dos niveles:**

```bison
line:     '\n'
        | sentenciaDeclaracion '\n'
        | error '\n' {printf("Falta tipo de dato \n"); … yyerrok;}   /* nivel LÍNEA */
;

identificadorA:	  IDENTIFICADOR {…}
		| IDENTIFICADOR '=' expresion {…}
		| error {…}                                          /* nivel SÍMBOLO */
;
```

El `error` interno atrapa un identificador mal formado y sigue con el resto de la lista. El `error` de `line` es la red de contención: si la recuperación fina falla, descarta la línea entera.

---

### Ejemplo 4 — Validación de Tipos

📁 `Bison/4. Validación de Tipos/src/`

Evalúa expresiones **verificando que los operandos sean del mismo tipo**. Introduce la idea de que un valor semántico puede ser **compuesto**.

**Un struct dentro de la unión:**

```bison
%union {
    struct yylval_struct
    {
        int   tipo;            /* qué es */
        int   valor_entero;    /* su valor si es entero */
        float valor_real;      /* su valor si es real */
    } mystruct;
}

%token <mystruct> NUMERO_ENTERO
%token <mystruct> NUMERO_REAL
%type  <mystruct> expresion
```

Hasta acá cada símbolo cargaba **un** dato. Ahora carga un **par (tipo, valor)**: es el germen de lo que en un compilador real sería una entrada de la tabla de símbolos.

**El scanner marca el tipo:**

```lex
[0-9]+	       { yylval.mystruct.valor_entero = atoi(yytext);
                 yylval.mystruct.tipo = TIPO_ENTERO;  return NUMERO_ENTERO; }
[0-9]+\.[0-9]+ { yylval.mystruct.valor_real  = atof(yytext);
                 yylval.mystruct.tipo = TIPO_REAL;    return NUMERO_REAL;   }
```

**La regla verifica y propaga:**

```bison
| expresion '+' expresion
    {
        if ($1.tipo != $3.tipo)
        {
            printf("Los operandos son de distinto tipo \n");
            $$.tipo = TIPO_ERROR;
        }
        else if ($1.tipo == TIPO_ENTERO)
        {
            $$.tipo = TIPO_ENTERO;
            $$.valor_entero = $1.valor_entero + $3.valor_entero;
        }
        else
        {
            $$.tipo = TIPO_REAL;
            $$.valor_real = $1.valor_real + $3.valor_real;
        }
    }
```

⚠️ **Lo importante es que `$$.tipo` se asigna siempre**, incluso en el caso de error. Si una rama se olvidara de hacerlo, el `$$` reducido quedaría con basura y la regla de más arriba tomaría una decisión equivocada. Este es el bug clásico de las gramáticas con atributos.

**Nota de implementación:** las constantes `TIPO_ENTERO` y `TIPO_REAL` se declaran en un bloque `%code requires`, que Bison copia al `.tab.h`. Así las ve también el scanner.

```bison
%code requires {
	#define TIPO_ERROR  0
	#define TIPO_ENTERO 1
	#define TIPO_REAL   2
}
```

---

### Ejemplos 5 y 6 — Calculadora con Funciones y Variables

📁 `Bison/5. … (TS gestionada por SCANNER)/src/`
📁 `Bison/6. … (TS gestionada por PARSER)/src/`

**La misma calculadora, implementada de dos maneras.** Acepta variables (`x = 3`), funciones (`sqrt(16)`) y expresiones (`x * sin(0.5)`). El punto de la clase es **comparar los dos enfoques**, no la calculadora en sí.

**La tabla de símbolos** (`calc.h`, idéntica en ambos) es una lista enlazada:

```c
typedef struct symrec {
  char *name;
  int   type;              /* TYP_VAR o TYP_FNCT */
  union {
    double var;            /* si es variable: su valor */
    func_t fnctptr;        /* si es función: puntero a la función */
  } value;
  struct symrec *next;
} symrec;

symrec *putsym(const char *, int);   /* alta */
symrec *getsym(const char *);        /* búsqueda */
```

Las funciones matemáticas se precargan en el `main` antes de llamar a `yyparse()`:

```c
struct init const arith_fncts[] = {
  { "atan", atan }, { "cos", cos }, { "exp", exp },
  { "ln", log }, { "sin", sin }, { "sqrt", sqrt }, { 0, 0 },
};
```

#### Enfoque A — la TS la gestiona el SCANNER (ejemplo 5)

El scanner busca el identificador, lo da de alta si no existe, y **devuelve un token distinto según lo que encontró**:

```lex
{ID} { yylval.sval = getsym(yytext);
       if (!yylval.sval) { yylval.sval = putsym(yytext, TYP_VAR); }
       return (yylval.sval->type == TYP_FNCT) ? FNCT : VAR; }
```

```bison
%union {
  double dval;
  struct symrec *sval;     /* el valor semántico es un PUNTERO a la TS */
}
%token <sval> VAR FNCT     /* dos tokens distintos */
```

La gramática queda **limpísima**, porque la ambigüedad ya se resolvió antes de llegar al parser:

```bison
| VAR                { $$ = $1->value.var; }
| VAR '=' exp        { $$ = $3; $1->value.var = $3; }
| FNCT '(' exp ')'   { $$ = (*($1->value.fnctptr))($3); }
```

#### Enfoque B — la TS la gestiona el PARSER (ejemplo 6)

El scanner es tonto: devuelve **un solo token** con el nombre, y nada más.

```lex
{ID} { yylval.idval = strdup(yytext); return ID; }
```

```bison
%union {
  double dval;
  char*  idval;            /* el valor semántico es el NOMBRE */
}
%token <idval> ID          /* un solo token */
```

Toda la lógica se muda a las acciones:

```bison
| ID  { aux = getsym($1);
        if (aux) { $$ = aux->value.var; }
        else { printf("La variable %s no esta declarada…\n", $1); $$ = 0; }
        free($1); }

| ID '=' exp  { aux = getsym($1);
                if (aux) { $$ = (aux->value.var) = $3; }
                else { printf("Se declara una nueva variable %s…\n", $1);
                       aux = putsym($1, TYP_VAR); $$ = (aux->value.var) = $3; }
                free($1); }
```

#### Comparación

| | Ejemplo 5 (scanner) | Ejemplo 6 (parser) |
|---|---|---|
| Tokens para identificadores | Dos: `VAR` y `FNCT` | Uno: `ID` |
| Valor semántico | `symrec*` (puntero a la TS) | `char*` (el nombre) |
| Quién consulta la TS | El scanner | El parser, en las acciones |
| Gramática | Corta y declarativa | Con lógica en las acciones |
| Memoria | El scanner pasa `yytext`; `putsym` copia | El scanner hace `strdup`; **el parser debe hacer `free`** |
| Ventaja | Gramática legible; el conflicto se resuelve antes | El scanner no depende de la semántica |
| Desventaja | El scanner "sabe" de semántica: acoplamiento | Acciones más largas y con manejo de memoria |

> **El enfoque B es el que se acerca más a un compilador real:** el análisis léxico debería ignorar el significado. El enfoque A es la solución clásica del manual de Bison, y sigue siendo válida cuando la distinción es simple.

---

## Referencia rápida

### Directivas

| Directiva | Para qué |
|---|---|
| `%union { … }` | Declara los tipos posibles de los valores semánticos |
| `%token <campo> NOMBRE` | Declara un terminal y su tipo |
| `%type <campo> noTerminal` | Declara el tipo de un no terminal |
| `%left` / `%right` | Asociatividad y precedencia (orden: de menor a mayor) |
| `%prec TOKEN` | Fuerza la precedencia de una regla |
| `%start noTerminal` | Declara el axioma |
| `%locations` | Activa el seguimiento de `yylloc` |
| `%define parse.error verbose` | Mensajes de error detallados |
| `%code requires { … }` | Código copiado al `.tab.h` (lo ve el scanner) |

### Variables y macros

| Nombre | Qué es |
|---|---|
| `yylval` | Valor semántico del token; global compartida Flex↔Bison |
| `yylloc` | Ubicación del token (línea/columna); requiere `%locations` |
| `yytext` / `yyleng` | Texto y longitud del lexema (Flex) |
| `$$`, `$N` | Pseudovariables de valor semántico |
| `@$`, `@N` | Pseudovariables de ubicación |
| `error` | Token predefinido de sincronización (valor 256) |
| `yyerrok` | Da por terminada la recuperación de errores |
| `YYERROR` | Provoca un error desde una acción |
| `YYACCEPT` / `YYABORT` | Retorno inmediato de `yyparse()` con 0 / 1 |

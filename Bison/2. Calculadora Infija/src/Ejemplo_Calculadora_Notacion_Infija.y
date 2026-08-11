/* Calculadora de notación infija */

/* Inicio de la seccion de prólogo (declaraciones y definiciones de C y directivas del preprocesador) */
%{
#include <stdio.h>
#include <math.h>

#include "general.h"

	/* Declaración de la funcion yylex del analizador léxico, necesaria para que la funcion yyparse del analizador sintáctico pueda invocarla cada vez que solicite un nuevo token */
extern int yylex(void);
	/* Declaracion de la función yyerror para reportar errores, necesaria para que la función yyparse del analizador sintáctico pueda invocarla para reportar un error */
void yyerror(const char*);

void menu(void);
%}
/* Fin de la sección de prólogo (declaraciones y definiciones de C y directivas del preprocesador) */

/* Inicio de la sección de declaraciones de Bison */

	/* Para requerir una versión mínima de Bison para procesar la gramática */
/* %require "2.4.1" */

	/* Para requirle a Bison que describa más detalladamente los mensajes de error al invocar a yyerror */
%define parse.error verbose
	/* Nota: la forma antigua de esta directiva era %error-verbose, obsoleta a partir de Bison v3.0 */

	/* Para activar el seguimiento de las ubicaciones de los tokens (número de linea, número de columna) */
%locations

	/* Para especificar la colección completa de posibles tipos de datos para los valores semánticos */
%union {
	int int_type;
        double double_type;
}

        /* */
%token <double_type> NUM
%token <int_type> ENTERO

        /* */
%type <double_type> exp

        /* Precedencia de MENOR a MAYOR segun el orden de declaracion.
           '^' es asociativo a DERECHA: 2^3^2 debe ser 2^(3^2) = 512, no (2^3)^2 = 64.
           NEG es un token ficticio que solo existe para darle al menos unario una
           precedencia mayor que la del '-' binario (ver la regla '-' exp %prec NEG).
           Los parentesis NO son operadores: no necesitan declaracion de precedencia. */
%left '+' '-'
%left '*' '/'
%left NEG
%right '^'

	/* Para especificar el no-terminal de inicio de la gramática (el axioma). Si esto se omitiera, se asumiría que es el no-terminal de la primera regla */
%start input

/* Fin de la sección de declaraciones de Bison */

/* Inicio de la sección de reglas gramaticales */
%%
input
        : /* intencionalmente se deja el resto de esta línea vacía: es la producción nula */
        | input line
        ;

line
        : '\n'
        | exp '\n'  { printf("El resultado de la expresion es: %g \n\n", $1); menu(); }
        | error '\n' { printf("\n"); menu(); yyerrok; }
        ;

	/* Como 'exp' esta declarado con %type <double_type>, alcanza con escribir
	   $$ y $1: la forma $<campo>N solo hace falta cuando el simbolo NO tiene
	   tipo declarado (como ENTERO, que aqui se lee por su propio campo). */
exp
        : NUM             { $$ = $1; }
	| ENTERO	  { $$ = $<int_type>1; }
        | exp '+' exp     { $$ = $1 + $3; }
        | exp '-' exp     { $$ = $1 - $3; }
        | exp '*' exp     { $$ = $1 * $3; }
        | exp '/' exp     {
                        if($3 == 0)
                        {
                                fprintf(stderr, "Bison: %d:%d: Error semantico: No se puede dividir por 0\n", @1.first_line, @1.first_column);
                                YYERROR;
                        }
                        else $$ = $1 / $3;
                }
        | exp '^' exp   {
                        if(($1 == 0) && ($3 == 0))
                        {
                                fprintf(stderr, "Bison: %d:%d: Error semantico: No se puede realizar 0^0\n", @1.first_line, @1.first_column);
                                YYERROR;
                        }
                        else $$ = pow ($1, $3);
                }
	| '-' exp %prec NEG	  { $$ = -$2; }
	| '(' exp ')'     { $$ = $2; }
        ;

%%
/* Fin de la sección de reglas gramaticales */

/* Inicio de la sección de epílogo (código de usuario) */

int main(void)
{
        inicializarUbicacion();

        #if YYDEBUG
                yydebug = 1;
        #endif

        menu();
        yyparse();

        pausa();
        return 0;
}

        /* Definición de la funcion yyerror para reportar errores, necesaria para que la funcion yyparse del analizador sintáctico pueda invocarla para reportar un error */
void yyerror(const char* literalCadena)
{
        fprintf(stderr, "Bison: %d:%d: %s\n", yylloc.first_line, yylloc.first_column, literalCadena);
}

void menu(void)
{
        printf("Ingrese una expresion aritmetica para resolver (constantes reales, octales o hexadecimales):\n");
}

/* Fin de la sección de epílogo (código de usuario) */
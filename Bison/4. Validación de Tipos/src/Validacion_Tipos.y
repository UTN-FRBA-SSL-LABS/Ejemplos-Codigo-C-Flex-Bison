%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int yylex();

int yywrap() {
	return 1;
}

void yyerror (const char *s) {
   fprintf (stderr, "%s\n", s);
}

%}

	/* Para que Bison describa mas detalladamente los mensajes de error */
%define parse.error verbose

	/* El codigo de %code requires se copia al archivo de cabecera generado
	   (*.tab.h), de modo que el analizador lexico tambien vea estas constantes */
%code requires {
	#define TIPO_ERROR  0
	#define TIPO_ENTERO 1
	#define TIPO_REAL   2
}

%union {

    struct yylval_struct
    {
        int tipo;
        int valor_entero;
        float valor_real;
    } mystruct;

}

%token <mystruct> NUMERO_ENTERO
%token <mystruct> NUMERO_REAL

%type <mystruct> expresion

	/* Sin estas declaraciones la gramatica es ambigua: 'expresion OP expresion'
	   genera conflictos shift/reduce que Bison resuelve por shift, es decir,
	   asociando a derecha (3-1-1 se evaluaria como 3-(1-1)). */
%left '+' '-'
%left '*'

%% /* A continuacion las reglas gramaticales y las acciones */

input
    : /* vacio */
    | input line
    ;

line
    : '\n'
    | expresion '\n'
        {
            if ($1.tipo == TIPO_ENTERO)
            {
                printf ("El resultado de la expresion es: %d \n", $1.valor_entero);
            }
            else if ($1.tipo == TIPO_REAL)
            {
                printf("El resultado de la expresion es: %g \n", $1.valor_real);
            }
            else
            {
                printf("La expresion no pudo evaluarse \n");
            }
        }
    ;

expresion
    : NUMERO_ENTERO { $$ = $1; }
    | NUMERO_REAL   { $$ = $1; }
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
    | expresion '-' expresion
        {
            if ($1.tipo != $3.tipo)
            {
                printf("Los operandos son de distinto tipo \n");
                $$.tipo = TIPO_ERROR;
            }
            else if ($1.tipo == TIPO_ENTERO)
            {
                $$.tipo = TIPO_ENTERO;
                $$.valor_entero = $1.valor_entero - $3.valor_entero;
            }
            else
            {
                $$.tipo = TIPO_REAL;
                $$.valor_real = $1.valor_real - $3.valor_real;
            }
        }
    | expresion '*' expresion
        {
            if ($1.tipo != $3.tipo)
            {
                printf("Los operandos son de distinto tipo \n");
                $$.tipo = TIPO_ERROR;
            }
            else if ($1.tipo == TIPO_ENTERO)
            {
                $$.tipo = TIPO_ENTERO;
                $$.valor_entero = $1.valor_entero * $3.valor_entero;
            }
            else
            {
                $$.tipo = TIPO_REAL;
                $$.valor_real = $1.valor_real * $3.valor_real;
            }
        }
    ;

%%

int main(void) {
    #if YYDEBUG
      yydebug = 1;
    #endif

	yyparse();
}

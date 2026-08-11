/* Ejemplo para detección de declaración de variables */

%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int yylex();
int yywrap(){
	return(1);
}

void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
}

%}

	/* Para que Bison describa mas detalladamente los mensajes de error */
%define parse.error verbose

	/* El codigo de %code requires se copia al archivo de cabecera generado
	   (*.tab.h), de modo que el analizador lexico tambien vea esta constante */
%code requires {
	#define LARGO_CADENA 30
}

%union {
char cadena[LARGO_CADENA];
int entero;
}

	/* %code se emite en el *.tab.c despues de la definicion de YYSTYPE,
	   asi que aqui ya podemos usar LARGO_CADENA */
%code {
int flag_error=0;
int contador=0;

	/* IMPORTANTE: 'tipo' es un buffer propio, NO un puntero.
	   Guardar aqui un 'char*' apuntando a $1 seria un error: ese puntero apunta
	   al slot de la pila de valores semanticos de Bison, que se reutiliza en las
	   reducciones siguientes. */
char tipo[LARGO_CADENA];
}

%token <entero> NUM
%token <cadena> IDENTIFICADOR
%token <cadena> TIPO_DATO
	/* 'error' es un token predefinido de Bison: no debe declararse con %token */

%type <cadena> identificadorA
%type <entero> expresion

%% /* A continuacion las reglas gramaticales y las acciones */

input:    /* vacio */
        | input line
;

line:     '\n'
        | sentenciaDeclaracion '\n'
	/* Recuperacion de errores a nivel de LINEA: el parser descarta tokens hasta
	   poder sincronizar con el '\n' y sigue con la linea siguiente. Es el mismo
	   patron que usan los ejemplos 2, 5 y 6. yyerrok le avisa a Bison que la
	   recuperacion termino, para que vuelva a reportar errores posteriores. */
        | error '\n' {printf("Falta tipo de dato \n");contador=0;flag_error=0;yyerrok;}
;

sentenciaDeclaracion: 	TIPO_DATO {strcpy(tipo,$1);} listaIdentificadores ';' {if(flag_error==0){printf("Se han declarado %d variables de tipo %s \n",contador,$1);};contador=0;flag_error=0;}
;

listaIdentificadores: 	identificadorA
						| identificadorA ',' listaIdentificadores
;

identificadorA:		  	IDENTIFICADOR {printf("Se declara el identificador %s de tipo %s \n",$1,tipo);contador++;}
						| IDENTIFICADOR '=' expresion {if(flag_error==0){printf("Se declara el identificador %s de tipo %s y se le asigna el valor %d \n",$1,tipo,$3);};contador++;}
						| error {if(flag_error==0){printf("Falta identificador \n");flag_error=1;};}
;

expresion:				NUM {$$=$1;}
						| error {flag_error=1;printf("Valor no reconocido para asignar \n");}
;

%%

int main ()
{
    #if YYDEBUG
      yydebug = 1;
    #endif

	yyparse ();
}

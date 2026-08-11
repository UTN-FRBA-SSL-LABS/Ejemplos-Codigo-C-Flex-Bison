%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc.h"
#include "mfcalc.tab.h"

%}

NUM [0-9]
ID [A-Za-z_][A-Za-z0-9_]*

%%

{NUM}+("."{NUM}*)? { yylval.dval = atof(yytext); return NUM; }

"exit" { printf("Hasta la proxima. Se cierra la calculadora\n"); exit(0); }

	/* IMPORTANTE: la accion debe empezar en la MISMA linea que el patron.
	   Si se la escribe en la linea siguiente, Flex toma el patron con accion
	   vacia y copia el bloque indentado como codigo suelto dentro de yylex(). */
	/* En este ejemplo es el SCANNER el que gestiona la tabla de simbolos:
	   busca el identificador, lo da de alta si no existe, y devuelve un token
	   distinto (VAR o FNCT) segun lo que encontro. */
{ID} { yylval.sval = getsym(yytext); if (!yylval.sval) { yylval.sval = putsym(yytext, TYP_VAR); } return (yylval.sval->type == TYP_FNCT) ? FNCT : VAR; }

	/* Ojo con los rangos: [+-/*...] se interpreta como el rango ASCII '+'..'/',
	   que ademas incluye ',' y '.'. Poniendo el '-' primero se lo toma literal. */
[-+*/=:\n()^] return yytext[0];

[ \t]+

%%

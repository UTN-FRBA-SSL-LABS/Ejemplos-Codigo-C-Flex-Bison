%{
#include "Ejemplo_DeclaracionVariables.tab.h"
#include <stdio.h>
#include <stdlib.h>	/* necesario para atoi() */
#include <string.h>
%}


%%

[0-9]+	{yylval.entero=atoi(yytext); return NUM;}
int|char|float|double {strncpy(yylval.cadena,yytext,LARGO_CADENA-1); yylval.cadena[LARGO_CADENA-1]='\0'; return TIPO_DATO;}
[A-Za-z_][A-Za-z_0-9]* {strncpy(yylval.cadena,yytext,LARGO_CADENA-1); yylval.cadena[LARGO_CADENA-1]='\0'; return IDENTIFICADOR;}
","     {return ',';}
"="     {return '=';}
";"     {return ';';}
\n	{return '\n';}
[\t ]
.

%%

%{

#include <stdio.h>
#include <stdlib.h>	/* necesario para atoi() y atof() */
#include <string.h>

#include "Validacion_Tipos.tab.h"

%}

%%

	/* Flex siempre elige el emparejamiento mas largo, asi que "3.14" entra por
	   la regla del real aunque la del entero este declarada antes. */
[0-9]+	{ yylval.mystruct.valor_entero = atoi(yytext); yylval.mystruct.tipo = TIPO_ENTERO; return NUMERO_ENTERO; }
[0-9]+\.[0-9]+ { yylval.mystruct.valor_real = atof(yytext); yylval.mystruct.tipo = TIPO_REAL; return NUMERO_REAL; }
"+"     { return '+'; }
"-"     { return '-'; }
"*"     { return '*'; }
\n	    { return '\n'; }
[\t ]
.

%%

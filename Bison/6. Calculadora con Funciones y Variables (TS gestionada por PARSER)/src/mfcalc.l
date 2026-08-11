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

{NUM}+("."{NUM}*)?	{ yylval.dval = atof(yytext); return NUM;	}

"exit"				{ printf("Hasta la proxima. Se cierra la calculadora\n"); exit(0);           	}

{ID}				{ yylval.idval=strdup(yytext); return ID;}

	/* Ojo con los rangos: [+-/*...] se interpreta como el rango ASCII '+'..'/',
	   que ademas incluye ',' y '.'. Poniendo el '-' primero se lo toma literal. */
[-+*/=:\n()^] 		return yytext[0];
     
[ \t]+

%%

// Reconoce la ER (AB)*CB*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//#include "definiciones.h"

#define CANT_ESTADOS 4
#define CANT_COLUMNAS 4

// Definición de los estados del AFD
typedef enum e_Estado {
    Q0,
    Q1,
    Q2,
    Q3
} e_Estado;

typedef enum e_Columna {
    A,
    B,
    C,
    Otro
} e_Columna;

#define ESTADO_INICIAL Q0
#define ESTADO_FINAL Q2
#define CENTINELA ','

// Definición de la tabla de transiciones
e_Estado tabla_transiciones[CANT_ESTADOS][CANT_COLUMNAS] = {
         /*  A  */  /*  B  */  /*  C  */  /* Otro */
/* Q0 */ {   Q1    ,    Q3    ,    Q2    ,    Q3   },
/* Q1 */ {   Q3    ,    Q0    ,    Q3    ,    Q3   },
/* Q2 */ {   Q3    ,    Q2    ,    Q3    ,    Q3   },
/* Q3 */ {   Q3    ,    Q3    ,    Q3    ,    Q3   }
};

e_Columna caracter_a_columna(int c) {
    switch (c) {
        case 'A':
            return A;

        case 'B':
            return B;

        case 'C':
            return C;
        
        default:
            return Otro;
    }
}

void fin_de_cadena(e_Estado estado, FILE *output) {
    if (estado == ESTADO_FINAL) {
        fprintf(output, " Aceptada\n");
    } else {
        fprintf(output, " Rechazada\n");
    }
}

// Lee caracter a caracter y aplica la funcion de transición hasta encontrar un centinela o EOF, después empieza de nuevo con el siguiente lexema
void scanner(FILE *entrada, FILE *salida) {
    int c;
    e_Estado estado_actual = ESTADO_INICIAL;
    while((c = fgetc(entrada)) != EOF) {
        if (c != CENTINELA) {
            fputc(c, salida);
            estado_actual = tabla_transiciones[estado_actual][caracter_a_columna(c)];
        }
        else {
            fin_de_cadena(estado_actual, salida);
            estado_actual = ESTADO_INICIAL;
        }
    }
    fin_de_cadena(estado_actual, salida);
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Uso: %s <ARCHIVO_ENTRADA> [...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *entrada = fopen(argv[1], "r");
    if(entrada == NULL) {
        printf("%s: Error al intentar abrir el archivo: %s\n", argv[1], strerror(errno));
        return EXIT_FAILURE;
    }

    scanner(entrada, stdout);

    fclose(entrada);
    return EXIT_SUCCESS;
}

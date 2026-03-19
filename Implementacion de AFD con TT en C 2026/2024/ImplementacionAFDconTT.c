#include <stdlib.h>
#include <stdio.h>

#define CANT_ESTADOS 4
#define CANT_SIMBOLOS 3

// Definición de los estados del AFD
typedef enum {
    Q0,
    Q1,
    Q2,
    Q3
} t_estado;

typedef enum {
    A,
    B,
    C
} t_caracter;

#define ESTADO_INICIAL Q0
#define ESTADO_FINAL Q2
#define CENTINELA ','

// Definición de la tabla de transiciones
int tabla_transiciones[CANT_ESTADOS][CANT_SIMBOLOS] = {
    {Q1, Q3, Q2},
    {Q3, Q0, Q3},
    {Q3, Q2, Q3},
    {Q3, Q3, Q3}
};

t_estado char_to_enum(char c){
    switch (c)
    {
    case 'a':
        return A;
        break;

    case 'b':
        return B;
        break;

    case 'c':
        return C;
        break;
    
    default:
        break;
    }
}

// Lee caracter a caracter y aplica la funcion de transición hasta encontrar un centinela o EOF, después empieza de nuevo con el siguiente lexema
void lexer(FILE* input, FILE* output) {
    char c;
    int estado = ESTADO_INICIAL;
    while((c = fgetc(input)) != EOF){
        if(c != CENTINELA){
            fputc(c, output);
            estado = tabla_transiciones[estado][char_to_enum(c)];
        }
        else{
            fputs("    ", output);
            if(estado == ESTADO_FINAL){
                fputs("Acepatda\n", output);
            }
            else{
                 fputs("No Acepatda\n", output);
            }
            estado = ESTADO_INICIAL;
        }
    }
    fputs("    ", output);
    if(estado == ESTADO_FINAL){
                fputs("Acepatda", output);
            }
            else{
                 fputs("No Acepatda", output);
            }
}

int main(int argc, char* argv[]) {

    if(argc < 2) {
        printf("Debe pasarse un nombre de archivo válido como parámetro.\n");
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[1], "r");
    if(file == NULL) {
        printf("Error al intentar abrir el archivo %s.\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    lexer(file, stdout);

    fclose(file);
    return EXIT_SUCCESS;
}

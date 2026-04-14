#include <stdio.h>
#include <stdlib.h>

void cambiar_valor_mal(int variable, int nuevo_valor);
void cambiar_valor_bien(int *variable, int nuevo_valor);

int valorYReferencia() {
    int variable_entera = 10;

    printf("\n(1) variable_entera = %d (en main)\n", variable_entera);

    cambiar_valor_mal(variable_entera, 20);
    printf("(3) variable_entera = %d (en main)\n", variable_entera);

    cambiar_valor_bien(&variable_entera, 30);
    printf("(5) variable_entera = %d (en main)\n", variable_entera);

    return EXIT_SUCCESS;
}

void cambiar_valor_mal(int variable, int nuevo_valor) {
    variable = nuevo_valor;
    printf("(2) variable_entera = %d (en función - paso por valor)\n", variable);
}

void cambiar_valor_bien(int *variable, int nuevo_valor) {
    *variable = nuevo_valor;
    printf("(4) variable_entera = %d (en función - paso por referencia)\n", *variable);
}

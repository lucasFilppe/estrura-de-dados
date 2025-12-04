#include <stdio.h>
#include "crianca.h"

int main() {
    int n;

    printf("Quantas crianças deseja cadastrar? ");
    scanf("%d", &n);

    Crianca **vet = le_Vetor_Criancas(n);

    imprime_Vetor_Criancas(vet, n);

    libera_Vetor_Criancas(vet, n);

    return 0;
}

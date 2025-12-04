#include <stdio.h>
#include <stdlib.h>
#include "pessoa.h"

int main() {
    Pessoa* pessoas = criaVetorPessoas();

    int total = lerPessoas(pessoas);

    if (total == 0) {
        printf("Nenhum dado informado.\n");
        free(pessoas);
        return 0;
    }

    double mSal = mediaSalario(pessoas, total);
    double mFilhos = mediaFilhos(pessoas, total);
    double maior = maiorSalario(pessoas, total);
    double perc = percentualAte1350(pessoas, total);

    printf("\n====== RESULTADOS ======\n");
    printf("Total de pessoas: %d\n", total);
    printf("Media do salario: R$ %.2f\n", mSal);
    printf("Media de numero de filhos: %.2f\n", mFilhos);
    printf("Maior salario: R$ %.2f\n", maior);
    printf("Percentual com salario ate 1350: %.2f%%\n", perc);

    modaSalarios(pessoas, total);

    free(pessoas);
    return 0;
}

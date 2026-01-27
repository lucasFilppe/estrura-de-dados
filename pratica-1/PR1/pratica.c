#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"

int main()
{
    int n = 0;
    Pokemon **p = NULL; // Vetor de ponteiros (matriz dinâmica de Pokémon)

    char nomeTemp[100], tipoTemp[100];
    int pc;

    // Loop de leitura: A condição de parada é o nome "0"
    while (1)
    {
        scanf("%s", nomeTemp);
        if (strcmp(nomeTemp, "0") == 0)
            break;

        scanf("%s %d", tipoTemp, &pc);

        // realloc: Aumenta o tamanho do vetor de ponteiros conforme a necessidade
        // Nota: Em termos de complexidade, muitos reallocs podem ser O(n²) no total [cite: 354]
        p = realloc(p, (n + 1) * sizeof(Pokemon *));
        p[n] = cria_Pokemon(nomeTemp, tipoTemp, pc);
        n++;
    }

    // Chamada das funções de processamento
    maior_Tipo(p, n);
    nome_Repetido(p, n);

    libera_Memoria(p, n);
    p = NULL; // Boa prática: anula o ponteiro para evitar uso acidental

    return 0;
}
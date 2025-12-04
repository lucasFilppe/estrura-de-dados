#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"

int main()
{
    int n = 0;

    Pokemon **p = NULL;

    char nomeTemp[100], tipoTemp[100];
    int pc;

    while (1)
    {
        scanf("%s", nomeTemp);
        if (strcmp(nomeTemp, "0") == 0)
            break;

        scanf("%s %d", tipoTemp, &pc);

        p = realloc(p, (n + 1) * sizeof(Pokemon *));
        p[n] = cria_Pokemon(nomeTemp, tipoTemp, pc);
        n++;
    }

    printf("\n=== Maior PC por Tipo ===\n");
    maior_Tipo(p, n);

    printf("\n=== Pokémons com nomes repetidos ===\n");
    nome_Repetido(p, n);

    // liberar memória
    for (int i = 0; i < n; i++)
        free(p[i]);
    free(p);
    // liberar memória
    /* for (int i = 0; i < n; i++) {
         free(p[i]->nome);
         free(p[i]->tipo);
         free(p[i]);
     }
     free(p);*/

    return 0;
}
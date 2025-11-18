#include <stdio.h>
#include "aluno.h"
#include <stdlib.h>
#include <string.h>

// Função para criar um novo Pokémon
Pokemon *criarPokemon(char *nome, char *tipo, int pontosDeCombate)
{
    Pokemon *p = (Pokemon *)malloc(sizeof(Pokemon));
    if (p == NULL)
        printf("Erro ao alocar memoria para Pokemon\n");

    strncpy(p->nome, nome, TAM_MAX);
    strncpy(p->tipo, tipo, TAM_MAX);
    p->pontosDeCombate = pontosDeCombate;

    return p;
}

// Função para criar um novo Estoque
Estoque *criarEstoque()
{
    Estoque *e = (Estoque *)malloc(sizeof(Estoque));

    if (e == NULL)
        printf("Erro ao alocar memoria para Estoque\n");

    e->capacidade = 100; // A capacidade pode ser ajustada conforme os casos testes
    e->qtd = 0;          // estoque inicialmente vazio

    // aloca espaço para os pokémons
    e->estoque = (Pokemon *)malloc(e->capacidade * sizeof(Pokemon));
    return e;
}

void adicionarPokemon(Estoque *estoque, Pokemon *pokemon)
{
    if (estoque->qtd < estoque->capacidade)
    {
        estoque->estoque[estoque->qtd] = *pokemon;
        estoque->qtd++;
    }
    else
    {
        printf("Estoque cheio\n");
    }
}
void liberarPokemon(Pokemon *pokemon)
{
    free(pokemon);
}

void liberarEstoque(Estoque *estoque)
{
    if (estoque)
    {
        free(estoque->estoque);
        free(estoque);
    }
}

// Função para ler pokémons até digitar 0
Estoque *lerPokemons()
{
    Estoque *estoque = criarEstoque();
    char nome[TAM_MAX], tipo[TAM_MAX];
    int pc;
    while (1)
    {
        if (scanf("%s", nome) != 1)
            break;
        if (strcmp(nome, "0") == 0)
            break;
        if (scanf("%s %d", tipo, &pc) != 2)
            break;
        Pokemon *p = criarPokemon(nome, tipo, pc);
        adicionarPokemon(estoque, p);
    }
    return estoque;
}

void mostrarMaioresPorTipo(Estoque *estoque) {
    int i, j;

    for (i = 0; i < estoque->qtd; i++) {
        int jaMostrou = 0;

        // Verifica se o tipo já foi mostrado
        for (j = 0; j < i; j++) {
            if (strcmp(estoque->estoque[i].tipo, estoque->estoque[j].tipo) == 0) {
                jaMostrou = 1;
                break;
            }
        }

        if (jaMostrou) continue;

        // Procura o Pokémon com maior PC desse tipo
        int idxMax = i;
        for (j = i + 1; j < estoque->qtd; j++) {
            if (strcmp(estoque->estoque[i].tipo, estoque->estoque[j].tipo) == 0 &&
                estoque->estoque[j].pontosDeCombate > estoque->estoque[idxMax].pontosDeCombate) {
                idxMax = j;
            }
        }

        // Imprime no formato desejado
        printf("%s: %s\n",
               estoque->estoque[i].tipo,
               estoque->estoque[idxMax].nome);
    }

    printf("\n");
}


void mostrarRepetidos(Estoque *estoque)
{
    int i, j;
    int repetido;

    // Percorre cada Pokémon do estoque
    for (i = 0; i < estoque->qtd; i++)
    {
        repetido = 0;

        // Compara o Pokémon atual com os próximos da lista
        for (j = i + 1; j < estoque->qtd; j++)
        {
            // Se nome e tipo forem iguais, é repetido
            if (strcmp(estoque->estoque[i].nome, estoque->estoque[j].nome) == 0 &&
                strcmp(estoque->estoque[i].tipo, estoque->estoque[j].tipo) == 0)
            {
                repetido = 1;
                break; // Não precisa continuar comparando
            }
        }

        // Se encontrou repetição, mostra o Pokémon uma vez
        if (repetido)
            printf("%s\n",estoque->estoque[i].nome);
    }

    printf("\n");
}

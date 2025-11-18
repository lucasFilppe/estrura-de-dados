#ifndef ALUNO_H
#define ALUNO_H
#define TAM_MAX 30
#include <stdio.h>

typedef struct {
    // a criterio do aluno
    char nome[TAM_MAX];
    char tipo[TAM_MAX];
    int pontosDeCombate;

} Pokemon;

typedef struct {
    Pokemon *estoque;
    int qtd;
    int capacidade; // necessário para gerenciar realocação
    // a criterio do aluno
} Estoque;

/*

------------------ Protótipos -------------------
      entrada e retorno a cargo do aluno

*/ 
Pokemon* criarPokemon(char* nome, char* tipo, int pontosDeCombate);
Estoque* criarEstoque();
void adicionarPokemon(Estoque* estoque, Pokemon* pokemon);
void liberarPokemon(Pokemon* pokemon);
void liberarEstoque(Estoque* estoque);
void mostrarMaioresPorTipo(Estoque* estoque);
void mostrarRepetidos(Estoque* estoque);
Estoque* lerPokemons();

#endif

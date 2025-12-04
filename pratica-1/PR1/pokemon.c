#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"

struct pokemon{
  char *nome;
  char *tipo;
  int pontos;
};

Pokemon* cria_Pokemon(char *nome, char *tipo, int pc){
  Pokemon *p = (Pokemon*)malloc(sizeof(Pokemon));
  if(p == NULL){
    printf("Erro ao alocar pokemon\n");
  }
  //colocamos +1 para o '\0'
  p->nome = (char*)malloc(strlen(nome) + 1);
  strcpy(p->nome, nome);

  p->tipo = (char*)malloc(strlen(tipo) + 1);
  strcpy(p->tipo, tipo);

  p->pontos = pc;

  return p;
}

void maior_Tipo(Pokemon **p, int n) {
    int *usado = calloc(n, sizeof(int)); 
    // usado[i] = 1 significa: "este Pokémon já foi agrupado pelo tipo"

    for (int i = 0; i < n; i++) {

        // Se já analisamos este Pokémon antes, pulamos
        if (usado[i]) continue;

        usado[i] = 1; // Marca o Pokémon base do tipo

        int maior = i; // índice do maior PC do tipo

        // Compara com todos os outros
        for (int j = i + 1; j < n; j++) {

            // Mesmo tipo?
            if (strcmp(p[i]->tipo, p[j]->tipo) == 0) {
                usado[j] = 1;

                // Atualiza o maior PC
                if (p[j]->pontos > p[maior]->pontos) {
                    maior = j;
                }
            }
        }

       

        // Sai apenas UM resultado por tipo
        printf("Tipo: %s -> Maior PC: %s (%d)\n",
               p[maior]->tipo, p[maior]->nome, p[maior]->pontos);
    }

    free(usado);
}

void nome_Repetido(Pokemon **p, int n) {
    int *usado = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {

        if (usado[i]) continue;

        int repetiu = 0;

        for (int j = i + 1; j < n; j++) {
            if (strcmp(p[i]->nome, p[j]->nome) == 0) {
                repetiu = 1;
                usado[j] = 1;  // marca os repetidos
            }
        }

        usado[i] = 1;

        if (repetiu) {
            printf("Nome repetido: %s\n", p[i]->nome);
        }
    }

    free(usado);
}




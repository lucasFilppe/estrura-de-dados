#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"

// Definição da Struct: O "esqueleto" do nosso TAD
struct pokemon{
  char *nome;  // Usamos ponteiro para alocar apenas o tamanho necessário na Heap
  char *tipo;
  int pontos;
};

// Construtor do TAD: Aloca memória para a struct e para as strings internas
Pokemon* cria_Pokemon(char *nome, char *tipo, int pc){
  // Alocação dinâmica da estrutura principal na Heap
  Pokemon *p = (Pokemon*)malloc(sizeof(Pokemon));
  if(p == NULL){
    printf("Erro ao alocar pokemon\n");
    return NULL;
  }
  
  // Alocação exata para a string (+1 para o caractere nulo '\0') 
  p->nome = (char*)malloc(strlen(nome) + 1);
  strcpy(p->nome, nome);

  p->tipo = (char*)malloc(strlen(tipo) + 1);
  strcpy(p->tipo, tipo);

  p->pontos = pc;

  return p;
}

// Algoritmo de busca com complexidade Quadrática Θ(n²) [cite: 361]
void maior_Tipo(Pokemon **p, int n) {
    // Vetor auxiliar para evitar processar o mesmo tipo várias vezes
    int *usado = calloc(n, sizeof(int)); 

    for (int i = 0; i < n; i++) {
        if (usado[i]) continue; // Se o Pokémon já foi agrupado, pula

        usado[i] = 1;
        int maior = i; // Assume que o primeiro do tipo é o maior

        // Loop interno para comparar com os demais: Padrão clássico de busca [cite: 355, 356]
        for (int j = i + 1; j < n; j++) {
            if (strcmp(p[i]->tipo, p[j]->tipo) == 0) {
                usado[j] = 1; // Marca outros Pokémon do mesmo tipo
                if (p[j]->pontos > p[maior]->pontos) {
                    maior = j;
                }
            }
        }

        printf("Tipo: %s -> Maior PC: %s (%d)\n",
               p[maior]->tipo, p[maior]->nome, p[maior]->pontos);
    }
    free(usado); // Libera o vetor auxiliar
}

void nome_Repetido(Pokemon **p, int n) {
    // 1. Aloca um vetor auxiliar preenchido com zeros (calloc)
    // 0 = não verificado, 1 = já verificado/impresso
    int *usado = (int*)calloc(n, sizeof(int));
    
    if (usado == NULL) {
        printf("Erro de alocação auxiliar.\n");
        return;
    }

    printf("\n=== Pokémons com nomes repetidos ===\n");
    int encontrouAlgum = 0; // Variável para controlar se imprimimos algo

    for (int i = 0; i < n; i++) {
        // Se este Pokémon já foi marcado como "usado" (cópia de um anterior), pula
        if (usado[i] == 1) continue;

        int temRepeticao = 0; // Flag para saber se este específico tem cópias

        // Loop interno: procura duplicatas deste nome daqui para frente
        for (int j = i + 1; j < n; j++) {
            // Compara as strings
            if (strcmp(p[i]->nome, p[j]->nome) == 0) {
                temRepeticao = 1;
                usado[j] = 1; // Marca o duplicado para não ser processado depois
            }
        }

        // Se encontrou pelo menos uma repetição, imprime o nome
        if (temRepeticao) {
            printf("%s\n", p[i]->nome);
            encontrouAlgum = 1;
        }

        // Marca o original como usado também
        usado[i] = 1;
    }

    if (!encontrouAlgum) {
        printf("Nenhum nome repetido encontrado.\n");
    }

    // 2. IMPORTANTE: Libera a memória do vetor auxiliar
    free(usado);
}

// Sugestão: Crie esta função para manter o main limpo
void libera_Memoria(Pokemon **p, int n) {
    if (p == NULL) return; // Segurança extra

    for (int i = 0; i < n; i++) {
        if (p[i] != NULL) {
            // 1. PRIMEIRO: Libera o conteúdo interno (strings alocadas)
            free(p[i]->nome);
            free(p[i]->tipo);
            
            // Nota: 'pontos' é int (não é ponteiro), então não precisa de free.

            // 2. SEGUNDO: Libera a casca (a struct Pokemon em si)
            free(p[i]);
        }
    }

    // 3. TERCEIRO: Libera o vetor principal que segurava os endereços
    free(p);
}
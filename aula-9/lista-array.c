#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definição da struct oculta no .c (Encapsulamento)
struct lista {
    Item *itens;
    int maxTam;
    int n; // Quantidade atual de elementos
};

// --- Funções de Criação e Destruição ---

Lista* ListaCria(int tam) {
    Lista *pLista = (Lista*)malloc(sizeof(Lista));
    if (pLista == NULL) return NULL;

    pLista->itens = (Item*)malloc(sizeof(Item) * tam);
    if (pLista->itens == NULL) {
        free(pLista);
        return NULL;
    }

    pLista->maxTam = tam;
    pLista->n = 0;
    return pLista;
}

Lista* ListaDestroi(Lista *pLista) {
    if (pLista != NULL) {
        free(pLista->itens);
        free(pLista);
    }
    return NULL;
}

// --- Funções de Informação ---

int ListaTamanho(Lista *pLista) {
    if (pLista == NULL) return -1;
    return pLista->n;
}

bool ListaEhVazia(Lista *pLista) {
    if (pLista == NULL) return true;
    return (pLista->n == 0);
}

// --- Funções de Inserção ---

// Complexidade: O(n) - Precisa deslocar elementos
bool ListaInsereMeio(Lista *pLista, Item item, int pos) {
    if (pLista == NULL) return false;
    
    // 1. Verifica se a lista está cheia
    if (pLista->n >= pLista->maxTam) return false;
    
    // 2. Verifica se a posição é válida (pode inserir na posição 'n' que é o fim)
    if (pos < 0 || pos > pLista->n) return false;

    // 3. O "Arrasta-Arrasta" para a DIREITA (abre espaço)
    // Começa do último e vai puxando para frente
    for (int i = pLista->n; i > pos; i--) {
        pLista->itens[i] = pLista->itens[i-1];
    }

    // 4. Insere o item e atualiza o contador
    pLista->itens[pos] = item;
    pLista->n++;
    return true;
}

// Complexidade: O(n) - Pois chama o InsereMeio na posição 0
bool ListaInsereInicio(Lista *pLista, Item item) {
    return ListaInsereMeio(pLista, item, 0);
}

// Complexidade: O(1) - Melhor caso! Não precisa arrastar ninguém.
bool ListaInsereFim(Lista *pLista, Item item) {
    // Insere direto na posição 'n' (que é a primeira livre)
    // Poderíamos chamar ListaInsereMeio(pLista, item, pLista->n), 
    // mas fazer direto é mais rápido e didático para mostrar o O(1).
    
    if (pLista == NULL)
     return false;
    if (pLista->n >= pLista->maxTam) 
      return false;

    pLista->itens[pLista->n] = item;
    pLista->n++;
    return true;
}

// --- Funções de Remoção ---

// Complexidade: O(n) - Precisa deslocar elementos para tapar o buraco
bool ListaRemoveMeio(Lista *pLista, int pos, Item *pItem) {
    if (pLista == NULL) return false;
    if (ListaEhVazia(pLista)) return false;
    if (pos < 0 || pos >= pLista->n) return false;

    // 1. Salva o item removido para devolver ao usuário
    if (pItem != NULL) {
        *pItem = pLista->itens[pos];
    }

    // 2. O "Arrasta-Arrasta" para a ESQUERDA (tapa buraco)
    // Copia o da frente (i+1) para a posição atual (i)
    for (int i = pos; i < pLista->n - 1; i++) {
        pLista->itens[i] = pLista->itens[i+1];
    }

    // 3. Decrementa o tamanho
    pLista->n--;
    return true;
}

// Complexidade: O(n) - Remove do índice 0 e arrasta tudo
bool ListaRemoveInicio(Lista *pLista, Item *pItem) {
    return ListaRemoveMeio(pLista, 0, pItem);
}

// Complexidade: O(1) - Apenas decrementa o contador. O dado fica lá como "lixo" até ser sobrescrito.
bool ListaRemoveFim(Lista *pLista, Item *pItem) {
    if (pLista == NULL || ListaEhVazia(pLista)) return false;

    // Pega o último elemento (n-1)
    int ultimaPos = pLista->n - 1;
    
    if (pItem != NULL) {
        *pItem = pLista->itens[ultimaPos];
    }

    pLista->n--; // Simples assim! O usuário não alcança mais aquele dado.
    return true;
}

// --- Funções de Acesso e Busca ---

// Complexidade: O(1) - Acesso direto pelo índice
bool ListaGet(Lista *pLista, int pos, Item *pItem) {
    if (pLista == NULL || pItem == NULL) return false;
    if (pos < 0 || pos >= pLista->n) return false;

    *pItem = pLista->itens[pos];
    return true;
}

// Complexidade: O(n) - Busca Linear (pior caso: item não existe ou está no final)
bool ListaPesquisa(Lista *pLista, char *nome, Item *pItem) {
    if (pLista == NULL || nome == NULL) return false;

    for (int i = 0; i < pLista->n; i++) {
        // Usa strcmp para comparar strings (retorna 0 se iguais)
        if (strcmp(pLista->itens[i].nome, nome) == 0) {
            if (pItem != NULL) {
                *pItem = pLista->itens[i];
            }
            return true; // Encontrou!
        }
    }
    return false; // Não encontrou
}

// No arquivo lista.c, atualize a ListaPrint para:
void ListaPrint(Lista *pLista) {
    if (pLista == NULL) return;
    
    printf("\n=== Lista (n=%d) ===\n", pLista->n);
    for (int i = 0; i < pLista->n; i++) {
        printf("[%d] ", i);
        ItemPrint(pLista->itens[i]); 
        printf("\n"); // <--- ADICIONE ISTO (pois sua ItemPrint não tem \n)
    }
    printf("====================\n");
}
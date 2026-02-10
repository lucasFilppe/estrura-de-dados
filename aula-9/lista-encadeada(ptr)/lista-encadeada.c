#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Necessário para usar 'bool', 'true', 'false' padrão do C

// Renomeei 'prox' para 'proximo' para clareza
typedef struct celula {
    Item item;
    struct celula *proximo;
} Celula;

// Renomeei 'n' para 'quantidadeElementos' para evitar ambiguidade
struct lista {
    Celula* celulaCabeca;  // Antes: cabeca (Deixa claro que é a sentinela)
    Celula* celulaUltima;  // Antes: ultimo (Aponta para a última célula válida)
    int quantidadeElementos;
};

// --- FUNÇÕES DE CRIAÇÃO E DESTRUIÇÃO ---

Lista* ListaCria(int capacidadeInicial) { // O(1)
    // Nota: 'capacidadeInicial' é ignorado pois lista encadeada cresce dinamicamente
    Lista *lista = (Lista*) malloc(sizeof(Lista));
    
    if (lista != NULL) {
        // Aloca a Célula Cabeça (Sentinela)
        lista->celulaCabeca = (Celula*) malloc(sizeof(Celula));
        
        if (lista->celulaCabeca != NULL) {
            lista->celulaCabeca->proximo = NULL;
            lista->celulaUltima = lista->celulaCabeca; // No início, última é a própria cabeça
            lista->quantidadeElementos = 0;
        } else {
            // Falha ao alocar cabeça: libera a lista e retorna NULL
            free(lista);
            lista = NULL;
        }
    }    
    return lista;
}

Lista* ListaDestroi(Lista *lista) { // O(n)
    if (lista != NULL) {
        Item itemDescartavel;
        // Remove todos os itens um por um
        while(ListaRemoveInicio(lista, &itemDescartavel));
        
        // Libera a célula cabeça (sentinela) que sobrou
        free(lista->celulaCabeca);
        free(lista);
    }
    return NULL;
}

// --- FUNÇÕES DE CONSULTA ---

int ListaTamanho(Lista *lista) { // O(1)
    if (lista != NULL) {
        return lista->quantidadeElementos;
    }
    return -1; // Código de erro para lista inexistente
}

bool ListaEhVazia(Lista *lista) { // O(1)
    return ListaTamanho(lista) == 0;
}

// --- FUNÇÕES DE INSERÇÃO ---

bool ListaInsereInicio(Lista *lista, Item novoItem) { // O(1)
    return ListaInsereMeio(lista, novoItem, 0);
}

bool ListaInsereMeio(Lista *lista, Item novoItem, int posicaoDestino) { // O(n)
    if (lista == NULL) return false;
    
    // Validação da posição (0 até N)
    if (posicaoDestino > lista->quantidadeElementos || posicaoDestino < 0)
        return false;

    Celula* novaCelula = (Celula*) malloc(sizeof(Celula));
    if (novaCelula == NULL)
        return false; // Falha de memória
    
    novaCelula->item = novoItem;

    // 'cursor' navega até a célula ANTERIOR à posição de inserção
    Celula* cursor = lista->celulaCabeca;
    for (int i = 0; i < posicaoDestino; i++) {
        cursor = cursor->proximo;
    }

    // Engate da nova célula na lista
    novaCelula->proximo = cursor->proximo;
    cursor->proximo = novaCelula;

    // Se inseriu no final, atualiza o ponteiro 'celulaUltima'
    if (posicaoDestino == lista->quantidadeElementos) {
        lista->celulaUltima = novaCelula;
    }

    lista->quantidadeElementos++;    
    return true;
}

bool ListaInsereFim(Lista *lista, Item novoItem) { // O(1) - Otimizado!
    if (lista == NULL) return false;

    Celula* novaCelula = (Celula*) malloc(sizeof(Celula));
    if (novaCelula == NULL) return false;
    
    novaCelula->item = novoItem;
    novaCelula->proximo = NULL;

    // Uso direto do ponteiro 'celulaUltima' para evitar percorrer a lista
    lista->celulaUltima->proximo = novaCelula;
    lista->celulaUltima = novaCelula;
    
    lista->quantidadeElementos++;

    return true;
}

// --- FUNÇÕES DE REMOÇÃO ---

bool ListaRemoveInicio(Lista *lista, Item *itemRecuperado) { // O(1)
    return ListaRemoveMeio(lista, 0, itemRecuperado);
}

bool ListaRemoveMeio(Lista *lista, int posicaoAlvo, Item *itemRecuperado) { // O(n)
    if (lista == NULL) return false;
    if (ListaEhVazia(lista)) return false;
    
    // Validação da posição (0 até N-1)
    if (posicaoAlvo >= ListaTamanho(lista) || posicaoAlvo < 0)
        return false;

    // Navega até o ANTERIOR ao alvo
    Celula* cursor = lista->celulaCabeca;
    for (int i = 0; i < posicaoAlvo; i++) {
        cursor = cursor->proximo;
    }
    
    // Identifica a célula a ser removida
    Celula* celulaParaRemover = cursor->proximo;
    
    // Pulo do gato: anterior aponta para o próximo do removido
    cursor->proximo = celulaParaRemover->proximo;
    
    // Recupera o dado antes de apagar
    *itemRecuperado = celulaParaRemover->item;

    // Se removeu o último, o 'cursor' (anterior) vira o novo último
    if (celulaParaRemover->proximo == NULL) {
        lista->celulaUltima = cursor;
    }

    free(celulaParaRemover);
    lista->quantidadeElementos--;

    return true;
}

bool ListaRemoveFim(Lista *lista, Item *itemRecuperado) {  // O(n)
    // Remove o índice (N - 1)
    return ListaRemoveMeio(lista, lista->quantidadeElementos - 1, itemRecuperado);
}

// --- OUTRAS FUNÇÕES ---

void ListaPrint(Lista *lista) { // O(n)
    if (lista != NULL) {
        Celula *cursor = lista->celulaCabeca->proximo; // Começa do primeiro item real
        printf("[");
        
        while (cursor != NULL) {
            ItemPrint(cursor->item);
            cursor = cursor->proximo;
        }

        printf("]\n");
    }
}

bool ListaGet(Lista *lista, int posicao, Item *itemRecuperado) {
    if (lista == NULL || ListaEhVazia(lista)) return false;
    if (posicao >= ListaTamanho(lista) || posicao < 0) return false;

    Celula* cursor = lista->celulaCabeca->proximo; // Pula a cabeça
    for (int i = 0; i < posicao; i++) {
        cursor = cursor->proximo;
    }
    
    *itemRecuperado = cursor->item;
    return true;
}

bool ListaPesquisa(Lista *lista, char *nomeBusca, Item *itemRecuperado) { // O(n)
    if (lista != NULL) {
        Celula* cursor = lista->celulaCabeca->proximo;
        while (cursor != NULL) {
            if (strcmp(cursor->item.nome, nomeBusca) == 0) {
                *itemRecuperado = cursor->item;
                return true;
            }
            cursor = cursor->proximo;
        }
    }
    return false;
}
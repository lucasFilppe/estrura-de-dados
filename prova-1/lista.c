#include <stdio.h>
#include <stdlib.h>

typedef struct celula{
    int chave;
    struct celula *prox;
} Celula;

typedef struct lista{
    Celula *cabeca;
} Lista;

Lista* ListaCria() {
    Lista *l = (Lista*) malloc(sizeof(Lista));
    if (l == NULL) return NULL;

    l->cabeca = NULL;
    return l;
}

void ListaAdicionaInicio(Lista *l, int chave) {
    if (l == NULL) return;

    Celula *nova = (Celula*) malloc(sizeof(Celula));
    if (nova == NULL) return;

    nova->chave = chave;
    nova->prox = l->cabeca;
    l->cabeca = nova;
}

void moveElemento(Lista *l, int chave) {
    if (l == NULL || l->cabeca == NULL || l->cabeca->chave == chave)
        return;

    Celula *anterior = l->cabeca;
    Celula *atual = l->cabeca->prox;

    while (atual != NULL && atual->chave != chave) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return;

    anterior->prox = atual->prox;
    atual->prox = l->cabeca;
    l->cabeca = atual;
}

void ListaPrint(Lista *lista) {
    if (lista == NULL) return;

    Celula *cursor = lista->cabeca;

    printf("cabeca -> ");

    while (cursor != NULL) {
        printf("%d -> ", cursor->chave);
        cursor = cursor->prox;
    }

    printf("NULL\n");
}
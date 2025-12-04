#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

static No* criaNo(int cidade) {
    No *n = (No*) malloc(sizeof(No));
    n->cidade = cidade;
    n->prox = NULL;
    return n;
}

static void insereAdj(No **lista, int cidade) {
    No *novo = criaNo(cidade);
    novo->prox = *lista;
    *lista = novo;
}

void criaMapa(MapaCidades *m, int n, int mConexoes) {
    m->qtd = n;
    m->vetor = (No**) calloc(n, sizeof(No*));

    for (int i = 0; i < mConexoes; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        if (a >= 0 && a < n && b >= 0 && b < n) {
            insereAdj(&m->vetor[a], b);
        }
    }
}

int existeCaminho(MapaCidades *m, int origem, int destino) {
    if (origem < 0 || origem >= m->qtd ||
        destino < 0 || destino >= m->qtd)
        return 0;

    int *visitado = calloc(m->qtd, sizeof(int));
    int *fila = malloc(m->qtd * sizeof(int));
    int ini = 0, fim = 0;

    fila[fim++] = origem;
    visitado[origem] = 1;

    while (ini < fim) {
        int atual = fila[ini++];

        //encontrou destino
        if (atual == destino) {
            free(fila);
            free(visitado);
            return 1;
        }

        // percorre lista de adjacências do nó atual
        for (No *p = m->vetor[atual]; p != NULL; p = p->prox) {
            if (!visitado[p->cidade]) {
                visitado[p->cidade] = 1;
                fila[fim++] = p->cidade;
            }
        }
    }

    free(fila);
    free(visitado);
    return 0;
}

void liberaMapa(MapaCidades *m) {
    for (int i = 0; i < m->qtd; i++) {
        No *p = m->vetor[i];
        while (p != NULL) {
            No *aux = p;
            p = p->prox;
            free(aux);
        }
    }
    free(m->vetor);
}



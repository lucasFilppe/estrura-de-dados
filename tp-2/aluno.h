#ifndef ALUNO_H
#define ALUNO_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_CICLOS 100

// Estrutura do Processo
typedef struct {
    int id;
    float tempo_chegada;
    int prioridade;
    int ciclos_totais;
    int ciclos_executados;
} Processo;

// Nó da lista encadeada
typedef struct No {
    Processo proc;
    struct No* prox;
} No;

// Estrutura da Fila
typedef struct {
    No* inicio;
    No* fim;
    int tamanho;
    
    // Arrays dinâmicos para o log (evitar limite fixo e estouro de pilha)
    Processo* log;
    int* ciclos_log;
    int* prioridade_log;
    int tam_log;
    int cap_log; // Capacidade atual do log
} FilaProcessos;

// Funções do TAD
FilaProcessos* criarFila();
void destroiFila(FilaProcessos* fila);
void adicionaFila(FilaProcessos* fila, int id, float tempo_chegada, int prioridade, int ciclos);
void escalonador(FilaProcessos* fila);
void imprimeLog(FilaProcessos* fila);

#endif
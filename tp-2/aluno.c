#include "aluno.h"
#include <string.h>

// Função auxiliar para inicializar o nó
No* criarNo(int id, float tempo_chegada, int prioridade, int ciclos) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) return NULL;

    novo->proc.id = id;
    novo->proc.tempo_chegada = tempo_chegada;
    novo->proc.prioridade = prioridade;
    novo->proc.ciclos_totais = ciclos;
    novo->proc.ciclos_executados = 0;
    novo->prox = NULL;
    return novo;
}

FilaProcessos* criarFila() {
    FilaProcessos* fila = (FilaProcessos*)malloc(sizeof(FilaProcessos));
    if (fila == NULL) return NULL;

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    
    // Inicializa Log dinâmico
    fila->cap_log = 10;
    fila->tam_log = 0;
    fila->log = (Processo*)malloc(fila->cap_log * sizeof(Processo));
    fila->ciclos_log = (int*)malloc(fila->cap_log * sizeof(int));
    fila->prioridade_log = (int*)malloc(fila->cap_log * sizeof(int));

    return fila;
}

void destroiFila(FilaProcessos* fila) {
    if (fila == NULL) return;

    No* atual = fila->inicio;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    
    // Libera logs
    if (fila->log) free(fila->log);
    if (fila->ciclos_log) free(fila->ciclos_log);
    if (fila->prioridade_log) free(fila->prioridade_log);

    free(fila);
}

void adicionaFila(FilaProcessos* fila, int id, float tempo_chegada, int prioridade, int ciclos) {
    No* novo = criarNo(id, tempo_chegada, prioridade, ciclos);
    if (novo == NULL) return;

    // Critério: PRIORIDADE cresce, TEMPO cresce.
    // Inserir no início se:
    // 1. Fila vazia
    // 2. Nova Prioridade < Prioridade do Início
    // 3. Mesma Prioridade, mas Novo Tempo < Tempo do Início
    int inserirNoInicio = 0;
    
    if (fila->inicio == NULL) {
        inserirNoInicio = 1;
    } else if (novo->proc.prioridade < fila->inicio->proc.prioridade) {
        inserirNoInicio = 1;
    } else if (novo->proc.prioridade == fila->inicio->proc.prioridade && 
               novo->proc.tempo_chegada < fila->inicio->proc.tempo_chegada) {
        inserirNoInicio = 1;
    }

    if (inserirNoInicio) {
        novo->prox = fila->inicio;
        fila->inicio = novo;
        if (fila->fim == NULL) fila->fim = novo;
    } else {
        No* atual = fila->inicio;
        
        // Insertion Sort: Procura o lugar
        while (atual->prox != NULL) {
            int p_prox = atual->prox->proc.prioridade;
            float t_prox = atual->prox->proc.tempo_chegada;
            
            // Se o próximo tem prioridade menor (melhor), avança.
            if (p_prox < novo->proc.prioridade) {
                atual = atual->prox;
            }
            // Se tem mesma prioridade, mas chegou antes ou junto, avança.
            else if (p_prox == novo->proc.prioridade && t_prox <= novo->proc.tempo_chegada) {
                atual = atual->prox;
            }
            // Caso contrário, achamos o ponto de inserção
            else {
                break;
            }
        }
        
        novo->prox = atual->prox;
        atual->prox = novo;
        
        if (novo->prox == NULL) {
            fila->fim = novo;
        }
    }
    fila->tamanho++;
}

// Remove processo do início (para execução)
Processo* removeInicio(FilaProcessos* fila) {
    if (fila->inicio == NULL) return NULL;

    No* temp = fila->inicio;
    Processo* p = (Processo*)malloc(sizeof(Processo));
    if (p == NULL) return NULL;

    *p = temp->proc; // Copia dados

    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);
    fila->tamanho--;
    return p;
}

// REINSERÇÃO (Ordenação por PRIORIDADE)
// "Somente a primeira ordenação leva em conta o instante de chegada. 
// A reinserção ... deve levar em conta apenas a prioridade."
void reinserirNaFila(FilaProcessos* fila, Processo p) {
    p.prioridade++; // Penalização
    
    No* novo = criarNo(p.id, p.tempo_chegada, p.prioridade, p.ciclos_totais);
    novo->proc.ciclos_executados = p.ciclos_executados;
    
    // Inserir no início se fila vazia ou nova prioridade for ESTRITAMENTE MELHOR (menor) que a do início
    // Se for igual, vai depois (para respeitar quem já estava esperando)
    if (fila->inicio == NULL || novo->proc.prioridade < fila->inicio->proc.prioridade) {
        novo->prox = fila->inicio;
        fila->inicio = novo;
        if (fila->fim == NULL) fila->fim = novo;
    } else {
        No* atual = fila->inicio;
        
        // Avança enquanto o próximo tiver prioridade MELHOR ou IGUAL
        // Isso garante que o novo processo vá para o FINAL da fila de sua prioridade
        while (atual->prox != NULL && atual->prox->proc.prioridade <= novo->proc.prioridade) {
            atual = atual->prox;
        }
        
        novo->prox = atual->prox;
        atual->prox = novo;
        
        if (novo->prox == NULL) {
            fila->fim = novo;
        }
    }
    fila->tamanho++;
}

void escalonador(FilaProcessos* fila) {
    while (fila->inicio != NULL) {
        Processo* p = removeInicio(fila);
        
        // Simulação de execução
        int faltam = p->ciclos_totais - p->ciclos_executados;
        int executar = (faltam > MAX_CICLOS) ? MAX_CICLOS : faltam;

        // Loop vazio para simular CPU (conforme pedido)
        for(int i=0; i < executar; i++); 

        // Registro no LOG
        if (fila->tam_log >= fila->cap_log) {
            fila->cap_log *= 2;
            fila->log = (Processo*)realloc(fila->log, fila->cap_log * sizeof(Processo));
            fila->ciclos_log = (int*)realloc(fila->ciclos_log, fila->cap_log * sizeof(int));
            fila->prioridade_log = (int*)realloc(fila->prioridade_log, fila->cap_log * sizeof(int));
        }
        
        fila->log[fila->tam_log] = *p;
        fila->ciclos_log[fila->tam_log] = executar;
        fila->prioridade_log[fila->tam_log] = p->prioridade;
        fila->tam_log++;

        p->ciclos_executados += executar;

        // Verifica se terminou ou precisa reinserir
        if (p->ciclos_executados < p->ciclos_totais) {
            reinserirNaFila(fila, *p);
        }
        
        free(p);
    }
}

void imprimeLog(FilaProcessos* fila) {
    printf("\nLog CPU:\n");
    for (int i = 0; i < fila->tam_log; i++) {
        printf("%d %d %d\n", 
            fila->log[i].id, 
            fila->prioridade_log[i], // Imprime a prioridade que tinha NO MOMENTO da execução
            fila->ciclos_log[i]);
    }
}
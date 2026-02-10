#include "aluno.h"
#include <stdio.h>

int main() {
    int N;
    // Lê quantidade de processos
    if (scanf("%d", &N) != 1) return 0;

    FilaProcessos* fila = criarFila();
    
    int id, prioridade, ciclos;
    float tempo_chegada;

    // Lê os N processos
    for (int i = 0; i < N; i++) {
        scanf("%d %f %d %d", &id, &tempo_chegada, &prioridade, &ciclos);
        // Adiciona usando Insertion Sort por Tempo de Chegada
        adicionaFila(fila, id, tempo_chegada, prioridade, ciclos);
    }

    // Executa simulação
    escalonador(fila);

    // Mostra resultados
    imprimeLog(fila);

    // Limpa memória
    destroiFila(fila);

    return 0;
}
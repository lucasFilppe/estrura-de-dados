#include <stdio.h>
#include "formula.h"

int main() {
    int N, M; // Variáveis e Cláusulas
    int x, y, z; // Literais temporários para leitura

    // 1. Leitura de N e M (unica vez, conforme sua solicitação)
    // Se o scanf falhar, encerra o programa
    if (scanf("%d %d", &N, &M) != 2) {
        return 0;
    }

    // 2. Criação da Fórmula
    Formula *f = criaFormula(N, M);
    if (f == NULL) {
        fprintf(stderr, "Erro de memória.\n");
        return 1;
    }

    // 3. Leitura das M cláusulas
    for (int i = 0; i < M; i++) {
        if (scanf("%d %d %d", &x, &y, &z) != 3) {
             // Tratamento de erro de leitura
             destroiFormula(f);
             return 1;
        }
        adicionaClausula(f, x, y, z);
        
    }

    // 4. Execução do Algoritmo de Resolução (Backtracking)
    int resultado = solucaoFormula(f);

    // 5. Saída de Dados (Respeitando estritamente o enunciado)
    
    // Passo A: Imprimir a fórmula
    imprimeFormula(f);

    // Passo B: Verificar resultado e imprimir valoração ou erro
    if (resultado == TRUE) {
        imprimeValoracao(f); // Imprime $a= True, etc.
    } else {
        printf("Formula insatisfazivel!\n");
    }

    // 6. Limpeza de Memória (Obrigatório para não ter Memory Leak)
    destroiFormula(f);

    return 0;
}
#ifndef FORMULA_H
#define FORMULA_H

#include <stdio.h>
#include <stdlib.h>

// --- Definições de Constantes ---
#define ERRO -1
#define SUCESSO 0

#define TRUE 1
#define FALSE 0
#define NAO_VALORADA -1 // Estado inicial das variáveis antes do backtracking decidir

// --- Estruturas de Dados ---

// Representa uma variável (ex: 'a') ou sua negação (ex: '~a')
typedef struct literal {
    int id_variavel; // Índice numérico: 1 para 'a', 2 para 'b', etc.
    int negado;      // 1 se for negado (~a), 0 se for normal (a)
} Literal;

// Representa uma cláusula do 3-CNF (ex: a V b V ~c)
typedef struct clausula {
    Literal literais[3];// Exatamente 3 literais por cláusula [cite: 41]
} Clausula;

// Estrutura principal que guarda todo o problema
typedef struct formula {
    int num_variaveis;      // N
    int num_clausulas;      // M
    int prox_clausula_idx;  // Contador para saber quantas cláusulas já adicionamos
    
    Clausula *clausulas;    // Vetor dinâmico contendo todas as cláusulas
    int *valoracao_variaveis; // Vetor dinâmico com o estado atual (V/F) de cada variável
} Formula;

// --- Protótipos das Funções (API) ---

// Aloca memória para a estrutura Formula e seus vetores internos [cite: 71]
Formula* criaFormula(int n_variaveis, int n_clausulas);
// Libera toda a memória alocada para evitar memory leaks [cite: 72]
void destroiFormula(Formula *formula);

// Recebe 3 inteiros da entrada, converte para Literais e salva na Fórmula [cite: 73]
int adicionaClausula(Formula *formula, int x, int y, int z);

// Exibe a fórmula formatada (ex: (aVbVc) ^ ...) [cite: 74]
void imprimeFormula(const Formula *formula);

// Função Wrapper que inicia o processo de resolução (Backtracking) [cite: 75]
int solucaoFormula(Formula *formula);

// Função auxiliar para imprimir o resultado final (a valoração encontrada)
void imprimeValoracao(const Formula *formula);

#endif // FORMULA_H
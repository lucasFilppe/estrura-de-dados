// formula.h

#ifndef FORMULA_H
#define FORMULA_H

#include <stdio.h>
#include <stdlib.h>

// --- Constantes ---
#define ERRO -1
#define SUCESSO 0

#define TRUE 1
#define FALSE 0
#define NAO_VALORADA -1 // Usado para variáveis na busca de backtracking

// --- Estruturas (TADs) ---

// Estrutura para representar um Literal (variável ou sua negacao)
typedef struct literal {
    int literal_positivo; // 1 a N, onde N <= 26
    int leiteral_negativo;      // 1 se for negado, 0 se não for
} Literal;

// Estrutura para representar uma Clausula em 3-CNF
typedef struct clausula {
    Literal literais[3]; // Exatamente 3 literais
    int indice;          // Índice para ajudar na organização
} Clausula;

// Estrutura para representar a Formula em 3-CNF
typedef struct formula {
    int num_variaveis;      // N (de 1 a 26) [cite: 87, 90]
    int num_clausulas;      // M [cite: 87]
    int prox_clausula_idx;  // Contador para o índice da próxima cláusula a ser adicionada
    
    // Vetor alocado dinamicamente de cláusulas [cite: 78]
    Clausula *clausulas; 
    
    // Vetor para armazenar a valoração atual das variáveis (índice 1 a N)
    // TRUE, FALSE ou NAO_VALORADA [cite: 96]
    int *valoracao_variaveis; 
    
} Formula;


// --- Protótipos das Funções do TAD Formula ---

// 1. criaFormula: aloca um TAD Formula [cite: 71]
Formula* criaFormula(int n_variaveis, int n_clausulas);

// 2. destroiFormula: desaloca um TAD Formula [cite: 72, 48]
void destroiFormula(Formula *formula);

// 3. adicionaClausula: adiciona uma cláusula lida ao TAD Formula [cite: 73]
int adicionaClausula(Formula *formula, int x, int y, int z);

// 4. imprimeFormula: função que imprime o TAD Formula de acordo com o formato 3-CNF [cite: 74, 95]
void imprimeFormula(const Formula *formula);

// 5. solucaoFormula: função que tenta encontrar uma valoração (recursiva com backtracking) [cite: 75, 76]
int solucaoFormula(Formula *formula); 

// Função auxiliar para verificar se uma cláusula é satisfeita
int verificaClausula(const Formula *formula, int clausula_idx);

#endif // FORMULA_H
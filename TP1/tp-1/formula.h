#ifndef FORMULA_H
#define FORMULA_H

// Tipo incompleto: detalhes são escondidos no .c
typedef struct Formula Formula;

// Funções obrigatórias do TAD formula

// Cria uma fórmula com N variáveis e M cláusulas
Formula *criaFormula(int nVars, int nClausulas);

// Libera toda a memória da fórmula
void destroiFormula(Formula **f);

// Adiciona uma cláusula (3 literais) ao vetor interno
int adicionaClausula(Formula *f, int x, int y, int z);

// Imprime a fórmula em formato 3-CNF
void imprimeFormula(Formula *f);

// Executa o algoritmo recursivo (backtracking) para encontrar valoração
void solucaoFormula(Formula *f);

#endif

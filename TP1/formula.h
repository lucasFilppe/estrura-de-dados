#ifndef FORMULA_H
#define FORMULA_H

// ===========================================
// 1. DEFINIÇÃO DO TAD LITERAL
// ===========================================
// Um Literal é uma variável (a, b, c, ...) ou sua negação (~a, ~b, ~c, ...).
// A entrada usa números, onde o sinal negativo indica negação.
typedef struct {
    int id_variavel; // O número da variável (1 a N). Ex: 1 para 'a', 2 para 'b'.
    int negado;      // Flag: 1 se for negado (ex: -1), 0 se não for (ex: 1).
} Literal;

// ===========================================
// 2. DEFINIÇÃO DO TAD CLAUSULA
// ===========================================
// Uma Cláusula 3-CNF é uma disjunção (OU) de exatamente três Literais.
typedef struct {
    Literal l1; // Primeiro literal
    Literal l2; // Segundo literal
    Literal l3; // Terceiro literal
} Clausula;

// ===========================================
// 3. DEFINIÇÃO DO TAD FORMULA
// ===========================================
// A Fórmula é uma conjunção (E) de M cláusulas.
typedef struct {
    Clausula *clausulas; // Vetor alocado dinamicamente para armazenar as M cláusulas.
    int num_variaveis;   // N: Número total de variáveis (1 a 26).
    int num_clausulas;   // M: Número de cláusulas.
} Formula;


// ===========================================
// 4. PROTÓTIPOS DAS FUNÇÕES (Interface)
// ===========================================
// Estas são as funções que devem ser implementadas em 'formula.c'.
// O arquivo 'tp.c' (com o main) só pode chamar estas funções.

/**
 * @brief Aloca e inicializa o TAD Formula.
 * @param N Número total de variáveis.
 * @param M Número total de cláusulas.
 * @return Um ponteiro para a Formula alocada ou NULL em caso de erro.
 */
Formula* criaFormula(int N, int M);

/**
 * @brief Desaloca a memória de todo o TAD Formula.
 * @param f Ponteiro para a Formula a ser destruída.
 */
void destroiFormula(Formula* f);

/**
 * @brief Adiciona uma cláusula lida da entrada na posição 'indice' do TAD Formula.
 * @param f Ponteiro para a Formula.
 * @param x, y, z Os três inteiros lidos que representam os literais (o sinal indica negação).
 * @param indice A posição no vetor onde a cláusula deve ser inserida.
 * @return 1 (Sucesso) ou 0 (Erro, se for definido tratamento de erro).
 */
int adicionaClausula(Formula* f, int x, int y, int z, int indice);

/**
 * @brief Imprime a fórmula no formato 3-CNF, usando letras e conectivos (~, v, ^).
 * @param f Ponteiro para a Formula.
 */
void imprimeFormula(Formula* f); 

/**
 * @brief Tenta encontrar uma valoração (True/False) para as variáveis que satisfaça a fórmula.
 * [cite_start]Esta função deve ser implementada de forma recursiva (Backtracking). [cite: 77, 78]
 * @param f Ponteiro para a Formula.
 * @param var_atual A variável que está sendo testada na recursão (começa em 1).
 * @param val O vetor que armazena as valorações atuais (val[i] é o valor da variável i+1).
 * @return 1 se uma solução for encontrada, 0 se não for satisfazível.
 */
int solucaoFormula(Formula* f, int var_atual, int* val);

// FUNÇÃO AUXILIAR SUGERIDA:
/**
 * @brief Verifica se a Fórmula é satisfeita com as valorações atuais.
 * @param f Ponteiro para a Formula.
 * @param val O vetor de valorações a ser testado.
 * @return 1 se a fórmula for True, 0 se for False.
 */
int verificaSatisfatibilidade(Formula* f, int* val);


#endif // FORMULA_H
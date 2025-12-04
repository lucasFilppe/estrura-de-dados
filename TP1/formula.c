#include "formula.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Para a função fabs (valor absoluto)

// =================================================================
// 1. FUNÇÕES DE GERENCIAMENTO DE MEMÓRIA (Criação e Destruição)
// =================================================================

/**
 * @brief Aloca e inicializa o TAD Formula.
 */
Formula* criaFormula(int N, int M) {
    // 1. Aloca a estrutura principal Formula
    Formula* f = (Formula*) malloc(sizeof(Formula));
    
    // Verifica se a alocação da estrutura falhou
    if (f == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar a estrutura Formula.\n");
        return NULL;
    }

    // 2. Aloca o vetor de Clausulas dinamicamente
    f->clausulas = (Clausula*) malloc(M * sizeof(Clausula));
    
    // Verifica se a alocação do vetor de cláusulas falhou
    if (f->clausulas == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar o vetor de Clausulas.\n");
        // Se o vetor falhar, devemos liberar a estrutura pai antes de sair
        free(f); 
        return NULL;
    }

    // 3. Inicializa os campos
    f->num_variaveis = N;
    f->num_clausulas = M;

    return f;
}

/**
 * @brief Desaloca a memória de todo o TAD Formula. (Crucial para evitar Memory Leaks)
 */
void destroiFormula(Formula* f) {
    if (f != NULL) {
        // 1. Libera o vetor de cláusulas (memória alocada dinamicamente)
        if (f->clausulas != NULL) {
            free(f->clausulas);
        }
        
        // 2. Libera a estrutura Formula em si
        free(f);
    }
}

// =================================================================
// 2. FUNÇÃO DE ENTRADA (Adição de Cláusulas)
// =================================================================

// Função auxiliar para configurar um Literal
static void configuraLiteral(Literal* literal, int valor) {
    // O valor absoluto é o ID da variável (1 a N)
    literal->id_variavel = (int)fabs(valor); 
    
    // Se o valor lido é negativo, significa que o literal é negado.
    if (valor < 0) {
        literal->negado = 1; // True
    } else {
        literal->negado = 0; // False
    }
}

/**
 * @brief Adiciona uma cláusula lida da entrada na posição 'indice' do TAD Formula.
 */
int adicionaClausula(Formula* f, int x, int y, int z, int indice) {
    if (f == NULL || indice < 0 || indice >= f->num_clausulas) {
        fprintf(stderr, "Erro: Formula inválida ou índice de cláusula fora dos limites.\n");
        return 0; // Erro
    }
    
    Clausula* c = &(f->clausulas[indice]);

    // Configura os três literais da cláusula
    configuraLiteral(&(c->l1), x);
    configuraLiteral(&(c->l2), y);
    configuraLiteral(&(c->l3), z);
    
    return 1; // Sucesso
}

// =================================================================
// 3. FUNÇÃO DE SAÍDA (Impressão)
// =================================================================

// Função auxiliar para imprimir um Literal
static void imprimeLiteral(Literal l) {
    // 1. Imprime a negação se for o caso
    if (l.negado) {
        printf("~"); // Usamos ~ para negação como no arquivo de saída de exemplo
    }
    
    // 2. Converte o número da variável (1=a, 2=b, ...) para a letra
    // A variável 1 corresponde a 'a', então ('a' + (1-1)).
    printf("%c", (char)('a' + (l.id_variavel - 1)));
}

/**
 * @brief Imprime a fórmula no formato 3-CNF.
 */
void imprimeFormula(Formula* f) {
    if (f == NULL) return;
    
    printf("Formula:\n");
    
    for (int i = 0; i < f->num_clausulas; i++) {
        Clausula c = f->clausulas[i];
        
        printf("(");
        
        // Imprime os 3 literais separados por 'v' (OR)
        imprimeLiteral(c.l1);
        printf(" v ");
        imprimeLiteral(c.l2);
        printf(" v ");
        imprimeLiteral(c.l3);
        
        printf(")");
        
        // Se não for a última cláusula, adiciona o conectivo '∧' (AND)
        if (i < f->num_clausulas - 1) {
            printf(" ^ "); // Usamos ^ para conjunção (AND)
        }
    }
    printf("\n");
}

// =================================================================
// 4. FUNÇÕES DE RESOLUÇÃO (Verificação e Backtracking)
// =================================================================

// Função auxiliar para avaliar um literal com a valoração atual
static int avaliaLiteral(Literal l, int* val) {
    // O índice da variável no vetor 'val' é (id_variavel - 1)
    int valor_variavel = val[l.id_variavel]; 
    
    // Se o literal for negado, inverte o valor da variável.
    if (l.negado) {
        return 1 - valor_variavel; // 1 se 0, 0 se 1
    } else {
        return valor_variavel; // Retorna o valor direto
    }
}

// Função auxiliar para avaliar uma cláusula
static int avaliaClausula(Clausula c, int* val) {
    // Uma cláusula é TRUE (1) se PELO MENOS UM literal for TRUE.
    int v1 = avaliaLiteral(c.l1, val);
    int v2 = avaliaLiteral(c.l2, val);
    int v3 = avaliaLiteral(c.l3, val);
    
    // Retorna o resultado da operação OR (v1 OR v2 OR v3)
    return (v1 || v2 || v3); 
}

/**
 * @brief Verifica se a Fórmula é satisfeita com as valorações atuais.
 * Uma fórmula 3-CNF é TRUE se TODAS as cláusulas forem TRUE.
 */
int verificaSatisfatibilidade(Formula* f, int* val) {
    if (f == NULL || val == NULL) return 0;
    
    for (int i = 0; i < f->num_clausulas; i++) {
        // Se QUALQUER cláusula for FALSA (0), a fórmula inteira é FALSA.
        if (avaliaClausula(f->clausulas[i], val) == 0) {
            return 0; // Insatisfazível
        }
    }
    
    // Se todas as cláusulas forem TRUE, a fórmula é Satisfazível (1).
    return 1;
}

/**
 * @brief Tenta encontrar uma valoração (True/False) para as variáveis que satisfaça a fórmula (Backtracking).
 */
int solucaoFormula(Formula* f, int var_atual, int* val) {
    // Caso Base: Se já atribuímos um valor para TODAS as variáveis (1 até N)
    if (var_atual > f->num_variaveis) {
        // Todas as variáveis têm valor. Verificamos se essa valoração é uma solução.
        return verificaSatisfatibilidade(f, val);
    }

    // O índice no vetor 'val' é (var_atual - 1), mas usaremos var_atual diretamente
    // e faremos val[var_atual] no main (tp.c) ser o valor da var_atual.

    // ----------------------------------------------------
    // 1. TENTATIVA: Atribuir TRUE (1) para a variável atual
    // ----------------------------------------------------
    val[var_atual] = 1; // Atribui TRUE (1) para a variável 'var_atual'

    // Chamada recursiva para a PRÓXIMA variável
    if (solucaoFormula(f, var_atual + 1, val)) {
        // Se a chamada recursiva retornar TRUE, encontramos a solução.
        return 1;
    }

    // ----------------------------------------------------
    // 2. TENTATIVA: Atribuir FALSE (0) para a variável atual
    // ----------------------------------------------------
    // (BACKTRACKING: Se chegamos aqui, a atribuição TRUE falhou, então tentamos FALSE.)
    val[var_atual] = 0; // Atribui FALSE (0) para a variável 'var_atual'

    // Chamada recursiva para a PRÓXIMA variável
    if (solucaoFormula(f, var_atual + 1, val)) {
        // Se a chamada recursiva retornar TRUE, encontramos a solução.
        return 1;
    }

    // ----------------------------------------------------
    // 3. Se as duas tentativas falharem:
    // ----------------------------------------------------
    // Retornamos 0 (FALSE) para a chamada anterior, indicando que não há solução
    // a partir deste ponto, e o backtracking continua para a variável anterior.
    return 0;
}
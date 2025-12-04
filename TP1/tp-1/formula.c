#include <stdio.h>
#include <stdlib.h>
#include "formula.h"

// ------------------------------------------------------------
// ESTRUTURAS INTERNAS (OCULTAS DO USUÁRIO)
// ------------------------------------------------------------

// Cada cláusula possui exatamente 3 literais (3-CNF)
struct Clausula {
    int vars[3];  // exemplo: {1, -2, 3} → (a v ~b v c)
};

// Estrutura principal da fórmula
struct Formula {
    int nVars;             // número de variáveis
    int nClausulas;        // número de cláusulas
    struct Clausula *clauses; // vetor dinâmico das M cláusulas
    int pos;               // quantidade já inserida com success
};

// ------------------------------------------------------------
// CRIA FORMULA
// ------------------------------------------------------------
Formula *criaFormula(int nVars, int nClausulas)
{
    // Aloca a estrutura principal
    Formula *f = malloc(sizeof(Formula));
    if (!f) return NULL;

    f->nVars = nVars;
    f->nClausulas = nClausulas;

    // Aloca vetor de cláusulas (M cláusulas)
    f->clauses = malloc(sizeof(struct Clausula) * nClausulas);
    if (!f->clauses) {
        free(f);
        return NULL;
    }

    f->pos = 0; // nenhum elemento inserido ainda
    return f;
}

// ------------------------------------------------------------
// DESTROI FORMULA
// ------------------------------------------------------------
void destroiFormula(Formula **f)
{
    if (!f || !*f) return;

    // libera vetor
    free((*f)->clauses);

    // libera fórmula
    free(*f);

    // evita ponteiro solto
    *f = NULL;
}

// ------------------------------------------------------------
// ADICIONA CLAUSULA
// ------------------------------------------------------------
int adicionaClausula(Formula *f, int x, int y, int z)
{
    // erro: já inseriu todas M cláusulas
    if (!f || f->pos >= f->nClausulas)
        return 0;

    // salva os três literais
    f->clauses[f->pos].vars[0] = x;
    f->clauses[f->pos].vars[1] = y;
    f->clauses[f->pos].vars[2] = z;

    f->pos++;  // aumenta contador
    return 1;  // sucesso
}

// ------------------------------------------------------------
// IMPRESSÃO DO LITERAL (auxiliar)
// ------------------------------------------------------------
static void imprimeLiteral(int x)
{
    // converte 1→'a', 2→'b', ... 26→'z'
    char nome = 'a' + (abs(x) - 1);

    if (x < 0)
        printf("~%c", nome);  // literal negado
    else
        printf("%c", nome);
}

// ------------------------------------------------------------
// IMPRIME FORMULA COMPLETA EM 3-CNF
// ------------------------------------------------------------
void imprimeFormula(Formula *f)
{
    printf("Formula:\n");

    for (int i = 0; i < f->nClausulas; i++)
    {
        // coloca "∧" somente entre as cláusulas
        printf(i == 0 ? "(" : " ∧ (");

        imprimeLiteral(f->clauses[i].vars[0]);
        printf(" v ");
        imprimeLiteral(f->clauses[i].vars[1]);
        printf(" v ");
        imprimeLiteral(f->clauses[i].vars[2]);

        printf(")");
    }
    printf("\n");
}

// ------------------------------------------------------------
// VERIFICA SE VALORAÇÃO ATUAL SATISFAZ TODAS AS CLÁUSULAS
// ------------------------------------------------------------
static int satisfaz(Formula *f, int val[])
{
    // percorre cláusula por cláusula
    for (int i = 0; i < f->nClausulas; i++) {

        int ok = 0;  // assume que cláusula é falsa

        // percorre os 3 literais
        for (int j = 0; j < 3; j++) {

            int lit = f->clauses[i].vars[j];  // literal atual (ex: -2)
            int var = abs(lit);               // pega var positiva (ex: 2)

            int isTrue = val[var];            // 0 ou 1 da valoração

            // literal negativo: usa negação lógica
            if (lit < 0)
                isTrue = !isTrue;

            // se um literal é verdadeiro → cláusula verdadeira
            if (isTrue) {
                ok = 1;
                break;
            }
        }

        // se nenhuma literal da cláusula é verdadeira → fórmula falha
        if (!ok) return 0;
    }

    return 1; // satisfaz tudo
}

// ------------------------------------------------------------
// ALGORITMO BACKTRACKING PARA ATRIBUIR VALORES
// Backtracking que tenta TRUE antes de FALSE
static int backtrack(Formula *f, int k, int val[])
{
    if (k > f->nVars)
        return satisfaz(f, val);

    // tenta TRUE primeiro
    val[k] = 1;
    if (backtrack(f, k + 1, val)) return 1;

    // depois tenta FALSE
    val[k] = 0;
    if (backtrack(f, k + 1, val)) return 1;

    return 0;
}
// ------------------------------------------------------------
// ENVOLVE O ALGORITMO E IMPRIME A SOLUÇÃO
// ------------------------------------------------------------
void solucaoFormula(Formula *f)
{
    // vetor que guarda TRUE/FALSE das variáveis
    int *val = calloc(f->nVars + 1, sizeof(int));

    // roda backtracking a partir da variável 1
    int ok = backtrack(f, 1, val);

    if (ok) {
        printf("Solução encontrada:\n");
        for (int i = 1; i <= f->nVars; i++) {
            char nome = 'a' + (i - 1);
            printf("%c: %s\n", nome, val[i] ? "True" : "False");
        }
    } else {
        printf("Formula insatisfazivel.\n");
    }

    free(val); // libera memória
}

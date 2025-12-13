// formula.c

#include "formula.h"

// --- Funções Auxiliares Internas ---

// Converte um valor inteiro (positivo/negativo) para a estrutura Literal
Literal criaLiteral(int val) {
    Literal l;
    if (val < 0) {
        l.literal_positivo = -val;
        l.leiteral_negativo = 1; // 1 = Negado
    } else {
        l.literal_positivo = val;
        l.leiteral_negativo = 0; // 0 = Não Negado
    }
    return l;
}

// Verifica se a fórmula está em um estado de CONFLITO (cláusula FALSA)
// Retorna TRUE se houve conflito (cláusula falsa), FALSE caso contrário.
int verificaConflito(const Formula *formula) {
    // Itera sobre todas as cláusulas já adicionadas
    for (int i = 0; i < formula->prox_clausula_idx; i++) {
        int clausula_satisfeita = FALSE;
        int tem_nao_valorada = FALSE;

        // Itera sobre os 3 literais
        for (int j = 0; j < 3; j++) {
            Literal lit = formula->clausulas[i].literais[j];
            int valor_var = formula->valoracao_variaveis[lit.literal_positivo];

            if (valor_var == NAO_VALORADA) {
                tem_nao_valorada = TRUE;
            } else {
                // Checa se o literal é TRUE: (L V V) = V
                // Literal L é V se: (L não negado E var=TRUE) OU (L negado E var=FALSE)
                if ((lit.leiteral_negativo == 0 && valor_var == TRUE) || 
                    (lit.leiteral_negativo == 1 && valor_var == FALSE)) {
                    clausula_satisfeita = TRUE;
                    break; 
                }
            }
        }
        
        // PODA (Pruning): Se a cláusula não foi satisfeita, E 
        // todas as suas variáveis foram valoradas (não tem NAO_VALORADA),
        // então a cláusula é FALSE (F V F V F) = F. CONFLITO!
        if (clausula_satisfeita == FALSE && tem_nao_valorada == FALSE) {
            return TRUE; // Conflito encontrado
        }
    }
    return FALSE; // Nenhum conflito nas cláusulas valoradas
}


// Função recursiva principal do backtracking (chama a si mesma)
int resolveRecursivamente(Formula *formula, int idx_var) {
    
    // 1. CASO BASE DE SUCESSO: Todas as variáveis foram valoradas (de 1 a N)
    if (idx_var > formula->num_variaveis) {
        // Não é necessário chamar verificaConflito, pois a poda já fez o trabalho.
        // Se chegamos aqui, a valoração é uma solução (TRUE)
        return TRUE; 
    }
    
    // 2. PASSO RECURSIVO: Tenta atribuir a variável 'idx_var'
    
    // Tenta (1): TRUE (conforme a dica para manter resultados consistentes) [cite: 106]
    formula->valoracao_variaveis[idx_var] = TRUE;
    
    // Poda: Verifica se a valoração atual causou algum conflito
    if (verificaConflito(formula) == FALSE) {
        // Chamada recursiva para a próxima variável
        if (resolveRecursivamente(formula, idx_var + 1) == TRUE) {
            return TRUE; // Sucesso: propaga a solução
        }
    }
    // Senão, a tentativa TRUE falhou ou levou a um caminho sem solução

    // Tenta (2): FALSE
    formula->valoracao_variaveis[idx_var] = FALSE;
    
    // Poda: Verifica se a valoração atual causou algum conflito
    if (verificaConflito(formula) == FALSE) {
        // Chamada recursiva para a próxima variável
        if (resolveRecursivamente(formula, idx_var + 1) == TRUE) {
            return TRUE; // Sucesso: propaga a solução
        }
    }
    // Senão, a tentativa FALSE também falhou

    // 3. BACKTRACK: Se nenhuma das tentativas (TRUE/FALSE) funcionou
    formula->valoracao_variaveis[idx_var] = NAO_VALORADA; // Desfaz a atribuição (backtrack)
    return FALSE; // Retorna falha
}

// --- Implementação das Funções da Interface (formula.h) ---

// 1. criaFormula: aloca um TAD Formula [cite: 71, 48]
Formula* criaFormula(int n_variaveis, int n_clausulas) {
    if (n_variaveis < 1 || n_clausulas < 0 || n_variaveis > 26) {
        return NULL; // Erro de entrada
    }

    Formula *f = (Formula *)malloc(sizeof(Formula));
    if (f == NULL) return NULL;

    f->num_variaveis = n_variaveis;
    f->num_clausulas = n_clausulas;
    f->prox_clausula_idx = 0;
    
    // Aloca vetor de cláusulas
    f->clausulas = (Clausula *)malloc(f->num_clausulas * sizeof(Clausula));
    if (f->clausulas == NULL) {
        free(f);
        return NULL;
    }

    // Aloca vetor de valoração (+1 para usar índice 1 a N)
    f->valoracao_variaveis = (int *)malloc((f->num_variaveis + 1) * sizeof(int));
    if (f->valoracao_variaveis == NULL) {
        free(f->clausulas);
        free(f);
        return NULL;
    }
    
    // Inicializa valoração (todas como NÃO_VALORADA)
    for (int i = 0; i <= f->num_variaveis; i++) {
        f->valoracao_variaveis[i] = NAO_VALORADA;
    }

    return f;
}

// 2. destroiFormula: desaloca um TAD Formula [cite: 72, 48]
void destroiFormula(Formula *formula) {
    if (formula != NULL) {
        if (formula->clausulas != NULL) {
            free(formula->clausulas);
        }
        if (formula->valoracao_variaveis != NULL) {
            free(formula->valoracao_variaveis);
        }
        free(formula);
    }
}

// 3. adicionaClausula: adiciona uma cláusula lida ao TAD Formula [cite: 73]
int adicionaClausula(Formula *formula, int x, int y, int z) {
    if (formula == NULL || formula->prox_clausula_idx >= formula->num_clausulas) {
        return ERRO;
    }
    
    Clausula *c = &formula->clausulas[formula->prox_clausula_idx];
    
    c->literais[0] = criaLiteral(x);
    c->literais[1] = criaLiteral(y);
    c->literais[2] = criaLiteral(z);
    
    formula->prox_clausula_idx++;
    return SUCESSO;
}

// 4. imprimeFormula: imprime o TAD Formula no formato 3-CNF [cite: 74, 95]
void imprimeFormula(const Formula *formula) {
    printf("Formula:\n");
    for (int i = 0; i < formula->prox_clausula_idx; i++) {
        // Obtém o caractere da variável (1='a', 2='b', ...)
        printf("(");
        for (int j = 0; j < 3; j++) {
            Literal l = formula->clausulas[i].literais[j];
            char var_char = (char)('a' + l.literal_positivo - 1);
            
            if (l.leiteral_negativo) {
                printf("~"); // ~ ou ¬
            }
            printf("%c", var_char);
            
            if (j < 2) {
                printf("V"); // V (OR)
            }
        }
        printf(")");
        if (i < formula->prox_clausula_idx - 1) {
            printf(" ^ "); // ^ (AND)
        }
    }
    printf("\n");
}

// 5. solucaoFormula: Função Wrapper para iniciar a busca [cite: 75, 76]
int solucaoFormula(Formula *formula) {
    // Inicia a busca pela primeira variável (índice 1)
    return resolveRecursivamente(formula, 1);
}

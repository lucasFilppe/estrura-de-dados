#include "formula.h"

// --- Funções Auxiliares (Privadas) ---

// Função auxiliar para criar um Literal a partir de um inteiro
// Ex: entrada -2 vira Literal{id: 2, negado: 1}
Literal criaLiteral(int val) {
    Literal l;
    if (val < 0) {
        l.id_variavel = -val; // Remove o sinal para pegar o ID
        l.negado = 1;         // Marca como negado
    } else {
        l.id_variavel = val;
        l.negado = 0;
    }
    return l;
}

// --- O Coração da Poda (Pruning) ---
// Verifica se a valoração ATUAL das variáveis gera algum CONFLITO (Cláusula Falsa).
// Retorna TRUE se houve conflito (devemos fazer backtrack).
// Retorna FALSE se está tudo ok (podemos continuar aprofundando).
int verificaConflito(const Formula *formula) {
    // Percorre todas as cláusulas cadastradas na fórmula
    for (int i = 0; i < formula->prox_clausula_idx; i++) {
        int clausula_satisfeita = FALSE; // Assume falso até provar o contrário
        int literais_falsos = 0;         // Conta quantos literais já sabemos que são Falsos

        // Analisa os 3 literais da cláusula atual
        for (int j = 0; j < 3; j++) {
            Literal lit = formula->clausulas[i].literais[j];
            int valor_var = formula->valoracao_variaveis[lit.id_variavel];

            // Se a variável ainda não tem valor, não podemos afirmar nada sobre este literal
            if (valor_var == NAO_VALORADA) {
                continue; 
            }

            // Lógica Booleana:
            // Literal é VERDADEIRO se: (Não Negado E Var=TRUE) OU (Negado E Var=FALSE)
            if ((lit.negado == 0 && valor_var == TRUE) || 
                (lit.negado == 1 && valor_var == FALSE)) {
                clausula_satisfeita = TRUE;
                break; // Se um literal é V, a cláusula inteira (OR) é V. Para de checar esta cláusula.
            } else {
                // Se não é verdadeiro, então é Falso
                literais_falsos++;
            }
        }

        // Se a cláusula já foi satisfeita, ótimo, passa para a próxima cláusula.
        if (clausula_satisfeita) continue;

        // SE TODOS OS 3 LITERAIS SÃO FALSOS, TEMOS UM CONFLITO!
        // A cláusula é (F V F V F) = Falso. A fórmula quebrou.
        if (literais_falsos == 3) {
            return TRUE; // Reporta conflito para parar o backtracking
        }
    }
    return FALSE; // Nenhuma cláusula quebrou (pode haver cláusulas indeterminadas ainda)
}


// --- Função Recursiva (Backtracking) ---
int resolveRecursivamente(Formula *formula, int idx_var) {
    
    // 1. CASO BASE: Verificamos se já passamos da última variável (N)
    if (idx_var > formula->num_variaveis) {
        // Se chegamos aqui sem ser interrompidos pela Poda, achamos uma solução!
        return TRUE; 
    }
    
    // 2. TENTATIVA 1: Atribuir TRUE [cite: 106]
    formula->valoracao_variaveis[idx_var] = TRUE;
    
    // Poda: Antes de continuar, verifica se essa escolha quebrou alguma regra
    if (verificaConflito(formula) == FALSE) {
        // Se não quebrou, chama a recursão para a próxima variável (idx_var + 1)
        if (resolveRecursivamente(formula, idx_var + 1) == TRUE) {
            return TRUE; // Se o filho achou solução, retorna SUCESSO subindo a pilha
        }
    }

    // 3. TENTATIVA 2: Atribuir FALSE (Se a tentativa TRUE falhou)
    formula->valoracao_variaveis[idx_var] = FALSE;
    
    // Poda: Verifica novamente se FALSE quebra alguma regra
    if (verificaConflito(formula) == FALSE) {
        // Chama a recursão
        if (resolveRecursivamente(formula, idx_var + 1) == TRUE) {
            return TRUE; // Sucesso encontrado
        }
    }

    // 4. BACKTRACK (Retrocesso)
    // Se nem TRUE nem FALSE funcionaram, resetamos a variável e retornamos falha
    formula->valoracao_variaveis[idx_var] = NAO_VALORADA;
    return FALSE;
}

// --- Implementação das Funções da Interface ---

Formula* criaFormula(int n_variaveis, int n_clausulas) {
    Formula *f = (Formula *)malloc(sizeof(Formula));
    if (f == NULL) return NULL;

    f->num_variaveis = n_variaveis;
    f->num_clausulas = n_clausulas;
    f->prox_clausula_idx = 0;

    // Aloca vetor de cláusulas
    f->clausulas = (Clausula *)malloc(n_clausulas * sizeof(Clausula));
    
    // Aloca vetor de valoração (tamanho N+1 para usar índices 1 a N diretamente)
    f->valoracao_variaveis = (int *)malloc((n_variaveis + 1) * sizeof(int));

    // Inicializa valoração
    for(int i=0; i <= n_variaveis; i++) {
        f->valoracao_variaveis[i] = NAO_VALORADA;
    }

    return f;
}

void destroiFormula(Formula *formula) {
    if (formula != NULL) {
        // Libera os vetores internos primeiro
        if (formula->clausulas) free(formula->clausulas);
        if (formula->valoracao_variaveis) free(formula->valoracao_variaveis);
        // Libera a estrutura principal
        free(formula);
    }
}

int adicionaClausula(Formula *formula, int x, int y, int z) {
    if (formula->prox_clausula_idx >= formula->num_clausulas) return ERRO;

    // Acessa a posição livre no vetor de cláusulas
    Clausula *c = &formula->clausulas[formula->prox_clausula_idx];
    
    // Converte e armazena os 3 literais
    c->literais[0] = criaLiteral(x);
    c->literais[1] = criaLiteral(y);
    c->literais[2] = criaLiteral(z);

    formula->prox_clausula_idx++;
    return SUCESSO;
}

void imprimeFormula(const Formula *formula) {
    printf("Formula:\n");
    for (int i = 0; i < formula->prox_clausula_idx; i++) {
        printf("(");
        for (int j = 0; j < 3; j++) {
            Literal l = formula->clausulas[i].literais[j];
            
            // Converte ID numérico para char ('a', 'b'...)
            // 1 -> 'a', 2 -> 'b'
            char var = 'a' + (l.id_variavel - 1);
            
            if (l.negado) printf("~"); // Ou símbolo de negação
            printf("%c", var);
            
            if (j < 2) printf("V"); // Separador OR
        }
        printf(")");
        if (i < formula->prox_clausula_idx - 1) printf(" ^ "); // Separador AND (opcional visualmente)
    }
    printf("\n");
}

void imprimeValoracao(const Formula *formula) {
    printf("Valoracao:\n");
    for (int i = 1; i <= formula->num_variaveis; i++) {
        char var = 'a' + (i - 1);
        printf("$%c=$ ", var); // Formato específico pedido
        if (formula->valoracao_variaveis[i] == TRUE)
            printf("True\n");
        else
            printf("False\n");
    }
}

int solucaoFormula(Formula *formula) {
    // Inicia a recursão pela primeira variável (índice 1)
    return resolveRecursivamente(formula, 1);
}
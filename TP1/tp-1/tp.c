// tp.c

#include "formula.h"

// Função auxiliar para imprimir a valoração (saída obrigatória)
void imprimeValoracao(const Formula *formula) {
    printf("Valoracao:\n");
    // Itera de 1 até o número de variáveis
    for (int i = 1; i <= formula->num_variaveis; i++) {
        char var_char = (char)('a' + i - 1);
        printf("$%c=$ ", var_char);
        
        if (formula->valoracao_variaveis[i] == TRUE) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }
}
int main(){
int N, M; // N=variáveis, M=cláusulas
    int x, y, z;
    Formula *f = NULL;

    // --- MODIFICAÇÃO AQUI: Remove o loop 'while' e processa uma única vez ---
    
    // 1. Lê a primeira linha: N (variáveis) e M (cláusulas)
    if (scanf("%d %d", &N, &M) != 2) {
        // Se a leitura falhar (ex: arquivo vazio), termina o programa
        return ERRO;
    }
    
    // 2. Cria a Fórmula
    f = criaFormula(N, M);
    if (f == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a fórmula.\n");
        return ERRO;
    }

    // 3. Lê e Adiciona as M Cláusulas
    for (int i = 0; i < M; i++) {
        if (scanf("%d %d %d", &x, &y, &z) != 3) {
            fprintf(stderr, "Erro ao ler cláusula %d. A fórmula esperava %d cláusulas.\n", i + 1, M);
            destroiFormula(f);
            return ERRO;
        }
        // Adiciona a cláusula (Ex: 1 -2 3 é lido como a V ~b V c)
        if (adicionaClausula(f, x, y, z) == ERRO) {
            fprintf(stderr, "Erro ao adicionar cláusula no índice %d.\n", i);
            destroiFormula(f);
            return ERRO;
        }
    }

    // 4. Tenta encontrar a Solução (Backtracking)
    int resultado = solucaoFormula(f);
    
    // 5. Imprime a Saída (Obrigatória)
   // A impressão da fórmula deve ser a primeira linha de saída [cite: 95]
    imprimeFormula(f);

    if (resultado == TRUE) {
        // Imprime a primeira solução válida encontrada [cite: 99]
        imprimeValoracao(f);
    } else {
        // Fórmula insatisfatível, imprime mensagem [cite: 97]
        printf("Formula insatisfazivel!\n");
    }

    // 6. Desaloca a Fórmula (Garantir que não há memory leaks)
    destroiFormula(f);
    
    return SUCESSO;
}
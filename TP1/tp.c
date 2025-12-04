#include <stdio.h>
#include <stdlib.h>
#include "formula.h" // Inclui a interface do nosso TAD Formula

// Função auxiliar para imprimir a valoração encontrada
void imprimeValoracao(int N, int* val) {
    printf("Valoracao:\n");
    // As variáveis são 1 a N, mas no vetor val elas estão nos índices 1 a N
    for (int i = 1; i <= N; i++) {
        char variavel_char = (char)('a' + (i - 1));
        
        // Verifica se é True (1) ou False (0)
        const char* valor_str = (val[i] == 1) ? "True" : "False";
        
        // Exemplo de saída: "a: True" ou "$a=$ True" (Adaptando ao formato da saída de exemplo)
        printf("%c: %s\n", variavel_char, valor_str); 
    }
}

int main() {
    int N, M; // N: número de variáveis, M: número de cláusulas
    
    // O loop 'while' permite que o programa processe VÁRIOS conjuntos de testes
    // se o arquivo de entrada contiver mais de um (como é comum em testes automáticos).
    // A função scanf retorna o número de itens lidos com sucesso.
    while (scanf("%d %d", &N, &M) == 2) {
        
        // ----------------------------------------------------
        // 1. CRIAÇÃO E LEITURA DA FÓRMULA
        // ----------------------------------------------------
        
        // Cria a estrutura TAD Formula (aloca memória para ela e para o vetor de cláusulas)
        Formula* f = criaFormula(N, M);
        
        if (f == NULL) {
            fprintf(stderr, "Erro fatal: Não foi possível alocar a fórmula. Terminando.\n");
            return EXIT_FAILURE;
        }

        // Lê e adiciona M cláusulas. O índice 'i' é a posição no vetor de cláusulas.
        for (int i = 0; i < M; i++) {
            int X, Y, Z;
            // Lê os três inteiros (literais) de uma cláusula
            if (scanf("%d %d %d", &X, &Y, &Z) != 3) {
                 fprintf(stderr, "Erro ao ler os literais da cláusula %d.\n", i + 1);
                 destroiFormula(f);
                 return EXIT_FAILURE;
            }
            adicionaClausula(f, X, Y, Z, i);
        }
        
        // ----------------------------------------------------
        // 2. BUSCA POR SOLUÇÃO (Backtracking)
        // ----------------------------------------------------

        // Vetor para armazenar as valorações das variáveis.
        // O tamanho é N+1, pois usaremos os índices 1 a N (para corresponder ao ID da variável)
        // O índice 0 será ignorado.
        int* valoracoes = (int*) malloc((N + 1) * sizeof(int));
        
        if (valoracoes == NULL) {
            fprintf(stderr, "Erro fatal: Não foi possível alocar o vetor de valorações.\n");
            destroiFormula(f);
            return EXIT_FAILURE;
        }
        
        // Imprime a fórmula antes de tentar resolver, conforme a saída esperada
        imprimeFormula(f);
        
        // Chama o algoritmo recursivo de Backtracking. 
        // Começamos pela variável de ID 1 (que corresponde a 'a').
        int solucao_encontrada = solucaoFormula(f, 1, valoracoes);
        
        // ----------------------------------------------------
        // 3. IMPRESSÃO DA SAÍDA
        // ----------------------------------------------------

        if (solucao_encontrada) {
            // Se solucaoFormula retornou 1 (True), imprimimos o resultado
            imprimeValoracao(N, valoracoes);
        } else {
            // Se solucaoFormula retornou 0 (False), a fórmula é insatisfazível
            printf("Formula insatisfazivel!\n");
        }

        // ----------------------------------------------------
        // 4. LIMPEZA DA MEMÓRIA
        // ----------------------------------------------------
        
        // Libera a memória alocada dinamicamente
        free(valoracoes);
        destroiFormula(f);
    }

    return EXIT_SUCCESS;
}
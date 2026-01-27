#include <stdio.h>
#include <time.h>

// Função O(n^2) - Lenta propositalmente
// Simula algo como "comparar todo mundo com todo mundo"
void algoritmoLento(long int n) {
    long int i, j;
    long int soma = 0;
    
    // Loop Duplo (O clássico vilão de desempenho)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            soma += (i + j); // Apenas uma operação boba para gastar CPU
        }
    }
}

int main() {
    // TESTE 1: Entrada Pequena
    long int n_pequeno = 2000;
    
    clock_t t1_inicio = clock();
    algoritmoLento(n_pequeno);
    clock_t t1_fim = clock();
    
    double tempo_pequeno = (double)(t1_fim - t1_inicio) / CLOCKS_PER_SEC;
    printf("Entrada N = %ld: %f segundos\n", n_pequeno, tempo_pequeno);

    // ---------------------------------------------------------

    // TESTE 2: Entrada Grande (20x maior)
    long int n_grande = 40000;
    
    printf("Processando entrada grande... aguarde (vai demorar)...\n");
    
    clock_t t2_inicio = clock();
    algoritmoLento(n_grande);
    clock_t t2_fim = clock();
    
    double tempo_grande = (double)(t2_fim - t2_inicio) / CLOCKS_PER_SEC;
    printf("Entrada N = %ld: %f segundos\n", n_grande, tempo_grande);

    // Comparação final
    printf("\n--- CONCLUSAO ---\n");
    printf("A entrada aumentou %.0fx\n", (double)n_grande/n_pequeno);
    printf("Mas o tempo aumentou %.0fx!\n", tempo_grande/tempo_pequeno);

    return 0;
}
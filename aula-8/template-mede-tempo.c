#include <stdio.h>
#include <time.h> // 1. Importar a biblioteca

int main() {
    // 2. Definir variáveis de tempo
    clock_t inicio, fim;
    double tempo_gasto;

    // 3. Marcar o início
    inicio = clock();

    // --- SEU CÓDIGO OU FUNÇÃO AQUI ---
    minhaFuncaoPesada();
    // ---------------------------------

    // 4. Marcar o fim
    fim = clock();

    // 5. Calcular e converter para segundos
    tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo levado: %f segundos\n", tempo_gasto);

    return 0;
}
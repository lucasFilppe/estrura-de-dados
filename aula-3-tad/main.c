#include <stdio.h>
#include "ponto.h"

int main() {
    // 1. CRIAÇÃO (Alocação)
    // O usuário pede dois pontos. O sistema reserva dois espaços na memória.
    printf("Criando pontos...\n");
    
    // Note que passar '3' (inteiro) funciona, o C converte para 3.0 (float) automaticamente.
    Ponto *p = ponto_criar(3, 5.8);   
    Ponto *p2 = ponto_criar(4.1, 2.8);

    // Verificação de segurança (Boa prática!)
    if (p == NULL || p2 == NULL) {
        printf("Erro: Memória insuficiente!\n");
        return 1;
    }

    // 2. USO (Processamento)
    // Aqui corrigimos o nome da função para bater com a biblioteca
    float distancia = ponto_distancia(p, p2);
    
    // %.2f formata o número para mostrar apenas 2 casas decimais
    printf("Distancia entre os pontos: %.2f\n", distancia);

    // 3. DESTRUIÇÃO (Limpeza)
    // Devolvemos a memória dos DOIS pontos
    ponto_destruir(p);
    ponto_destruir(p2); // Adicionado para evitar vazamento de memória

    return 0;
}
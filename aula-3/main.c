#include <stdio.h>
#include "ponto.h"

int main() {
    float x, y;
    Ponto* p = ponto_criar(3.0f, 4.0f);
    if (ponto_acessa(p, &x, &y)) {
        printf("Ponto criado em (%.2f, %.2f)\n", x, y);
    } else {
        printf("Erro ao acessar o ponto.\n");
    }

    if(ponto_atribui(p, 5.0, 6.0)) {
        printf("Ponto atualizado com sucesso.\n");
    } else {
        printf("Erro ao atualizar o ponto.\n");
    }

    Ponto* p2 = ponto_criar(1.0f, 2.0f);
    float distancia = ponto_distancia(p, p2);

    ponto_destruir(p);
    return 0;
}
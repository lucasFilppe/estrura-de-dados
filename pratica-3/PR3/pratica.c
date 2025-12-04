#include <stdio.h>
#include "aluno.h"

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    MapaCidades mapa;
    criaMapa(&mapa, n, m);

    int origem, destino;
    scanf("%d %d", &origem, &destino);

    if (existeCaminho(&mapa, origem, destino))
        printf("SIM\n");
    else
        printf("NAO\n");

    liberaMapa(&mapa);
    return 0;
}

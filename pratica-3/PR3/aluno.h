#ifndef ALUNO_H
#define ALUNO_H

typedef struct No {
    int cidade;
    struct No *prox;
} No;

typedef struct {
    // pode adicionar mais informações
    No **vetor; 
    int qtd;
} MapaCidades;

void criaMapa(MapaCidades *m, int n, int mConexoes);

/*
    Libera toda a memória do mapa
*/
void liberaMapa(MapaCidades *m);

/*
    Retorna 1 se existe caminho de origem → destino
    Retorna 0 caso contrário
*/
int existeCaminho(MapaCidades *m, int origem, int destino);


#endif

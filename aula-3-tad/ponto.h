#ifndef  PONTO_H
#define  PONTO_H
#include <stdbool.h>

typedef struct ponto Ponto;

Ponto* ponto_criar(float x, float y);
Ponto* ponto_destruir(Ponto* p);
bool ponto_acessa(Ponto* p, float* x, float* y);
bool ponto_atribui(Ponto* p, float x, float y);
float ponto_distancia(Ponto* p1, Ponto* p2);
float PontoDist(Ponto *p1, Ponto *p2);
float calculaDistanciaPontoAPonto(float x1, float y1, float x2, float y2);


#endif /* PONTO_H */
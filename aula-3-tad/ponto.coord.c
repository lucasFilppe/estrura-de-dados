#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ponto.h"

struct ponto
{
  float coordenada[2];
};

Ponto *ponto_criar(float x, float y)
{
  Ponto *pt = malloc(sizeof(Ponto));
  if (pt == NULL)
    printf("Erro ao alocar ponto\n");

  pt->coordenada[0] = x;
  pt->coordenada[1] = y;

  return pt;
}

Ponto *ponto_destruir(Ponto *p)
{
  free(p);
  return NULL;
}

bool ponto_acessa(Ponto *p, float *x, float *y)
{
  if (p == NULL)
  {
    printf ("Erro ao acessar ponto\n");
  }
  *x = p->coordenada[0];
  *y = p->coordenada[1];

  return true;
}

bool ponto_atribui(Ponto *p, float x, float y)
{
  if (p == NULL)
    printf("Erro ao atribuur valores ao ponto\n");
  p->coordenada[0] = x;
  p->coordenada[1] = y;

  return true;
}

float PontoDist(Ponto *p1, Ponto *p2)
{
  if (!p1 || !p2) // p1 == NULL || p2 == NULL
    return -1.0;
  return calculaDistanciaPontoAPonto(p1->coordenada[0], p1->coordenada[1],
                                     p2->coordenada[0], p2->coordenada[1]);
}

float calculaDistanciaPontoAPonto(float x1, float y1, float x2, float y2)
{
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

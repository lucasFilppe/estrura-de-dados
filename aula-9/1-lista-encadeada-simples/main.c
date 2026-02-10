#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <time.h>
#define N 200000

int main()
{

  Lista *lista = criaLista();

  listaAdicionaInicio(lista, 5);
  listaAdicionaInicio(lista, 4);
  listaAdicionaInicio(lista, 2);
  listaAdicionaInicio(lista, 10);

  listaPrint(lista);

  // adicionado elemnto noi final da lista
  clock_t inicio = clock();

  for (int i = 0; i < N; i++)
  {
    listaAdicionaFinal(lista, i);
  }

  clock_t fim = clock();

  double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo O(n): %f segundos\n", tempo);

  Lista *lista2 = criaLista();
  inicio = clock();
  for (int i = 0; i < N; i++)
  {
    listaAdicionaFinalRapida(lista2, i);
  }
  fim = clock();

  tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo O(1): %f segundos\n", tempo);

  //listaPrint(lista);
  return 0;
}
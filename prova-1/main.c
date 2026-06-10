

#include <stdio.h>
#include "lista.h"

int main(){

  Lista *lista = ListaCria();

  ListaAdicionaInicio(lista , 13);
  ListaAdicionaInicio(lista , 4);
  ListaAdicionaInicio(lista , 21);
  ListaAdicionaInicio(lista , 10);

  ListaPrint(lista);

  moveElemento(lista, 13);
  ListaPrint(lista);

  return 0;
}
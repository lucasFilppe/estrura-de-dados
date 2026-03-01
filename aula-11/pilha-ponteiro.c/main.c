#include <stdio.h>
#include "pilha.h"


int main(){
  Pilha *p = PilhaCria(5);
  Item i1 = {"Lucas", 1};
  Item i2 = {"Gui", 2};
  Item i3 = {"bilu", 3};

  PilhaPush(p, i1);
  PilhaPush(p, i2);
  PilhaPush(p, i3);

  PilhaPrint(p);

  Item remocao;
  PilhaPop(p, &remocao);
  printf("Item removido: %s,%d\n", remocao.nome, remocao.id);
  PilhaPrint(p);

  return 0;
}
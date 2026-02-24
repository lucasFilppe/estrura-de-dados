
#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>

#include "item.h"

typedef struct pilha Pilha;

Pilha* PilhaCria(int tam);
Pilha* PilhaDestroi(Pilha *pPilha);
int PilhaTamanho(Pilha *pPilha);
bool PilhaEhVazia(Pilha *pPilha);
bool PilhaPush(Pilha *pPilha, Item item);
bool PilhaPop(Pilha *pPilha, Item *pItem);
void PilhaPrint(Pilha *pPilha);

bool PilhaTopo(Pilha *pPilha, Item *pItem);

#endif // !PILHA_H
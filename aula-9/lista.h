
#ifndef LISTA_H
#define LISTA_H
#include <stdbool.h>

#include "item.h"

typedef struct lista Lista;
Lista* ListaCria(int tam);
Lista* ListaDestroi(Lista *pLista);
int ListaTamanho(Lista *pLista);
bool ListaEhVazia(Lista *pLista);
bool ListaInsereInicio(Lista *pLista, Item item);
bool ListaInsereMeio(Lista *pLista, Item item, int pos);
bool ListaInsereFim(Lista *pLista, Item item);
bool ListaRemoveInicio(Lista *pLista, Item *pItem);
bool ListaRemoveMeio(Lista *pLista, int pos, Item *pItem);
bool ListaRemoveFim(Lista *pLista, Item *pItem);
void ListaPrint(Lista *pLista);
bool ListaGet(Lista *pLista, int pos, Item *pItem);
bool ListaPesquisa(Lista *pLista, char *nome, Item *pItem);
#endif // !LISTA_H
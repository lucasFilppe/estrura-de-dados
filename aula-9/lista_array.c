#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//criando estrura da lista
struct lista
{
  Item *itens;
  int maxTam;
  int n;
};

//O(1)
Lista* ListaCria(int tam){
  Lista *pLista = (Lista*)malloc(sizeof(Lista));
  if(pLista == NULL)
    printf("erro ao alocar lista\n");
  
  pLista->itens = (Item*)malloc(sizeof(Item) * tam);
  if (pLista->itens == NULL)
    printf("Erro ao alocar memoria para itens da lsita\n");
  pLista->maxTam = tam;
  pLista->n = 0;

  return pLista;
}

//O(1)
Lista* ListaDestroi(Lista *pLista){
  if (pLista)
  {
    free(pLista->itens);
    free(pLista);
  }
  return NULL;
}

//O(1)
int ListaTamanho(Lista *pLista){
  if (pLista)
  {
    return pLista->n;
  }
  return -1;
}

// O(1)
bool ListaEhVazia(Lista *pLista){
  if(pLista){
    pLista->n == 0;
    return true;
  }

  return false;
}

bool ListaInsereInicio(Lista *pLista, Item item) { // O(n)
    return ListaInsereMeio(pLista, item, 0);
}

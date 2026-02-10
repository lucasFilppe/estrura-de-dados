#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct celula{
  int valor;
  struct celula *proximo;
};

struct lista
{
  Celula *inicio;
  Celula *ultimo;
};

Lista* criaLista(){
  //alocando memoria para lista
  Lista *l = (Lista*)malloc(sizeof(Lista));

  l->inicio = NULL;
  l->ultimo = NULL;
  
  return l;
}

bool ListaEhVazia(const Lista *l){
  return(l->inicio == NULL && l->ultimo == NULL);
}

Celula* criaCelula(int valor){
  //alocando memoria para a estrura da celula
  Celula *celula = (Celula*)malloc(sizeof(Celula));
  celula->valor = valor;
  celula->proximo = NULL;

  return celula;
}

void listaAdicionaInicio(Lista *l, int valor) {
    Celula *p = criaCelula(valor);

    if (l->inicio == NULL) {
        l->inicio = p;
        l->ultimo = p;   // 🔴 correção essencial
    } else {
        p->proximo = l->inicio;
        l->inicio = p;
    }
}


void listaAdicionaFinal(Lista *l, int valor){
  Celula *final= criaCelula(valor);

  if(l->inicio == NULL){
    l->inicio = final;
    l->ultimo = final;
  }
  else{
    Celula *p = l->inicio;

    while (p->proximo != NULL)
    {
      p = p->proximo;
    }
    p->proximo = final;
    l->ultimo = final;  // 🔴 correção
  }
}

void listaAdicionaFinalRapida(Lista *l, int valor){
  Celula *final= criaCelula(valor);

  if(l->inicio == NULL){
    l->inicio = final;
    l->ultimo = final;
  }
   
  else{
    l->ultimo->proximo = final;
    l->ultimo = l->ultimo->proximo;
  }
}

void listaRemove(Lista *l, int valor){
  if(lista)
}

void listaPrint(const Lista *l){
  Celula *p = l->inicio;

  printf("lista -> ");
  while(p != NULL){
    printf("%d -> ", p->valor);
    p = p->proximo;
  }
  printf("\n");
}                                                                                                                                                                                                                    
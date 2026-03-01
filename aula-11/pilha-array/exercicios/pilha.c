#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct pilha {
    int dados[MAX];
    int topo; // índice do elemento do topo
};

void inicializa(Pilha *p){
    if(p != NULL){
      p->topo = 0;
    }
}

int estaVazia(Pilha *p){
  if(p->topo == 0)
    return 1;
  
  return 0;
}

int estaCheia(Pilha *p){
  if(p->topo == MAX){
    return 1;
  }

  return 0;
}


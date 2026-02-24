#include <stdio.h>
#include "resposta.h"
#include <stdlib.h>

struct entrevista{
  char sexo;
  char resposta;
};

Entrevista* criarEntrevista(char sexo, char resposta){
  Entrevista *e = (Entrevista*)malloc(sizeof(Entrevista));
  if (e == NULL)
  {
    printf("Erro ao alocar entrevista\n");
  }
  
  e->sexo = sexo;
  e->resposta = resposta;

  return e;
}

void qtdRespostasProduto(Entrevista **e, int n, int *contSim, int *contNao){

  *contNao = 0, *contSim = 0;
  for (int i = 0; i < n; i++)
  {
    if(e[i]->resposta == 's'){
      (*contSim)++;
    }
    else
      (*contNao)++;
  }
  
}
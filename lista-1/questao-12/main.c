#include <stdio.h>
#include <stdlib.h>
#include "resposta.h"
#define TAM 10

int main(){

  Entrevista **entrevistas = (Entrevista**)malloc(TAM * sizeof(Entrevista*));
  char s, r;

  for (int i = 0; i < TAM; i++)
  {
    printf("Digite o sexo e resposta: ");
    scanf(" %c %c", &s, &r);
    entrevistas[i] = criarEntrevista(s, r);
  }
  
  int qntSim, qntNao;

  qtdRespostasProduto(entrevistas, TAM, &qntSim, &qntNao);
  printf("Quantidade de sim: %d\nQuantidade de nao %d\n", qntSim, qntNao);

  return 0;
}
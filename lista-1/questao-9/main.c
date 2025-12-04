#include <stdio.h>
#include "aluno.h"
#include <stdlib.h>

int main(){

  int n;
  char nome[21];
  float nota;

  printf("Digite a quantidade de alunos: ");
  scanf("%d", &n);
  Aluno **alunos = malloc(n * sizeof(Aluno*));

  for (int i = 0; i < n; i++)
  {
    //printf("digite o nome: ");
    scanf("%s", nome);
    //printf("Digite a nota: ");
    scanf("%f", &nota);
    alunos[i] = cria_Aluno(nome, nota); 
  }
  
  aluno_Imprime(alunos, n);
  aluno_Aprovado(alunos, n);

  destroi_Alunos(alunos, n);

  return 0;
}
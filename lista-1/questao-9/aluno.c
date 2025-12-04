#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include <string.h>

struct aluno
{
  char nome[21];
  float nota;
};

Aluno* cria_Aluno(char nome[21], float nota){
  Aluno *a = (Aluno*)malloc(sizeof(Aluno));
  if(a == NULL)
    printf("eRRO AO ALOcar aluno\n");
  
  strcpy(a->nome, nome);

  a->nota = nota;

  return a;
}

void aluno_Aprovado(Aluno **alunos, int n){
  printf("ALUNOS APROVADOS\n\n");
  for (int i = 0; i < n; i++)
  {
    if(alunos[i]->nota > 6){
      printf(" %s %f\n", alunos[i]->nome, alunos[i]->nota);
    }
    else
      printf("Aluno %s nao aprovado\n", alunos[i]->nome);
  }
  
}

void aluno_Imprime(Aluno **alunos, int n){
  for (int i = 0; i < n; i++)
  {
    printf("%s %f\n", alunos[i]->nome, alunos[i]->nota);
  }
  
}

void destroi_Alunos(Aluno **alunos, int n){
  for( int i = 0; i < n; i++)
  {
    free(alunos[i]);
  }
  free(alunos);
}
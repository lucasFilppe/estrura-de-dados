#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#define MAX 50

struct aluno{
  int mat;
  int id;
};

Aluno* criaAluno(int matricula, int idade){
  Aluno *x = (Aluno*)malloc(sizeof(Aluno));
  if(x == NULL)
    printf("Erro ao alocar aluno\n");
  
  x->mat = matricula;
  x->id = idade;

  return x;
}

void lerVetorAlunos(Aluno *v[], int n){
    int matricula, idade;
    v[n] = (Aluno*)malloc(n * sizeof(Aluno));

    for (int i = 0; i < n; i++)
    {
      scanf("%d %d", &matricula, &idade);
      v[i] = criaAluno(matricula, idade);
    }
    
}

void imprimeAlunos(Aluno *v[], int n){
  for (int i = 0; i < n; i++)
  {
    printf("Maricula %d, idade: %d\n", v[i]->mat, v[i]->id);
  }
  
}

int maioresIdade(Aluno *v[], int n){
  int cont = 0;
  for (int i = 0; i < n; i++)
  {
    if(v[i]->id > 20)
      cont++;
  }
  
  return cont;
}
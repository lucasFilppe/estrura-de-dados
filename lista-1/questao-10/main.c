#include "aluno.h"
#include <stdio.h>

int main(){


  Aluno *v[50];

  lerVetorAlunos(v, 5);
  imprimeAlunos(v, 5);

  int contador = maioresIdade(v, 5);
  printf("Ha %d alunos com mais de 20 anos\n\n", contador);
  
  return 0;
}
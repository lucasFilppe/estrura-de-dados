#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionario.h"

struct funcionario{
  char *nome;
  int matricula;
  float salario;
};

Funcionario* criaFuncionario(char *nome, int matricula, float salario){
  Funcionario *f = (Funcionario*)malloc(sizeof(Funcionario));
  if(f == NULL){
    printf("erro ao alocar funcionario\n");
    return NULL;
  }
 
  f->nome = (char*)malloc((strlen(nome) + 1) * sizeof(char));
  if(f->nome == NULL){
    printf("Erro ao alocar nome\n");
    free(f);
    return NULL;
  }

  strcpy(f->nome, nome);
  f->matricula = matricula;
  f->salario = salario;

  return f;
}

Funcionario** criaVetorFuncionarios(int n) {
    Funcionario **vet = (Funcionario**) malloc(n * sizeof(Funcionario*));

    if (vet == NULL) {
        printf("Erro ao alocar vetor de funcionarios\n");
        return NULL;
    }

    // inicializa todas as posições com NULL (boa prática)
    for (int i = 0; i < n; i++) {
        vet[i] = NULL;
    }

    return vet;
}

//calcula novo salario
float calculaReajuste(Funcionario** f, int n){
  int encontrou = 0;
  float reajuste = -1;
  for (int i = 0; i < n; i++)
  {
    if(f[i] != NULL && f[i]->salario < 1000){
      reajuste = f[i]->salario + (f[i]->salario * 0.15f);
      encontrou = 1;
      break;
    }
  }
  return reajuste;
}

void imprimeFuncionario(Funcionario *f){
  printf("Nome %s ", f->nome);
  printf("matricula %d ", f->matricula);
  printf("salario R$ %.2f\n\n", f->salario);
}

// Função para liberar memória de um funcionário
void liberaFuncionario(Funcionario *f){
  if(f != NULL){
    free(f->nome);
    free(f);
  }
}
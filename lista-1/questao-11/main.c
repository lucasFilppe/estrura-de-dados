#include <stdio.h>
#include "funcionario.h"
#include <string.h>

int main(){
  int n;
  printf("Digite o numero de funcionarios: ");
  scanf("%d", &n);

  Funcionario **funcionarios = criaVetorFuncionarios(n);
  char nome[50];
  int matricula;
  float salario;

  for (int i = 0; i < n; i++)
  {
    getchar();
    printf("Digite o nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0; // Remove o '\n' do final
    printf("Digite a matricula: ");
    scanf("%d", &matricula);
    printf("Digite o salario: ");
    scanf("%f", &salario);

    funcionarios[i] = criaFuncionario(nome, matricula, salario);
  }

  printf("\nFuncionarios cadastrados:\n");
  for (int i = 0; i < n; i++)
  {
    imprimeFuncionario(funcionarios[i]);
  }

  // Exemplo de uso do calculaReajuste: mostra o novo salário do primeiro funcionário com salário < 1000
  float r = calculaReajuste(funcionarios, n);
  if(r != -1)
    printf("\nNovo salario reajustado: R$ %.2f\n", r);
  else
    printf("\nNenhum funcionario com salario menor que 1000 para reajuste.\n");

  // Libera memória
  for (int i = 0; i < n; i++)
    liberaFuncionario(funcionarios[i]);
  free(funcionarios);

  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pessoa.h"

// estrura real, invisivel na main
struct pessoa
{
  double salario;
  int filhos;
};

// cria vetor alocado dinamicamente
Pessoa *criaVetorPessoas()
{
  Pessoa *p = (Pessoa *)malloc(MAX * sizeof(Pessoa));
  if (p == NULL)
  {
    printf("Erro ao alocar vetor par5a estrutura pessoas\n");
    return 0;
  }

  return p;
}

int lerPessoas(Pessoa *vetor)
{
  int total = 0;

  printf("Digite <salario> <num_filhos> para cada pessoa.\n");
  printf("Digite um salario negativo para encerrar.\n");

  while (1)
  {
    int filhos;
    double salario;

    scanf("%lf", &salario);
    scanf("%d", &filhos);

    if (salario < 0)
      break;

    vetor[total]->salario = salario;
    vetor[total]->filhos = filhos;

    total++;

    if (total >= MAX)
    {
      printf("Limite de %d pessoas atingido.\n", MAX);
      break;
    }
  }

  return total;
}

double mediaSalario(Pessoa vetor[], int total) {
    double soma = 0;
    for (int i = 0; i < total; i++)
        soma += vetor[i]->salario;
    return soma / total;
}

double mediaFilhos(Pessoa vetor[], int total) {
    double soma = 0;
    for (int i = 0; i < total; i++)
        soma += vetor[i]->filhos;
    return soma / total;
}

double maiorSalario(Pessoa vetor[], int total) {
    double maior = vetor[0]->salario;
    for (int i = 1; i < total; i++)
        if (vetor[i]->salario > maior)
            maior = vetor[i]->salario;
    return maior;
}

double percentualAte1350(Pessoa vetor[], int total) {
    int cont = 0;
    for (int i = 0; i < total; i++)
        if (vetor[i]->salario <= 1350.0)
            cont++;

    return (cont / (double) total) * 100.0;
}

void modaSalarios(Pessoa vetor[], int total) {
    int valores[MAX];
    int contagens[MAX];
    int qtd_valores = 0;

    for (int i = 0; i < total; i++) {
        int cents = (int) llround(vetor[i]->salario * 100);
        int encontrado = 0;

        for (int j = 0; j < qtd_valores; j++) {
            if (valores[j] == cents) {
                contagens[j]++;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            valores[qtd_valores] = cents;
            contagens[qtd_valores] = 1;
            qtd_valores++;
        }
    }

    int maior_cont = 0;
    for (int i = 0; i < qtd_valores; i++)
        if (contagens[i] > maior_cont)
            maior_cont = contagens[i];

    printf("\nModa dos salários:\n");

    if (maior_cont == 1) {
        printf("Nao existe moda; todos aparecem 1 vez.\n");
        return;
    }

    for (int i = 0; i < qtd_valores; i++)
        if (contagens[i] == maior_cont)
            printf("  R$ %.2f (ocorrencias: %d)\n",
                   valores[i] / 100.0,
                   contagens[i]);
}


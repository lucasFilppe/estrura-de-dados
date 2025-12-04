#include <stdio.h>
#include <stdlib.h>
#include "crianca.h"
#include <string.h>
#define TAM_Perna 11

struct crianca
{
  int overall;
  int idade;
  char *perna;
};

Crianca *cria_Crianca(int overall, int idade, char *perna)
{
  Crianca *c = (Crianca *)malloc(sizeof(Crianca));
  if (c == NULL)
  {
    printf("Erro ao alocar estrutura crianca\n");
  }

  c->overall = overall;
  c->idade = idade;
  c->perna = (char *)malloc(TAM_Perna * sizeof(char));
  if (c->perna == NULL)
  {
    printf("Erro ao alocar qual perna a criaça chuta\n");
  }
  strcpy(c->perna, perna); // copia a string passada

  return c;
}

Crianca *le_Crianca()
{
  int overall, idade;
  char perna[TAM_Perna];

  // lendo dados de uma criança
  printf("Overall: ");
  scanf("%d", &overall);
  printf("idade: ");
  scanf("%d", &idade);
  printf("Perna: ");
  getchar();  
  fgets(perna, TAM_Perna, stdin);
  perna[strcspn(perna, "\n")] = '\0'; // remove o \n

  return cria_Crianca(overall, idade, perna);
}

void imprime_Crianca(Crianca *c)
{
  printf("Overall: %d | Idade: %d | Perna: %s\n",
         c->overall, c->idade, c->perna);
}

void libera_Crianca(Crianca *c)
{
  if (c)
  {
    free(c->perna);
    free(c);
  }
}

Crianca **le_Vetor_Criancas(int n)
{
  Crianca **vet = malloc(n * sizeof(Crianca *));

  for (int i = 0; i < n; i++)
  {
    printf("\n--- Criança %d ---\n", i + 1);
    vet[i] = le_Crianca();
    getchar();
  }

  return vet;
}

void imprime_Vetor_Criancas(Crianca **vet, int n)
{
  printf("\n=== DADOS CADASTRADOS ===\n");
  for (int i = 0; i < n; i++)
  {
    printf("Criança %d: ", i + 1);
    imprime_Crianca(vet[i]);
  }
}

void libera_Vetor_Criancas(Crianca **vet, int n)
{
  for (int i = 0; i < n; i++)
  {
    libera_Crianca(vet[i]);
  }
  free(vet);
}
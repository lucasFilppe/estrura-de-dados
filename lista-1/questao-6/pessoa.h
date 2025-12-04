#ifndef PESSOA_H
#define PESSOA_H

#define MAX 1000

//criando tipo de dado pessoa
typedef struct pessoa* Pessoa;

//cria um vetor de Pessoa
Pessoa* criaVetorPessoas();

//le dados dados ate salario negativo e retorna quantidade lida
int lerPessoas(Pessoa *vetor);

// Cálculos
double mediaSalario(Pessoa vetor[], int total);
double mediaFilhos(Pessoa vetor[], int total);
double maiorSalario(Pessoa vetor[], int total);
double percentualAte1350(Pessoa vetor[], int total);

// Moda impressa na tela
void modaSalarios(Pessoa vetor[], int total);

#endif
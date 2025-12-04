#ifndef CRIANCAS_H
#define CRIANCAS_H

typedef struct crianca Crianca;

Crianca* cria_Crianca(int overall, int idade, char *perna);
Crianca* le_Crianca();
void imprime_Crianca(Crianca *c);
void libera_Crianca(Crianca *c);

Crianca** le_Vetor_Criancas(int n);
void imprime_Vetor_Criancas(Crianca **vet, int n);
void libera_Vetor_Criancas(Crianca **vet, int n);
#endif
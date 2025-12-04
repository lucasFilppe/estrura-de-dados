#ifndef PESSOA_H
#define PESSOA_H

typedef struct pessoa Pessoa;

// Cria uma pessoa
Pessoa* Pessoa_criar(char sexo, char resposta);

// Retorna o sexo ('M' ou 'F')
char Pessoa_getSexo(Pessoa* p);

// Retorna a resposta ('S' ou 'N')
char Pessoa_getResposta(Pessoa* p);

// Destrói uma pessoa
void Pessoa_destruir(Pessoa* p);

#endif
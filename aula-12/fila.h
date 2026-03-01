
#ifndef FILA_H
#define FILA_H
#include <stdio.h>

#include <stdbool.h>

#include "item.h"

typedef struct fila Fila;

Fila* FilaCria(int tam);//cria uma fila
Fila* FilaDestroi(Fila *pFila);
int FilaTamanho(Fila *pFila);
bool FilaEhVazia(Fila *pFila);
bool FilaEnfileirar(Fila *pFila, Item item);
bool FilaDesenfileirar(Fila *pFila, Item *pItem);
void FilaPrint(Fila *pFila);

bool FilaPrimeiro(Fila *pFila, Item *pItem);

#endif // !FILA_H
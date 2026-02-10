#ifndef LISTA_H
#define LISTA_H
#include <stdbool.h>

typedef struct lista Lista;
typedef struct celula Celula;

//função que aloca lista
Lista* criaLista();

//função que cria a celula da lista
Celula* criaCelula(int valor);

//cria a primeira celula da lista
void listaAdicionaInicio(Lista *l, int valor);

//cria celula da lista no final O(n)
void listaAdicionaFinal(Lista *l, int valor);

//O(1)
void listaAdicionaFinalRapida(Lista *l, int valor);

//mostra a lista
void listaPrint(const Lista *l);

bool ListaEhVazia(const Lista *l);

void listaRemove(Lista *l, int valor);



#endif
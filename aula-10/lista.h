
#ifndef LISTA_H
#define LISTA_H
#include <stdbool.h>
typedef struct {
    int chave;
    char nome[21];
} Item;

typedef struct lista Lista;

/* procedimentos e funcoes do TAD */
Lista* ListaCria();
Lista* ListaDestroi(Lista*);
bool ListaEhVazia(Lista*);
bool ListaInsereFinal(Lista*, Item);
bool ListaInsereInicio(Lista*, Item);
bool ListaRetiraFinal(Lista*, Item*);
void ListaImprime(Lista*);
void ListaImprimeInverso(Lista*);
bool ListaGet(Lista*, int, Item*);
int ListaTamanho(Lista*);

#endif // !LISTA_DUPLAMENTE_ENCADEADA_H
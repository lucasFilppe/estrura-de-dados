
#include <stdio.h>
#include "lista.h"

int main() {
    Lista* lista = ListaCria();
    Item item;
    printf("Lista Vazia: %s\n", ListaEhVazia(lista) ? "true" : "false");
    printf("Inseriu 1: %s\n", ListaInsereFinal(lista, (Item){1, "pedro"}) ? "true" : "false"); 
    printf("Inseriu 2: %s\n", ListaInsereFinal(lista, (Item){2, "maria"}) ? "true" : "false"); 
    printf("Inseriu 3: %s\n", ListaInsereFinal(lista, (Item){3, "jose"}) ? "true" : "false"); 
    printf("Inseriu 4: %s\n", ListaInsereFinal(lista, (Item){4, "ana"}) ? "true" : "false"); 
    printf("Inseriu 5: %s\n", ListaInsereFinal(lista, (Item){5, "carlos"}) ? "true" : "false"); 
    printf("Inseriu 6: %s\n", ListaInsereFinal(lista, (Item){6, "joao"}) ? "true" : "false"); 
    printf("Removeu: %s", ListaRetiraFinal(lista, &item) ? "true" : "false"); 
    printf(" (%d - %s)\n", item.chave, item.nome);
    printf("Inseriu 7: %s\n", ListaInsereInicio(lista, (Item){0, "henrique"}) ? "true" : "false"); 
    printf("Lista Vazia: %s\n", ListaEhVazia(lista) ? "true" : "false");
    ListaImprime(lista);
    ListaImprimeInverso(lista);
    printf("Pegou: %s", ListaGet(lista, 1, &item) ? "true" : "false"); 
    printf(" (%d - %s)\n", item.chave, item.nome);
    lista = ListaDestroi(lista);
    return 0;
}
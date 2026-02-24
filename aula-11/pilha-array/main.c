#include "pilha.h"
#include <stdio.h>
#include <stdbool.h>


void testaPilha() {
    Pilha *pilha = NULL;
    pilha = PilhaCria(5);
    printf("A pilha eh vazia: %s\n", PilhaEhVazia(pilha) ? "sim" : "nao");
    printf("O tamanho da pilha eh %d\n", PilhaTamanho(pilha));
    printf("Inserindo pedro na pilha: %s\n", PilhaPush(pilha, (Item) {"pedro", 1}) ? "sim" : "nao");
    printf("A pilha eh vazia: %s\n", PilhaEhVazia(pilha) ? "sim" : "nao");
    printf("O tamanho da pilha eh %d\n", PilhaTamanho(pilha));
    
    printf("Inserindo joao na pilha: %s\n", PilhaPush(pilha, (Item) {"joao", 2}) ? "sim" : "nao");
    printf("Inserindo guilherme na pilha: %s\n", PilhaPush(pilha, (Item) {"guilherme", 3}) ? "sim" : "nao");
    printf("Inserindo ana na pilha: %s\n", PilhaPush(pilha, (Item) {"ana", 4}) ? "sim" : "nao");
    printf("Inserindo maria na pilha: %s\n", PilhaPush(pilha, (Item) {"maria", 5}) ? "sim" : "nao");
    printf("Inserindo jose na pilha: %s\n", PilhaPush(pilha, (Item) {"jose", 6}) ? "sim" : "nao");
    PilhaPrint(pilha);


    bool resultado;
    Item item;
    resultado = PilhaPop(pilha, &item);
    if (resultado) {
        printf("Removeu o item: ");
        ItemPrint(item);
        printf("\n");
    } else
        printf("Nao removeu o item\n");
    
    resultado = PilhaPop(pilha, &item);
    if (resultado) {
        printf("Removeu o item: ");
        ItemPrint(item);
        printf("\n");
    } else
        printf("Nao removeu o item\n");


    resultado = PilhaPop(pilha, &item);
    if (resultado) {
        printf("Removeu o item: ");
        ItemPrint(item);
        printf("\n");
    } else
        printf("Nao removeu o item\n");


    resultado = PilhaPop(pilha, &item);
    if (resultado) {
        printf("Removeu o item: ");
        ItemPrint(item);
        printf("\n");
    } else
        printf("Nao removeu o item\n");


    PilhaPrint(pilha);


    printf("A pilha eh vazia: %s\n", PilhaEhVazia(pilha) ? "sim" : "nao");
    printf("O tamanho da pilha eh %d\n", PilhaTamanho(pilha));
    
    resultado = PilhaTopo(pilha, &item);
    if (resultado) {
        printf("O item no topo eh: ");
        ItemPrint(item);
        printf("\n");
    } else
        printf("Nao tem item na posicao\n");


    pilha = PilhaDestroi(pilha);
}

int main(){
  testaPilha();
  return 0;
}

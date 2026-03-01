
#include "fila.h"
#include <stdio.h>  
void testaFila();     
       
void testaFila() {
    Fila* fila = FilaCria(5);


    printf("A fila eh vazia: %s\n", FilaEhVazia(fila) ? "sim" : "nao");
    printf("O tamanho da fila eh %d\n", FilaTamanho(fila));
    printf("Inserindo pedro na fila: %s\n", FilaEnfileirar(fila, (Item) {"pedro", 1}) ? "sim" : "nao");
    printf("A fila eh vazia: %s\n", FilaEhVazia(fila) ? "sim" : "nao");
    printf("O tamanho da fila eh %d\n", FilaTamanho(fila));
    
    printf("Inserindo joao na fila: %s\n", FilaEnfileirar(fila, (Item) {"joao", 2}) ? "sim" : "nao");
    printf("Inserindo guilherme na fila: %s\n", FilaEnfileirar(fila, (Item) {"guilherme", 3}) ? "sim" : "nao");
    printf("Inserindo ana na fila: %s\n", FilaEnfileirar(fila, (Item) {"ana", 4}) ? "sim" : "nao");
    printf("Inserindo maria na fila: %s\n", FilaEnfileirar(fila, (Item) {"maria", 5}) ? "sim" : "nao");
    printf("Inserindo jose na fila: %s\n", FilaEnfileirar(fila, (Item) {"jose", 6}) ? "sim" : "nao");
    FilaPrint(fila);


    bool resultado;
    Item item;
    resultado = FilaDesenfileirar(fila, &item);
    if (resultado) {
        printf("Removeu o item: ");
        ItemPrint(item);
        printf("\n");
    } else
        printf("Nao removeu o item\n");
    FilaPrint(fila);
    
    resultado = FilaDesenfileirar(fila, &item);
    if (resultado) {
        printf("Removeu o item: ");
        ItemPrint(item);
        printf("\n");
    } else
        printf("Nao removeu o item\n");
    FilaPrint(fila);

    resultado = FilaDesenfileirar(fila, &item);
    if (resultado) {
        printf("Removeu o item: ");
        ItemPrint(item);
        printf("\n");
    } else
        printf("Nao removeu o item\n");
    FilaPrint(fila);

    resultado = FilaDesenfileirar(fila, &item);
    if (resultado) {
        printf("Removeu o item: ");
        ItemPrint(item);
        printf("\n");
    } else
        printf("Nao removeu o item\n");


    FilaPrint(fila);


    printf("A fila eh vazia: %s\n", FilaEhVazia(fila) ? "sim" : "nao");
    printf("O tamanho da fila eh %d\n", FilaTamanho(fila));
    printf("Inserindo pedro na fila: %s\n", FilaEnfileirar(fila, (Item) {"pedro", 1}) ? "sim" : "nao");
   
    FilaPrint(fila);


    resultado = FilaPrimeiro(fila, &item);
    if (resultado) {
        printf("O primeiro item eh: ");
        ItemPrint(item);
        printf("\n");
    } else
        printf("Nao tem item na posicao\n");


    // fila = FilaDestroi(fila);
    // fila = FilaDestroi(fila);
}

int main(){
  
  testaFila();
  return 0;
}
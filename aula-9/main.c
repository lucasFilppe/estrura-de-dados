#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main()
{
  printf("=== TESTE COM FORMATO (Nome|ID) ===\n\n");

  // 1. CRIAÇÃO
  Lista *minhaLista = ListaCria(5);

  // Preparando dados
    Item i1 = {"Mario", 1};
    Item i2 = {"Luigi", 2};
    Item i3 = {"Yoshi", 3};
    Item i4 = {"Toad", 4};
    Item i5 = {"Bowser", 5};
    Item i6 = {"Peach", 6}; // Item extra para testar erro

  // 2. INSERÇÃO
  printf("[2] Inserindo Elementos...\n");

  ListaInsereFim(minhaLista, i1);
  printf(" -> Inseriu: ");
  ItemPrint(i1);
  printf(" no Fim\n");

  ListaInsereFim(minhaLista, i2);
  printf(" -> Inseriu: ");
  ItemPrint(i2);
  printf(" no Fim\n");

  ListaInsereInicio(minhaLista, i3);
  printf(" -> Inseriu: ");
  ItemPrint(i3);
  printf(" no Inicio\n");

  // Mostra a lista completa com a sua formatação
  ListaPrint(minhaLista);

  ListaInsereMeio(minhaLista, i4, 1);
  printf(" -> Inseriu: ");
  ItemPrint(i4);
  printf(" na pos 1\n");
  ListaPrint(minhaLista);

  ListaInsereFim(minhaLista, i5);
  printf(" -> Inseriu: ");
  ItemPrint(i5);
  printf(" no Fim\n");
  ListaPrint(minhaLista);
  

  // Mostra a lista completa com a sua formatação
  //ListaPrint(minhaLista);

  // 3. PESQUISA
  printf("\n[3] Testando Busca...\n");
  Item recuperado;

  if (ListaPesquisa(minhaLista, "lucas", &recuperado))
  {
    printf(" -> Encontrado: ");
    ItemPrint(recuperado);
    printf("\n");
  }
  else
  {
    printf(" -> nao encontrado.\n");
  }

  // 4. REMOÇÃO
  printf("\n[4] Removendo Elementos...\n");

  // Remove do início (Yoshi)
  ListaRemoveInicio(minhaLista, &recuperado);
  printf(" -> Removeu Inicio: ");
  ItemPrint(recuperado);
  printf("\n");
  // 5. ESTADO FINAL
  ListaPrint(minhaLista);

  // Remove do Fim (Luigi estava no fim antes?)
  // Estado atual esperado antes de remover fim: [Toad, Mario, Luigi]
  ListaRemoveFim(minhaLista, &recuperado);
  printf(" -> Removeu Fim:    ");
  ItemPrint(recuperado);
  printf("\n");

  // 5. ESTADO FINAL
  ListaPrint(minhaLista);

  ListaDestroi(minhaLista);
  return 0;
}
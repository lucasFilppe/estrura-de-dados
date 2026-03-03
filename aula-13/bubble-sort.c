#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "item.h"

void troca(Item *i1, Item *i2)
{
  Item aux = *i1; // guarda o valor de item 1
  *i1 = *i2;      // copia o segundo para peimeiro
  *i2 = aux;      // copia o valor de aux para o segundo
}
/*Antes:  i1 = 5,  i2 = 3
Passo 1: aux = 5
Passo 2: i1 = 3
Passo 3: i2 = 5
Depois:  i1 = 3,  i2 = 5  ✓*/

void bubbleSort(Item *v, int n)
{
  if (!v || n <= 0)
    return; // sai da função se alguma das condiçoes for verdadeira

  bool trocou = false; //

  for (int i = 0; i < n - 1; i++)
  {
    trocou = false;
    /*Array: [5, 3, 1, 2]  (n=4)
    'Precisamos de 3 passadas, não 4!
      Passada 1: compara 4 elementos
Passada 2: compara 3 elementos
Passada 3: compara 2 elementos
Passada 4: não é necessária (1 elemento)*/
    for (int j = 1; j < n - i; j++)
    {
      if (ItemCompara(v[j - 1], v[j]) == MAIOR)
      {
        trocou = true;
        troca(&v[j - 1], &v[j]);
      }
    }
    if (!trocou)
      return;
  }
}
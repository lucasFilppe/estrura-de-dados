#include <stdio.h>

/*Então,f(n) =2(n−1)paran>0, para o melhor caso, pior caso e caso
***************
**************
*/

void maior_Menor(int *A, int n, int *ponteiro_Max, int *ponteiro_Min){
  *ponteiro_Max = A[0];
  *ponteiro_Min = A[0];

  for(int i = 1; i < n; i++){
    if(A[i] > *ponteiro_Max)//comparação envolvendo os elementos
      *ponteiro_Max = A[i];

    if(A[i] < *ponteiro_Min)//comparação envolvendo elementos
      *ponteiro_Min = A[i];
  }
}

int main(){

  int vetor[] = {12 , 124, 3, 231, 453, 23};

  int maior, menor, n = 6;

  maior_Menor(vetor, n, &maior, &menor);

  printf("Maior %d\n", maior);
  printf("Menor %d\n", menor);

  return 0;
}
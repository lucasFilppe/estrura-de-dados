#include <stdio.h>

int Max(int *A, int n){
  int maior = A[0];

  for (int i = 1; i < n; i++)
  {
    if(A[i] > maior){ //comparação envolvendo os elementoa
      maior = A[i];
    }
  }
  return maior;
}
int main(){

  int v[] = {1, 2, 7, 3};
  int maior = Max(v, 4);

  printf("maior = %d\n", maior);
  return 0;
}
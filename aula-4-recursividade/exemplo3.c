#include <stdio.h>

int potencia(int a, int b) {
    printf("Entrando em potencia(a=%d, b=%d)\n", a, b);   // DESCIDA

    if (b == 0) {
        printf("b == 0, retornando 1\n");                // CASO BASE
        return 1;
    }

    int r = a * potencia(a, b - 1);

    printf("Retornando %d para potencia(a=%d, b=%d)\n", r, a, b);  // SUBIDA

    return r;
}

int main(){
  int base = 2, expoente = 3;

  int resultado = potencia(base, expoente);
  printf("Resultado %d\n", resultado);

  return 0;
}
#include <stdio.h>
#include "convert.h"

int main(){
  float celsius;

  printf("Digite o valor da temperatura erm celsius: ");
  scanf("%f", &celsius);

  float farenheit = convert_Celsius_to_Fahrenheit(celsius);

  printf("A temperatura em Farenheit eh: %.2f\n", farenheit);

  return 0;
}
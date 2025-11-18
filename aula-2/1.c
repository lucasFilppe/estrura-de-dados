#include <stdio.h>
void quad(int n)
{
  n = n * n;
  printf("n = %d\n", n);
}

int main()
{
  int n = 3;
  quad(n);
  printf("n = %d\n", n);
  return 0;
}
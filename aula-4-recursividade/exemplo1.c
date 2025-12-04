#include <stdio.h>

void func ( int n ) {
  printf("%d\n", n );
  func (n) ;
}

int main(){
  int n = 1;
  func(n);

  return 0;
}
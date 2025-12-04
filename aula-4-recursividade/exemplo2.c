#include <stdio.h>

void func ( int n ) {
  printf("%d\n", n );

  //comdição de parada
  if(n > 0){
    func (n - 1) ;
    printf("* ");
  }
}
  

int main(){
  int n = 4;
  func(n);

  return 0;
}
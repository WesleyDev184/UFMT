#include <stdio.h>
#include <stdlib.h>

int main(){
 
 int n;
 
 scanf("%d", &n);
 
 for(int i=1;i<=n*4;i+=4){
  printf("%d ", i);
  printf("%d ", i+1);
  printf("%d ",i+2);
  printf("PUM\n");
 }
}
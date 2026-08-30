#include <stdio.h>
int main(void){
  int carry=0;
  int n=5;
  int A[4] = {0,1,1,0};
  int B[4] = {1,0,1,1};
  int C[5] = {0,0,0,0,0};
  for (int i=0; i<n;++i){
    C[i] = (A[i]+B[i]+carry)%2;
    if (A[i]+B[i]+carry>=2){
      carry = 1;
      
    } else {
      carry = 0;
    }
    
  }
  C[n-1] = carry;
  for (int i=0; i<n;++i){
    printf("%d ",C[i]);
  }
  printf("\n");
  
}

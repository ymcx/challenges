#include <stdio.h>
#include <stdlib.h>

void merge(int array[8], int p, int q, int r){
  int nL=q-p+1;
  int nR=r-q;

  int *L=malloc(sizeof(int)*nL);
  int *R=malloc(sizeof(int)*nR);

  for (int i=0;i<nL;++i){
    L[i] = array[p+i];
  }
  for (int i=0;i<nR;++i){
    R[i] = array[q+i+1];
  }

  int i=0;
  int j=0;
  int k=p;

  while (i<nL && j<nR){
    if (L[i] <= R[j]){
      array[k++] = L[i++];
    } else {
      array[k++] = R[j++];
    }
  }

  while (i<nL){
    array[k++] = L[i++];
  }
  while (j<nR){
    array[k++] = R[j++];
  }

  free(L);
  free(R);
}

void mergesort(int array[8],int p,int r){
  if (p>=r){
    return;
  }

  int q=(p+r)/2;
  mergesort(array, p, q);
  mergesort(array, q+1, r);
  merge(array,p,q,r);
}

int main(void){
  int array[8]={2,4,6,7,1,2,3,5};

  printf("MERGE\n");
  
  for (int i=0;i<8;++i){
    printf("%d ",array[i]);
  }
  printf("\n");


  mergesort(array,0,7);
  
  for (int i=0;i<8;++i){
    printf("%d ",array[i]);
  }
  printf("\n");
}

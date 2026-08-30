#include <stdio.h>
#include <stdlib.h>

#define X 5

int merge(int array[X], int p, int q, int r){
  int inversions=0;


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
      ++inversions;
      array[k++] = R[j++];
    }
  }

  while (i<nL){
    array[k++] = L[i++];
  }
  while (j<nR){
    array[k++] = R[j++];
    ++inversions;
  }

  free(L);
  free(R);


  return inversions;
}

int mergesort(int array[X],int p,int r){
  int inversions=0;



  if (p>=r){
    return inversions;
  }

  int q=(p+r)/2;
  inversions+=mergesort(array, p, q);
  inversions+=mergesort(array, q+1, r);
  inversions+=merge(array,p,q,r);


  return inversions;
}


int main(void){
  // int array[X]={2, 3, 8, 6, 1, 9, 10, 0};
  int array[X]={2, 3, 8, 6, 1};

  printf("MERGE\n");
  
  for (int i=0;i<X;++i){
    printf("%d ",array[i]);
  }
  printf("\n");


  int inversions=mergesort(array,0,X-1);
  printf("%d\n",inversions);
  
  for (int i=0;i<X;++i){
    printf("%d ",array[i]);
  }
  printf("\n");
}

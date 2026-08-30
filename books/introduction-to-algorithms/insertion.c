#include <stdio.h>
#include <stdlib.h>

void sort(int array[10]){
  for (int i=1; i<10;++i){
    int key=array[i];
    int j=i-1;
    while (j>=0 && key >array[j]){
      array[j+1] = array[j];
      j -=1;
    }
    array[j+1]=key;
  }
}

int main(void){
  int *array=malloc(sizeof(int)*10);
  int b=-1;
  array[++b]=4;
  array[++b]=3;
  array[++b]=2;
  array[++b]=1;
  array[++b]=5;
  array[++b]=6;
  array[++b]=0;
  array[++b]=9;
  array[++b]=8;
  array[++b]=7;
  for (int i=0; i<10;++i){
    printf("%d ",array[i]);
  }
  printf("\n");
  sort(array);
  for (int i=0; i<10;++i){
    printf("%d ",array[i]);
  }
  free(array);
  printf("\n");
}

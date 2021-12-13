#include<stdio.h>
#include<stdlib.h>

int selecao (int* array, int L, int R) {
   int aux, i, j = L;
   for (i = L; i < R; ++i)
      if (array[i] <= array[R]) {
         aux = array[j];
         array[j] = array[i];
         array[i] = aux;
         ++j;
      }
   aux = array[j];
   array[j] = array[R];
   array[R] = aux;
   return j;
}


void quicksort(int* array, int L, int R, int k){
    if(L<R){
        int j = selecao(array, L, R);

        if(k-1 == j){
            return;
        }else if(k-1 < j){
            quicksort(array, L, j-1, k);
        }else{
            quicksort(array, j+1, R, k);
        }
    }
}


int main(){
    int K, N, i=0;
    int* array;

    do{
        scanf("%d", &K);
    }while(K<1 || K>1000);

    do{
        scanf("%d", &N);
    }while(N<0 || N>1000);

    array = malloc(N*sizeof(int));
    for(i=0; i<N; i++){
        scanf("%d", &array[i]);
    }

    quicksort(array, 0, N-1, K);

    printf("%do menor elemento eh o %d\n", K, array[K-1]);

    for(i=0;i<N;i++){
        printf("%d ", array[i]);
    }
    free(array);
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#define MAX 100000

int count(int* v, int p1, int p2, int cont, int K){
    if(p1==p2) return cont;
    else{
        if( p1<p2 && v[p1]>K*v[p2]){
            cont++;
        }
        count(v, p1+1, p2, cont, K);
    }
}

int merge(int* v, int p, int q, int N, int cont, int K){
    int *aux, p1, p2, tamanho, i, j, x;
    int fim1 = 0, fim2 = 0;
    tamanho = N-p+1;
    p1 = p;
    p2 = q+1;
    aux = (int *) malloc(tamanho*sizeof(int));
    if(aux != NULL){
        for(i = 0 ; i < tamanho; i++){
            if(!fim1 && !fim2){
                if(v[p1] > K * v[p2] && p1 < p2){
                    cont = count(v, p1, p2, cont, K);
                }
                if(v[p1] < v[p2]){
                    aux[i] = v[p1++];
                }else{

                    aux[i] = v[p2++];
                }
                if(p1>q) fim1 = 1;
                if(p2>N) fim2 = 1;
            }else{
                if(!fim1)
                    aux[i]= v[p1++];
                else
                    aux[i]= v[p2++];
            }
        }
        for(j=0, x = p; j < tamanho; j++,x++){
            v[x]=aux[j];
        }
    }
    free(aux);
    return cont;
}

int mergesort(int* v, int p, int N, int cont, int K){
    int q;
    if(p<N){
        q = (p+N)/2;
        mergesort(v, p, q, cont, K);
        mergesort(v, q+1, N, cont, K);
        cont = merge(v, p, q, N, cont, K);
    }
    return cont;
}

int main(){
    int *v;
    int N, i, K, result, p = 0;

    do{
        scanf("%d", &N);
    }while(N<0 || N>MAX);

    v = malloc(N * sizeof(int));
    
    do{
        scanf("%d", &K);
    }while(K<0);
    
    for(i=0; i < N; i++){
        scanf("%d", &v[i]);
    }

    result = mergesort(v, p, N-1, result, K);
    printf("%d", result);
    return 0;
}
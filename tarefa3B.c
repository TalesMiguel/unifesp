#include <stdio.h>
#include <stdlib.h>

int insertion_sort(int n, int *vet, int nivel){
    int chave, posicao, i = nivel;

    chave = vet[nivel];
    posicao = (int)nivel/2;

    if (chave > vet[posicao]){
        while (chave > vet[posicao])
            if(posicao == nivel) break;
            else posicao++;
    } else if (chave < vet[posicao]){
        while (chave < vet[posicao]) 
            if(chave > vet[posicao-1]) break;
            else posicao--;
    }

    while (i>posicao){
        vet[i] = vet[i-1];
        i--;
    }

    vet[posicao] = chave;

    // M linhas
    printf("%d %d %d\n", (n-nivel), chave, posicao);
    nivel++;

    if (nivel != n) insertion_sort(n, vet, nivel);
    else return 0;
}

int main(void) {
    int n, i, *vet, cont, nivel = 1;
    scanf("%d", &n);

    vet = (int*) malloc(n*sizeof(int));

    for (i = 0; i < n; i++){
        scanf(" %d", &vet[i]);
    }

    insertion_sort(n, vet, nivel);

    for (i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
    return 0;
}
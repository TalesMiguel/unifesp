#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main(){
    int i, aux, contador, N, teste = 0;
    int *numeros;

    do{
        scanf("%d", &N);
    }while(N<0 || N>1000);

    numeros = malloc(N * sizeof(int));

    char proxChar;
    while(scanf("%d%c", &numeros[i], &proxChar) == 2) { 
        i++;
        if(proxChar == '\n') break;
        if (i==N) break;
    }

    // Bubblesort:
    for (contador = 1; contador < N; contador++) {
        for (i = 0; i < N - 1; i++) {
            if (numeros[i] > numeros[i + 1]) {
                aux = numeros[i];
                numeros[i] = numeros[i + 1];
                numeros[i + 1] = aux;
                teste++;
            }
        }
    }
    for (i = 0; i < N-1; i++) {
        printf("%d ", numeros[i]);
    }
    printf("%d\n", numeros[N-1]);
    if(teste%2==0){
        printf("Carlos");
    }else{
        printf("Marcelo");
    }
		free(numeros);
    return 0;

 } 
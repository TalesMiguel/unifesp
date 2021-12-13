//ARVORE BINARIA AVL

// ENTRADA:
    // PRIMEIRA LINHA
    // numeros inteiros a serem inseridos na arvore, if n < 0 -> break (-1 n deve entrar)

    // SEGUNDA LINHA
    // numeros inteiros a serem pesquisados na árvore, if n < 0 -> break
    // if n not in arvore, add n. Else, remove n
    // pesquisa numeros inteiros positivos. se existirem na arvore, retira eles. Senão, adiciona. 

    //TERCEIRA LINHA
    // unico numero inteiro n > 0 a ser pesquisado 
    // pesquisa numeros inteiros positivos.

// SAIDA:
    // PRIMERA LINHA
    // {Altura max da AVL a partir do seu no raiz}, {altura sub-arvore esquerda}, {altura sub-arvore direita}

    // SEGUNDA LINHA
    // If n not in arvore:
        // return 'Valor nao encontrado'
    // {Altura do no pesquisado da linha 3}, {altura esquerda}, {altura direira}

//============================////============================////============================////========

// Nome: Tales Miguel Machado Pereira
// RA: 140247

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct reg {
   int chave;
   int conteudo;
   struct reg *esq, *dir; 
} noh; // nó

// Recebe uma árvore de busca r e
// um número k. Devolve um nó
// cuja chave é k; se tal nó não existe,
// devolve NULL.

noh *
busca (arvore r, int k) {
    if (r == NULL || r->chave == k)
       return r;
    if (r->chave > k)
       return busca (r->esq, k);
    else
       return busca (r->dir, k);
}

// A função recebe uma árvore de busca r
// e uma folha avulsa novo e insere a folha
// na árvore de modo que a árvore continue
// sendo de busca. A função devolve a raiz 
// da árvore resultante.

arvore 
insere (arvore r, noh *novo) {  
    if (r == NULL) return novo;
    if (r->chave > novo->chave) 
       r->esq = insere (r->esq, novo);
    else 
       r->dir = insere (r->dir, novo);
    return r;
}

// Recebe uma árvore não vazia r.
// Remove a raiz da árvore e rearranja
// a árvore de modo que ela continue sendo
// de busca. Devolve o endereço da
// nova raiz.

arvore 
removeraiz (arvore r) {  
    noh *p, *q;
    if (r->esq == NULL) {
       q = r->dir;
       free (r);
       return q;
    }
    p = r; q = r->esq;
    while (q->dir != NULL) {
       p = q; q = q->dir;
    }
    // q é nó anterior a r na ordem e-r-d
    // p é pai de q
    if (p != r) {
       p->dir = q->esq;
       q->esq = r->esq;
    }
    q->dir = r->dir;
    free (r);
    return q;
}

int main(){
    int arvore, pesquisa1, pesquisa2;
    int* array;

    do{
        scanf("%d", &arvore);
    }while(arvore>0);
    array = malloc(arvore*sizeof(int)); // vetor iniciado dinamicamente em ref a N

    do{
        scanf("%d", &pesquisa1); // tamanho do vetor
    }while(pesquisa1>0);

    do{
        scanf("%d", &pesquisa2); // tamanho do vetor
    }while(pesquisa2>0);

    
    for(i=0; i<N; i++){
        scanf("%d", &array[i]);
    }

    binarysearch(array, 0, N-1, K);
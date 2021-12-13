// Nome: Tales Miguel Machado Pereira
// RA: 140247

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct arv{
    int val;
    struct arv *esq, *dir;
}TArv;
typedef TArv *node;


node insere (node a, int c){ // insere nó/valor
    if (a == NULL) {
        node novo=(node)malloc(sizeof(TArv));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->val = c;
        a = novo;
    }
    else if (c < a->val) a->esq = insere(a->esq,c);
    else a->dir = insere(a->dir,c);
    return a;
}


node busca (node a, int c) { // busca nó
    if (a == NULL || a->val == c) return a;
    else if(c < a->val) return(busca(a->esq,c));
    else if (c > a->val) return(busca(a->dir,c));
}


node libera(node a){ //limpa a árvore
    if (a == NULL) return a;
    libera(a->esq);
    libera(a->dir);
    free(a);
}


node removeNo(node r, int v){ // remove o nó passado
    if (r == NULL) return r;
    else{
        if (r->val > v) r->esq = removeNo(r->esq, v);
        else if (r->val < v) r->dir = removeNo(r->dir, v);
        else {
            if ((r-> esq == NULL) && (r-> dir == NULL)){
                r=NULL;
            }
            if (r->esq == NULL) {
                node t = r;
                r = r->dir;
            }
            if (r->dir == NULL) {
                node t = r;
                r = r->esq;
            }
            else {
                node f = r->esq;
                while (f->dir != NULL) f = f->dir;
                r->val = f->val;
                f->val = v;
                r->esq = removeNo(r->esq,v);
            }
        }
    }
    return r;
}


int maior(int a, int b){
    if (a>b) return a;
    else return b;
}


int altura(node r) { // altura do nó (começa em 0)
    if (r == NULL) 
        return 0;
    else {
        int altEsq = altura (r->esq);
        int altDir = altura (r->dir);
        if (altEsq < altDir) return altDir + 1;
        else return altEsq + 1;
    }
}


void imprime_crescente(node a){
    if (a != NULL){
        imprime_crescente(a->esq);
        printf("%d, ", a->val);
        imprime_crescente(a->dir);
    }
}

int main() {
    int temp, j, val_altura[3], pesquisa;
    node arv = NULL;

    do{
        scanf("%d", &temp);
        if(temp < 0) break; // caso de parada
            arv = insere(arv, temp);
    }while(temp >= 0);

    val_altura[1] = altura(arv->esq);
    val_altura[2] = altura(arv->dir);
    val_altura[0] = maior(val_altura[1], val_altura[2]);

    //valores pra pesquisar:
    do{
        scanf("%d", &pesquisa);
        if (pesquisa > 0) { //caso de parada
            if(busca(arv, pesquisa) != NULL) removeNo(arv, pesquisa);
            else insere(arv, pesquisa);
        }
    } while(pesquisa >= 0);

    // pesquisa de um só nó
    scanf("%d", &pesquisa);

    printf("\n%i, %i, %i", val_altura[0], val_altura[1], val_altura[2]);

    arv = busca(arv, temp);
    if (arv == NULL) printf("\nValor nao encontrado");
    else printf("\n%i, %i, %i", maior(altura(arv->esq), altura(arv->dir)), altura(arv->esq), altura(arv->dir));

    libera(arv);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
 
float arr[100];
int i=0;
struct reg {
    float item; 
    struct reg *prox; 
};
typedef struct reg NO;


int hash(float chave, int tamanho) {
    return abs(chave) % tamanho;
}


int busca(float chave, NO **HASH, int tamanho) {
    int pos = hash(chave, tamanho);
    NO *lista = HASH[pos];
    while (lista != NULL) {
        if (chave == lista->item) return 1;
        lista = lista->prox;
    }
    return 0;
}
 

void criaTable(NO **HASH, int tamanho) {
    for(i=0; i<tamanho; i++){
        HASH[i]=NULL;         
    }
}


void delete(float chave, NO **HASH, int tamanho) { 
    int pos = hash(chave, tamanho);
    if (!busca(chave,HASH, tamanho)) return;
    NO **lista = &HASH[pos];
    NO *anterior = *lista;
    NO *proximo = (*lista)->prox;
    NO *guarda = HASH[pos];
    NO *K = (*lista)->prox;
    while (*lista!=NULL) {
        if ((*lista)->item == chave) {    
            if (*lista == anterior) {
                (*lista)->prox=proximo->prox;
                (*lista)->item=proximo->item;
                HASH[pos]=guarda;
            }else {
                anterior->prox=proximo;
                HASH[pos]=guarda;
            }
            return;
        }    
        anterior = *lista;
 
        *lista = (*lista)->prox;
        proximo = (*lista)->prox;         
    }
    HASH[pos]=guarda; 
    free(anterior);
    free(proximo);
    free(guarda);    
}


void insertInTable(int item, NO **HASH, int tamanho) {
    int pos = hash(item, tamanho);
    NO **lista = &HASH[pos];

    if (*lista == NULL) {
        *lista = (NO *) malloc(sizeof(NO));
        if (*lista == NULL) {
        exit(1);
        }
        (*lista)->item=item;
        (*lista)->prox=NULL;
    }else {
        NO *guarda= HASH[pos];
        while ((*lista)->prox != NULL){
            *lista=(*lista)->prox; 
        }
        (*lista)->prox=(NO *) malloc(sizeof(NO));
        
        if ((*lista)->prox == NULL) {
            exit(1);
        }
        *lista=(*lista)->prox;
        (*lista)->item=item;
        (*lista)->prox=NULL; 
        HASH[pos]=guarda; 
    }
}


void insere(int item, NO **HASH, int tamanho) { 
    insertInTable(item,HASH, tamanho);
}


void printTable(int pos, NO **HASH) {
    NO *lista = HASH[pos];
    while (lista != NULL) {
        arr[i] = lista->item;
        printf(" %g", lista->item);
        lista = lista->prox;
        i++;
    }
} 


void imprime(NO **HASH, int tamanho) {
    int i;
    puts("");
    for (i=0; i<tamanho; i++) {
        printf("\nHASH[%d] ->",i);
        printTable(i,HASH);
    }
}


void libera(NO **HASH, int tamanho) {
    int i;
    NO *next;
    for(i=0; i<tamanho; i++) {
        NO **lista=&HASH[i]; 
        while(*lista!= NULL) {
            next = (*lista)->prox;                
            free(*lista);
            *lista = next; 
        } 
    }
    free(next);      
}


int main(){
    int tamanho, numero, linha, x, w, i;
    char opcao;
    float item;
 
    scanf("%d", &tamanho);
    NO *HASH[tamanho]; 
    criaTable(HASH, tamanho);
 
    for (i=0; i >= 0; i++) { 
        scanf("%d", &numero);   
        if (numero==-1) break;
        insere(numero,HASH, tamanho);
    }
    scanf("%d", &x);
    scanf("%d", &linha);
    if(busca(x,HASH, tamanho)==0){
        printf("Valor não encontrado\n");
    }
    printf("[%d]", linha);
    if(busca(x,HASH, tamanho)==1){
        delete(x,HASH, tamanho);
    }
    printTable(linha,HASH);
}
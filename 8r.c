#include <stdio.h>
#include <stdlib.h>

typedef struct arv{
  int val;
  struct arv* esq;
  struct arv* dir;
}TArv;
typedef TArv *PArv;

//Libera AB
PArv libera(PArv a){
  if (a != NULL){
    libera(a->esq);
    libera(a->dir);
    free(a);
  }
  return NULL;
}

//insere na ABB
PArv insereABB (PArv a, int c)
{
  // printf("\nentrei com o valor %d", c);
  if (a == NULL) 
  {
    PArv novo=(PArv)malloc(sizeof(TArv));
    novo->esq = NULL;
    novo->dir = NULL;
    novo->val = c;
    a = novo;
  }
  else if (c < a->val) a->esq = insereABB(a->esq,c);
  else a->dir = insereABB(a->dir,c);
  return a;
}

//faz busca na ABB
PArv buscaABB (PArv a, int c) 
{
  if (a==NULL) return NULL;
  else if(c < a->val) return(buscaABB(a->esq,c));
  else if (c > a->val) return(buscaABB(a->dir,c));
  else return a;
}

//remove da ABB
PArv removeABB(PArv r, int v)
{
 if (r->val > v) r->esq = removeABB(r->esq, v);
 else if (r->val < v) r->dir = removeABB(r->dir, v);
 else if (r == NULL) return NULL;
 else { 
  if (r->esq == NULL) {
    PArv t = r;
    r = r->dir;
  }
  if (r->dir == NULL) {
    PArv t = r;
    r = r->esq;
  }
  else if (r->esq == NULL && r->dir == NULL) r = NULL;
  else {
    PArv f = r->esq;
    while (f->dir != NULL) f = f->dir;
    r->val = f->val;
    f->val = v;
    r->esq = removeABB(r->esq,v);
  }
 }
 return r;
}

int maior(int a, int b){
  if (a>b) return a;
  else return b;
}

int altura(PArv r) {
  if (r == NULL) 
      return 0; // altura da árvore vazia
   else {
      int he = altura (r->esq);
      int hd = altura (r->dir);
      if (he < hd) return hd + 1;
      else return he + 1;
   }
}

//Imprime ABB em ordem
void imprime_crescente(PArv a){
  if (a != NULL){
    imprime_crescente(a->esq); /* mostra sae */
    printf("%d, ", a->val); /* mostra raiz */
    imprime_crescente(a->dir); /* mostra sad */
  }
}

int main() {
  int temp, j, val_altura[3];
  PArv arv = NULL;
  
  //Cria ABB a certin
  do{
    scanf(" %d", &temp);
    if(temp < 0) break;
    arv = insereABB(arv, temp);
  }while(temp >= 0);

  val_altura[1] = altura(arv->esq);
  val_altura[2] = altura(arv->dir);
  val_altura[0] = maior(val_altura[1], val_altura[2]);

  //valores para a chave de pesquisa:
  do{
    scanf(" %d", &temp);
    if (temp > 0) {
      if(buscaABB(arv, temp) != NULL) removeABB(arv, temp);
      else insereABB(arv, temp);
    }
  } while(temp >= 0);

  // valor a ser pesquisado na árvore:
  scanf(" %d", &temp);

  printf("\n%i, %i, %i", val_altura[0], val_altura[1], val_altura[2]);

  arv = buscaABB(arv, temp);
  if (arv != NULL) printf("\n%i, %i, %i", maior(altura(arv->esq), altura(arv->dir)), altura(arv->esq), altura(arv->dir));
  else printf("\nValor nao encontrado");
  
  libera(arv);
  return 0;
}

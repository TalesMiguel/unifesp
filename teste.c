#include <stdio.h>
#include <stdlib.h>
 
#define RED 1
#define BLACK 0
 
typedef struct arv{
  int info; // antigo 'val'
  int altura; // altura da sub-arvore
  struct arv* esq;
  struct arv* dir;
  int cor;
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
 
int altura_NO(PArv no){
    if(no == NULL) return -1;
    else return no->altura;
}
 
int cor(PArv no){ // novo
    if(no == NULL) return BLACK;
    else return no->cor;
}
 
void trocaCor(PArv no){ // novo
    no->cor = !no->cor;
    if(no->esq != NULL){
        no->esq->cor = !no->esq->cor;
    }if(no->dir != NULL){
        no->dir->cor = !no->dir->cor;
    }
}
 
PArv rotacionaEsquerda(PArv a){
    PArv b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    b->cor = a->cor;
    a->cor = RED;
    return b;
}
 
PArv rotacionaDireita(PArv a){
    PArv b = a->esq;
    a->esq = b->dir;
    b->dir = a;
    b->cor = a->cor;
    a->cor = RED;
    return b;
}
 
PArv move2EsqRed(PArv no){
    trocaCor(no);
    if(cor(no->dir->esq) == RED){
        no->dir = rotacionaDireita(no->dir);
        no = rotacionaEsquerda(no);
        trocaCor(no);
    }
    return no;
}
 
PArv move2DirRed(PArv no){
    trocaCor(no);
    if(cor(no->esq->esq) == RED){
        no = rotacionaDireita(no);
        trocaCor(no);
    }
    return no;
}
 
PArv balancear(PArv no){
    if(cor(no->dir) == RED){
        no = rotacionaEsquerda(no);
    }
    if(no->esq != NULL && cor(no->dir) == RED && cor(no->esq->esq) == RED){
        no = rotacionaDireita(no);
    }
    if(cor(no->esq)==RED && cor(no->dir)==RED){
        trocaCor(no);
    }
    return no;
}
 
// PArv fatorBalanceamento_NO(PArv no){
//     return labs (altura_NO(no->esq) - altura_NO(no->dir));
// }
 
// PArv rotacaoLL(PArv raiz){
//     PArv no = raiz->esq;
//     raiz->esq = no->dir;
//     no->dir = raiz;
//     raiz->altura = maior(altura_NO(raiz->esq), altura_NO(raiz->dir))+1;
//     no->altura = maior(altura_NO(no->esq), raiz->altura) +1;
//     raiz = no;
// }
 
// PArv rotacaoRR(PArv raiz){
//     PArv no = raiz->dir;
//     raiz->dir = no->esq;
//     no->esq = raiz;
//     raiz->altura = maior(altura_NO(raiz->esq), altura_NO(raiz->dir))+1;
//     no->altura = maior(altura_NO(no->dir), raiz->altura) +1;
//     raiz = no;
// }
 
// void rotacaoLR(PArv raiz){
//     rotacaoRR(raiz->esq); // (&raiz)->esq
//     rotacaoLL(raiz);
// }
 
// void rotacaoRL(PArv raiz){
//     rotacaoLL(raiz->dir); // (&raiz)->dir
//     rotacaoRR(raiz);
// }
 
PArv insereNO(PArv no, int valor, int *resp){
    if(no == NULL){
        PArv novo;
        novo = (PArv)malloc(sizeof(TArv));
        if(novo == NULL){
            *resp = 0;
            return NULL;
        }
        novo->info=valor;
        novo->cor = RED;
        novo -> dir = NULL;
        novo ->esq = NULL;
        *resp = 1;
        return novo;
    }
    if(valor == no->info){
        *resp=0;
    }else{
        if(valor < no->info){
            no->esq = insereNO(no->esq, valor, resp);
        }else{
            no->dir = insereNO(no->dir, valor, resp);
        }
    }
    if(cor(no->dir)==RED && cor(no->esq)==BLACK){
        no = rotacionaEsquerda(no);
    }
    if(cor(no->esq)==RED && cor(no->esq->esq)==RED){
        no = rotacionaDireita(no);
    }
    if(cor(no->esq) == RED && cor(no->dir)==RED){
        trocaCor(no);
    }
    return(no);
}
 
PArv removerMenor(PArv no){
    if(no->esq == NULL){
        free(no);
        return NULL;
    }
    if(cor(no->esq) == BLACK && cor(no->esq->esq)==BLACK){
        no = move2EsqRed(no);
    }
    no->esq = removerMenor(no->esq);
    return balancear(no);
}
 
PArv procuraMenor(PArv atual){
    PArv no1 = atual;
    PArv no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}
 
PArv remove_NO(PArv no, int valor){
    if(valor<no->info){
        if(cor(no->esq) == BLACK && cor(no->esq->esq)==BLACK){
            no = move2EsqRed(no);
        }
        no ->esq = remove_NO(no->esq, valor);
    }else{
        if(cor(no->esq)==RED){
            no = rotacionaDireita(no);
        }
        if(valor == no->info && (no->dir == NULL)){
            free(no);
            return NULL;
        }
        if(cor(no->dir)==BLACK&&cor(cor(no->dir->esq)==BLACK)){
            no = move2DirRed(no);
        }
        if(valor==no->info){
            PArv x = procuraMenor(no->dir);
            no -> info = x->info;
            no->dir = removerMenor(no->dir);
        }else{
            no->dir = remove_NO(no->dir, valor);
        }
    }
    return balancear(no);
}
 
int insere_ArvLLRB(PArv raiz, int valor){
    int resp;
    raiz = insereNO(raiz, valor, &resp);
    if((raiz) != NULL){
        (raiz)->cor = BLACK;
    }
    return resp;
}
 
int remove_ArvLLRB(PArv raiz, int valor){
    PArv no = raiz;
    raiz = remove_NO(no,valor);
    if(raiz != NULL){
        raiz->cor = BLACK;
    } return 1;
}
 
//insere na AVL
// PArv insereAVL (PArv raiz, int valor)
// {
//     int res;
//     if (raiz == NULL){
//         PArv novo=(PArv)malloc(sizeof(TArv));
//         if (novo == NULL){
//             return 0; // alocação de memoria falhou -> não da pra inserir nó
//         }
//         novo->esq = NULL;
//         novo->dir = NULL;
//         novo->info = valor;
//         raiz = novo;
//         return 1;
//     }
//     PArv atual = raiz;
//     if (valor < atual->info) {
//         if((res=insereAVL(&(atual->esq), valor))==1){ // retira o & ?
//             if(fatorBalanceamento_NO(atual) >= 2){
//                 if (valor < (raiz)->esq->info){
//                     rotacaoLL(raiz);
//                 }else{
//                     rotacaoLR(raiz);
//                 }
//             }
//         }
//     }
//     else{
//         // if(valor > atual -> info){
//             if((res=insereAVL(&(atual->dir), valor)) == 1){
//                 if(fatorBalanceamento_NO(atual)>=2){
//                     if(raiz ->dir->info < valor){
//                         rotacaoRR(raiz);
//                     }else{
//                         rotacaoRL(raiz);
//                     }
//                 }
//             }
//         // }
//     }
//     atual->altura = maior(altura_NO(atual->esq), altura_NO(atual->dir))+1;
//     return res; // return raiz
// }
 
//faz busca na ABB
PArv buscaABB (PArv a, int c) 
{
  if (a==NULL) return NULL;
  else if(c < a->info) return(buscaABB(a->esq,c));
  else if (c > a->info) return(buscaABB(a->dir,c));
  else return a;
}
 
//remove da ABB
// PArv removeAVL(PArv raiz, int valor)
// {
//     int res;
//     if (raiz == NULL) return NULL;
//     if (raiz->info > valor){
//         // raiz->esq = removeAVL(raiz->esq, valor);
//         if((res=removeAVL(&(raiz)->esq,valor))==1){
//             if(fatorBalanceamento_NO(raiz)>=2){
//                 if(altura_NO(raiz->dir->esq) <= altura_NO(raiz->dir->dir)){
//                     rotacaoRR(raiz);
//                 }
//                 else rotacaoRL(raiz);
//             }
//         }
//     }
        
//     if (raiz->info < valor){
//     // raiz->dir = removeAVL(raiz->dir, valor);
//         if((res=removeAVL(&(raiz)->dir, valor))==1){
//             if(fatorBalanceamento_NO(raiz) >=2){
//                 if(altura_NO(raiz->esq->dir) <=altura_NO(raiz->esq->esq)){
//                     rotacaoLL(raiz);
//                 }else{
//                     rotacaoLR(raiz);
//                 }
//             }
//         }
//     }
//     if (raiz->info==valor){
//         if((raiz->esq==NULL || raiz->dir==NULL)){
//             PArv oldNode = raiz;
//             if(raiz->esq != NULL){
//                 raiz = raiz->esq;
//             }else{
//                 raiz=raiz->dir;
//             }
//             free(oldNode);
//         }else { // no com 2 filhos
//             PArv temp = menor(raiz->dir);
//             raiz->info = temp ->info;
//             removeAVL(&(raiz->dir), raiz->info);
//             if(fatorBalanceamento_NO(raiz)>=2){
//                 if(altura_NO(raiz->esq->dir) <= altura_NO(raiz->esq->esq)){
//                     rotacaoLL(raiz);
//                 }else{
//                     rotacaoLR(raiz);
//                 }
//             }
//             return 1;
//         }
//     return res;
// }
 
int maior(int a, int b){
  if (a>b) return a;
  else return b;
}
 
int menor(PArv atual){
    PArv no1 = atual;
    PArv no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2 ->esq;
    }
    return no1;
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
    printf("%d, ", a->info); /* mostra raiz */
    imprime_crescente(a->dir); /* mostra sad */
  }
}
 
int main() {
  int temp, j, info_altura[3];
  PArv arv = NULL;
  
  //Cria ABB a certin
  do{
    scanf(" %d", &temp);
    if(temp < 0) break;
    arv = insere_ArvLLRB(arv, temp);
  }while(temp >= 0);
 
  info_altura[1] = altura(arv->esq);
  info_altura[2] = altura(arv->dir);
  info_altura[0] = maior(info_altura[1], info_altura[2]);
 
  //valores para a chave de pesquisa:
  do{
    scanf(" %d", &temp);
    if (temp > 0) {
      if(buscaABB(arv, temp) != NULL) remove_ArvLLRB(arv, temp);
      else insere_ArvLLRB(arv, temp);
    }
  } while(temp >= 0);
 
  // valor a ser pesquisado na árvore:
  scanf(" %d", &temp);
 
  printf("\n%i, %i, %i", info_altura[0], info_altura[1], info_altura[2]);
 
  arv = buscaABB(arv, temp);
  if (arv != NULL) printf("\n%i, %i, %i", maior(altura(arv->esq), altura(arv->dir)), altura(arv->esq), altura(arv->dir));
  else printf("\nValor nao encontrado");
  
  libera(arv);
  return 0;
}
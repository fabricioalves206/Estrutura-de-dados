#include <stdlib.h>
#include <stdio.h>

typedef struct no{
 int elem; //elemento
 int fatBal; //fator de balanceamento do no
 struct no *pai; //pai do no
 struct no *esq; //no da esquerda
 struct no *dir; //no da direita
}noArvAVL;

typedef enum bool{false,true}bool;

noArvAVL *rotacaoEsquerda(noArvAVL *no){
 noArvAVL *atual;
 atual = no->dir;
 no->dir = atual->esq;
 if(atual->esq != NULL){
    atual->esq->pai = no;
 }//end if
 atual->esq = no;
 atual->pai = no->pai;

 no->pai = atual;
 no->fatBal = 0;
 return atual;
}

noArvAVL *rotacaoDireita(noArvAVL *no){
 noArvAVL *atual;
 atual = no->esq;
 no->esq = atual->dir;
 if(atual->dir != NULL){
    atual->dir->pai = no;
 }//end if
 atual->dir = no;
 atual->pai = no->pai;

 no->pai = atual;
 no->fatBal = 0;
 return atual;
}//end rotacaoDireita

noArvAVL *rotacaoEsqDir(noArvAVL *no){
 noArvAVL *auxPai, *noEsq, *novo;
 int fatBalDir;
 auxPai = no->pai;
 noEsq = no->esq;
 fatBalDir = noEsq->dir->fatBal;
 no->esq = rotacaoEsquerda(noEsq);
 novo = rotacaoDireita(no);
 novo->pai = auxPai;
 if(fatBalDir == 1){
    no->fatBal = -1;
 }
 else{
    no->fatBal = 0;
 }//end else
 if(fatBalDir == -1){
    noEsq->fatBal = 1;
 }//end if
 else{
    noEsq->fatBal = 0;
 }//end else
 return novo;
}//end rotacaoEsqDir

noArvAVL *rotacaoDirEsq(noArvAVL *no){
 noArvAVL *auxPai, *noDir, *novo;
 int fatBalEsq;
 auxPai = no->pai;
 noDir = no->dir;
 fatBalEsq = noDir->esq->fatBal;
 no->dir = rotacaoDireita(noDir);
 novo = rotacaoEsquerda(no);
 novo->pai = auxPai;
 if(fatBalEsq == -1){
    no->fatBal = 1;
 }
 else{
    no->fatBal = 0;
 }//end else
 if(fatBalEsq == 1){
    noDir->fatBal = -1;
 }//end if
 else{
    noDir->fatBal = 0;
 }//end else

 return novo;
}

noArvAVL *balanceaEsq(noArvAVL *no){
 noArvAVL *atual;
 atual = no->esq;
 if(atual->fatBal == -1){
    no = rotacaoDireita(no);
 }//end if
 else{
    no = rotacaoEsqDir(no);
 }//end else

 no->fatBal = 0;
 return no;
}

noArvAVL *balanceaDir(noArvAVL *no){
 noArvAVL *atual;

 atual = no->dir;
 if(atual->fatBal == 1){
    no = rotacaoEsquerda(no);
 }//end if
 else{
    no = rotacaoDirEsq(no);
 }//end else

 no->fatBal = 0;
 return no;
}

noArvAVL *insereArvAVL(noArvAVL *raiz, int valor, bool *fatBalAtual){
 noArvAVL *novo;

 if(raiz == NULL){
 novo = (noArvAVL *) malloc(sizeof(noArvAVL));
 novo->elem = valor;
 novo->pai = NULL;
 novo->esq = NULL;
 novo->dir = NULL;
 novo->fatBal = 0;
 return novo;
 }//end if(raiz == NULL)
 else{
    if(valor < raiz->elem){
        raiz->esq = insereArvAVL(raiz->esq, valor, fatBalAtual);
 //atualiza o pai do no inserido
        if(!raiz->esq->pai){
        raiz->esq->pai = raiz;
 }//end if(!raiz->esq->pai)
 //atualiza o fator de balanceamento
        if(*fatBalAtual){
            switch(raiz->fatBal){
                case 1:
                    raiz->fatBal = 0;
                    *fatBalAtual = false;
                    break;
                case 0:
                    raiz->fatBal = -1;
                    break;
                case -1: //fatBal=2, precisa balancear
                    raiz = balanceaEsq(raiz);
                    *fatBalAtual = false;
                    break;
            }//end switch
        }
        //end if(*fatBalAtual)
    }//
    else{
      if(valor > raiz->elem){
          raiz->dir = insereArvAVL(raiz->dir, valor, fatBalAtual);
 //atualiza o pai do no inserido
         if(!raiz->dir->pai){
           raiz->dir->pai = raiz;
          }//end if(!raiz->dir->pai)
 //atualiza o fator de balanceamento
          if(*fatBalAtual){
              switch(raiz->fatBal){
                  case -1:
                      raiz->fatBal = 0;
                      *fatBalAtual = false;
                      break;
                  case 0:
                      raiz->fatBal = 1;
                      break;
                  case 1: //fatBal=-2, precisa balancear
                      raiz = balanceaDir(raiz);
                      *fatBalAtual = false;
                      break;
              }//end switch
          }
          //end if(*fatBalAtual)
     }//end if(valor > raiz->elem)
    }//end else
 if(raiz->pai == NULL){
    *fatBalAtual = true;
 }
 return raiz;
}//end else
}//end insereArvAVL

void imprimePreOrdemArvBB(noArvAVL *n){
 if(n != NULL){
    printf(" %d ",n->elem);
    imprimePreOrdemArvBB(n->esq);
    imprimePreOrdemArvBB(n->dir);
 }//end if
}

int main(){
 noArvAVL *raiz = NULL;
 bool balanceada = true;
 int i;
 for(i = 1; i<10; i++){
    raiz = insereArvAVL(raiz, i, &balanceada);
 }
 imprimePreOrdemArvBB(raiz);//end for
}//end main



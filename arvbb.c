#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true}bool;

typedef struct no{
   int numero;
   struct no *esq;
   struct no *dir;
}noArvB;
noArvB *raiz=NULL;

bool insere(int valor){
    noArvB* ant = NULL;
    noArvB* atual = raiz;
    noArvB* novo = (noArvB*)malloc(sizeof(noArvB));
    if(atual == NULL){
        raiz = novo;
    }
    else{
        while(atual != NULL && atual->numero != valor){
            if(valor < atual->numero){
                ant = atual;
                atual = atual->esq;
            }
            else{
                ant = atual;
                atual = atual->dir;
            }
        }
        if(ant->numero == valor){
            return false;
        }
        if(ant->numero > valor){
            ant->esq = novo;
        }
        else{
             ant->dir = novo;
        }
    }
    novo->esq = NULL;
    novo->dir = NULL;
    novo->numero = valor;
    return true;
}

bool busca(int valor){
    noArvB* atual = raiz;
    while(atual != NULL){
        if(atual->numero == valor){
            return true;
        }
        else{
            if(valor < atual->numero){
                atual = atual->esq;
            }
            else{
                atual = atual->dir;
            }
        }
    }
    return false;
}

void imprime(noArvB* n){
    if(n != NULL){
        printf("%d ", n->numero);
        imprime(n->esq);
        imprime(n->dir);
    }
}

int main(){
    int i,aux;
    for(i = 0; i<4; i++){
        scanf("%d", &aux);
        insere(aux);
    }
    printf("encontrado: %d\n", busca(2));
    imprime(raiz);
}

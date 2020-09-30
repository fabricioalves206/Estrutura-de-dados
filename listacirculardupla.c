#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum{false, true}bool;

typedef struct no{
    int elem;
    struct no* prox;
    struct no* ant;
}noLista;

noLista* prim = NULL;
noLista* ult;

void insere(int valor){
    noLista* atual = prim;
    noLista* aux = NULL;
    noLista* novo = (noLista*)malloc(sizeof(noLista));
    if(atual == NULL){
        novo->ant = novo;
        novo->prox = novo;
        ult = novo;
        prim = novo;
    }
    else{
        while(atual->elem < valor){
            aux = atual;
            atual = atual->prox;
            if(atual == prim){
                break;
            }
        }
        if(aux == NULL){
            prim = novo;
            atual->ant = novo;
            novo->prox = atual;
            ult->prox = novo;
            novo->ant = ult;
        }
        else{
            aux->prox = novo;
            novo->ant = aux;
            novo->prox = atual;
            atual->ant = novo;
        }
    }
    if(atual == prim){
            ult = novo;
        }
    novo->elem = valor;
}

void imprime(){
    noLista* atual = prim;
    noLista* ulti = ult;
    printf("imprimindo em forma crescente\n");
    while(true){
        printf("%d ", atual->elem);
        atual = atual->prox;
        if(atual == prim){
            break;
        }
    }
    printf("\n\n");
    /*printf("imprimindo em forma decrescente\n");
    while(true){
        printf("%d ", ulti->elem);
        ulti = ulti->ant;
        if(ulti == ult){
            break;
        }
    }*/

}

void removeElem(int valor){
    noLista* atual = prim;
    noLista* aux = NULL;
    while(atual->elem != valor){
        aux = atual;
        atual = atual->prox;
        if(atual == prim){
            if(atual == valor)
                break;
            else
                return;
        }
    }
    if(atual == ult){
        ult = aux;
    }
    if(aux == NULL){
        prim = atual->prox;
        atual->ant->prox= prim;
        prim->ant = atual->ant;
        free(atual);
    }
    else{
        aux->prox = atual->prox;
        atual->prox->ant = aux;
        free(atual);
    }
}


int main(){
    int i, aux;
    srand(time(NULL));
    for(i=0;i<10;i++){
        aux = rand()%100;
        insere(aux);
    }
    imprime();
    for(i=0; i<4; i++){
        scanf("%d", &aux);
        removeElem(aux);
        imprime();
    }
}



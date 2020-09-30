#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum{false, true}bool;

typedef struct no{
    int elem;
    struct no* prox;
}noLista;

noLista* prim;
noLista* ult;

void insere(int valor){
    noLista* atual = prim;
    noLista* aux = NULL;
    noLista* novo = (noLista*)malloc(sizeof(noLista*));
    //insere o primeiro elemento
    if(atual == NULL){
        prim = novo;
        novo->prox = novo;
        ult = novo;
    }
    //caso nao seja o primeiro elemento
    else{
        //percorre a lista para encontrar a posição
        while(atual->elem < valor){
            aux = atual;
            atual = atual->prox;
            if(atual == prim){
                break;
            }
        }
        //insere na primeira posição
        if(aux == NULL){
            ult->prox = novo;
            novo->prox = atual;
            prim = novo;
        }
        //insere em qualquer posição
        else{
            aux->prox = novo;
            novo->prox = atual;
        }
        //atualiza o ultimo elemento
        if(atual == prim){
            ult = novo;
        }

    }
    //insere o elemnto na struct
    novo->elem = valor;

}

void imprime(){
    noLista* atual = prim;
    if(atual != NULL){
        while(true){
            printf("%d ", atual->elem);
            atual = atual->prox;
            if(atual == prim){
                break;
            }
        }
    }
}

void removeNum(int valor){
    noLista* atual = prim;
    noLista* aux = NULL;
    while(atual->elem != valor){
        aux = atual;
        atual = atual->prox;
        if(atual==prim){
            break;
        }
    }
    if(atual == ult){
        ult = aux;
    }
    if(aux == NULL){
       prim = atual->prox;
       ult->prox = atual->prox;
       free(atual);
    }
    else{
        aux->prox = atual->prox;
        free(atual);
    }
}

int main(){
    int i,aux;
    srand(time(NULL));
    for(i=0;i<10;i++){
        aux = rand()%100;
        insere(aux);
    }
    imprime();
    for(i=0;i<3;i++){
        scanf("\n%d", &aux);
        removeNum(aux);
        imprime();
    }
}

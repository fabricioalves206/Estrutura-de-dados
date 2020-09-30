#include <stdio.h>
#include <stdlib.h>
#define MAX 13

int hash[MAX];

void inicializa(){
    int i;
    for(i=0; i<MAX;i++){
        hash[i] = 0;
    }
}

void insere(int chave){
    int pos = chave % MAX;
    while(hash[pos] != 0){
        pos++;
        if(pos == MAX){
            pos = 0;
        }
    }
    hash[pos] = chave;
}

void imprime(){
    int i;
    for(i=0;i<MAX;i++){
        printf("%d ", hash[i]);
    }
}
int main(){
    inicializa();
    int aux,i;
    for(i = 0; i<5;i++){
        scanf("%d", &aux);
        insere(aux);
    }
    imprime();
}

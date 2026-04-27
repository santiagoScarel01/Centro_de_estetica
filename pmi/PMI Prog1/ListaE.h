#ifndef LISTAE_CLIENTE_H_INCLUDED
#define LISTAE_CLIENTE_H_INCLUDED
#define MAX 300
#include "Clientes.h"

typedef struct{
    int cursor;
    int ultimo;
    Cliente cliente[MAX];
} ListaE;

void InitListaE(ListaE *l){
l->cursor=0;
l->ultimo=-1;
}

void ResetListaE(ListaE *l){
l->cursor=0;
}

void ForwardsListaE(ListaE *l){
    l->cursor++;//solo avanza no controla
}

int isOosListaE (ListaE l){
if(l.cursor > l.ultimo){
    return 1; //SI DESBORDADO
}
else {
    return 0; //NO DESBORDADO
}
}

Cliente CopyListaE(ListaE l){
return (l.cliente[l.cursor]);
}

int isFullListaE(ListaE l){
if(l.ultimo==MAX-1){
    return 1;
}
else {
    return 0;
}
}

int isEmptyListaE(ListaE l){
if(l.ultimo==-1){
    return 1;
}
else {
    return 0;
}
}

int InsertListaE(ListaE *l, Cliente c){
int i;

for(i=l->ultimo; i>=l->cursor; i--){
    l->cliente[i+1]=l->cliente[i];
}
l->cliente[l->cursor]=c;
l->ultimo++;
return 1;
}

int SupressListaE(ListaE *l){
int i;
for(i=l->cursor; i<l->ultimo; i++){
    l->cliente[i]=l->cliente[i+1];
}
l->ultimo--;
return 1;
}

#endif // LISTAE_CLIENTE_H_INCLUDED

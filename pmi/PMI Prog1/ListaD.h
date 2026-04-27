#ifndef LISTAD_H_INCLUDED
#define LISTAD_H_INCLUDED
#include "turno.h"

struct nodo {
    Turno vipd;
    struct nodo* siguiente;
};

typedef struct nodo Nodo;

typedef struct {
    Nodo *acc;
    Nodo *cur;
    Nodo *aux;
} ListaD;

void InitListaD(ListaD *l) {
    l->acc = NULL;
    l->cur = NULL;
    l->aux = NULL;
}

void ResetListaD(ListaD *l) {
    l->cur = l->acc;
    l->aux = l->cur;
}

int isEmptyListaD(ListaD l) {
    if(l.acc == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int isFullListaD(ListaD l){
 Nodo* nuevonodo=(Nodo*)malloc(sizeof(Nodo));
 if(nuevonodo==NULL){
    return 1;
 }
    free(nuevonodo);
    return 0;
}

int isOosListaD(ListaD l) {
    if (l.cur == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

//cada vez que se invoque un fordwards hay que controlar
//que el CURSOR no este caido
void ForwardsListaD(ListaD *l) {
       l->aux=l->cur;
       l->cur=l->cur->siguiente;
}
//cada vez que se invoque el insertar hay que controlar que
//la lista NO ESTE LLENA
void insertar(ListaD *l, Turno nuevoTurno) {
    Nodo* nuevonodo = (Nodo *)malloc(sizeof(Nodo));

    if(l->acc==l->cur){
        l->acc=nuevonodo;
        nuevonodo->siguiente=l->cur;
        l->cur=nuevonodo;
        l->aux=nuevonodo;
    }
    else{
        l->aux->siguiente=nuevonodo;
        nuevonodo->siguiente=l->cur;
        l->cur=nuevonodo;

    }
     l->cur->vipd=nuevoTurno;
}

void supressListaD(ListaD *l) {
    if(l->acc==l->cur){
        l->acc=l->cur->siguiente;
        free(l->cur);
        l->aux=l->cur=l->acc;
    }
    else{
        Nodo *eliminar=l->cur;
        l->cur=l->cur->siguiente;
        free(eliminar);
        l->aux->siguiente=l->cur;
    }
}

Turno CopyListaD(ListaD l) {
    return (l.cur->vipd);
}

#endif // LISTAD_H_INCLUDED

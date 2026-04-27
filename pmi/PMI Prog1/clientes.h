#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED
#include <string.h>

typedef struct {
    long idCliente;
    char nombre[25];
    char apellido[25];
    int cantidadTratamientos;
    int nivel;
} Cliente;

void inicializarCliente(Cliente *c){
    c->idCliente=0;
    c->cantidadTratamientos=0;
    c->nivel=0;
}

void set_idClienteC(Cliente *c, long dni){
    c->idCliente=dni;
}

int long get_idClienteC(Cliente c){
    return c.idCliente;
}

void set_nombreCliente(Cliente *c, char nombre[]){
    strcpy(c->nombre, nombre);
}

char *get_nombreCliente(Cliente c){
    char *aux;
    aux=(char*)malloc(strlen(c.nombre)+1);
    if(aux==NULL){
        exit(1);
}
strcpy(aux, c.nombre);
    return aux;
}

void set_apellidoCliente(Cliente *c, char apellido[] ){
    strcpy(c->apellido, apellido);
}

char *get_apellido(Cliente c){
    char *aux;
    aux=(char*)malloc(strlen(c.apellido)+1);
    if(aux==NULL){
        exit(1);
}
strcpy(aux, c.apellido);
    return aux;
}

void set_cantidadTratamientos(Cliente *c, int ct){
    c->cantidadTratamientos=ct;
}

int get_cantidadTratamientos(Cliente c){
    return c.cantidadTratamientos;
}

void set_nivel (Cliente *c, int nivel){
    c->nivel=nivel;//modificar y poner losif que tengan la cantdad de tratamientos
}

int get_nivel(Cliente c){
    return c.nivel;
}

#endif // CLIENTES_H_INCLUDED

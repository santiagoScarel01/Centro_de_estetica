#ifndef TURNO_H_INCLUDED
#define TURNO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TRATAMIENTOS 10
#define MAX_METODOS_PAGO 4

typedef struct fecha {
    int dia;
    int mes;
    int anio;
    int hs;
}Fecha;

typedef struct turno{
    long idTurno;
    char nombre[100];
    long idCliente; //DNI
    int tratamiento[MAX_TRATAMIENTOS];
    int formaPago;
    float total;
    Fecha fecha;
    int realizado;
}Turno;

void inicializar(Turno *turno) {
    //TRATAMIENTO
    int i;
    for (i = 0; i < MAX_TRATAMIENTOS; i++) {
        turno->tratamiento[i] = 0;
    }

    turno->total = 0;
    turno->realizado = 0;
    turno->fecha.anio = 2024;
}

void set_idTurno(Turno *turno, long idT){
turno->idTurno=idT;
}

int get_idTurno(Turno turno) {
    return turno.idTurno;
}

void set_nombre(Turno *turno, char Inombre[]){
    strcpy(turno->nombre,Inombre);
}

char* get_nombre(Turno turno){
    char* c;
    c = (char*)malloc(strlen(turno.nombre)+1);
        if (c==NULL){
            exit(1);
        }
        strcpy(c,turno.nombre);
        return c;

}

void set_idCliente(Turno *turno, long IidCliente){
    turno->idCliente=IidCliente;
}

int get_idCliente(Turno turno){
    return turno.idCliente;
}

void set_tratamiento(Turno *turno, int Itratamiento){
    turno->tratamiento[Itratamiento] = 1;
}

int get_tratamiento(Turno turno, int Itratamiento) {
    return turno.tratamiento[Itratamiento];
}

void set_formaPago(Turno *turno, int IformaPago){
    turno->formaPago = IformaPago;
}

int get_formaPago(Turno turno){
    return turno.formaPago;
}

void set_total(Turno *turno, int Itotal){
    turno->total=Itotal;
}

float get_total(Turno turno){
    return turno.total;
}

void set_fechaDia(Turno *turno, int dia){
    turno->fecha.dia=dia;
}

void set_fechaMes(Turno *turno, int mes){
    turno->fecha.mes=mes;
}
 void set_fechaAnio(Turno *turno, int anio){
    turno->fecha.anio=anio;
}
void set_fechaHora(Turno *turno, int hora){
    turno->fecha.hs=hora;
}

int get_fechaAnio(Turno turno){
    return turno.fecha.anio;
}

int get_fechaDia(Turno turno){
    return turno.fecha.dia;
}
int get_fechaMes(Turno turno){
    return turno.fecha.mes;
}
int get_fechaHora(Turno turno){
    return turno.fecha.dia;
}

void set_realizado(Turno *turno, int Irealizado){
    turno->realizado=Irealizado;
}

int get_realizado(Turno turno){
    return turno.realizado;
}

#endif // TURNO_H_INCLUDED

#include <stdio.h>
#include "listaD.h"
#include "ListaE.h"
#define MAX_IDTURNO 1000000
#define MAX_TRATAMIENTOS 10
#define MAX_METODOS_PAGO 4

//==INFORMACION=DE=TRATAMIENTOS=======================================================================
typedef struct {
    char nombre[100];
    float precio;
} TratamientoInfo;

TratamientoInfo tratamientosDisponibles[MAX_TRATAMIENTOS] = {
    {"Limpieza facial + peelings", 14000.0},
    {"Limpieza facial antiage + Radiofrecuencia", 14000.0},
    {"Depilacion definitiva: piernas completas", 4500.0},
    {"Masaje cuerpo completo", 7000.0},
    {"Hifu: Abdomen + Flancos + Brazos + Gluteos + Piernas completas", 59900.0},
    {"Kapping con disenio (1 unia por mano)", 6300.0},
    {"Esmaltado semipermanente liso (un color)", 5000.0},
    {"Lifting + Tinte de pestanias", 5000.0},
    {"Perfilado de cejas + Lifting de pestanias", 7900.0},
    {"Peinado + Maquillaje", 79000.0}
};

void mostrarTratamientos() {
    int j;
    printf("------------------------------------------------------------");
    printf("\n--- Tratamientos Disponibles -------------------------------\n");
    for (j = 0; j < MAX_TRATAMIENTOS; j++) {
        printf("%d. %s - $%.2f\n", j + 1, tratamientosDisponibles[j].nombre, tratamientosDisponibles[j].precio);
    }
    printf("------------------------------------------------------------\n");
}
//====================================================================================================


//====================================================================================================
//FUNCIONES COMPLEMENTARIAS CARGAR TURNO
int getNextId() {
    static long variableID = 0;
    variableID++;
    return variableID;
}

//FUNCION B
int TurnoSinRealizar(ListaD ld, int id){
    ResetListaD(&ld);

    while(!isOosListaD(ld) && get_idCliente(CopyListaD(ld) )  != id){
        ForwardsListaD(&ld);
    }
    if(!isOosListaD(ld)){
        if(get_realizado(CopyListaD(ld)) == 0){
            printf("El cliente ya tiene un turno sin realizar\n");
            return 0;
        }
    }
    return 1;
}
//====================================================================================================


//===FUNCIONES========================================================================================
//FUNCION A
int cargarTurno(ListaD ld,ListaE cliente, Turno *T,Cliente *C){
    char nombre[100];
    long id,IdAsignar;
    int fp,dia,mes,hora,op,ctDeTrata=0,i;
    float total;
    inicializar(T);

    if(isEmptyListaE(cliente)==1){
        printf("------------------------------------------------------------\n");
        printf("No hay ningun cliente cargado. Cargue un cliente primero.\n");
        printf("------------------------------------------------------------\n\n");
        return 0;
    }

    printf("Ingrese el DNI del cliente para saber si esta registrado sino es asi lo tiene que cargar como cliente\n");
    scanf(" %ld",&id);

    ResetListaE(&cliente);
    while(!isOosListaE(cliente) && get_idClienteC(CopyListaE(cliente)) != id){
        ForwardsListaE(&cliente);
    }

    if(!isOosListaE(cliente)){
        printf("------------------------------------------------------------\n");
        printf("La persona con el DNI:%ld es cliente registrado\n", id);
        printf("------------------------------------------------------------\n");
    }
    else {
        printf("------------------------------------------------------------\n");
        printf("La persona con el DNI:%ld no se encuentra registrado\n", id);
        printf("------------------------------------------------------------\n");
        return 0;
    }

    if(TurnoSinRealizar(ld,id)==0){
        return 0;
    }

    IdAsignar=getNextId();

    strcpy(nombre,get_nombreCliente(CopyListaE(cliente)));
    set_nombre(T,nombre);
    set_idTurno(T,IdAsignar);
    set_idCliente(T,id);

    printf("------------------------------------------------------------\n");
    printf("Elija los tratamientos que desea (Maximo 3 por turno)\n");
    printf("Ingrese 0 para dejar de seleccionar.\n");
    printf("------------------------------------------------------------\n");
    mostrarTratamientos();
    int cantTratameinto=0;
    printf("Seleccione los tratamientos:");

    for(i=0;i<3;i++){
        scanf(" %d", &ctDeTrata);

        if(ctDeTrata==0){
            printf("------------------------------------------------------------\n");
            printf("Usted dejo de elegir tratamientos\n");
            break;
        }
        while(ctDeTrata<1 || ctDeTrata>10){
            printf("Opcion invalida, Ingrese nuevamente\n");
            scanf(" %d", &ctDeTrata);
        }
        cantTratameinto++;
        set_tratamiento(T,ctDeTrata-1);
    }

    set_cantidadTratamientos(C,cantTratameinto);
    cantTratameinto = get_cantidadTratamientos(*C);
    printf("------------------------------------------------------------\n");
    printf("--- Forma de pago ------------------------------------------\n");
    printf("1.Debito\n");
    printf("2.Credito\n");
    printf("3.QR\n");
    printf("4.Efectivo\n");
    printf("------------------------------------------------------------\n");
    printf("Seleccione metodo de pago:");
    scanf(" %d", &fp);

    do {
        if (fp < 1 || fp > 4) {
            printf("Opcion invalida. Ingrese nuevamente (1-4): ");
            scanf(" %d",&fp);
        }
    } while (fp < 1 || fp > 4);

        set_formaPago(T,fp);

        do{
            printf("------------------------------------------------------------\n");
            printf("--- Fecha del turno ----------------------------------------\n");
            printf("Disponible del 1/11/2024 hasta el 31/12/2024. Horario de 9 a 20hs\n");
            printf("Ingrese dia:");
            scanf(" %d", &dia);
            printf("Ingrese mes:");
            scanf(" %d", &mes);
            printf("Ingrese hora:");
            scanf(" %d", &hora);
        }while(dia<1 || dia>31 || mes<11 || mes>12 || hora<9 || hora>20);

    set_fechaDia(T,dia);
    set_fechaMes(T,mes);
    set_fechaAnio(T,2024);
    set_fechaHora(T,hora);

    printf("------------------------------------------------------------\n");
    printf("--- Datos del turno ----------------------------------------\n");
    printf("Id turno:%ld\n", IdAsignar);
    printf("Nombre:%s\n", get_nombre(*T));
    printf("Id cliente:%ld\n", id);
    printf("Tratamientos:\n");
    int j;
    for(j=0;j<MAX_TRATAMIENTOS;j++){
        if(get_tratamiento(*T,j)==1){
            printf("%s\n", tratamientosDisponibles[j].nombre);
        }
    }
    for(j=0;j<MAX_TRATAMIENTOS;j++){
        if(get_tratamiento(*T,j)==1){
             total+=tratamientosDisponibles[j].precio;
        }
    }



    set_total(T,total);
    int nivel=get_nivel(CopyListaE(cliente));
    if(nivel==0){
        printf("Total:%.2f\n", total);
    }
     if(nivel==1){
        printf("Tiene un descuento del 5 porciento\n");
        printf("Total:%.2f\n", total*0.95);
        total=total*0.95;
        set_total(T,total);
    }

     if(nivel==2){
        printf("Tiene un descuento del 10 porciento\n");
        printf("Total:%.2f\n", total*0.90);
        total=total*0.90;
        set_total(T,total);
    }
     if(nivel==3){
        printf("Tiene un descuento del 15 porciento\n");
        printf("Total:%.2f\n", total*0.85);
        total=total*0.85;
        set_total(T,total);
    }
    if(fp==1)
        printf("Forma de pago:Debito\n");
    if(fp==2)
        printf("Forma de pago:Credito\n");
    if(fp==3)
        printf("Forma de pago:QR\n");
    if(fp==4){
        printf("Forma de pago:Efectivo\n");
        }
        printf("La fecha es: %d/%d/2024 a las %d:00\n",dia,mes,hora);
        printf("Estado:No realizado\n");

    printf("------------------------------------------------------------\n");

    do{
        printf("Quiere confirmar la carga del turno? (1=SI 0=NO)\n");
        scanf("%d",&op);
    }while(op!=1 && op!=0);

    printf("------------------------------------------------------------\n");

    if(op== 1){
        printf("Turno cargado exitosamente\n");
        return 1;
    }else if(op==0){
        printf("Creacion del turno cancelada\n");
    }
    return 0;
}

//FUNCION C
void mostrarTurnosPorMes(ListaD ld) {
    int mesBuscado,i;

    if (isEmptyListaD(ld)) {
        printf("------------------------------------------------------------\n");
        printf("No hay ningun turno cargado.\n");
        printf("------------------------------------------------------------\n");
        return;
    }
    printf("------------------------------------------------------------\n");
    printf("Ingrese el numero del mes para mostrar los turnos (Mes 11 o 12): ");
    scanf("%d", &mesBuscado);

    if (mesBuscado < 11 || mesBuscado > 12) {
        printf("Mes invalido. Ingrese un valor entre 11 y 12.\n");
        return;
    }

    ResetListaD(&ld);
    int contador=0,SeguirMostrando;
    while (!isOosListaD(ld)) {
        if (get_fechaMes(CopyListaD(ld)) == mesBuscado) {
            printf("------------------------------------------------------------\n");
            printf("IdTurno: %d\n", get_idTurno(CopyListaD(ld)));
            printf("Nombre: %s\n", get_nombre(CopyListaD(ld)));
            printf("Dni: %d\n", get_idCliente(CopyListaD(ld)));
            printf("Tratamientos:\n");

            for (i = 0; i < MAX_TRATAMIENTOS; i++) {
                if (get_tratamiento(CopyListaD(ld), i) == 1) {
                    printf("%s\n", tratamientosDisponibles[i].nombre);
                }
            }

            printf("Forma de pago: ");
            int fp = get_formaPago(CopyListaD(ld));
            if (fp == 1) printf("Debito\n");
            else if (fp == 2) printf("Credito\n");
            else if (fp == 3) printf("QR\n");
            else if (fp == 4) printf("Efectivo\n");

            printf("Total: %.2f\n", get_total(CopyListaD(ld)));
            printf("Fecha: %d/%d/%d a las %d:00\n",
                   get_fechaDia(CopyListaD(ld)),
                   get_fechaMes(CopyListaD(ld)),
                   get_fechaAnio(CopyListaD(ld)),
                   get_fechaHora(CopyListaD(ld)));

            if (get_realizado(CopyListaD(ld)) == 1) {
                printf("Estado: Realizado\n");
            } else {
                printf("Estado: No realizado\n");
            }
            contador++;
        }
        ForwardsListaD(&ld);
        if(isOosListaD(ld)){
            printf("------------------------------------------------------------\n");
            printf("No hay mas turnos del mes:%d\n", mesBuscado);
            return;
        }
        if(contador==3){
            do{
                printf("------------------------------------------------------------\n");
                printf("Quiere seguir mostrando los turnos del mes:%d 1=SI 0=NO\n", mesBuscado);
                scanf(" %d", &SeguirMostrando);
            }while(SeguirMostrando!=1 && SeguirMostrando!=0);
            if(SeguirMostrando==1){
                contador=0;
            }
            if(SeguirMostrando==0){
                return;
            }
        }
    }
}

//FUNCION D
void MostrarTurnosPorNombre(ListaD ld){
    char Nombre[100];
    int i;
    if(isEmptyListaD(ld)==1){
        printf("------------------------------------------------------------\n");
        printf("No hay ningun turno cargado.\n");
        printf("------------------------------------------------------------\n\n");
        return;
    }
    printf("-------------------------------------------------\n");
    printf("Ingrese el nombre a buscar:");
    scanf(" %[^\n]", Nombre);
    printf("-------------------------------------------------\n");

    ResetListaD(&ld);

    int contador=0,SeguirMostrando;
    while (!isOosListaD(ld)) {
        if (strcmp(get_nombre(CopyListaD(ld)), Nombre) == 0){
            printf("IdTurno: %d\n", get_idTurno(CopyListaD(ld)));
            printf("Nombre: %s\n", get_nombre(CopyListaD(ld)));
            printf("Dni: %d\n", get_idCliente(CopyListaD(ld)));
            printf("Tratamientos:\n");

            for (i = 0; i < MAX_TRATAMIENTOS; i++){
                if (get_tratamiento(CopyListaD(ld), i) == 1){
                    printf("%s\n", tratamientosDisponibles[i].nombre);
                }
            }

            printf("Forma de pago: ");
            int fp = get_formaPago(CopyListaD(ld));
            if (fp == 1) printf("Debito\n");
            else if (fp == 2) printf("Credito\n");
            else if (fp == 3) printf("QR\n");
            else if (fp == 4) printf("Efectivo\n");

            printf("Total: %.2f\n", get_total(CopyListaD(ld)));
            printf("Fecha: %d/%d/%d a las %d:00\n",
                   get_fechaDia(CopyListaD(ld)),
                   get_fechaMes(CopyListaD(ld)),
                   get_fechaAnio(CopyListaD(ld)),
                   get_fechaHora(CopyListaD(ld)));

            if (get_realizado(CopyListaD(ld)) == 1) {
                printf("Estado: Realizado\n");
            } else {
                printf("Estado: No realizado\n");

            }
            contador++;
        }
        printf("-------------------------------------------------\n");

        ForwardsListaD(&ld);
        if(isOosListaD(ld)){
            printf("No hay mas turnos con el nombre:%s\n", Nombre);
            return;
        }
        if(contador==3){
            do{
                printf("Mostrar mas turnos? (1=SI 0=NO)\n");
                scanf(" %d", &SeguirMostrando);
                printf("-------------------------------------------------\n");
            }while(SeguirMostrando!=1 && SeguirMostrando!=0);

            if(SeguirMostrando==1){
                contador=0;
            }
            if(SeguirMostrando==0){
                return;
            }
        }

    }

}

//FUNCION E
void mostrarTurnosPorClienteRecursivo(ListaD ld, int idClienteBuscado, int encontrado) {
    if (isOosListaD(ld)) {
        if (!encontrado) {
            printf("No hay turnos para el cliente especificado\n");
        }
        return;
    }

    if (get_idCliente(CopyListaD(ld)) == idClienteBuscado) {
        encontrado = 1;
        printf("\nIdTurno: %d\n", get_idTurno(CopyListaD(ld)));
        printf("Fecha: %d/%d/%d a las %d:00\n",
               get_fechaDia(CopyListaD(ld)),
                   get_fechaMes(CopyListaD(ld)),
                   get_fechaAnio(CopyListaD(ld)),
                   get_fechaHora(CopyListaD(ld)));
        printf("Total: %.2f\n", get_total(CopyListaD(ld)));
    }

    ForwardsListaD(&ld);
    mostrarTurnosPorClienteRecursivo(ld, idClienteBuscado, encontrado);
}

//FUNCION F
float gananciaMensuales(ListaD listaTurnos, Turno turno, int mesB,float Gtotal){

    if(isOosListaD(listaTurnos) ==1 ){
        return Gtotal;
    }
    else{
        if (get_realizado(CopyListaD(listaTurnos))==1 && (get_fechaMes(CopyListaD(listaTurnos)))== mesB){
            Gtotal+=get_total(CopyListaD(listaTurnos));
             }

        ForwardsListaD(&listaTurnos);
        return gananciaMensuales(listaTurnos, turno, mesB, Gtotal);}

}

//FUNCION G
void MostrarListaTurnos(ListaD ld) {
    int i;

    if (isEmptyListaD(ld)) {
        printf("------------------------------------------------------------\n");
        printf("No hay ningun turno cargado.\n");
        printf("------------------------------------------------------------\n\n");
        return;
    }
    ResetListaD(&ld);

   int contador=0,SeguirMostrando;
       while(!isOosListaD(ld)){
             printf("IdTurno:%d\n", get_idTurno(CopyListaD(ld)));
            printf("Nombre:%s\n", get_nombre(CopyListaD(ld)));
            printf("Dni:%d\n", get_idCliente(CopyListaD(ld)));
            printf("Tratamientos:\n");
        for(i=0;i<MAX_TRATAMIENTOS;i++){
            if(get_tratamiento(CopyListaD(ld),i) == 1){
                printf("%s\n", tratamientosDisponibles[i].nombre);
            }
        }   printf("Forma de pago:");
            int fp=get_formaPago(CopyListaD(ld));
            if(fp==1)
                printf("Debito\n");
            if(fp==2)
                printf("Credito\n");
            if(fp==3)
                printf("QR\n");
            if(fp==4)
                printf("Efectivo\n");
            printf("Total:%.2f\n", get_total(CopyListaD(ld)));
            printf("Fecha\n");
            printf("Dia:%d\n", get_fechaDia(CopyListaD(ld)));
            printf("Mes:%d\n", get_fechaMes(CopyListaD(ld)));
            printf("Anio:%d\n", get_fechaAnio(CopyListaD(ld)));
            printf("Hora:%d:00\n", get_fechaHora(CopyListaD(ld)));
            if(get_realizado(CopyListaD(ld))==1)
            printf("Realizado\n");
            if(get_realizado(CopyListaD(ld))==0)
            printf("No realizado\n");
            printf("\n\n");
            contador++;

        ForwardsListaD(&ld);
        if(isOosListaD(ld)){
            printf("No hay mas turnos para mostrar\n");
            return;
        }
        if(contador==3){
                do{
            printf("Quiere seguir mostrando mas turnos? 1=SI 0=NO\n");
            scanf(" %d", &SeguirMostrando);
            }while(SeguirMostrando!= 1 && SeguirMostrando!=0);
            if(SeguirMostrando==0){
                printf("Dejando de mostrar turnos cargados\n");
                return;
            }
            if(SeguirMostrando==1){
                printf("Mostrando mas turnos cargados\n");
                contador=0;
            }
        }

       }
       }

//FUNCION H
void modificarCantidadTratamiento(ListaE *l) {
    int idCliente, nuevaCantidad, nuevoNivel;
    Cliente auxCliente;

    if (isEmptyListaE(*l)) {
        printf("------------------------------------------------------------\n");
        printf("No hay ningun cliente cargado. Cargue un cliente primero.\n");
        printf("------------------------------------------------------------\n\n");
        return;
    }

    printf("Ingrese el DNI del cliente para buscar:\n");
    scanf(" %d", &idCliente);

    ResetListaE(l);
    while (!isOosListaE(*l) && get_idClienteC(CopyListaE(*l)) != idCliente) {
        ForwardsListaE(l);
    }

    if (!isOosListaE(*l)) {
        printf("El cliente tiene actualmente %d tratamientos\n", get_cantidadTratamientos(CopyListaE(*l)));

        printf("Ingrese la nueva cantidad de tratamientos:\n");
        scanf(" %d", &nuevaCantidad);

        auxCliente = CopyListaE(*l);
        set_cantidadTratamientos(&auxCliente, nuevaCantidad);


        if (nuevaCantidad < 5) {
            nuevoNivel = 1;
        } else if (nuevaCantidad >= 5 && nuevaCantidad <= 10) {
            nuevoNivel = 2;
        } else {
            nuevoNivel = 3;
        }


        set_nivel(&auxCliente, nuevoNivel);


        SupressListaE(l);
        InsertListaE(l, auxCliente);

        printf("Cantidad de tratamientos y nivel actualizados correctamente.\n");
    } else {
        printf("Cliente no encontrado\n");
    }
}

//FUNCION I
void ModificaLaFormaDePago(ListaD *ld){
Turno auxTurno;

if(isOosListaD(*ld)){
    printf("------------------------------------------------------------\n");
    printf("No hay ningun turno cargado.\n");
    printf("------------------------------------------------------------\n\n");
    return;
}
long id;
int fp;
printf("Ingrese el DNI del cliente para buscar\n");
scanf(" %ld", &id);
ResetListaD(ld);
while(!isOosListaD(*ld) && get_idCliente(CopyListaD(*ld)) !=id){
    ForwardsListaD(ld);
}
if(!isOosListaD(*ld) && get_realizado(CopyListaD(*ld)) !=1){
    printf("el Cliente tiene la forma de pago:\n");
    if(get_formaPago(CopyListaD(*ld))==1)
        printf("Debito\n");
    if(get_formaPago(CopyListaD(*ld))==2)
        printf("Credito\n");
    if(get_formaPago(CopyListaD(*ld))==3)
        printf("QR\n");
    if(get_formaPago(CopyListaD(*ld))==4)
        printf("Efectivo\n");
    printf("Ingrese la forma de pago a modificar\n");
    do{
    printf("1:Debito\n2:Credito\n3:QR\n4:Efectivo\n");
    scanf(" %d", &fp);
    }while(fp<1 || fp>4);
    auxTurno=CopyListaD(*ld);
    set_formaPago(&auxTurno,fp);
    supressListaD(ld);
    insertar(ld,auxTurno);
}
else{
    printf("El cliente tiene el turno realizado\n");
    return;
}
}

//FUNCION J
void CancelarTurnoId(ListaD *ld){
long id;

    if(isEmptyListaD(*ld)){
    printf("------------------------------------------------------------\n");
    printf("No hay ningun turno cargado.\n");
    printf("------------------------------------------------------------\n\n");

    return;
    }

    printf("Ingrese el DNI del cliente:\n");
    scanf("%ld",&id);
    FILE *fp1;
    fp1=fopen("TurnoCancelado.txt","a");
    if (fp1==NULL){
        printf("Error\n");
        return;
    }
    Turno auxiliarT;

    ResetListaD(ld);
    while (!isOosListaD(*ld)) {
        if (get_idCliente(CopyListaD(*ld)) == id && get_realizado(CopyListaD(*ld)) == 0) {
            break;
        }
    ForwardsListaD(ld);
    }
    if(isOosListaD(*ld)){
        printf("No hay ningun turno en la lista sin realizar\n");
        return;

    }auxiliarT=CopyListaD(*ld);

    fprintf(fp1,"IdTurno:%d\n",get_idTurno(auxiliarT));
    fprintf(fp1,"Dni:%d\n",get_idCliente(auxiliarT));
    fprintf(fp1,"Nombre:%s\n",get_nombre(auxiliarT));
    int i;
    fprintf(fp1,"Tratamientos a realizar:\n");

    for(i=0;i<MAX_TRATAMIENTOS;i++){
        if(get_tratamiento(auxiliarT,i)==1){
            fprintf(fp1,"%s\n",tratamientosDisponibles[i].nombre);
        }
        }
    if(get_formaPago(auxiliarT)==1){
        fprintf(fp1,"Debito\n");
    }
    if(get_formaPago(auxiliarT)==2){
        fprintf(fp1,"Credito\n");
    }
    if(get_formaPago(auxiliarT)==3){
        fprintf(fp1,"QR\n");
    }
    if(get_formaPago(auxiliarT)==4){
        fprintf(fp1,"Efectivo\n");
    }
    fprintf(fp1,"Monto total:%.2f\n", get_total(auxiliarT));
    fprintf(fp1,"Fecha establecida del turno\n");
    fprintf(fp1, "Dia: %d\n", get_fechaDia(auxiliarT));
    fprintf(fp1,"Mes:%d\n",get_fechaMes(auxiliarT));
    fprintf(fp1,"Anio:%d\n",get_fechaAnio(auxiliarT));
    fprintf(fp1,"Hora:%02d:00\n",get_fechaHora(auxiliarT));
    fprintf(fp1,"=======================================\n");
    fclose(fp1);
    printf("Datos guardados en archivo exitosamente\n");


    char confirmacion;
        printf("¿Esta seguro que desea cancelar este turno? (s/n): ");
        printf("Ingrese s para cancelar y n para no hacerlo.\n");
        scanf(" %c", &confirmacion);

        if (confirmacion == 's' || confirmacion == 'S') {
            supressListaD(ld);
            printf("Turno cancelado exitosamente.\n");
        } else {
            printf("Cancelacion de turno abortada.\n");
        }
}

//FUNCION K
void ArchivoTurno(ListaD ld,int FormaPagoB){

    FILE*fp3;
    fp3=fopen("PagoTurno.txt","w");
    if (fp3==NULL){
        printf("Error al abrir archivo\n");
        return;

}
int turnosCopiados = 0;

    if(isEmptyListaD(ld)){
        printf("------------------------------------------------------------\n");
        printf("No hay ningun turno cargado.\n");
        printf("------------------------------------------------------------\n\n");

        fclose(fp3);
        return;
}
    ResetListaD(&ld);
    Turno auxiliardeturno;

   while (!isOosListaD(ld)) {
         if (get_realizado(CopyListaD(ld)) == 1 && get_formaPago(CopyListaD(ld)) == FormaPagoB) {
            auxiliardeturno=CopyListaD(ld);
            fwrite(&auxiliardeturno, sizeof(Turno), 1, fp3);
            ForwardsListaD(&ld);
            turnosCopiados++;
        }else{
        ForwardsListaD(&ld);
        }

}

    if(!isOosListaD(ld)){
        printf("No hay ningun turno realizado con esa forma de pago\n");
        fclose(fp3);
        printf("Se copiaron %d turnos al archivo.\n", turnosCopiados);
        return;

}
    fclose(fp3);
    printf("Se copiaron %d turnos al archivo.\n", turnosCopiados);
}

//FUNCION L
int CargaCliente(ListaE lc,Cliente *C){
    char nombre[100],apellido[100];
    long dni;
    int op;
    inicializarCliente(C);

    printf("Ingrese el DNI de la persona a registrar:");
    scanf(" %ld", &dni);

    ResetListaE(&lc);
    while(!isOosListaE(lc) && get_idClienteC(CopyListaE(lc)) != dni){
        ForwardsListaE(&lc);
    }
    if(!isOosListaE(lc)){
        printf("------------------------------------------------------------\n");
        printf("Ya es cliente registrado\n");
        printf("------------------------------------------------------------\n");
        return 0;
    }
    else{
        printf("------------------------------------------------------------\n");
        printf("La persona no es cliente\n");
        printf("------------------------------------------------------------\n");
    }

    printf("Ingrese el nombre del cliente:");
    scanf(" %[^\n]", nombre);
    set_nombreCliente(C,nombre);

    printf("Ingrese el apellido:");
    scanf(" %[^\n]", apellido);
    set_apellidoCliente(C,apellido);
    set_idClienteC(C,dni);

    printf("------------------------------------------------------------\n");
    printf("--- Datos del cliente --------------------------------------\n");
    printf("Nombre:%s\n", nombre);
    printf("Apellido:%s\n", apellido);
    printf("DNI:%ld", dni);
    printf("\n------------------------------------------------------------\n");

    do{
        printf("Quiere cargar al cliente? (1=SI 0=NO)\n");
        scanf(" %d", &op);
    }while(op!=1 && op!=0);

    if(op==1){
        printf("------------------------------------------------------------\n");
        printf("Carga de cliente exitosa\n");
        printf("------------------------------------------------------------\n");
        return 1;
    }else if(op==0){
        printf("------------------------------------------------------------\n");
        printf("Carga de cliente cancelada\n");
        printf("------------------------------------------------------------\n");
    }
    return 0;
}

//FUNCION M
void MostrarTurnosPorTratamiento(ListaD ld, int TrataBuscar){

int NoEntro=0,vuelta,i,op;

        ResetListaD(&ld);

        do{
        vuelta=0;
        while(vuelta<3){
        if(!isOosListaD(ld) && get_tratamiento(CopyListaD(ld), TrataBuscar-1)==1){
            printf("IdTurno:%d\n", get_idTurno(CopyListaD(ld)));
            printf("Nombre:%s\n", get_nombre(CopyListaD(ld)));
            printf("Dni:%d\n", get_idCliente(CopyListaD(ld)));
            printf("Tratamientos:\n");
        for(i=0;i<MAX_TRATAMIENTOS;i++){
            if(get_tratamiento(CopyListaD(ld),i) == 1){
                printf("%s\n", tratamientosDisponibles[i].nombre);
            }
        }   printf("Forma de pago:");
            int fp=get_formaPago(CopyListaD(ld));
            if(fp==1)
                printf("Debito\n");
            if(fp==2)
                printf("Credito\n");
            if(fp==3)
                printf("QR\n");
            if(fp==4)
                printf("Efectivo\n");
            printf("Total:%.2f\n", get_total(CopyListaD(ld)));
            printf("Fecha\n");
            printf("Dia:%d\n", get_fechaDia(CopyListaD(ld)));
            printf("Mes:%d\n", get_fechaMes(CopyListaD(ld)));
            printf("Anio:%d\n", get_fechaAnio(CopyListaD(ld)));
            printf("Hora:%d:00\n", get_fechaHora(CopyListaD(ld)));
            if(get_realizado(CopyListaD(ld))==1)
            printf("Realizado\n");
            if(get_realizado(CopyListaD(ld))==0)
            printf("No realizado\n");
            ForwardsListaD(&ld);
            printf("\n\n");
            NoEntro++;
        }
        if(NoEntro==0){
            printf("No hay ningun turno con el tratamiento:%s\n", tratamientosDisponibles[TrataBuscar-1].nombre);
            return;
        }
       if(isOosListaD(ld)==1){
        printf("No hay mas turnos para mostrar\n");
        return;
       }
            vuelta++;
        }
        printf("Quiere mostrar mas turnos? 1=SI 0=NO:\n");
        scanf("%d", &op);
        }while(op==1 && op!=0);


}

//FUNCION N
void PrecargaClientesDesdeArchivo(ListaE *lc) {
    FILE *fp = fopen("clientes.txt", "r");
    if (fp == NULL) {
        printf("------------------------------------------------------------\n");
        printf("Error al abrir el archivo.\n");
        printf("------------------------------------------------------------\n");
        return;
    }

    Cliente nuevoCliente;
    int id, cantt, nivell;
    char nombre[100], apellido[100];


   while (feof(fp) ==0) {
        fscanf(fp,"%d\n", &id);
        fscanf(fp, "%[^\n]\n", nombre);
        fscanf(fp, "%[^\n]\n", apellido);
        fscanf(fp, "%d\n", &cantt);
        fscanf(fp, "%d\n", &nivell);

        set_idClienteC(&nuevoCliente, id);
        set_nombreCliente(&nuevoCliente, nombre);
        set_apellidoCliente(&nuevoCliente, apellido);
        set_cantidadTratamientos(&nuevoCliente, cantt);
        set_nivel(&nuevoCliente, nivell);
        if(isFullListaE(*lc)){
        printf("No se pueden cargar mas clientes");
        return;
    }
        InsertListaE(lc, nuevoCliente);
    }

    fclose(fp);
    printf("------------------------------------------------------------\n");
    printf("Clientes precargados desde el archivo exitosamente.\n");
    printf("------------------------------------------------------------\n\n");
}

//FUNCION Ñ
void MostrarListaClientes(ListaE lc){
int vuelta=0,op;

 if(isEmptyListaE(lc)){
            printf("------------------------------------------------------------\n");
            printf("No hay ningun cliente cargado. Cargue un cliente primero.\n");
            printf("------------------------------------------------------------\n\n");
            return;
        }
            ResetListaE(&lc);
        do{
        vuelta=0;
        while(vuelta<3){

        if(!isOosListaE(lc)){
            printf("DNI:%ld\n", get_idClienteC(CopyListaE(lc)));
            printf("Nombre:%s\n", get_nombreCliente(CopyListaE(lc)));
            printf("Apellido:%s\n", get_apellido(CopyListaE(lc)));
            printf("Cantidad de Tratamientos:%d\n", get_cantidadTratamientos(CopyListaE(lc)));
            printf("Nivel:%d\n", get_nivel(CopyListaE(lc)));
            ForwardsListaE(&lc);
            printf("\n\n");
        }
            vuelta++;
        }
        if(isOosListaE(lc)){
            printf("No hay mas clientes para mostrar\n");
            return;
        }
        printf("Quiere mostrar mas clientes? (1=SI 0=NO): ");
        scanf("%d", &op);
        }while(op==1 && op!=0);

}

//FUNCION O
int EliminarClienteDni(ListaE *lc){
long id;
int op;
if(isEmptyListaE(*lc)==1){
    printf("------------------------------------------------------------\n");
    printf("No hay ningun cliente cargado. Cargue un cliente primero.\n");
    printf("------------------------------------------------------------\n\n");
    return 0;
}
printf("Ingrese el DNI del cliente a eliminar:\n");
scanf("%ld", &id);

ResetListaE(lc);
while(!isOosListaE(*lc) && get_idClienteC(CopyListaE(*lc)) !=id){
    ForwardsListaE(lc);
        }
    if(isOosListaE(*lc)==1){
        printf("No hay ningun cliente registrado con ese DNI\n");
        return 0;
    }
        printf("El cliente a eliminar es el siguiente:\n");
        printf("DNI:%ld\n", get_idClienteC(CopyListaE(*lc)));
        printf("Nombre:%s\n", get_nombreCliente(CopyListaE(*lc)));
        printf("Apellido:%s\n", get_apellido(CopyListaE(*lc)));
        printf("Cantidad de Tratamientos:%d\n", get_cantidadTratamientos(CopyListaE(*lc)));
        printf("Nivel:%d\n", get_nivel(CopyListaE(*lc)));
        printf("\n");
        printf("Esta seguro de proceder con la eliminacion?\n  1=SI 0=NO\n");
        do{
            scanf(" %d", &op);
        }while(op!= 1 && op!=0);
        if(op==1){
            printf("Decidio borrar el cliente\n");
        SupressListaE(lc);
            return 1;
        }
        else{
            printf("decidio no proceder con la eliminacion del cliente\n");
            return 0;
        }

}

//FUNCION P
void TurnoRealizado(ListaD *ld, ListaE *lc) {
    long id;
    int r,i;
    Cliente auxCliente;
    Turno auxTurno;

    if (isEmptyListaD(*ld)) {
        printf("------------------------------------------------------------\n");
        printf("No hay ningun turno cargado.\n");
        printf("------------------------------------------------------------\n\n");
        return;
    }

    printf("Ingrese el DNI del cliente a marcar como realizado el turno\n");
    scanf("%ld", &id);
    ResetListaD(ld);


    while (!isOosListaD(*ld) && get_idCliente(CopyListaD(*ld)) != id) {
        ForwardsListaD(ld);
    }

    if (!isOosListaD(*ld)) {
        auxTurno = CopyListaD(*ld);


        if (get_realizado(auxTurno) == 1) {
            printf("El turno ya esta marcada como realizado.\n");
            return;
        }


        printf("------------------------------------------------------------\n");
        printf("Datos del turno:\n");
        printf("ID turno: %d\n", get_idTurno(auxTurno));
        printf("Nombre: %s\n", get_nombre(auxTurno));
        printf("DNI: %d\n", get_idCliente(auxTurno));

        printf("Tratamientos:\n");
        float total = 0;
        int i;
        for (i = 0; i < MAX_TRATAMIENTOS; i++) {
            if (get_tratamiento(auxTurno, i) == 1) {
                printf("%s\n", tratamientosDisponibles[i].nombre);
                total += tratamientosDisponibles[i].precio;
            }
        }


        printf("Total: %.2f\n", total);
        printf("Fecha:\n");
        printf("Dia:%d\n",get_fechaDia(CopyListaD(*ld)));
        printf("Mes:%d\n",get_fechaMes(CopyListaD(*ld)));
        printf("Anio:%d\n",get_fechaAnio(CopyListaD(*ld)));
        printf("------------------------------------------------------------\n");


        do {
            printf("Ingrese 1 para marcar como realizado\n");
            scanf("%d", &r);
        } while (r != 1);


        set_realizado(&auxTurno, r);
        supressListaD(ld);
        insertar(ld, auxTurno);
    } else {
        printf("No hay ningun turno con ese DNI\n");
        return;
    }


    ResetListaE(lc);
    while (!isOosListaE(*lc) && get_idClienteC(CopyListaE(*lc)) != id) {
        ForwardsListaE(lc);
    }

    if (!isOosListaE(*lc)) {
        int cts = 0;
        for (i = 0; i < MAX_TRATAMIENTOS; i++) {
            if (get_tratamiento(auxTurno, i) == 1) {
                cts++;
            }
        }
        auxCliente = CopyListaE(*lc);
        cts += get_cantidadTratamientos(auxCliente);
        set_cantidadTratamientos(&auxCliente, cts);

        int auxNivel = get_cantidadTratamientos(auxCliente);
        if (auxNivel >= 1 && auxNivel <= 4) {
            set_nivel(&auxCliente, 1);
        } else if (auxNivel >= 5 && auxNivel <= 10) {
            set_nivel(&auxCliente, 2);
        } else if (auxNivel > 10) {
            set_nivel(&auxCliente, 3);
        }

        SupressListaE(lc);
        InsertListaE(lc, auxCliente);
    } printf("Turno cambiado a realizado.\n");
    return;
}

//FUNCION Q
void MostrarTurnosNoRealizado(ListaD ld){
int i;

        if(isEmptyListaD(ld)==1){
            printf("------------------------------------------------------------\n");
            printf("No hay ningun turno cargado.\n");
            printf("------------------------------------------------------------\n\n");
            return;
        }
            ResetListaD(&ld);
int contador=0,SeguirMostrando;
       while(!isOosListaD(ld)){
        if(get_realizado(CopyListaD(ld))== 0){
             printf("IdTurno:%d\n", get_idTurno(CopyListaD(ld)));
            printf("Nombre:%s\n", get_nombre(CopyListaD(ld)));
            printf("Dni:%d\n", get_idCliente(CopyListaD(ld)));
            printf("Tratamientos:\n");
        for(i=0;i<MAX_TRATAMIENTOS;i++){
            if(get_tratamiento(CopyListaD(ld),i) == 1){
                printf("%s\n", tratamientosDisponibles[i].nombre);
            }
        }   printf("Forma de pago:");
            int fp=get_formaPago(CopyListaD(ld));
            if(fp==1)
                printf("Debito\n");
            if(fp==2)
                printf("Credito\n");
            if(fp==3)
                printf("QR\n");
            if(fp==4)
                printf("Efectivo\n");
            printf("Total:%.2f\n", get_total(CopyListaD(ld)));
            printf("Fecha\n");
            printf("Dia:%d\n", get_fechaDia(CopyListaD(ld)));
            printf("Mes:%d\n", get_fechaMes(CopyListaD(ld)));
            printf("Anio:%d\n", get_fechaAnio(CopyListaD(ld)));
            printf("Hora:%d:00\n", get_fechaHora(CopyListaD(ld)));
            if(get_realizado(CopyListaD(ld))==1)
            printf("Realizado\n");
            if(get_realizado(CopyListaD(ld))==0)
            printf("No realizado\n");
            printf("\n\n");
            contador++;
        }
        ForwardsListaD(&ld);
        if(isOosListaD(ld)){
            printf("No hay mas turnos sin realizar para mostrar\n");
            return;
        }
        if(contador==3){
                do{
            printf("Quiere seguir mostrando mas turnos? 1=SI 0=NO\n");
            scanf(" %d", &SeguirMostrando);
            }while(SeguirMostrando!= 1 && SeguirMostrando!=0);
            if(SeguirMostrando==0){
                printf("Dejando de mostrar turnos sin realizar\n");
                return;
            }
            if(SeguirMostrando==1){
                printf("Mostrando mas turnos sin realizar\n");
                contador=0;
            }
        }

       }
       if(isOosListaD(ld)){
        printf("No hay ningun turno sin realizar\n");
        return;
       }
}

//==MAIN===============================================================================================

int main() {
    Turno turno;
    Cliente cliente;
    ListaE listaClientes;
    ListaD listaTurnos;

    int opcion,mesB,Gtotal=0,idClienteBuscado,encontrado=0,TrataBuscar,fpr,subopcion;

    InitListaD(&listaTurnos);
    InitListaE(&listaClientes);
    inicializar(&turno);
    inicializarCliente(&cliente);

    do {
    printf("------------------------------------------------------------\n");
    printf("====================== MENU PRINCIPAL ======================");

    printf("\n------------------------------------------------------------\n");
    printf(">>FUNCIONES PARA LOS TURNOS<<\n");
    printf(" 1. Cargar turno\n"); //FUNCIONALIDAD A
    printf(" 2. Modificar turno a realizado\n"); //FUNCIONALIDAD P
    printf(" 3. Eliminar turno y cargarlo en archivo\n"); //FUNCIONALIDAD J
    printf(" 4. Modificar forma de pago\n"); //FUNCIONALIDAD I

    printf("\n------------------------------------------------------------\n");

    printf(">>FUNCIONES PARA LOS CLIENTES<<\n");
    printf(" 5. Cargar cliente\n"); //FUNCIONALIDAD L
    printf(" 6. Eliminar cliente\n"); //FUNCIONALIDAD O
    printf(" 7. Cargar clientes automaticamente\n"); //FUNCIONALIDAD N
    printf(" 8. Modificar tratamientos clientes \n"); //FUNCIONALIDAD H
    printf(" 9. Calcular cantidad de turnos con forma de pago ingresada\n\n"); //FUNCIONALIDAD K

    printf("------------------------------------------------------------\n");

    printf("============================    ============================\n");
    printf(" 10. INGRESAR AL OTRO MENU       11. SALIR\n");
    printf("============================    ============================");
    printf("\n------------------------------------------------------------\n");

    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    printf("------------------------------------------------------------\n");

        switch (opcion) {
            case 1:
                system("cls");
                if(cargarTurno(listaTurnos,listaClientes, &turno,&cliente)==1){
                    insertar(&listaTurnos,turno);
                }
                break;

            case 2:
                system("cls");
                TurnoRealizado(&listaTurnos, &listaClientes);
                break;

            case 3:
                system("cls");
                 CancelarTurnoId(&listaTurnos);
                break;

            case 4:
                system("cls");
                ModificaLaFormaDePago(&listaTurnos);
                break;

            case 5:
                system("cls");
                printf("------------------------------------------------------------\n");
                 if(CargaCliente(listaClientes,&cliente)==1){
                    ResetListaD(&listaTurnos);
                    InsertListaE(&listaClientes,cliente);
                }
                break;

            case 6:
                system("cls");
                EliminarClienteDni(&listaClientes);
                break;

            case 7:
                system("cls");
                PrecargaClientesDesdeArchivo(&listaClientes);
                break;

            case 8:
                system("cls");
                modificarCantidadTratamiento(&listaClientes);
                break;

            case 9:
                system("cls");
                if (isEmptyListaD(listaTurnos)){
                    printf("No hay turnos cargados\n");
                    break;
                }

                do{
                    printf("------------------------------------------------------------\n");
                    printf("Ingrese la forma de pago a buscar\n");
                    printf("1. Debito\n2. Credito\n3. QR\n4. Efectivo\n0. Cancelar\n");
                    printf("------------------------------------------------------------\n");
                    scanf(" %d", &fpr);
                    }while(fpr<0 || fpr>4);
                if(fpr==0){
                    printf("Cancelo la operacion\n");
                    break;
                }
                ArchivoTurno(listaTurnos,fpr);
                break;

            case 11:
                system("cls");
                printf("Saliendo....\n");
                break;

            case 10:
                system("cls");
                do {
                    printf("-------------------------------------------------\n");
                    printf("========== MENU DE CONSULTA Y MUESTRA ==========\n");
                    printf("-------------------------------------------------\n");
                    printf(">>FUNCIONES MUESTRA<<\n");

                    printf(" 1. Mostrar turnos cargados\n");//FUNCIONALIDAD G
                    printf(" 2. Mostrar clientes cargados\n"); //FUNCIONALIDAD Ñ
                    printf(" 3. Mostrar ganancia mensual\n");//FUNCIONALIDAD F

                    printf("\n-------------------------------------------------\n");
                    printf(">>FUNCIONES MUESTRA ESPECIFICAS<<\n");
                    printf(" 4. Mostrar turnos no realizados\n"); //FUNCIONALIDAD Q
                    printf(" 5. Mostrar turnos de mes ingresado\n");//FUNCIONALIDAD C
                    printf(" 6. Buscar y mostrar turnos por nombre ingresado\n");//FUNCIONALIDAD D
                    printf(" 7. Buscar y mostrar turnos por DNI ingresado\n");//FUNCIONALIDAD E
                    printf(" 8. Mostrar turnos por tratamiento seleccionado\n\n");//FUNCIONALIDAD M
                    printf("-------------------------------------------------\n");
                    printf("================================\n");
                    printf(" 9. REGRESAR AL MENU PRINCIPAL\n");
                    printf("================================\n");
                    printf("-------------------------------------------------\n");

                    printf("Seleccione una opcion:");
                    scanf("%d",&subopcion);

                    switch(subopcion){
                    case 1:
                        system("cls");
                        MostrarListaTurnos(listaTurnos);
                        break;

                    case 2:
                        system("cls");
                        MostrarListaClientes(listaClientes);
                        break;

                    case 3:
                        system("cls");
                        if (isEmptyListaD(listaTurnos)){
                            printf("No hay turnos cargados.\n");
                            break;
                        }

                        do{
                        printf("-----------------------------------------------------------\n");
                        printf("Ingrese el mes para ver todas las ganancias mensuales: ");
                        scanf("%d", &mesB);

                        }while(mesB!=11 && mesB!=12);

                        ResetListaD(&listaTurnos);
                        printf("Las ganancias mensuales son: %.2f\n", gananciaMensuales(listaTurnos, turno, mesB,Gtotal));
                        printf("-----------------------------------------------------------\n\n");

                        break;

                    case 4:
                        system("cls");
                        MostrarTurnosNoRealizado(listaTurnos);
                        break;

                    case 5:
                        system("cls");
                        mostrarTurnosPorMes(listaTurnos);
                        break;

                    case 6:
                        system("cls");
                        MostrarTurnosPorNombre(listaTurnos);
                        break;

                    case 7:
                        system("cls");
                        if(isEmptyListaD(listaTurnos)){
                            printf("------------------------------------------------------------\n");
                            printf("No hay ningun turno cargado.\n");
                            printf("------------------------------------------------------------\n\n");
                            break;
                        }
                        printf("Ingrese el dni a buscar: ");
                        scanf("%d", &idClienteBuscado);
                        mostrarTurnosPorClienteRecursivo(listaTurnos,idClienteBuscado,encontrado);
                        break;

                    case 8:
                        system("cls");
                        if(isEmptyListaD(listaTurnos)==1){
                            printf("------------------------------------------------------------\n");
                            printf("No hay ningun turno cargado.\n");
                            printf("------------------------------------------------------------\n\n");
                            break;
                        }

                        mostrarTratamientos();
                        do{
                            printf("\nIngrese el tratamiento a buscar, para mostrar los turnos con los mismo\nIngrese 0 para cancelar\n");
                            scanf(" %d", &TrataBuscar);
                        }while(TrataBuscar<0 || TrataBuscar>10);
                        if(TrataBuscar==0){
                            printf("Usted cancelo!!\n");
                            break;
                        }
                        MostrarTurnosPorTratamiento(listaTurnos,TrataBuscar);
                        break;

                    case 9:
                        system("cls");
                        break;

                    default:

                        system("cls");
                        printf("Opcion invalida en submenu. Intente de nuevo.\n");
                        break;
                }
            } while (subopcion != 9);
            break;

            default:

                system("cls");
                printf("Opcion invalida. Intente de nuevo.\n");
                break;
        }

}while (opcion != 11);
 return 0;
}

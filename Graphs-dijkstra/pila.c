#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pila.h"



int
pilaCreaVacia(Pila *p) {
    *p = NULL;
    return 0;
}

int
pilaVacia(Pila *p) {
    if (*p == NULL){
        return 1;
    } else {
        return 0;
    }
}

int
pilaInserta(Pila *p,tipoElementoPila elemento) {
    tipoCelda *nuevaCelda, *aux;

    if (NULL == (nuevaCelda = malloc(sizeof(tipoCelda)))){
        return -1;
    }
    nuevaCelda->elemento = elemento;
    nuevaCelda->sig = NULL;
    if(pilaVacia(p)) { // Caso: Pila vacía
        *p = nuevaCelda;
    } else { // Caso: Pila con al menos un nodo
        aux = *p;
        *p = nuevaCelda;
        nuevaCelda->sig = aux;
    }
    return 0;
}

void imprimePila(Pila *p) {
    tipoCelda *aImprimir;
    int posicion;

    if (p == NULL) {
        return;
    } else {
        posicion = 1;
        aImprimir = *p;

        while (aImprimir != NULL) {
            printf("Valor: %d en posicion %d\n", aImprimir->elemento, posicion++);
            aImprimir = aImprimir->sig;
        }
        printf("%d valores en la cola\n",posicion-1);
    }
}

tipoElementoPila
pilaSuprime(Pila *p) {
    tipoCelda *aux;
    tipoElementoPila salida;

    if (pilaVacia(p)){ // Pila vacía (no es posible suprimir!)
        return -1;
    } else {
        aux = *p;
        salida = aux->elemento;
        *p = aux->sig;
        free(aux);
        return salida;
    }
}


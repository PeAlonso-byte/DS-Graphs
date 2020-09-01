#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cola.h"



int colaCreaVacia(Cola *c) {
    if (colaVacia(c) == -1){
        return -1;
    }
    c->frente = NULL;
    c->fondo = NULL;
    return 0;
}

int colaVacia(Cola *c) {
    if (c == NULL){
        return -1;
    } else if (c->frente == NULL && c->fondo == NULL){
        return 1;
    } else {
        return 0;
    }
}

tipoElementoCola colaSuprime(Cola *c) {
    tipoCelda *delete;
    tipoElementoCola salida;

    if (colaVacia(c) == -1){         // Si da error 
        return -1;
    } else if (colaVacia(c) == 1){   // Si la cola está vacía
        return -2;
    } else {                         
        if (c->frente->sig == NULL){ 
            delete = c->frente;
            salida = delete->elemento;
            c->fondo = c->frente = NULL;
            free(delete);
            return salida;
        } else {
            delete = c->frente;
            salida = delete->elemento;
            c->frente = c->frente->sig;
            free(delete);
            return salida;
        }
    }
}

int colaInserta(Cola *c,tipoElementoCola elemento)
{
    tipoCelda *new;
    if (colaVacia(c) == -1) {
        return -1;
    }

    new = malloc(sizeof(tipoCelda));
    if (new == NULL) {
        return -2;
    }
    new->sig = NULL;
    new->elemento = elemento;
    if (c->frente == NULL) {
        
        c->frente   = new;
        c->fondo    = new;

    } else
    {
        c->fondo->sig   = new;
        c->fondo        = new;
    }
    
    return 0;
    
}

void imprime(Cola *c) {
    tipoCelda *aImprimir;
    int posicion;

    if (c == NULL || c->frente == NULL) {
        return;
    } else {
        posicion = 1;
        aImprimir = c->frente;

        while (aImprimir != NULL) {
            printf("Valor: %d en posicion %d\n", aImprimir->elemento, posicion++);
            aImprimir = aImprimir->sig;
        }
        printf("%d valores en la cola\n",posicion-1);
    }
}




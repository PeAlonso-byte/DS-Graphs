#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "lista.h"



int
creaVacia(Lista *l)
{
    if (l == NULL)
        return -2;
    else if (NULL == (l->raiz = l->ultimo = (tipoCelda *)malloc(sizeof(tipoCelda))))
        return -1;
    else {
        l->raiz->sig = NULL;
        return 0;
    }
}


int
vacia(Lista *l)
{
    if (l == NULL || l->raiz == NULL) {
        return -1;
    }
    else if (l->raiz->sig == NULL)
        return 1;
    else
        return 0;
}

int
destruye(Lista *l)
{
    if (l == NULL || l->raiz == NULL) {
        return -1;
    }
    else if (l->raiz->sig != NULL){
        return -2;
    }
    else {
        free(l->raiz);
        l->raiz = l->ultimo = NULL;
        return 0;
    }
}


void
imprime(Lista *l)
{
    tipoCelda *aImprimir;
    int posicion;
    
    if (l == NULL || l->raiz == NULL) {
        return;
    }
    else {
        posicion = 1;
        aImprimir = l->raiz->sig;
        while (aImprimir != NULL) {
            printf("Valor: %d en posición: %d\n",aImprimir->elemento, posicion++);
            aImprimir = aImprimir->sig;
        }
        printf("%d valores en la lista\n",posicion-1);
    }
}

tipoPosicion
anterior(tipoPosicion p, Lista *l)
{

    tipoCelda *anterior;
    
    if (l == NULL || l->raiz == NULL || p == NULL) {
        return NULL;
    }
    else if (p == l->raiz){
        return l->raiz;
    }
    else {
        anterior = l->raiz;
        while (anterior->sig != p)
            anterior = anterior->sig;
        return anterior;
    }
}


tipoPosicion
primero(Lista *l)
{
    if ((l == NULL) || (l->raiz == NULL)) {
        return NULL;
    } else {
        return (l->raiz);
    }  
}



tipoPosicion
fin(Lista *l)
{
    if ((l == NULL) || (l->raiz == NULL)) {
        return NULL;
    } else {
        return (l->ultimo); 
    } 
    
}




int
inserta(tipoElementoLista x, tipoPosicion p, Lista *l)
{
    tipoPosicion new;
    
    if (vacia(l) == -1) {
        return -1;
    }

    new = malloc(sizeof(tipoCelda));
    if (new == NULL) {
        return -2;
    }

    new->elemento = x;
    new->sig = p->sig;
    p->sig = new;

    if (p == fin(l)) {
        l->ultimo = p->sig;
    }
        
    return 0;
    
}


int
suprime (tipoPosicion p, Lista *l)
{
    tipoPosicion delete;
    if ((l == NULL) || (l->raiz == NULL) || (p == NULL)) {
        return -1;
    } else {
        delete = p->sig;
        p->sig = delete->sig;
        free(delete);

        if (p->sig == NULL) l->ultimo = p;
    }

    return 0;
}



tipoPosicion
siguiente(tipoPosicion p,Lista *l)
{
    
    tipoPosicion temp;
    if ((p == NULL) || (l == NULL) || (l->raiz == NULL)) {
        return temp;
    }

    if (p->sig == NULL) {
        return fin(l);
    } else {
        temp = p->sig;
        
    }

    return temp;
}




tipoPosicion
localiza (tipoElementoLista x, Lista *l)
{
	tipoPosicion toFind;
    toFind = l->raiz;

    while (toFind->sig != NULL) {
        if (toFind->sig->elemento == x) {
            return toFind;
        }
    }
    return toFind;
}



tipoElementoLista
recupera(tipoPosicion p, Lista *l)
{
    if ((p == NULL) || (l == NULL) || (l->raiz == NULL)) {
        return -1;
    }

    return p->sig->elemento;
    
}


int
anula(Lista *l)
{
    tipoPosicion delete, q;
    if ((l == NULL) || (l->raiz == NULL)) {
        return -1;
    }

    q = l->raiz->sig;
    l->raiz->sig = NULL;

    while (q != NULL) {
        delete = q;
        q = q->sig;
        free(delete);
    }
 
    //while (l->raiz->sig != NULL) {
    //    delete = l->raiz->sig;
    //    l->raiz = delete->sig;
    //    free(delete);
    //}
    return 0;
}

int
concatena(Lista *lA, Lista *lB)
{
    if ((lA == NULL) || (lA->raiz == NULL) || (lB == NULL) || (lB->raiz == NULL)) {
        return -1;
    }

    tipoPosicion temp, aux;
    temp = lB->raiz;
    aux = lA->ultimo;
    while (temp != NULL) {
        if (temp->sig != NULL) {
            inserta(temp->sig->elemento, aux, lA);
            aux = siguiente(aux,lA);
        }
        temp = temp->sig;

    }
    anula(lB);

    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "monticulo.h"


void iniciaMonticulo(Monticulo *m) {
    if (m != NULL) {
        m->tamanno = 0;
    }
}

int vacioMonticulo(Monticulo m) {
    if (m.tamanno == 0) {
        return 1;
    }
    return 0;
}

int insertar(tipoElemento x, Monticulo *m) {
    int hueco;
    if (m == NULL) return -1;
    if (m->tamanno >= MAXIMO) {
        printf("Monticulo lleno\n");
        return -1;
    }
    m->tamanno+=1;
    hueco = m->tamanno;

    while (m->elemento[hueco/2].clave > x.clave) {
        m->elemento[hueco] = m->elemento[hueco/2];
        hueco/=2;
    }
    m->elemento[hueco] = x;
    return 0;
}

void decrementarClave(int pos, tipoClave cantidad, Monticulo *m) {
    
    if (m == NULL || vacioMonticulo(*m)) return;
    m->elemento[pos].clave -= cantidad;
    filtradoAscendente(m, pos);
}

void filtradoAscendente(Monticulo *m, int i){
	tipoElemento aux;
	aux = m->elemento[i];
	while (i > 1 && (m->elemento[i/2].clave > m->elemento[i].clave)){
		m->elemento[i] = m->elemento[i/2];
		i = i/2;
	}
	m->elemento[i] = aux;
}

void incrementarClave(int pos, tipoClave cantidad, Monticulo *m){
	if (m == NULL || vacioMonticulo(*m)) return;
	m->elemento[pos].clave += cantidad;
	filtradoDescendente(m, pos);
}

int eliminarMinimo(Monticulo *m, tipoElemento *minimo) {
    int i, hijo, hueco, finFiltrado;
    tipoElemento ultimo;
    int minimo1 = 0;
    if (vacioMonticulo(*m)) {
        printf("Error, el monticulo está vacío.\n");
        return 1;
    }

    *minimo = m->elemento[1];
    minimo1 = m->elemento[1].clave;
    ultimo = m->elemento[m->tamanno];

    m->tamanno-=1;
    m->elemento[1] = ultimo;
	filtradoDescendente(m, 1);
    hueco = 1;
    finFiltrado = 0;

    while (2* hueco < m->tamanno && !finFiltrado) {
        hijo = 2*hueco;
        if (hijo != m->tamanno) {
            if (m->elemento[hijo+1].clave < m->elemento[hijo].clave) {
                hijo+=1;
            }
        }

        if (m->elemento[hijo].clave < ultimo.clave) {
            m->elemento[hueco] = m->elemento[hijo];
            hueco = hijo;
        } else {
            finFiltrado = 1;
        }
    }
    m->elemento[hueco] = ultimo;
    return minimo1;
}



void filtradoDescendente(Monticulo *m, int i) {
    tipoElemento aux;
    int hijo;
    aux = m->elemento[i];

    hijo = 2*i;

    if ((hijo < m->tamanno) && (m->elemento[hijo+1].clave > m->elemento[hijo].clave)) {
        hijo+=1;
        while ((hijo < m->tamanno) && (aux.clave < m->elemento[hijo].clave)) {
            if ((hijo < m->tamanno) && (m->elemento[hijo+1].clave > m->elemento[hijo].clave)){
                hijo+=1;
            }
            m->elemento[i] = m->elemento[hijo];
            i = hijo;
            hijo = 2*i;
        }
        m->elemento[i] = aux;
    }
}

/*void intercambiarValor(Monticulo *m, int a, int b) {
    tipoElemento aux;
    aux = m->elemento[a];
    m->elemento[a] = m->elemento[b];
    m->elemento[b] = aux; 
}

void heapsort (Monticulo *m) {
    int i;
    for (i = m->tamanno/2; i >= 0; i--) {
        filtradoDescendente(m, i);
    }

    for (i = m->tamanno-1; i > 0; i--) {
        intercambiarValor(m, 0, i);
        filtradoDescendente(m, 0);

    }
}*/


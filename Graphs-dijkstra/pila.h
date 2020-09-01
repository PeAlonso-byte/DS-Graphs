#ifndef __PILA_H
#define __PILA_H

#ifndef __TIPO_ELEMENTOPILA
#define __TIPO_ELEMENTOPILA
typedef int tipoElementoPila;
#endif

#ifndef __TIPO_CELDA
#define __TIPO_CELDA
typedef struct tipoCelda {
	tipoElementoPila elemento;
	struct tipoCelda * sig;
	} tipoCelda;
#endif

typedef tipoCelda * Pila;

int pilaCreaVacia(Pila *p);


// En vacía no sería necesario el paso por referencia,
// se hace por mantener la misma interfaz con la implementación
// de matrices
int pilaVacia(Pila *p);

int pilaInserta(Pila *p,tipoElementoPila elemento);
void imprimePila(Pila *p);

tipoElementoPila pilaSuprime(Pila *p);

#endif


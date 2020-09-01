/*
 * grafos.c
 *
 *  Created on: 21/04/2014
 *      Author: MJ Polo
 */
#include <stdio.h>
#include "cola.h"
#include "grafos.h"
#include "pila.h"
#include "monticulo.h"

/****************************************************************************************************/
/*                                  INICIAR                                                        */
/***************************************************************************************************/

void iniciar(tipoGrafo *g) {
  pArco p;
  for (int i = 1; i <= g->orden; i++) { 
    g->directorio[i].alcanzado = 0;
    g->directorio[i].anterior = 0;
    g->directorio[i].distancia = INF;
    g->directorio[i].gradoEntrada = 0;
    g->directorio[i].ordenTop = 0;
    g->directorio[i].peso = 1;      // Inicializamos el peso a 1 (Gráfos dirigidos)

    for (int j = 1; j <= g->orden; j++) {     // Encontramos los valores de entrada
      p = g->directorio[j].lista;

      while (p != NULL) {
        if (p->v == i) {
          g->directorio[i].gradoEntrada +=1;
        }
        p = p->sig;
      }  
    }
  }
}

/****************************************************************************************************/
/* Recorrido en PROFUNDIDAD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/***************************************************************************************************/
void profundidad(int v_inicio,tipoGrafo * grafo)
{ int w;
  pArco  p;
  printf("%d ",v_inicio);
  grafo->directorio[v_inicio].alcanzado=1;
  p = grafo->directorio[v_inicio].lista;
  while (p!=NULL)
  { w=p->v;
    if (!grafo->directorio[w].alcanzado)
        profundidad(w,grafo);
    p = p->sig;
  }
}

void profundidadMejorado(int v_inicio,tipoGrafo * grafo)
{ int w;
  pArco  p;
  printf("%d ",v_inicio);
  grafo->directorio[v_inicio].alcanzado=1;
  p = grafo->directorio[v_inicio].lista;
  while (p!=NULL)
  { 
    w=p->v;
    if (!grafo->directorio[w].alcanzado)
        profundidad(w,grafo);
    p = p->sig;
  }
  for (int i = 1; i < 8; i++) {
    if (!grafo->directorio[i].alcanzado)
        profundidad(i,grafo);
  }
}


/************************************************************************************************/
/* Recorrido en AMPLITUD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/************************************************************************************************/
void amplitud(int v_inicio,tipoGrafo *grafo)
{ int w;
  pArco  p;
  Cola c;

  colaCreaVacia(&c);
  colaInserta(&c, v_inicio);
  while (!colaVacia(&c))  {
	w =colaSuprime(&c);
        if (!grafo->directorio[w].alcanzado) {
		printf("%d ",w);
	        grafo->directorio[w].alcanzado=1;
        	p =grafo->directorio[w].lista;
 		while (p!=NULL){
			w = p->v;
			colaInserta(&c,w);
			p = p->sig;
		}
	}
  }
	  
}

void amplitudMejorado(int v_inicio,tipoGrafo *grafo)
{ int w;
  pArco  p;
  Cola c;

  colaCreaVacia(&c);
  colaInserta(&c, v_inicio);
  while (!colaVacia(&c))  {
	w =colaSuprime(&c);
        if (!grafo->directorio[w].alcanzado) {
		printf("%d ",w);
	        grafo->directorio[w].alcanzado=1;
        	p =grafo->directorio[w].lista;
 		while (p!=NULL){
			w = p->v;
			colaInserta(&c,w);
			p = p->sig;
		}
    for (int i = 1; i <= grafo->orden; i++) {
      if (!grafo->directorio[i].alcanzado)
        amplitudMejorado(i,grafo);
    }
	}
  }
	  
}
/**********************************************************************************************/
/* Función auxiliar para ver el contenido de la estructura que representa un grafo en memoria */
/**********************************************************************************************/
void verGrafo(tipoGrafo *g)
{  int i;
   pArco p;

   printf("\nGrafo  (Orden %d)\n\n",g->orden);
   printf("       alc gEnt oTop dist peso ant \n");
   printf("     +----+----+----+----+----+----+\n");

   for(i=1;i<=g->orden;i++)
   {  printf("  %2d | %2d | %2d | %2d |", i, g->directorio[i].alcanzado,
                       g->directorio[i].gradoEntrada, g->directorio[i].ordenTop);
       if (g->directorio[i].distancia == INF) printf("  * |");
       else   printf(" %2d |", g->directorio[i].distancia);
       if (g->directorio[i].peso == INF) printf("  * |");
       else   printf(" %2d |", g->directorio[i].peso);
       printf(" %2d |",g->directorio[i].anterior);
       p = g->directorio[i].lista;
       while (p != NULL)
       {   printf(" ->%2d", p->v);	// Grafos no ponderados
           //printf(" ->%2d, %2d", p->v, p->peso); // Grafos ponderados
           p = p->sig;
       }
       printf("\n");
   }
   printf("     +----+----+----+----+----+----+\n\n");
}

int ordenTop2(tipoGrafo *grafo) {
  int w;
  pArco  p;
  Cola c;
  
  iniciar(grafo);

  colaCreaVacia(&c);

  for (int w = 1; w <= grafo->orden; w++) {
    if (grafo->directorio[w].gradoEntrada == 0) 
      colaInserta(&c, w);
  }
  int orden = 1;

  while (!colaVacia(&c)) {
    w = colaSuprime(&c);
    grafo->directorio[w].ordenTop = orden;
    orden += 1;

    p = grafo->directorio[w].lista;

    while (p != NULL) {
      w = p->v;
      grafo->directorio[w].gradoEntrada = grafo->directorio[w].gradoEntrada - 1;
      if (grafo->directorio[w].gradoEntrada == 0) {
        colaInserta(&c, w);
      }
      p = p->sig;
    }
  }
  orden -=1;
  if (orden != grafo->orden) {
    //printf("El orden es %d\n", orden);
    //printf("El orden grafo es %d\n", grafo->orden);
    return -1;
  }
  return 0;
}

/**********************************************************************************************/
/*                            Función algoritmo de Dijkstra                                   */
/**********************************************************************************************/

void dijkstra1(int vInicio, tipoGrafo *g) {
  pArco p;
  int v,w,i;
  iniciar(g);

  g->directorio[vInicio].distancia = 0;
  g->directorio[vInicio].anterior  = 0;

  for (i = 1; i <= g->orden; i++) {
    if ((v = buscarVerticeDistanciaMinimaNoAlcanzado(g)) == INF) {
      printf("Error la distancia es infinito\n");
    }
    g->directorio[v].alcanzado = 1;
    p = g->directorio[v].lista;

    while (p != NULL) {
      w = p->v;
      if (!g->directorio[w].alcanzado) {
        if ((g->directorio[v].distancia + p->peso) < (g->directorio[w].distancia)) {
          g->directorio[w].distancia = g->directorio[v].distancia + p->peso;
          g->directorio[w].anterior = v;
        }
      }
      p = p->sig;
    }
  }
}

void dijkstra2(int vInicio, tipoGrafo *g) {
  pArco p;
  int v, w, i, coste;
  Monticulo m;
  tipoElemento x;

  iniciar(g);
  g->directorio[vInicio].distancia  = 0;
  g->directorio[vInicio].anterior   = 0;
  iniciaMonticulo(&m);
  x.clave = 0; // distancia minima
  x.informacion = vInicio;
  insertar(x, &m);

  while (!vacioMonticulo(m)) {
    eliminarMinimo(&m, &x);
    if (!g->directorio[x.informacion].alcanzado) {
      v = x.informacion;
      g->directorio[v].alcanzado = 1;
      p = g->directorio[v].lista;

      while (p != NULL) {
        w = p->v;

        if (!g->directorio[w].alcanzado) {
          coste = g->directorio[v].distancia + p->peso;
          if (coste < g->directorio[w].distancia) {
            g->directorio[w].distancia = coste;
            g->directorio[w].anterior  = v;
            x.clave = g->directorio[w].distancia;
            x.informacion = w;
            insertar(x, &m);
          }
        }
        p = p->sig;
      }
    }
  }
}

int buscarVerticeDistanciaMinimaNoAlcanzado(tipoGrafo *g){
  pArco p;
  int v;
  int dmin = INF;
  for (int i = 1; i <= g->orden; i++) { // I -> VALOR DEL VERTICE
    if (!g->directorio[i].alcanzado) {
      if (dmin > g->directorio[i].distancia) {
        dmin = g->directorio[i].distancia;
        v = i;
      }
    }
  }
  return v;
}

int costeyTrayectoria(int vIni, int vFin,tipoGrafo *vGrafo) {
  int distancia = INF;
  Pila p;
  pilaCreaVacia(&p);
  int numero = vFin;
  int aux = 0;
  int flag = 0;
  int auxiliar = 0;
  while (numero != 0) {
    aux = vGrafo->directorio[numero].anterior;
    numero = aux;
    if (numero == 0) break;
    pilaInserta(&p, numero);
    if (numero == vIni) {
      distancia = vGrafo->directorio[vFin].distancia - vGrafo->directorio[vIni].distancia;
      flag = 1;
      break;
    }
  }

  if (flag == 0) return INF;

  while (!pilaVacia(&p)){
    auxiliar = pilaSuprime(&p);
    printf(" %d --»", auxiliar);
  }
  printf(" %d ", vFin);
  return distancia;
  
}

void todosCaminosMin (int vIni, tipoGrafo *g) {
  int distancia = INF;
  for (int i = 1; i <= g->orden; i++) {

    if (i != vIni) {
      printf("CAMINO DESDE %d HASTA %d : ", vIni, i);
     distancia =  costeyTrayectoria(vIni, i, g);
     if (distancia == INF) {
       printf(" NO EXISTE CAMINO\n");
     } else {
       printf(" DISTANCIA = %d\n", distancia);
     }
    }
    
  }
}

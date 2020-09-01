# Caminos mínimos en grafos dirigidos ponderados 
# Change main for main2 to switch between the exercises.

prueba2: main.c grafos.h grafos.o cola.o pila.o monticulo.o
	gcc -g main.c grafos.o pila.o cola.o monticulo.o -o main	
grafos.o: grafos.c grafos.h 
	gcc -g -c grafos.c
pila.o: pila.c pila.h
	gcc -c -g pila.c
cola.o: cola.c cola.h
	gcc -c -g cola.c
monticulo.o: monticulo.c monticulo.h
	gcc -g -c monticulo.c
clean:
	rm *.o


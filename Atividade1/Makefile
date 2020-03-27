all: main.o adjacency_matrix.o 
	gcc main.o adjacency_matrix.o -o program -g

main.o: main.c
	gcc main.c -c

adjacency_matrix.o: adjacency_matrix.c
	gcc adjacency_matrix.c -c

run:
	./program

clean:
	rm -rf program *.o

zip:
	zip atv1 main.c adjacency_matrix.c adjacency_matrix.h Makefile
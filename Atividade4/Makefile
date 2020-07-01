all: main.o directed_adjacency_list.o 
	gcc main.o directed_adjacency_list.o -o program -g

main.o: main.c
	gcc main.c -c

directed_adjacency_list.o: directed_adjacency_list.c
	gcc directed_adjacency_list.c -c

run:
	./program

clean:
	rm -rf program *.o

zip:
	zip atv4 main.c directed_adjacency_list.c directed_adjacency_list.h Makefile

debug:
	valgrind ./program -v < teste.txt
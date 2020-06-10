all: main.o adjacency_list.o 
	gcc main.o adjacency_list.o -o program -g

main.o: main.c
	gcc main.c -c

adjacency_list.o: adjacency_list.c
	gcc adjacency_list.c -c

run:
	./program

clean:
	rm -rf program *.o

zip:
	zip atv2 main.c adjacency_list.c adjacency_list.h Makefile

debug:
	valgrind ./program -v
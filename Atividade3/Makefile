all: main.o directed_adjacency_list.o queue.o
	gcc main.o directed_adjacency_list.o queue.o -o program -g

main.o: main.c
	gcc main.c -c

directed_adjacency_list.o: directed_adjacency_list.c
	gcc directed_adjacency_list.c -c

queue.o: queue.c
	gcc queue.c -c

run:
	./program

clean:
	rm -rf program *.o

zip:
	zip atv3 main.c directed_adjacency_list.c directed_adjacency_list.h queue.c queue.h Makefile

debug:
	valgrind ./program -v
all: main.o adjacency_list.o queue.o
	gcc main.o adjacency_list.o queue.o -o program -g

main.o: main.c
	gcc main.c -c

adjacency_list.o: adjacency_list.c
	gcc adjacency_list.c -c

queue.o: queue.c
	gcc queue.c -c

run:
	./program

clean:
	rm -rf program *.o

zip:
	zip atv2 main.c adjacency_list.c adjacency_list.h queue.c queue.h Makefile

debug:
	valgrind ./program -v
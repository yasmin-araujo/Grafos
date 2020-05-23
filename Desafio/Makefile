all: prog

run: prog
	./prog
	
valgrind: prog
	valgrind --leak-check=full --show-leak-kinds=all ./prog

prog: fila.o listaadj.o pacman.o
	gcc -o prog -g -Wall fila.o listaadj.o pacman.o -g

pacman.o: pacman.c
	gcc -c pacman.c

listaadj.o: listaadj.c
	gcc -c listaadj.c

fila.o: fila.c
	gcc -c fila.c

clean: 
	rm -rf *o prog
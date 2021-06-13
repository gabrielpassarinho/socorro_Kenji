all:
	gcc main.c ordena_lista.c -o ordena -lm -Wall
run:
	./ordena < input/random_power4.txt
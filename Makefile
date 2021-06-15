all:
	gcc main.c ordena_lista.c -o ordena -lm -Wall
run:
	./ordena 
run_debugging:
	./ordena < Inputs/random_power1.txt


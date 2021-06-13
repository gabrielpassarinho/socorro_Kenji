all:
	gcc main.c ordena_lista.c -o ordena -lm -Wall
run_random:
	./ordena < Inputs/random_power1.txt Inputs/random_power2.txt Inputs/random_power3.txt Inputs/random_power4.txt Inputs/random_power5.txt
run_ordenado_decrescente:
	./ordena < Inputs/descending1.txt Inputs/descending2.txt Inputs/descending3.txt Inputs/descending4.txt Inputs/descending5.txt
run_ordenado_crescente:
	./ordena < Inputs/ordered1.txt Inputs/ordered2.txt Inputs/ordered3.txt Inputs/ordered4.txt Inputs/ordered5.txt

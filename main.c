#include <stdio.h>
#include "ordena_lista.h"
#include <time.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define total_entradas 1

int main(void){
	/*Declarando variáveis*/
	lista* L_aux = malloc(sizeof(lista));
	lista* L = malloc(sizeof(lista));
	elem aux;
	int i, j, k;
	long n;
	clock_t tempo_ini;
	clock_t media_tempos_hs[total_entradas] = {0}; 
	clock_t media_tempos_bs[total_entradas] = {0}; 
	clock_t media_tempos_qs[total_entradas] = {0}; 
	clock_t media_tempos_rs[total_entradas] = {0};
	
	/*Inicia a Lista*/
	//cria(L_aux, (long) pow(10, total_entradas));
	//cria(L, (long) pow(10, total_entradas));
	cria(L_aux, (long) pow(10, total_entradas*5));
	cria(L, (long) pow(10, total_entradas*5));
	
	for(k = 1; k <= total_entradas; k++){
		//n = pow(10, k);
		n = pow(10, 5);
		
		for(i=0;i<n;i++){
			scanf("%d", &aux);
			insere(L_aux, aux);
		}
		
		for(j = 1;  j <= 10; j++){
			/*
			printf("HS:\n");
			copia(L_aux, L);
			imprime(L);
			tempo_ini = clock();
			ordena_heap_sort(L);
			media_tempos_hs[k] += clock() - tempo_ini;
			imprime(L);*/
			
			/*
			printf("BS:\n");
			copia(L_aux, L);
			imprime(L);
			tempo_ini = clock();
			ordena_bubble_sort(L);
			media_tempos_bs[k] += clock() - tempo_ini;
			imprime(L);*/
			
			/*
			printf("QS:\n");
			copia(L_aux, L);
			imprime(L);
			tempo_ini = clock();
			ordena_quick_sort(L);
			media_tempos_qs[k] += clock() - tempo_ini;
			imprime(L);*/
			
			printf("RS:\n");
			copia(L_aux, L);
			imprime(L);
			tempo_ini = clock();
			ordena_radix_sort(L);
			media_tempos_rs[k] += clock() - tempo_ini;
			imprime(L);*/
			
		}
		
		printf("Terminei uma rodada\n");
	}

	printf("\nTempo total de cada\n");
	printf("HeapSort:");
	for(k = 0; k <= total_entradas -1; k++)
		printf("  %lf  ", (media_tempos_hs[k]/(double) 10)/CLOCKS_PER_SEC);
		
	printf("\nBubbleSort:");
	for(k = 0; k <= total_entradas -1; k++)
		printf("  %lf  ", (media_tempos_bs[k]/(double) 10)/CLOCKS_PER_SEC);
		
	printf("\nQuickSort:");
	for(k = 0; k <= total_entradas -1; k++)
		printf("  %lf  ", (media_tempos_qs[k]/(double) 10)/CLOCKS_PER_SEC);
	
	printf("\nRadixSort:");
	for(k = 0; k <= total_entradas -1; k++)
		printf("  %lf  ", (media_tempos_rs[k]/(double) 10)/CLOCKS_PER_SEC);
	
	printf("\n");
		
	return 0;
}

/*lista* L = malloc(sizeof(lista));
	elem aux;
	cria(L, (long) pow(10, 5));
	
	for(int i=0;i<100000;i++){
			scanf("%d", &aux);
			insere(L, aux);
	}
	
	imprime(L);
	for(int j = 0; j <= 10; j++)
		ordena_quick_sort(L);
	imprime(L);*/

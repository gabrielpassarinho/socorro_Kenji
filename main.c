#include <stdio.h>
#include "ordena_lista.h"
#include <time.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define total_entradas 5

int main(void){
	/*Declarando variáveis*/
	lista* L = malloc(sizeof(lista));
	elem aux;
	int i, j, k;
	long n;
	clock_t tempo_ini;
	clock_t media_tempos_hs[total_entradas]; 
	clock_t media_tempos_bs[total_entradas]; 
	clock_t media_tempos_qs[total_entradas]; 
	clock_t media_tempos_rs[total_entradas];

	for(k = 1; k <= total_entradas; k++){
		n = pow(10, k);
		
		/*Inicia a Lista*/
		cria(L, n);

		for(i=0;i<n;i++){
			scanf("%d", &aux);
			insere(L, aux);
		}

		//printf("Antes do sort\n")
		//imprime(L);
		media_tempos_hs[k], media_tempos_bs[k], media_tempos_qs[k], media_tempos_rs[k] = 0;
		for(j = 1;  j <= 10; j++){
			tempo_ini = clock();
			/*Código que deve ser medido o tempo*/
			ordena_heap_sort(L);
			media_tempos_hs[k] += clock() - tempo_ini;
			
			tempo_ini = clock();
			/*Código que deve ser medido o tempo*/
			ordena_bubble_sort(L);
			media_tempos_bs[k] += clock() - tempo_ini;
			
			tempo_ini = clock();
			/*Código que deve ser medido o tempo*/
			ordena_quick_sort(L);
			media_tempos_qs[k] += clock() - tempo_ini;
			
			tempo_ini = clock();
			/*Código que deve ser medido o tempo*/
			ordena_radix_sort(L);
			media_tempos_rs[k] += clock() - tempo_ini;
		}
		
		media_tempos_hs[k] = media_tempos_hs[k]/10; 
		media_tempos_bs[k] = media_tempos_bs[k]/10;
		media_tempos_qs[k] = media_tempos_qs[k]/10;
		media_tempos_rs[k] = media_tempos_rs[k]/10;
	}

	printf("\nTempo total de cada algoritmo nas entradas de tamanho: %ld\n", n);
	printf("HeapSort:");
	for(k = 0; k <= total_entradas -1; k++)
		printf("  %lf  ", (double) media_tempos_hs[k]/CLOCK_PER_SEC);
	
	printf("\nBubbleSort:");
	for(k = 0; k <= total_entradas -1; k++)
		printf("  %lf  ", (double) media_tempos_bs[k]/CLOCK_PER_SEC);
	
	printf("\nQuickSort:");
	for(k = 0; k <= total_entradas -1; k++)
		printf("  %lf  ", (double) media_tempos_qs[k]/CLOCK_PER_SEC);
	
	printf("\nRadixSort:");
	for(k = 0; k <= total_entradas -1; k++)
		printf("  %lf  ", (double) media_tempos_rs[k]/CLOCK_PER_SEC);
	
	
	return 0;
	}

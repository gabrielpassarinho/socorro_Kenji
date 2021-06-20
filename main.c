#include <stdio.h>
#include "ordena_lista.h"
#include <time.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define total_entradas 5

int main(void){
	//Declarando variáveis
	lista* L = malloc(sizeof(lista));
	int i, j, k;
	long n;
	clock_t tempo_ini;
	clock_t media_tempos_hs[3][total_entradas]; 
	clock_t media_tempos_bs[3][total_entradas]; 
	clock_t media_tempos_qs[3][total_entradas]; 
	clock_t media_tempos_rs[3][total_entradas];
	
	//Inicia a Lista
	cria(L, (long) pow(10, total_entradas));
	
	for(i = 0; i<= 2; i++)
		for(j = 0; j<= total_entradas-1;j++){
			media_tempos_hs[i][j] = 0; 
			media_tempos_bs[i][j] = 0; 
			media_tempos_qs[i][j] = 0; 
			media_tempos_rs[i][j] = 0;
		}	
		
	
	int c = 0;
	for(i = 0; i <= 2; i++ ){
		for(k = 1; k <= total_entradas; k++){
			n = pow(10, k);
			for(j = 1;  j <= 10; j++){
				preenche(L, n, c);
				tempo_ini = clock();
				ordena_heap_sort(L);
				media_tempos_hs[i][k - 1] += clock() - tempo_ini;
				
				preenche(L, n, c);
				tempo_ini = clock();
				ordena_bubble_sort(L);
				media_tempos_bs[i][k - 1] += clock() - tempo_ini;
			
				preenche(L, n, c);
				tempo_ini = clock();
				ordena_quick_sort(L);
				media_tempos_qs[i][k - 1] += clock() - tempo_ini;
				
				preenche(L, n, c);
				tempo_ini = clock();
				ordena_radix_sort(L);
				media_tempos_rs[i][k - 1] += clock() - tempo_ini;
				//printf("\nterminei, j = %d\n", j);
			}
		}
		
		if(c == 0){
			printf("\nVetores Aleatorios");
			c = 1;
		} else if(c == 1){
			printf("\nVetores em ordem crescente");
			c = -1;
		} else if(c == -1)
			printf("\nVetores em ordem decrescente");
			
		printf("\nTempo total de cada algoritmo\n");
		printf("HeapSort:  ");
		for(k = 0; k <= total_entradas -1; k++)
			printf("  %lf  ", (media_tempos_hs[i][k]/(double) 10)/CLOCKS_PER_SEC);
			
		printf("\nBubbleSort:");
		for(k = 0; k <= total_entradas -1; k++)
			printf("  %lf  ", (media_tempos_bs[i][k]/(double) 10)/CLOCKS_PER_SEC);
			
		printf("\nQuickSort: ");
		for(k = 0; k <= total_entradas -1; k++)
			printf("  %lf  ", (media_tempos_qs[i][k]/(double) 10)/CLOCKS_PER_SEC);
		
		printf("\nRadixSort: ");
		for(k = 0; k <= total_entradas -1; k++)
			printf("  %lf  ", (media_tempos_rs[i][k]/(double) 10)/CLOCKS_PER_SEC);
		printf("\n");
	}
	
	destroi(L);
		
	return 0;
}


/*
int main(){
	// run_debugging
	lista* L = malloc(sizeof(lista));
	
	cria(L, (long) pow(10, 5));
	preenche(L,  (long) pow(10, 4), -1);
	
	imprime(L);
	
	clock_t tempo_ini;
	clock_t media = 0;
	for(int j = 0; j < 10; j++){
		tempo_ini = clock();
		ordena_bubble_sort(L);
		media += clock() - tempo_ini;
	}
	
	imprime(L);
	
	printf("  %lf  \n", (media/(double) 10)/CLOCKS_PER_SEC);
	
	return 0;	
}*/


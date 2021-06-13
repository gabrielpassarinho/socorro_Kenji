#include <stdio.h>
#include "ordena_lista.h"
#include <time.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int main(void){
  /*Declarando variáveis*/
  lista* L = malloc(sizeof(lista));
  elem aux;
  int i;
  int n = 10000;
  clock_t tempo_ini,tempo_fim;

  /*Inicia a Lista*/
  cria(L);
  

  for(i=0;i<n;i++){
    scanf("%d", &aux);
    insere(L,aux);
  }
  printf("Antes do sort\n");


  imprime(L);
  
  tempo_ini = clock();
  /*Código que deve ser medido o tempo*/
  ordena_heap_sort(L);
  tempo_fim = clock();

  printf("Depois do sort\n");
  imprime(L);
  printf("\nTempo total: %0.10f\n", (double) (tempo_fim - tempo_ini / CLOCKS_PER_SEC));
  return 0;
}
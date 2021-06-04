#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void cria(lista *l){
    l->tamanho = 0;
    l->elementos = malloc(sizeof(elem)*TAM);
    
    return;
}

void destroi(lista *l){
    free(lista->elementos);
    l->tamanho = 0;
	
	return;
};

int insere(lista *l, elem e){
    if(l->tamanho <= TAM){
        lista->elem[l->tamanho] = e;
		l->tamanho++;
		return 1; // insercao deu certo
    } else
		return 0; // lista cheia
}

void imprime(lista *l){
	long i = 0;

    if (l->tamanho == 0)  
        printf("( )\n"); //lista vazia
    else {
        printf("(");
        for (; i < l->tamanho-1; i++)
            printf("%d, ", l->elementos[i]);
        printf("%d)\n", l->elementos[i]);
    }

	return;
}

void ordena_bubble_sort(lista *l) {
	int ordenado = 0; // se ordenado == 1, vetor estah ordenado; 0, c.c.
	int i, j, aux = 0, 0, 0;

	while(i <= n-1 && !ordenado){ //enquanto nao chegarmos ao fum do vetor, e enquanto nosso vetor nao estiver ordenado
		ordenado = 1;
		while(j <= n-i-2){ // apos i rodadas, ninguem eh maior do que o i-esimo elemento, portanto, so executamos a rotina ate a posicao i-1 
			if (l->elementos[j] > l->elementos[j+1]){ //invertemos as posicoes desordenadas
				ordenado = 0;
				aux = l->elementos[j];
				l->elementos[j] = l->elementos[j+1];
				l->elementos[j+1] = aux;
			}
			j++;
		}
		i++;
	}

	return;
}

// void ordena_quick_sort(lista *l);

void ordena_contagem(lista *l, long ordem){ // funcao auxiliar da ordena_radix_sort
	int i; //contador
	elem  b[10] = {0}; // auxiliar
	elem ordenado[l->tamanho]; // auxiliar

	for(i = 0; i <= l->tamanho; i++)
		b[l->elementos[i]/ordem % 10]++;
	
	for(i = 1; i<= 9; i++)
		b[i] += b[i - 1];

	for(i = l->tamanho - 1; i >= 0; i--)
		ordenado[b[l->elementos/ordem % 10]-1] = l->elementos[i];

	for(i = 0; i <= l->tamanho - 1; i++)
		l->elementos[i] = ordenado[i];

	return;
}

void ordena_radix_sort(lista *l){
	long i, ordem; //contadores
	elem maior; //maior elemento de l

	//determinando maior
	maior = l->elementos[0];
	for(i = 1; i<= l->tamanho - 1; i++)
		if(maior <= l->elementos[i])
			maior = l->elementos[i];
	
	//ordenando
	while(maior/ordem > 0){
		ordena_contagem(l, ordem);
		ordem *= 10;
	}
}

// void ordena_heap_sort(lista *l);

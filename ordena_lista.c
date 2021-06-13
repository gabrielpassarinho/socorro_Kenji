/**/
#include <stdio.h>
#include <stdlib.h>
#include "ordena_lista.h"

/*Funções de Lista*/
void cria(lista *l, long TAM){
    l->tamanho = 0;
    l->TAM_MAX = TAM;
    l->elementos = malloc(sizeof(elem)*TAM);
    
    return;
}

void destroi(lista *l){
    free(l->elementos);
    l->tamanho = 0;
    
    return;
};

int insere(lista *l, elem e){
	if (l->tamanho <= l->TAM_MAX - 1) {
		l->elementos[l->tamanho] = e;
		l->tamanho++;
		return 1; // insercao deu certo
    } else
		return 0; // lista cheia
}

void imprime(lista *l){
	long i;
    if (l->tamanho == 0)  
        printf("( )\n"); //lista vazia
    else {
        printf("(");
        for (i = 0; i < l->tamanho-1; i++)
            printf("%d, ", l->elementos[i]);
        printf("%d)\n", l->elementos[i]);
    }

	return;
}

/***********/
/*BubbleSort*/
/***********/

void ordena_bubble_sort(lista *l) {
	int ordenado = 0; // se ordenado == 1, vetor estah ordenado; 0, c.c.
	int i, j, aux = 0;

	for(i = 0; i <= l->tamanho-1 && ordenado == 0; i++){ //enquanto nao chegarmos ao fum do vetor, e enquanto nosso vetor nao estiver ordenado
		ordenado = 1;
		for(j = 0; j <= l->tamanho-i-2; j++){ // apos i rodadas, ninguem eh maior do que o i-esimo elemento, portanto, so executamos a rotina ate a posicao i-1 
			if (l->elementos[j] > l->elementos[j+1]){ //invertemos as posicoes desordenadas
				ordenado = 0;
				aux = l->elementos[j];
				l->elementos[j] = l->elementos[j+1];
				l->elementos[j+1] = aux;
			}
		}
	}

	return;
}


/***********/
/*RadixSort*/
/***********/

void ordena_contagem(lista *l, long ordem){ // funcao auxiliar da ordena_radix_sort
	long i; //contador
	elem  b[10] = {0}; // auxiliar
	elem ordenado[l->tamanho]; // auxiliar

	for(i = 0; i <= l->tamanho-1; i++)
		b[(l->elementos[i]/ordem) % 10]++;
	
	for(i = 1; i <= 9; i++)
		b[i] += b[i - 1];

	for(i = l->tamanho - 1; i >= 0; i--){
		b[(l->elementos[i]/ordem) % 10]--;
		ordenado[b[(l->elementos[i]/ordem) % 10]] = l->elementos[i];
	}
	for(i = 0; i <= l->tamanho - 1; i++)
		l->elementos[i] = ordenado[i];
		
	return;
}

void ordena_radix_sort(lista *l){
	long i, ordem; //contadores
	elem maior; //maior elemento de l

	//determinando maior
	maior = l->elementos[0];
	for(i = 1; i <= l->tamanho - 1; i++)
		if(maior < l->elementos[i])
			maior = l->elementos[i];
	
	//ordenando
	ordem = 1;
	while(maior/ordem > 0){
		ordena_contagem(l, ordem);
		ordem *= 10;
	}
}

/***********/
/*Quicksort*/
/***********/

int partition(elem *A, int inicio, int fim){
  elem aux;
  elem pivo = A[fim];
  int i = inicio - 1;
  for(int j = inicio; j<fim; j++){
    if(A[j] < pivo){
      i = i + 1;
      aux = A[i];
      A[i] = A[j];
      A[j] = aux;
    }
  }

  aux = A[i+1];
  A[i+1] = A[fim];
  A[fim] = aux;
  return(i+1);
}

int random_partition(elem *A, int inicio, int fim){
  elem aux;
  int k = rand() % (fim + 1 - inicio) + inicio;

  aux = A[fim];
  A[fim] = A[k];
  A[k] = aux;

  return partition(A, inicio, fim);
}

void quicksort(elem *A, int inicio, int fim){
  int pivo;
  if (inicio < fim){
    pivo = random_partition(A, inicio, fim);

    quicksort(A, inicio, pivo-1);
    quicksort(A, pivo+1, fim);
  }
}

void ordena_quick_sort(lista *l){
  quicksort(l->elementos, 0, l->tamanho-1);
}

/***********/
/*HeapSort*/
/***********/

void heapfy(elem *A,int n,int i){
  int maior = i;
  int esq = (2*i) + 1;
  int dir = (2*i) + 2;
  elem aux;
  if(esq < n && A[esq] > A[maior]){
    maior = esq;
  }
  if(dir < n && A[dir]>A[maior]){
    maior = dir;
  }
  if(maior != i){
    aux = A[i];
    A[i] = A[maior];
    A[maior] = aux;
    heapfy(A,n,maior);
  }
}

void heapsort(elem *A, int n){
  int i;
  elem aux;
  for(i=n/2 - 1; i >= 0; i--){
    heapfy(A, n, i);
  }

  for(i=n-1; i>=1;i--){
    aux = A[0];
    A[0] = A[i];
    A[i] = aux;
    heapfy(A, i, 0);
  }
}

void ordena_heap_sort(lista *l){
  heapsort(l->elementos, l->tamanho);
}



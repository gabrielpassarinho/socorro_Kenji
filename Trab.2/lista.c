/* Autores
Danillo Mendes Santiago 10414592
Gabriel Passarelli 11218480
Marcelo Kenji Noda 11275359
*/
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cria_lista(lista *l){
	l->primeiro = NULL;
	l->tamanho = 0;
	
	return;
}

int insere_lista(lista *l, elem e){
	No* atual = l->primeiro;
	
	if(atual == NULL){ // primeiro elemento da lista
		l->primeiro = malloc(sizeof(No));
		l->primeiro->valor = (elem) malloc(sizeof(char) * MAX_STRING_LEN);
		strcpy(l->primeiro->valor, e);
		l->primeiro->proximo = NULL;
		l->tamanho ++;
		return 1;
	}
	
	while(atual->proximo != NULL)// caminhando ate o final da lista
		if(strcmp(atual->valor, e) == 0)
			return 0; // elemento repetido
		else
			atual = atual->proximo;
	
	No* novo = malloc(sizeof(No));
	novo->valor = (elem) malloc(sizeof(char) * MAX_STRING_LEN);
	strcpy(novo->valor, e);
	novo->proximo = NULL;
	atual->proximo = novo;
	l->tamanho ++;
	return 1;
}

int busca_lista(lista* l, elem e){
	int i = 0;
	No* aux = l->primeiro;
	
	if(aux == NULL){
		return -1;
	}
		
	while(strcmp(aux->valor, e) != 0){
		aux = aux->proximo;
		if(aux == NULL)
			return -1; // final da lista
		i++;
	}
	
	return i;
}

void destroi_lista(lista *l){
	No* atual = l->primeiro;
	No* proximo;
	
	while(atual != NULL){
		proximo = atual->proximo;
		free(atual);
		atual = proximo;
	}
	
	l->tamanho = 0;
	
	return;
}

void imprime_lista(lista *l){
	long i;
	No* aux = l->primeiro;
    if (l->tamanho == 0)  
        printf("( )\n"); //lista vazia
    else {
    	printf("(");
        if(l->tamanho > 20){
        	for (i = 0; i < 10; i++){
            	printf("%s, ", aux->valor);
            	aux = aux->proximo;
            }	
            printf("..., ");
            
            for (i = l->tamanho - 10; i < l->tamanho - 1; i++){
            	printf("%s, ", aux->valor);
            	aux = aux->proximo;
            }
        	printf("%s)\n", aux->valor);
    	} else{
    		for (i = 0; i < l->tamanho - 1; i++){
            	printf("%s, ", aux->valor);
            	aux = aux->proximo;
            }
        	printf("%s)\n", aux->valor);
		}
    }

	return;
}


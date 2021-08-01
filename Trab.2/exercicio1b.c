/* Autores (a partir do codigo fornecido)
Danillo Mendes Santiago 10414592
Gabriel Passarelli 11218480
Marcelo Kenji Noda 11275359
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
unsigned char typedef bool;
#define TRUE  1
#define FALSE 0

int* ler_inteiros(const char * arquivo, const int n)
{
    FILE* f = fopen(arquivo, "r");

    int * inteiros = (int *) malloc(sizeof(int) * n);

    for (int i = 0; !feof(f); i++)
        fscanf(f, "%d\n", &inteiros[i]);

    fclose(f);

    return inteiros;
}

void inicia_tempo()
{
    srand(time(NULL));
    _ini = clock();
}

double finaliza_tempo()
{
    _fim = clock();
    return ((double) (_fim - _ini)) / CLOCKS_PER_SEC;
}

#include "lista_int.h"

int buscar(lista_int* l, int e){
    int iteracoes = 0;
    No* aux_pai = NULL;
    No* aux = l->primeiro;

    // busca e realoca para a 1ª posicao
    while (aux->proximo != NULL){// itera na lista:
        if(aux->valor == e){ // se achou
            if(iteracoes == 0){
                return 1;// se for o primeiro item, nao faz nada
            }// senao: 

            aux_pai->proximo = aux->proximo;// liga pai--->prox (pode ser null)
            
            // e coloca-o na 1ª pos da lista (existem pelo menos 2 itens na lista, facilita)
            No* primeiro = l->primeiro;
            l->primeiro = aux;
            aux->proximo = primeiro;
            
            return 1;
            // excecoes??****

        }
        // caso ainda nao achou...
        // saber de onde veio e continuar loop
        aux_pai = aux;
        aux = aux->proximo;
        iteracoes++;
    }
    return 0;//nao achou
    
}

int main(int argc, char const *argv[])
{
    const int N = 50000;
    unsigned encontrados = 0;

    int* entradas = ler_inteiros("inteiros_entrada.txt", N);
    int* consultas = ler_inteiros("inteiros_busca.txt", N);

    lista_int *l;
    cria_lista(l);

    // preenche a lista com os numeros de [int* entradas]
    for (int i = 0; i < N; i++){
        insere_lista(l,entradas[i]);
    }
    
    // realiza busca sequencial com realocação
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        // buscar o elemento consultas[i] na entrada
        encontrados += buscar(l, consultas[i]);
    }
    double tempo_busca = finaliza_tempo();

    printf("Tempo de busca    :\t%fs\n", tempo_busca);
    printf("Itens encontrados :\t%d\n", encontrados);

    return 0;
}

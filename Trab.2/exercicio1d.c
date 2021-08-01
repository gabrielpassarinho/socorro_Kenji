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

    int* inteiros = (int *) malloc(sizeof(int) * n);

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

//Função para comparar elementos utilizado no quicksort
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int buscar_elemento(int* tabela,int chave ,int N,int bucket){
  for(int i=0;i<N;i++){
    if(chave == tabela[bucket*N + i]){
      return 1;
    }
  }
  return -1;
}

int encontra_bucket(int *tabela_index,int tamanho_tab, int chave){
  for(int i=0;i<tamanho_tab;i++){
    if(chave<tabela_index[i]){
      return i;
    }
  }
  return -1;
}

int main(int argc, char const *argv[])
{
    const int N = 50000;
    const int index_size = 10000;
    unsigned encontrados = 0;
    int T = N/index_size;
    int* tabela_indice;
    int* entradas = ler_inteiros("inteiros_entrada.txt", N);
    int* consultas = ler_inteiros("inteiros_busca.txt", N);  

    int bucket = -1;
    // ordenar entrada
    //Usando função nativa para ordenar o vetor estático
    qsort(entradas, N, sizeof(int), cmpfunc);

    // criar tabela de indice
    tabela_indice = malloc(T * sizeof (int));

    for(int i=0;i<T;i++){
      if(i<T-1){
        tabela_indice[i] = entradas[(i+1)*index_size];
      }else{
        tabela_indice[i] = entradas[(i+1)*index_size-1];
      }
      
    }

    // realizar consultas na tabela de indices 
    inicia_tempo();
    for (int i = 0; i < N; i++) {
      bucket = encontra_bucket(tabela_indice,T, consultas[i]);
      if(bucket >= 0){
        if(buscar_elemento(entradas,consultas[i],index_size, bucket)>0){
          encontrados++;
        }
      }
    }

    double tempo_busca = finaliza_tempo();
    free(tabela_indice);
    printf("Tempo de busca    :\t%fs\n", tempo_busca);
    printf("Itens encontrados :\t%d\n", encontrados);

    return 0;
}

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

int buscar_elemento(int *tabela, int chave, int N){
  for(int i = 0; i<N;i++){
    if(tabela[i] == chave){
      if(i==0){
        // Caso o elemento já seja o primeiro, nada devera ser feito
        return 1;
      }else{
        int aux;
        // Realiza a trasnposicao
        aux = tabela[i-1];
        tabela[i-1] = tabela[i];
        tabela[i] = aux;
        return 1;
      }
    }
  }
  // retorna -1 caso nao encontre nada
  return -1;
}

int main(int argc, char const *argv[])
{
    const int N = 50000;
    unsigned encontrados = 0;

    int* entradas = ler_inteiros("inteiros_entrada.txt", N);
    int* consultas = ler_inteiros("inteiros_busca.txt", N);

    // realiza busca sequencia com realocação
    inicia_tempo();
    for (int i = 0; i < N; i++) {
      if(buscar_elemento(entradas,consultas[i],N)<0){
        encontrados++;
      }
        // buscar o elemento consultas[i] na entrada
    }
    double tempo_busca = finaliza_tempo();
    printf("Hello World");
    printf("Tempo de busca    :\t%fs\n", tempo_busca);
    printf("Itens encontrados :\t%d\n", encontrados);

    return 0;
}
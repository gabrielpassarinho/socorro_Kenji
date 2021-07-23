/* Autores (a partir do codigo fornecido)
Danillo Mendes Santiago 10414592
Gabriel Passarelli 11218480
Marcelo Kenji Noda 11275359
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> // funções strcmp e strcpy
#include <time.h>
#include "lista.h"

/* Definição do tipo booleano */
typedef unsigned char bool;
#define TRUE  1
#define FALSE 0

/* Definição das variaveis que controlam a medição de tempo */
clock_t _ini, _fim;

void inicia_tempo() {
    srand(time(NULL));
    _ini = clock();
}

double finaliza_tempo() {
    _fim = clock();
    return ((double) (_fim - _ini)) / CLOCKS_PER_SEC;
}

/* Definição do tipo string */
#define MAX_STRING_LEN 20
typedef char * string;

unsigned converter(string s) {
   unsigned h = 0;
   for (int i = 0; s[i] != '\0'; i++) 
      h = h * 256 + s[i];
   return h;
}

string* ler_strings(const char * arquivo, const int n) {
    FILE* f = fopen(arquivo, "r");
    
    string* strings = (string *) malloc(sizeof(string) * n);

    for (int i = 0; !feof(f); i++) {
        strings[i] = (string) malloc(sizeof(char) * MAX_STRING_LEN);
        fscanf(f, "%s\n", strings[i]);
    }

    fclose(f);

    return strings;
}

void imprime(string s){
	if(s == NULL)
		return;
		
	for (int i = 0; s[i] != '\0'; i++)
		printf("%c", s[i]);
		
	return;
}

/* Definicao da tabela de hash */
#define B 150001

typedef struct {
    lista elementos[B];
    int div; // se div = 1, entao a funcao de hash eh a hash div; se div = 0, eh a hash_mul
} hash;

unsigned h_div(unsigned x) {
    return x % B;
}

unsigned h_mul(unsigned x) {
    const double A = 0.6180;
    return fmod(x * A, 1) * B;
}

void inicializar(hash *tabela, int div) {
	if(div != 1 && div != 0)
		return; // valor invalido para div
	else
		tabela->div = div;
		
    for(int i = 0; i < B; i++)
        cria_lista(&(tabela->elementos[i]));
        
    return;
}

int inserir(hash *tabela, string palavra) { // retorna 1, em caso de colisao; 0, c.c.
	int deu_certo;
	if(tabela->div == 1){
		deu_certo = insere_lista( &(tabela->elementos[h_div(converter(palavra))]), palavra);
		return (tabela->elementos[h_div(converter(palavra))].tamanho > 1 && deu_certo == 1) ? 1 : 0; // se nao inserimos o primeiro no
	} else{
		deu_certo = insere_lista( &(tabela->elementos[h_mul(converter(palavra))]), palavra);
		return (tabela->elementos[h_mul(converter(palavra))].tamanho > 1 && deu_certo == 1) ? 1 : 0;
	}
}

int buscar(hash *tabela, string palavra) { // retorna a posicao na tabela, ou -1, caso a palavra nao tenha sido encontrada
	if(tabela->div == 1)
		return busca_lista( &(tabela->elementos[h_div(converter(palavra))]), palavra);
	else
		return busca_lista( &(tabela->elementos[h_mul(converter(palavra))]), palavra);
}

void limpa_tabela(hash * tabela){
	for(int i = 0; i < B; i++)
		destroi_lista(&(tabela->elementos[i]));

	return;
}

void imprime_hash(hash* tabela){
	int i = 0;
	int c = 0;
	while(i < 5){
		if(tabela->elementos[c].tamanho != 0){		
			imprime_lista(&(tabela->elementos[c]));
			i++;
		}
		c++;
		if(c == B - 1)
			break;
	}
			
}

int main(int argc, char const *argv[]) {
    const int N = 50000;
    const int M = 70000;

    unsigned colisoes_h_div = 0;
    unsigned colisoes_h_mul = 0;

    unsigned encontrados_h_div = 0;
    unsigned encontrados_h_mul = 0;
    string* insercoes = ler_strings("strings_entrada.txt", N);
    string* consultas = ler_strings("strings_busca.txt", M);
    
    // cria tabela hash com hash por divisão
    hash tabela_div;
	inicializar(&tabela_div, 1);
	
    // inserção dos dados na tabela hash com hash por divisão
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        // inserir insercoes[i] na tabela hash
        colisoes_h_div += inserir(&tabela_div, insercoes[i]);
    }
    double tempo_insercao_h_div = finaliza_tempo();
  
    // busca dos dados na tabela hash com hash por divisão
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        // buscar consultas[i] na tabela hash
        if(buscar(&tabela_div, consultas[i]) >= 0)
        	encontrados_h_div++;
    }
    double tempo_busca_h_div = finaliza_tempo();

    // destroi tabela hash com hash por divisão
	limpa_tabela(&tabela_div);

    // cria tabela hash com hash por multiplicação
	hash tabela_mul;
	inicializar(&tabela_mul, 0);
	
    // inserção dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        // inserir insercoes[i] na tabela hash
        colisoes_h_mul += inserir(&tabela_mul, insercoes[i]) ;
    }
    double tempo_insercao_h_mul = finaliza_tempo();

    // busca dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        // buscar consultas[i] na tabela hash
        if(buscar(&tabela_mul, consultas[i]) >= 0)
        	encontrados_h_mul++;
    }
    double tempo_busca_h_mul = finaliza_tempo();

    // destroi tabela hash com hash por multiplicação
	limpa_tabela(&tabela_mul);

    printf("Hash por Divisão\n");
    printf("Colisões na inserção: %d\n", colisoes_h_div);
    printf("Tempo de inserção   : %fs\n", tempo_insercao_h_div);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_div);
    printf("Itens encontrados   : %d\n", encontrados_h_div);
    printf("\n");
    printf("Hash por Multiplicação\n");
    printf("Colisões na inserção: %d\n", colisoes_h_mul);
    printf("Tempo de inserção   : %fs\n", tempo_insercao_h_mul);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_mul);
    printf("Itens encontrados   : %d\n", encontrados_h_mul);
    
    return 0;
}

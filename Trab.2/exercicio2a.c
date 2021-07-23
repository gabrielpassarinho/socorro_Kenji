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
    string elementos[B];
    int div; // se div = 1, entao a funcao de hash eh a hash div; se div = 0, eh a hash_mul
} hash;

unsigned h_div(unsigned x, unsigned i) {
    return ((x % B) + i) % B;
}

unsigned h_mul(unsigned x, unsigned i) {
    const double A = 0.6180;
    return  ((int) ((fmod(x * A, 1) * B) + i)) % B;
}

void inicializar(hash *tabela, int div) {
	if(div != 1 && div != 0)
		return; // valor invalido para div
	else
		tabela->div = div;
		
    for (int i = 0; i < B; i++)
        tabela->elementos[i] = NULL;
        
    return;
}

int inserir_div(hash *tabela, string palavra) { // nao deve ser utilizada na main
    int posicao;
    
    for (int i = 0; i < B; i++) {
        posicao = h_div(converter(palavra), i); // calcula posicao
        
        if(tabela->elementos[posicao] == NULL){ // posicao vazia nunca utilizada
        	tabela->elementos[posicao] = (string) malloc(sizeof(char) * MAX_STRING_LEN); // aloca a string
        	strcpy(tabela->elementos[posicao], palavra);
        	return (i > 0) ? 1 : 0; // retorna 1, se houve colisao; 0, c.c. (se tiver havido colisao, i > 0.)
        } else if (strcmp(tabela->elementos[posicao], palavra) == 0)
            return 0; // elemento repetido
    }
    
    return 0; // tabela cheia
}

int inserir_mul(hash *tabela, string palavra) { // nao deve ser utilizada na main
    int posicao;
    
    for (int i = 0; i < B; i++) {
        posicao = h_mul(converter(palavra), i); // calcula endereco
        
        if(tabela->elementos[posicao] == NULL){ // posicao vazia nunca utilizada
        	tabela->elementos[posicao] = (string) malloc(sizeof(char) * MAX_STRING_LEN); // aloca a string
        	strcpy(tabela->elementos[posicao], palavra);
        	return (i > 0) ? 1 : 0; // retorna 1, se houve colisao; 0, c.c. (se tiver havido colisao, i > 0.)
        } else if (strcmp(tabela->elementos[posicao], palavra) == 0)
            return 0; // elemento repetido
    }
    
    return 0; // tabela cheia
}

int inserir(hash *tabela, string palavra) { // retorna 0, se nao houver colisoes ou se der erro; 1, c.c.
	if(tabela->div == 1)
		return inserir_div(tabela, palavra);
	else
		return inserir_mul(tabela, palavra);
}

int buscar_div(hash *tabela, string palavra) { // nao deve ser utilizada na main
    int posicao;
    
    for (int i = 0; i < B; i++) {
        posicao = h_div(converter(palavra),i); // calcula posicao
        
        if (tabela->elementos[posicao] == NULL){
            return -1; // elemento nao encontrado (espaco na tabela)
        } else if (strcmp(tabela->elementos[posicao], palavra) == 0)
            return posicao; // elemento encontrado
    }
    
    return -1; // elemento nao encontrado (tabela cheia)
}

int buscar_mul(hash *tabela, string palavra) { // nao deve ser utilizada na main
    int posicao;
    
    for (int i = 0; i < B; i++) {
        posicao = h_mul(converter(palavra),i); // calcula posicao
        
        if (tabela->elementos[posicao] == NULL){
            return -1; // elemento nao encontrado (espaco na tabela)
        } else if (strcmp(tabela->elementos[posicao], palavra) == 0)
            return posicao; // elemento encontrado
    }
    
    return -1; // elemento nao encontrado (tabela cheia)
}

int buscar(hash *tabela, string palavra) { // retorna a posicao na tabela, ou -1, caso a palavra nao tenha sido encontrada
	if(tabela->div == 1)
		return buscar_div(tabela, palavra);
	else
		return buscar_mul(tabela, palavra);
}

void limpa_tabela(hash * tabela){
	for(int i = 0; i < B; i++){
		free(tabela->elementos[i]);
		tabela->elementos[i] = NULL;
	}
	
	return;
}

int main(int argc, char const *argv[]) {
    unsigned N = 50000;
    unsigned M = 70000;

    unsigned colisoes_h_div = 0;
    unsigned colisoes_h_mul = 0;

    unsigned encontrados_h_div = 0;
    unsigned encontrados_h_mul = 0;

    string* insercoes = ler_strings("strings_entrada.txt", N);
    string* consultas = ler_strings("strings_busca.txt", M);

	/*Hash por divisão*/
	hash tabela_div;
	inicializar(&tabela_div, 1);
	
    inicia_tempo();
    for (int i = 0; i < N; i++) 
        colisoes_h_div += inserir(&tabela_div, insercoes[i]);
    double tempo_insercao_h_div = finaliza_tempo();
    
    inicia_tempo();
    for (int i = 0; i < M; i++) 
        if(buscar(&tabela_div, consultas[i]) > 0)
        	encontrados_h_div++;
    double tempo_busca_h_div = finaliza_tempo();

	limpa_tabela(&tabela_div);
	
	/*Hash por multiplicacao*/
	hash tabela_mul;
	inicializar(&tabela_mul, 0);
	
    inicia_tempo();
    for (int i = 0; i < N; i++) 
        colisoes_h_mul += inserir(&tabela_mul, insercoes[i]) ;
    double tempo_insercao_h_mul = finaliza_tempo();

    inicia_tempo();
    for (int i = 0; i < M; i++)
        if(buscar(&tabela_mul, consultas[i]) > 0)
        	encontrados_h_mul++;
    double tempo_busca_h_mul = finaliza_tempo();
    
	limpa_tabela(&tabela_mul);

	/*Impressao dos resultados*/
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

/*
int remover_div(hash *tabela, string palavra) {
    int posicao;
    for (int i = 0; i < B; i++) {
        posicao = h_div(converter(palavra),i); // calcula endereco
        if (tabela->elementos[posicao] == NULL) {
            return -1; // elemento nao encontrado (espaco na tabela)
        } else if (strcmp(tabela->elementos[posicao], palavra) == 0) {
            tabela->elementos[posicao][0] = '-'; // "-" indica posicao vazia e jah utilizada
            return posicao; // sucesso
        }
    }
    return -1; // elemento nao encontrado (tabela cheia)
}

int remover_mul(hash *tabela, string palavra) {
    int posicao;
    for (int i = 0; i < B; i++) {
        posicao = h_mul(converter(palavra),i); // calcula endereco
        if (tabela->elementos[posicao] == NULL) {
            return -1; // elemento nao encontrado (espaco na tabela)
        } else if (strcmp(tabela->elementos[posicao], palavra) == 0) {
            tabela->elementos[posicao][0] = '-'; // "-" indica posicao vazia e jah utilizada
            return posicao; // sucesso
        }
    }
    return -1; // elemento nao encontrado (tabela cheia)
}

int remover(hash *tabela, string palavra) {
	if(tabela->div == 1)
		return remover_div(tabela, palavra);
	else
		return remover_mul(tabela, palavra);
}

void imprime_hash(hash* tabela){
	int i = 0;
	int c = 0;
	printf("(");
	while(i < 10){
		if(tabela->elementos[i] != NULL){
			if(tabela->elementos[i][0] != '-'){
				imprime(tabela->elementos[i]);
				printf(", ");
				i++;
			}
		}
		c++;
		if(c > B)
			break;
	}
	printf(")");
	return;
}
// trecho necessario pras funcoes de insercao, caso as de remocao sejam necessarias
else if (tabela->elementos[posicao][0] == '-') { // "-" indica posicao vazia, ja utilizada
            strcpy(tabela->elementos[posicao], palavra);
            return 1; // sucesso
        }
*/



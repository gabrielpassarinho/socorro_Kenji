/* Autores (a partir do codigo fornecido)
Danillo Mendes Santiago 10414592
Gabriel Passarelli 11218480
Marcelo Kenji Noda 11275359
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>

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
} hash;

unsigned h_div(unsigned x) {
    return (x % B) % B;
}

unsigned h_mul(unsigned x) {
    const double A = 0.6180;
    return  ((int) (fmod(x * A, 1) * B)) % B;
}

unsigned h(unsigned x, unsigned i){
	return (h_mul(x) + i*h_div(x)) % B;
}

void inicializar(hash *tabela) {
    for (int i = 0; i < B; i++)
        tabela->elementos[i] = NULL;
        
    return;
}

int inserir(hash *tabela, string palavra) {
    int posicao;
    
    for (int i = 0; i < B; i++) {
        posicao = h(converter(palavra), i); // calcula posicao
        
        if(tabela->elementos[posicao] == NULL){ // posicao vazia nunca utilizada
        	tabela->elementos[posicao] = (string) malloc(sizeof(char) * MAX_STRING_LEN); // aloca a string
        	strcpy(tabela->elementos[posicao], palavra);
        	return (i > 0) ? 1 : 0; // retorna 1, se houve colisao; 0, c.c. (se tiver havido colisao, i > 0.)
        } else if (strcmp(tabela->elementos[posicao], palavra) == 0)
            return 0; // elemento repetido
    }
    
    return 0; // tabela cheia
}

int buscar(hash *tabela, string palavra) {
    int posicao;
    
    for (int i = 0; i < B; i++) {
        posicao = h(converter(palavra),i); // calcula posicao
        
        if (tabela->elementos[posicao] == NULL){
            return -1; // elemento nao encontrado (espaco na tabela)
        } else if (strcmp(tabela->elementos[posicao], palavra) == 0)
            return posicao; // elemento encontrado
    }
    
    return -1; // elemento nao encontrado (tabela cheia)
}

void limpa_tabela(hash * tabela){
	for(int i = 0; i < B; i++){
		free(tabela->elementos[i]);
		tabela->elementos[i] = NULL;
	}
	
	return;
}

int main(int argc, char const *argv[]) {
    const int N = 50000;
    const int M = 70000;

    unsigned colisoes = 0;
    unsigned encontrados = 0;

    string* insercoes = ler_strings("strings_entrada.txt", N);
    string* consultas = ler_strings("strings_busca.txt", M);


    // cria tabela hash com hash por hash duplo
	hash tabela;
	inicializar(&tabela);
	
    // inserção dos dados na tabela hash
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        // inserir insercoes[i] na tabela hash
        colisoes += inserir(&tabela, insercoes[i]);
    }
    double tempo_insercao = finaliza_tempo();

    // busca dos dados na tabela hash
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        // buscar consultas[i] na tabela hash
         if(buscar(&tabela, consultas[i]) > 0)
        	encontrados++;
    }
    double tempo_busca = finaliza_tempo();

	limpa_tabela(&tabela);
	
    printf("Colisões na inserção: %d\n", colisoes);
    printf("Tempo de inserção   : %fs\n", tempo_insercao);
    printf("Tempo de busca      : %fs\n", tempo_busca);
    printf("Itens encontrados   : %d\n", encontrados);

    return 0;
}

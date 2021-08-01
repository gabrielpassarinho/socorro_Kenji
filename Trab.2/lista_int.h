/* Autores
Danillo Mendes Santiago 10414592
Gabriel Passarelli 11218480
Marcelo Kenji Noda 11275359
*/
typedef int elem_i;

typedef struct no {
	elem_i valor;
	struct no* proximo;
} No;

typedef struct {
   No* primeiro;
   long tamanho;
} lista_int;

void cria_lista(lista_int *l);
int insere_lista(lista_int *l, elem_i e);
int remove_lista(lista_int* l, int indice);
int busca_lista(lista_int* l, elem_i e);//retorna indice se achar ou -1
void destroi_lista(lista_int *l);
void imprime_lista(lista_int *l);


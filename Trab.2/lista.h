/* Autores
Danillo Mendes Santiago 10414592
Gabriel Passarelli 11218480
Marcelo Kenji Noda 11275359
*/
#define MAX_STRING_LEN 20
typedef char * elem;

typedef struct no {
	elem valor;
	struct no* proximo;
} No;

typedef struct {
   No* primeiro;
   long tamanho;

} lista;

void cria_lista(lista *l);
int insere_lista(lista *l, elem e);
int busca_lista(lista* l, elem e);
void destroi_lista(lista *l);
void imprime_lista(lista *l);




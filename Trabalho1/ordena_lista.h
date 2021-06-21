/* Autores
Danillo Mendes Santiago 10414592
Gabriel Passarelli 11218480
Marcelo Kenji Noda 11275359
*/

typedef int elem;

typedef struct {
   elem *elementos;
   long tamanho;
   long TAM_MAX;
   
} lista;

void cria(lista *l, long TAM);
void destroi(lista *l);
int insere(lista *l, elem e);
void imprime(lista *l);
//l2 recebe l1
int copia(lista *l1, lista *l2); 
/*c == 0, para preencher randomicamente; c == -1, decrescente; c == 1, crescente; 
TAM <= TAM_MAX eh p numero de elementos a serem inseridos em l*/
void preenche(lista *l, long TAM, int c); 
void limpa(lista *l);

void ordena_bubble_sort(lista *l);
void ordena_quick_sort(lista *l);
void ordena_radix_sort(lista *l);
void ordena_heap_sort(lista *l);


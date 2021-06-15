
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
int copia(lista *l1, lista *l2); // l2 recebe l1
void preenche(lista *l, long TAM, int c); // c == 0 para preencher randomicamente; c == -1, decrescente; c == 1, crescente
void limpa(lista *l);

void ordena_bubble_sort(lista *l);
void ordena_quick_sort(lista *l);
void ordena_radix_sort(lista *l);
void ordena_heap_sort(lista *l);



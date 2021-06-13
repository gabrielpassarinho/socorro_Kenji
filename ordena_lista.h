
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
int copia(lista *l1, lista *l2);
void limpa(lista *l);

void ordena_bubble_sort(lista *l);
void ordena_quick_sort(lista *l);
void ordena_radix_sort(lista *l);
void ordena_heap_sort(lista *l);



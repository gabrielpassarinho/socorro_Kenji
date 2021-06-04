#define TAM 100001

typedef int elem;

typedef struct {
   elem *elementos;
   long tamanho;
} lista;

void cria(lista *l);
void destroi(lista *l);
int insere(lista *l, elem e);
void imprime(lista *l);
void ordena_bubble_sort(lista *l);
void ordena_quick_sort(lista *l);
void ordena_radix_sort(lista *l);
void ordena_heap_sort(lista *l);

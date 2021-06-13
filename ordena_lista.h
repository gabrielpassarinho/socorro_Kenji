#define TAM 100001

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

void ordena_bubble_sort(lista *l);
void ordena_quick_sort(lista *l);
void ordena_radix_sort(lista *l);
void ordena_heap_sort(lista *l);



typedef struct celula Celula;
typedef struct lista Lista;

Lista* ListaCria(); 
void ListaAdicionaInicio(Lista *l, int chave);
void moveElemento(Lista *l, int chave);
void ListaPrint(Lista *lista);


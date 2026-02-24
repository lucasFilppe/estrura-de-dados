// ============================================================================
// Incluir o arquivo header que contém as declarações da lista
// ============================================================================
#include "lista.h"

// ============================================================================
// Bibliotecas padrão do C
// ============================================================================
#include <stdio.h>   // Para funções de entrada/saída (printf)
#include <stdlib.h>  // Para alocação de memória (malloc, free)

// ============================================================================
// ESTRUTURA: Celula (Nó da lista)
// ============================================================================
typedef struct celula {
    // Ponteiro para a próxima célula na lista (ou NULL se for a última)
    struct celula* prox;
    
    // Ponteiro para a célula anterior (ou NULL se for a primeira)
    struct celula* ant;
    
    // Estrutura Item que contém os dados armazenados (chave, nome, etc)
    Item item;
} Celula;

// ============================================================================
// ESTRUTURA: Lista (Cabeça da lista)
// ============================================================================
struct lista {
    // Ponteiro para a célula sentinela de cabeça (primeira sentinela vazia)
    Celula* cabeca;
    
    // Ponteiro para a célula sentinela de cauda (última sentinela vazia)
    Celula* cauda;
    
    // Variável que armazena a quantidade de elementos na lista
    int tam;
};

// ============================================================================
// FUNÇÃO: ListaCria()
// Propósito: Criar e inicializar uma lista vazia
// Retorno: Ponteiro para a nova lista criada
// ============================================================================
Lista* ListaCria() {
    // Aloca memória para a estrutura Lista no heap
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    
    // Aloca memória para a célula sentinela de cabeça
    lista->cabeca = (Celula*) malloc(sizeof(Celula));
    
    // Aloca memória para a célula sentinela de cauda
    lista->cauda = (Celula*) malloc(sizeof(Celula));
    
    // Conecta a cabeça apontando para a cauda (pois lista está vazia)
    lista->cabeca->prox = lista->cauda;
    
    // A cabeça não tem antecessor (é o início)
    lista->cabeca->ant = NULL;
    
    // A cauda não tem sucessor (é o final)
    lista->cauda->prox = NULL;
    
    // Conecta a cauda apontando para a cabeça (volta circular)
    lista->cauda->ant = lista->cabeca;
    
    // Inicializa o tamanho da lista como 0 (vazia)
    lista->tam = 0;
    
    // Retorna o ponteiro para a lista criada
    return lista;
}

// ============================================================================
// FUNÇÃO: ListaDestroi()
// Propósito: Liberar toda memória alocada pela lista
// Parâmetro: pLista - ponteiro para a lista a ser destruída
// Retorno: NULL (lista agora não existe mais)
// ============================================================================
Lista* ListaDestroi(Lista* pLista) {
    // Variável auxiliar para armazenar itens temporariamente
    Item aux;
    
    // Enquanto conseguir remover elementos do final da lista
    // A função retorna true enquanto houver elementos
    while (ListaRetiraFinal(pLista, &aux));
    
    // Libera memória alocada da célula sentinela de cabeça
    free(pLista->cabeca);
    
    // Libera memória alocada da célula sentinela de cauda
    free(pLista->cauda);
    
    // Libera memória alocada da estrutura lista em si
    free(pLista);
    
    // Retorna NULL para indicar que a lista foi destruída
    return NULL;
}

// ============================================================================
// FUNÇÃO: ListaEhVazia()
// Propósito: Verificar se a lista está vazia
// Parâmetro: pLista - ponteiro para a lista
// Retorno: true se vazia, false se contém elementos
// ============================================================================
bool ListaEhVazia(Lista* pLista) {
    // Compara o tamanho com 0 e retorna true ou false
    return pLista->tam == 0;
}

// ============================================================================
// FUNÇÃO: ListaInsereFinal()
// Propósito: Inserir um elemento no final da lista
// Parâmetro: pLista - ponteiro para a lista, x - elemento a inserir
// Retorno: true se conseguiu inserir, false se falhou na alocação
// ============================================================================
bool ListaInsereFinal(Lista* pLista, Item x) {
    // Aloca memória para uma nova célula no heap
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    
    // Verifica se a alocação de memória foi bem-sucedida
    if (nova == NULL)
        // Se malloc falhou, retorna false (não conseguiu inserir)
        return false;
    
    // Copia o item x para dentro da nova célula
    nova->item = x;
    
    // === ATUALIZANDO OS PONTEIROS DA NOVA CÉLULA ===
    
    // A célula anterior da nova célula é a célula que estava antes da cauda
    // (que era a última célula com dados, ou a cabeça se lista vazia)
    nova->ant = pLista->cauda->ant;
    
    // A próxima célula da nova célula é sempre a cauda (sentinela final)
    nova->prox = pLista->cauda;
    
    // === ATUALIZANDO OS PONTEIROS DAS OUTRAS CÉLULAS ===
    
    // A célula que estava antes da cauda agora aponta para a nova célula
    nova->ant->prox = nova;
    
    // A cauda agora aponta para a nova célula como antecessora
    pLista->cauda->ant = nova;
    
    // Incrementa o tamanho da lista em 1
    pLista->tam++;
    
    // Retorna true indicando que a inserção foi bem-sucedida
    return true;
}

// ============================================================================
// FUNÇÃO: ListaInsereInicio()
// Propósito: Inserir um elemento no início da lista
// Parâmetro: pLista - ponteiro para a lista, x - elemento a inserir
// Retorno: true se conseguiu inserir, false se falhou na alocação
// ============================================================================
bool ListaInsereInicio(Lista* pLista, Item x) {
    // Aloca memória para uma nova célula no heap
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    
    // Verifica se a alocação de memória foi bem-sucedida
    if (nova == NULL)
        // Se malloc falhou, retorna false (não conseguiu inserir)
        return false;
    
    // Copia o item x para dentro da nova célula
    nova->item = x;
    
    // === ATUALIZANDO OS PONTEIROS DA NOVA CÉLULA ===
    
    // A célula anterior da nova célula é sempre a cabeça (sentinela inicial)
    nova->ant = pLista->cabeca;
    
    // A próxima célula da nova célula é o primeiro elemento atual (após cabeça)
    nova->prox = pLista->cabeca->prox;
    
    // === ATUALIZANDO OS PONTEIROS DAS OUTRAS CÉLULAS ===
    
    // A cabeça agora aponta para a nova célula como próxima
    pLista->cabeca->prox = nova;
    
    // A célula que era a primeira agora aponta para a nova célula como anterior
    nova->prox->ant = nova;
    
    // Incrementa o tamanho da lista em 1
    pLista->tam++;
    
    // Retorna true indicando que a inserção foi bem-sucedida
    return true;
}

// ============================================================================
// FUNÇÃO: ListaRetiraFinal()
// Propósito: Remover e retornar o último elemento da lista
// Parâmetro: pLista - ponteiro para a lista, pX - ponteiro para armazenar item
// Retorno: true se conseguiu remover, false se lista estava vazia
// ============================================================================
bool ListaRetiraFinal(Lista* pLista, Item *pX) {
    // Verifica se a lista está vazia
    if (ListaEhVazia(pLista))
        // Se está vazia, retorna false (não há o que remover)
        return false;
    
    // Ponteiro auxiliar que aponta para a última célula com dados
    // (célula anterior à sentinela cauda)
    Celula* aux = pLista->cauda->ant;
    
    // A célula anterior ao último (penúltima) agora aponta diretamente para cauda
    aux->ant->prox = pLista->cauda;
    
    // A cauda agora aponta para a célula anterior ao último como sua anterior
    pLista->cauda->ant = aux->ant;
    
    // Copia o item da célula a ser removida para pX
    *pX = aux->item;
    
    // Libera a memória alocada da célula removida
    free(aux);
    
    // Decrementa o tamanho da lista em 1
    pLista->tam--;
    
    // Retorna true indicando que a remoção foi bem-sucedida
    return true;
}

// ============================================================================
// FUNÇÃO: ListaImprime()
// Propósito: Exibir todos os elementos da lista na ordem (início → fim)
// Parâmetro: pLista - ponteiro para a lista
// Retorno: void (não retorna nada)
// ============================================================================
void ListaImprime(Lista* pLista) {
    // Imprime o rótulo "Lista (" no início
    printf("Lista (");
    
    // Inicializa o ponteiro auxiliar apontando para a primeira célula com dados
    // (primeira célula após a sentinela cabeça)
    Celula* aux = pLista->cabeca->prox;
    
    // Loop que percorre todas as células da lista (pelo tamanho)
    for (int i=0; i<pLista->tam; i++) {
        // Imprime a chave (campo numérico) e o nome (campo texto) do item
        printf("[%d|%s] ", aux->item.chave, aux->item.nome);
        
        // Avança o ponteiro para a próxima célula
        aux = aux->prox;
    }
    
    // Imprime o fechamento do parêntese e quebra de linha
    printf(")\n");
}

// ============================================================================
// FUNÇÃO: ListaImprimeInverso()
// Propósito: Exibir todos os elementos da lista na ordem inversa (fim → início)
// Parâmetro: pLista - ponteiro para a lista
// Retorno: void (não retorna nada)
// ============================================================================
void ListaImprimeInverso(Lista* pLista) {
    // Imprime o rótulo "Lista Inverso (" no início
    printf("Lista Inverso (");
    
    // Inicializa o ponteiro auxiliar apontando para a última célula com dados
    // (célula anterior à sentinela cauda)
    Celula* aux = pLista->cauda->ant;
    
    // Loop que percorre todas as células da lista de trás para frente
    for (int i=0; i<pLista->tam; i++) {
        // Imprime a chave (campo numérico) e o nome (campo texto) do item
        printf("[%d|%s] ", aux->item.chave, aux->item.nome);
        
        // Retrocede o ponteiro para a célula anterior
        aux = aux->ant;
    }
    
    // Imprime o fechamento do parêntese e quebra de linha
    printf(")\n");
}

// ============================================================================
// FUNÇÃO: ListaGet()
// Propósito: Recuperar um elemento em uma posição específica
// Parâmetro: pLista - ponteiro para a lista, pos - posição desejada (0-indexado)
//            pX - ponteiro para armazenar o item recuperado
// Retorno: true se conseguiu recuperar, false se posição inválida
// ============================================================================
bool ListaGet(Lista* pLista, int pos, Item *pX) {
    // Verifica se a posição é válida (não negativa e dentro do tamanho)
    if (pos < 0 || pos >= pLista->tam)
        // Se posição inválida, retorna false
        return false;
    
    // Inicializa o ponteiro auxiliar apontando para o primeiro elemento
    // (primeira célula após a sentinela cabeça)
    Celula* aux = pLista->cabeca->prox;
    
    // Loop que avança o ponteiro até a posição desejada
    for (int i=0; i<pos; i++)
        // Move para a próxima célula
        aux = aux->prox;
    
    // Copia o item da célula encontrada para pX
    *pX = aux->item;
    
    // Retorna true indicando que a busca foi bem-sucedida
    return true;
}

// ============================================================================
// FUNÇÃO: ListaTamanho()
// Propósito: Obter a quantidade de elementos na lista
// Parâmetro: pLista - ponteiro para a lista
// Retorno: Número inteiro representando o tamanho da lista
// ============================================================================
int ListaTamanho(Lista* pLista) {
    // Retorna o campo tam que armazena a quantidade de elementos
    return pLista->tam;
}
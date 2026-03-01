#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Define a estrutura de uma célula (nó) da fila encadeada
 * Cada célula armazena um item e um ponteiro para a próxima célula
 */
typedef struct celula {
    Item item;              // Armazena o dado/valor da fila
    struct celula *prox;    // Ponteiro para a próxima célula
} Celula;

/**
 * Define a estrutura principal da fila
 * Utiliza dois ponteiros para eficiência: um no início e outro no fim
 */
struct fila {
    Celula *prim;   // Aponta para a célula sentinela (marca o início da fila)
    Celula *ult;    // Aponta para a última célula (facilita inserção no final)
    int n;          // Contador de elementos válidos na fila
};

/**
 * FilaCria - Cria uma nova fila vazia
 * 
 * Parâmetros:
 *   tam - Tamanho máximo (não utilizado nesta implementação dinâmica)
 * 
 * Retorna:
 *   Ponteiro para a fila alocada ou NULL em caso de erro
 * 
 * A fila começa com uma célula sentinela (vazia) que serve como marcador
 */
Fila* FilaCria(int tam) {
    // Aloca memória para a estrutura da fila
    Fila *fila = (Fila*) malloc(sizeof(Fila));
    
    if (fila) {
        // Aloca a célula sentinela (célula vazia no início)
        fila->prim = (Celula*) malloc(sizeof(Celula));
        
        if (!fila->prim) {
            // Se a alocação da sentinela falhar, libera a fila e retorna NULL
            free(fila);
            return NULL;
        }
        
        // Inicializa a sentinela como vazia (sem próximo)
        fila->prim->prox = NULL;
        
        // O último elemento aponta para a sentinela (fila vazia)
        fila->ult = fila->prim;
        
        // Inicializa o contador de elementos como zero
        fila->n = 0;
    }
    
    return fila;
}

/**
 * FilaDestroi - Libera toda a memória ocupada pela fila
 * 
 * Parâmetros:
 *   pFila - Ponteiro para a fila a ser destruída
 * 
 * Retorna:
 *   NULL (para permitir: fila = FilaDestroi(fila))
 * 
 * Remove todos os elementos antes de liberar a fila
 */
Fila* FilaDestroi(Fila *pFila) {
    if (pFila) {
        Item item;
        
        // Remove todos os elementos um por um
        // A função FilaDesenfileirar retorna false quando a fila fica vazia
        while (FilaDesenfileirar(pFila, &item));
        
        // Libera a célula sentinela
        free(pFila->prim);
        
        // Libera a estrutura da fila
        free(pFila);
    }
    
    // Retorna NULL para segurança (evita uso de ponteiro solto)
    return NULL;
}

/**
 * FilaTamanho - Retorna a quantidade de elementos na fila
 * 
 * Parâmetros:
 *   pFila - Ponteiro para a fila
 * 
 * Retorna:
 *   Número de elementos ou -1 se a fila é nula
 */
int FilaTamanho(Fila *pFila) {
    if (pFila)
        return pFila->n;  // Retorna o contador mantido durante enfileiramentos
    
    return -1;  // Erro: fila nula
}

/**
 * FilaEhVazia - Verifica se a fila está vazia
 * 
 * Parâmetros:
 *   pFila - Ponteiro para a fila
 * 
 * Retorna:
 *   true se a fila está vazia, false caso contrário
 */
bool FilaEhVazia(Fila *pFila) {
    if (pFila)
        return FilaTamanho(pFila) == 0;  // Fila vazia se contador é zero
    
    return false;  // Fila nula não é vazia (retorna false para segurança)
}

/**
 * FilaEnfileirar - Adiciona um elemento no final da fila
 * 
 * Parâmetros:
 *   pFila - Ponteiro para a fila
 *   item  - Elemento a ser adicionado
 * 
 * Retorna:
 *   true se inserção foi bem-sucedida, false caso contrário
 * 
 * Operação típica de FIFO: insere sempre no final
 */
bool FilaEnfileirar(Fila *pFila, Item item) {
    // Valida se a fila existe
    if (!pFila)
        return false;
    
    // Aloca memória para uma nova célula
    Celula *nova = (Celula*) malloc(sizeof(Celula));
    
    if (!nova)
        return false;  // Erro na alocação
    
    // Armazena o item na nova célula
    nova->item = item;
    
    // A nova célula será a última, então não tem próxima
    nova->prox = NULL;
    
    // Conecta a última célula à nova (encadeia)
    pFila->ult->prox = nova;
    
    // Atualiza o ponteiro de última célula para a nova
    pFila->ult = nova;
    
    // Incrementa o contador de elementos
    pFila->n++;
    
    return true;  // Sucesso
}

/**
 * FilaDesenfileirar - Remove e retorna o primeiro elemento da fila
 * 
 * Parâmetros:
 *   pFila - Ponteiro para a fila
 *   pItem - Ponteiro para armazenar o elemento removido
 * 
 * Retorna:
 *   true se remoção foi bem-sucedida, false caso contrário
 * 
 * Operação típica de FIFO: remove sempre do início
 */
bool FilaDesenfileirar(Fila *pFila, Item *pItem) {
    // Valida se a fila existe
    if (!pFila)
        return false;
    
    // Verifica se a fila está vazia
    if (FilaEhVazia(pFila))
        return false;
    
    // Obtém o primeiro elemento real (após a sentinela)
    // pFila->prim aponta para a sentinela
    // pFila->prim->prox aponta para o primeiro elemento válido
    Celula *aux = pFila->prim->prox;
    
    // Faz a sentinela apontar para o segundo elemento (pula o primeiro)
    pFila->prim->prox = aux->prox;
    
    // Se a fila ficou vazia após remoção, atualiza o último
    // para apontar novamente para a sentinela
    if(pFila->prim->prox == NULL)
        pFila->ult = pFila->prim;
    
    // Copia o item para o ponteiro fornecido
    *pItem = aux->item;
    
    // Libera a memória da célula removida
    free(aux);
    
    // Decrementa o contador de elementos
    pFila->n--;
    
    return true;  // Sucesso
}

/**
 * FilaPrint - Imprime todos os elementos da fila
 * 
 * Parâmetros:
 *   pFila - Ponteiro para a fila
 * 
 * Formato de saída: [elemento1 elemento2 elemento3...]
 * 
 * Nota: Usa a função ItemPrint definida em outro arquivo
 */
void FilaPrint(Fila *pFila) {
    // Imprime o abre colchete
    printf("[");
    
    // Inicia no primeiro elemento real (após a sentinela)
    Celula *aux = pFila->prim->prox;
    
    // Percorre todas as células da fila
    while(aux) {
        // Imprime o item atual usando a função ItemPrint
        ItemPrint(aux->item);
        
        // Avança para a próxima célula
        aux = aux->prox;
    }
    
    // Imprime o fecha colchete e quebra de linha
    printf("]\n");
}

/**
 * FilaPrimeiro - Obtém o primeiro elemento sem removê-lo
 * 
 * Parâmetros:
 *   pFila - Ponteiro para a fila
 *   pItem - Ponteiro para armazenar o primeiro elemento
 * 
 * Retorna:
 *   true se operação bem-sucedida, false caso contrário
 * 
 * Diferença de FilaDesenfileirar: apenas copia, não remove
 */
bool FilaPrimeiro(Fila *pFila, Item *pItem) {
    // Valida se a fila existe
    if (!pFila)
        return false;
    
    // Verifica se a fila está vazia
    if (FilaEhVazia(pFila))
        return false;
    
    // Copia o item do primeiro elemento (sem removê-lo)
    // pFila->prim->prox é o primeiro elemento válido
    *pItem = pFila->prim->prox->item;
    
    return true;  // Sucesso
}
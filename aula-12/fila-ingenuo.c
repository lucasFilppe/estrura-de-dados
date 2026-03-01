#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * ESTRUTURA DE DADOS - FILA COM ARRAY
 * 
 * Uma fila é uma estrutura que segue o princípio FIFO (First In, First Out)
 * ou seja, o primeiro elemento que entra é o primeiro a sair.
 * 
 * Analogia: Uma fila de banco - quem chega primeiro, é atendido primeiro!
 */

struct fila {
    Item *itens;        // Ponteiro para o array dinâmico que armazena os dados
    int maxTam;         // Capacidade máxima (tamanho total do array)
    int ini;            // Índice do primeiro elemento válido da fila
    int n;              // Número de elementos atualmente na fila
};

/**
 * FUNÇÃO: FilaCria
 * 
 * Propósito: Criar e inicializar uma nova fila vazia
 * 
 * Parâmetros:
 *   tam - O tamanho máximo que a fila pode ter
 * 
 * Retorno:
 *   Ponteiro para a fila criada, ou NULL se falhar na alocação
 * 
 * Explicação detalhada:
 *   1. Aloca memória para a estrutura Fila
 *   2. Inicializa todos os campos
 *   3. Aloca memória para o array de itens
 *   4. Se algo falhar, libera o que foi alocado (evita vazamento de memória)
 */
Fila* FilaCria(int tam) {
    // Aloca memória para a estrutura da fila
    Fila *fila = (Fila*) malloc(sizeof(Fila));
    
    // Verifica se a alocação da estrutura foi bem-sucedida
    if (fila) {
        // Define a capacidade máxima da fila
        fila->maxTam = tam;
        
        // Inicialmente, a fila tem 0 elementos
        fila->n = 0;
        
        // O primeiro elemento estará no índice 0 (posição inicial)
        fila->ini = 0;
        
        // Aloca memória para armazenar 'tam' itens
        fila->itens = (Item*) malloc(sizeof(Item) * tam);
        
        // Verifica se a alocação do array foi bem-sucedida
        if (!fila->itens) {
            // Se não conseguiu alocar o array, libera a estrutura
            free(fila);
            // Define como NULL para indicar que falhou
            fila = NULL;
        }
    }
    
    return fila;
}

/**
 * FUNÇÃO: FilaDestroi
 * 
 * Propósito: Destruir uma fila e liberar toda a memória alocada
 * 
 * Parâmetros:
 *   pFila - Ponteiro para a fila a ser destruída
 * 
 * Retorno:
 *   Sempre retorna NULL (para ajudar o programador a evitar dangling pointer)
 * 
 * Explicação:
 *   1. Libera o array de itens
 *   2. Libera a estrutura da fila
 *   3. Retorna NULL como sinal de "limpeza realizada"
 */
Fila* FilaDestroi(Fila *pFila) {
    // Verifica se a fila existe (não é NULL)
    if (pFila) {
        // Libera a memória do array de itens
        free(pFila->itens);
        
        // Libera a memória da estrutura em si
        free(pFila);
    }
    
    // Retorna NULL para que o programador possa fazer: fila = FilaDestroi(fila);
    return NULL;
}

/**
 * FUNÇÃO: FilaTamanho
 * 
 * Propósito: Retornar quantos elementos estão na fila no momento
 * 
 * Parâmetros:
 *   pFila - Ponteiro para a fila
 * 
 * Retorno:
 *   O número de elementos na fila, ou -1 se a fila for NULL
 */
int FilaTamanho(Fila *pFila) {
    // Verifica se a fila é válida
    if (pFila)
        // Retorna o campo 'n' que armazena o número de elementos
        return pFila->n;
    
    // Retorna -1 para indicar erro
    return -1;
}

/**
 * FUNÇÃO: FilaEhVazia
 * 
 * Propósito: Verificar se a fila está vazia
 * 
 * Parâmetros:
 *   pFila - Ponteiro para a fila
 * 
 * Retorno:
 *   true se a fila está vazia (n == 0)
 *   false caso contrário ou se a fila for NULL
 */
bool FilaEhVazia(Fila *pFila) {
    // Valida a fila
    if (pFila)
        // Uma fila vazia tem n elementos iguais a 0
        return FilaTamanho(pFila) == 0;
    
    // Se for NULL, retorna false
    return false;
}

/**
 * FUNÇÃO: FilaEnfileirar
 * 
 * Propósito: Adicionar um elemento no final da fila (enfileirar)
 * 
 * Parâmetros:
 *   pFila - Ponteiro para a fila
 *   item  - O item a ser adicionado
 * 
 * Retorno:
 *   true se conseguiu adicionar
 *   false se falhar (fila NULL ou fila cheia)
 * 
 * Explicação visual:
 *   Antes: [A][B][C][_][_][_]  (ini=0, n=3)
 *                  ↑
 *                 fim
 *   
 *   Depois de enfileirar(D):
 *          [A][B][C][D][_][_]  (ini=0, n=4)
 *                     ↑
 *                    fim
 */
bool FilaEnfileirar(Fila *pFila, Item item) {
    // Valida se a fila existe
    if (!pFila)
        return false;
    
    // Verifica se há espaço disponível na fila
    // Explicação: ini + n = posição que seria o fim
    // Se isso for igual a maxTam, significa que o próximo espaço seria fora do array
    if (pFila->ini + pFila->n == pFila->maxTam)
        return false;  // Fila cheio! Não é possível adicionar mais
    
    // Calcula onde o novo elemento será inserido
    // ini = onde começa a fila
    // n = quantos elementos já existem
    // fim = posição vazia onde irá o novo elemento
    int fim = pFila->ini + pFila->n;
    
    // Coloca o item na posição calculada
    pFila->itens[fim] = item;
    
    // Incrementa o contador de elementos
    pFila->n++;
    
    // Retorna true indicando sucesso
    return true;
}

/**
 * FUNÇÃO: FilaDesenfileirar
 * 
 * Propósito: Remover e retornar o primeiro elemento da fila
 * 
 * Parâmetros:
 *   pFila  - Ponteiro para a fila
 *   pItem  - Ponteiro para onde o item removido será copiado
 * 
 * Retorno:
 *   true se conseguiu remover
 *   false se falhar (fila NULL ou fila vazia)
 * 
 * Explicação visual:
 *   Antes: [A][B][C][D][_][_]  (ini=0, n=4)
 *           ↑
 *         ini
 *   
 *   Depois de desenfileirar():  // Remove A
 *          [A][B][C][D][_][_]  (ini=1, n=3)
 *              ↑
 *            ini
 *   
 *   OBSERVAÇÃO IMPORTANTE: O array não é "compactado"!
 *   O elemento A continua no array, mas ini foi incrementado.
 *   Isso economiza tempo, mas pode desperdiçar espaço.
 */
bool FilaDesenfileirar(Fila *pFila, Item *pItem) {
    // Valida se a fila existe
    if (!pFila)
        return false;
    
    // Verifica se há elementos para remover
    if (FilaEhVazia(pFila))
        return false;
    
    // Copia o primeiro elemento (que está em pFila->itens[pFila->ini])
    // para o local apontado por pItem
    *pItem = pFila->itens[pFila->ini];
    
    // Move o início da fila para o próximo elemento
    // Isso "remove" o primeiro elemento sem precisar copiar os demais
    pFila->ini = pFila->ini + 1;
    
    // Decrementa o contador de elementos
    pFila->n--;
    
    // Retorna true indicando sucesso
    return true;
}

/**
 * FUNÇÃO: FilaPrint
 * 
 * Propósito: Exibir todos os elementos da fila na tela
 * 
 * Parâmetros:
 *   pFila - Ponteiro para a fila
 * 
 * Retorno:
 *   Nenhum (void) - apenas imprime na tela
 * 
 * Explicação:
 *   Imprime algo como: [A][B][C][D]
 *   Apenas os elementos atualmente na fila são impressos
 */
void FilaPrint(Fila *pFila) {
    // Imprime o colchete de abertura
    printf("[");
    
    // Calcula onde a fila termina
    // fim = ini + n = última posição válida + 1
    int fim = pFila->ini + pFila->n;
    
    // Loop que itera de ini até fim-1 (todas as posições da fila)
    for (int i = pFila->ini; i < fim; i++)
        // Imprime cada item (usa função ItemPrint definida em outro lugar)
        ItemPrint(pFila->itens[i]);
    
    // Imprime o colchete de fechamento e quebra de linha
    printf("]\n");
}

/**
 * FUNÇÃO: FilaPrimeiro
 * 
 * Propósito: Obter o primeiro elemento da fila SEM remover
 * 
 * Parâmetros:
 *   pFila  - Ponteiro para a fila
 *   pItem  - Ponteiro para onde o item será copiado
 * 
 * Retorno:
 *   true se conseguiu obter o primeiro elemento
 *   false se falhar (fila NULL ou fila vazia)
 * 
 * Diferença com FilaDesenfileirar:
 *   - Desenfileirar: REMOVE o elemento (muda ini e n)
 *   - FilaPrimeiro: apenas LÊ o elemento (não muda nada)
 * 
 * Exemplo:
 *   Fila: [A][B][C]
 *   FilaPrimeiro retorna A, e a fila continua [A][B][C]
 *   FilaDesenfileirar retorna A, e a fila fica [B][C]
 */
bool FilaPrimeiro(Fila *pFila, Item *pItem) {
    // Valida se a fila existe
    if (!pFila)
        return false;
    
    // Verifica se há elementos na fila
    if (FilaEhVazia(pFila))
        return false;
    
    // Copia o primeiro elemento para o endereço apontado por pItem
    // O primeiro elemento está em pFila->itens[pFila->ini]
    *pItem = pFila->itens[pFila->ini];
    
    // Retorna true indicando sucesso
    return true;
}
#include "fila.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * =====================================================
 * ESTRUTURA DE DADOS: FILA CIRCULAR
 * =====================================================
 * Uma fila circular é uma estrutura FIFO (Primeiro a Entrar, Primeiro a Sair)
 * que utiliza um arranjo de tamanho fixo de forma circular.
 * O final do arranjo conecta-se ao início, reutilizando espaço
 * sem necessidade de deslocar elementos.
 */

struct fila {
    Item *itens;    // Ponteiro para o arranjo dinâmico que armazena os itens
    int maxTam;     // Tamanho máximo da fila (capacidade total)
    int ini;        // Índice do primeiro elemento válido (início da fila)
    int n;          // Quantidade atual de elementos armazenados na fila
};

/*
 * =====================================================
 * FUNÇÃO: FilaCria(int tam)
 * =====================================================
 * Objetivo: Criar e inicializar uma nova fila circular
 * 
 * Parâmetro:
 *   - tam: tamanho máximo (capacidade) da fila
 * 
 * Retorno:
 *   - Ponteiro para a fila alocada na memória
 *   - NULO se falhar na alocação
 * 
 * Complexidade: O(1)
 */
Fila* FilaCria(int tam) {
    // Aloca memória para a estrutura Fila
    Fila *fila = (Fila*) malloc(sizeof(Fila));
    
    if (fila) {  // Verifica se a alocação foi bem-sucedida
        fila->maxTam = tam;        // Define a capacidade máxima
        fila->n = 0;               // Inicializa com 0 elementos (fila vazia)
        fila->ini = 0;             // Primeiro elemento será na posição 0
        
        // Aloca o arranjo dinâmico que armazenará os itens
        fila->itens = (Item*) malloc(sizeof(Item) * tam);
        
        if (!fila->itens) {        // Se falhar na alocação do arranjo
            free(fila);            // Libera a estrutura alocada anteriormente
            fila = NULL;           // Define como NULO para indicar erro
        }
    }
    return fila;                   // Retorna o ponteiro (ou NULO em caso de erro)
}

/*
 * =====================================================
 * FUNÇÃO: FilaDestroi(Fila *pFila)
 * =====================================================
 * Objetivo: Liberar toda a memória alocada pela fila
 * 
 * Parâmetro:
 *   - pFila: ponteiro para a fila a ser destruída
 * 
 * Retorno:
 *   - Sempre retorna NULO (para evitar ponteiro flutuante)
 * 
 * Complexidade: O(1)
 */
Fila* FilaDestroi(Fila *pFila) {
    if (pFila) {                // Se a fila existe
        free(pFila->itens);     // Libera o arranjo de itens (alocado primeiro)
        free(pFila);            // Libera a estrutura da fila (alocada por último)
    }
    return NULL;                // Retorna NULO para indicar que foi destruída
}

/*
 * =====================================================
 * FUNÇÃO: FilaTamanho(Fila *pFila)
 * =====================================================
 * Objetivo: Obter a quantidade atual de elementos na fila
 * 
 * Parâmetro:
 *   - pFila: ponteiro para a fila
 * 
 * Retorno:
 *   - Número de elementos na fila
 *   - -1 se a fila é NULA (indica erro)
 * 
 * Complexidade: O(1)
 */
int FilaTamanho(Fila *pFila) {
    if (pFila)                  // Se a fila existe
        return pFila->n;        // Retorna a quantidade de elementos
    return -1;                  // Retorna -1 indicando erro
}

/*
 * =====================================================
 * FUNÇÃO: FilaEhVazia(Fila *pFila)
 * =====================================================
 * Objetivo: Verificar se a fila está vazia
 * 
 * Parâmetro:
 *   - pFila: ponteiro para a fila
 * 
 * Retorno:
 *   - verdadeiro se a fila está vazia (n == 0)
 *   - falso caso contrário ou se pFila é NULO
 * 
 * Complexidade: O(1)
 */
bool FilaEhVazia(Fila *pFila) {
    if (pFila)                              // Se a fila existe
        return FilaTamanho(pFila) == 0;     // Verifica se o tamanho é 0
    return false;                           // Se NULO, retorna falso
}

/*
 * =====================================================
 * FUNÇÃO: FilaEnfileirar(Fila *pFila, Item item)
 * =====================================================
 * Objetivo: Adicionar um elemento no final da fila
 * 
 * Parâmetro:
 *   - pFila: ponteiro para a fila
 *   - item: o item a ser adicionado
 * 
 * Retorno:
 *   - verdadeiro se conseguiu adicionar
 *   - falso se não conseguiu (fila NULA ou cheia)
 * 
 * Complexidade: O(1)
 * 
 * FUNCIONAMENTO DETALHADO:
 * A fórmula crítica é: fim = (ini + n) % maxTam
 * 
 * Exemplo com maxTam=5:
 *   - ini=0, n=3 → fim = (0+3) % 5 = 3
 *   - ini=2, n=3 → fim = (2+3) % 5 = 5 % 5 = 0 (volta ao início!)
 * 
 * O operador % (módulo) faz a "mágica" circular!
 */
bool FilaEnfileirar(Fila *pFila, Item item) {
    if (!pFila)                            // Se fila é NULA, retorna erro
        return false;
    
    // Verifica se a fila está cheia (quantidade = capacidade máxima)
    if (FilaTamanho(pFila) == pFila->maxTam)
        return false;                      // Não consegue adicionar, fila cheia
    
    // ⭐ CÁLCULO DA POSIÇÃO DO NOVO ELEMENTO
    // (ini + n) calcula onde será o próximo elemento
    // % maxTam faz voltar ao início quando atinge o final (comportamento circular)
    int fim = (pFila->ini + pFila->n) % pFila->maxTam;
    
    pFila->itens[fim] = item;              // Adiciona o item na posição calculada
    pFila->n++;                            // Incrementa o contador de elementos
    return true;                           // Sucesso!
}

/*
 * =====================================================
 * FUNÇÃO: FilaDesenfileirar(Fila *pFila, Item *pItem)
 * =====================================================
 * Objetivo: Remover e retornar o primeiro elemento da fila
 * 
 * Parâmetro:
 *   - pFila: ponteiro para a fila
 *   - pItem: ponteiro para armazenar o item removido
 * 
 * Retorno:
 *   - verdadeiro se conseguiu remover
 *   - falso se não conseguiu (fila NULA ou vazia)
 * 
 * Complexidade: O(1)
 * 
 * FUNCIONAMENTO DETALHADO:
 * 1. Recupera o elemento no índice 'ini'
 * 2. Avança 'ini' para o próximo elemento
 * 3. Decrementa 'n'
 * 
 * A fórmula ini = (ini + 1) % maxTam também usa módulo
 * para voltar ao início quando atinge o final!
 */
bool FilaDesenfileirar(Fila *pFila, Item *pItem) {
    if (!pFila)                           // Se fila é NULA, retorna erro
        return false;
    
    if (FilaEhVazia(pFila))               // Se fila está vazia, não há o que remover
        return false;
    
    // ⭐ RECUPERA O PRIMEIRO ELEMENTO
    *pItem = pFila->itens[pFila->ini];
    
    // ⭐ AVANÇA O ÍNDICE DE INÍCIO (com comportamento circular)
    // Quando ini atinge maxTam, o módulo o traz de volta para 0
    pFila->ini = (pFila->ini + 1) % pFila->maxTam;
    
    pFila->n--;                           // Decrementa a quantidade de elementos
    return true;                          // Sucesso!
}

/*
 * =====================================================
 * FUNÇÃO: FilaPrint(Fila *pFila)
 * =====================================================
 * Objetivo: Exibir todos os elementos da fila na tela
 * 
 * Parâmetro:
 *   - pFila: ponteiro para a fila a ser exibida
 * 
 * Retorno: nenhum (tipo vazio)
 * 
 * Complexidade: O(n) onde n é a quantidade de elementos
 * 
 * FUNCIONAMENTO DETALHADO:
 * 1. Calcula 'fim' = posição após o último elemento (virtualmente)
 * 2. Itera de 'ini' até 'fim-1'
 * 3. Usa módulo para circular quando i >= maxTam
 * 
 * Exemplo com ini=3, n=2, maxTam=5:
 *   - fim = 3 + 2 = 5
 *   - Laço: i=3 (itens[3]), i=4 (itens[4])
 *   - Se houvesse i=5, seria itens[5%5] = itens[0] (volta ao início)
 */
void FilaPrint(Fila *pFila) {
    printf("[");                          // Abre a representação visual
    
    // Calcula a posição virtual após o último elemento
    int fim = pFila->ini + pFila->n;
    
    // Laço que percorre todos os elementos da fila
    // Começa em 'ini' e vai até 'fim-1'
    for (int i = pFila->ini; i < fim; i++) {
        // ⭐ O MÓDULO FAZ A "MÁGICA" CIRCULAR
        // Se i >= maxTam, o módulo traz de volta para o início do arranjo
        ItemPrint(pFila->itens[i % pFila->maxTam]);
    }
    
    printf("]\n");                        // Fecha a representação visual
}

/*
 * =====================================================
 * FUNÇÃO: FilaPrimeiro(Fila *pFila, Item *pItem)
 * =====================================================
 * Objetivo: Consultar o primeiro elemento SEM remover
 * 
 * Parâmetro:
 *   - pFila: ponteiro para a fila
 *   - pItem: ponteiro para armazenar o item consultado
 * 
 * Retorno:
 *   - verdadeiro se conseguiu consultar
 *   - falso se não conseguiu (fila NULA ou vazia)
 * 
 * Complexidade: O(1)
 * 
 * DIFERENÇA IMPORTANTE:
 * - FilaDesenfileirar: remove o elemento (muda 'ini' e 'n')
 * - FilaPrimeiro: apenas LÊ o elemento (não modifica nada)
 */
bool FilaPrimeiro(Fila *pFila, Item *pItem) {
    if (!pFila)                           // Se fila é NULA, retorna erro
        return false;
    
    if (FilaEhVazia(pFila))               // Se fila está vazia, não há primeiro
        return false;
    
    // ⭐ APENAS LÊ O ELEMENTO, NÃO REMOVE
    *pItem = pFila->itens[pFila->ini];
    return true;                          // Sucesso!
}

/*
 * =====================================================
 * RESUMO DE OPERAÇÕES - COMPLEXIDADE
 * =====================================================
 * FilaCria()          → O(1) - alocação
 * FilaDestroi()       → O(1) - liberação
 * FilaTamanho()       → O(1) - apenas retorna campo
 * FilaEhVazia()       → O(1) - compara com 0
 * FilaEnfileirar()    → O(1) - acesso direto ao arranjo
 * FilaDesenfileirar() → O(1) - acesso direto ao arranjo
 * FilaPrint()         → O(n) - precisa iterar todos elementos
 * FilaPrimeiro()      → O(1) - apenas lê um elemento
 * 
 * =====================================================
 * O SEGREDO DA FILA CIRCULAR: O OPERADOR MÓDULO (%)
 * =====================================================
 * A circularidade é alcançada através de três fórmulas:
 * 
 * 1. Para adicionar: fim = (ini + n) % maxTam
 *    → Calcula a próxima posição, voltando a 0 quando atinge maxTam
 * 
 * 2. Para remover: ini = (ini + 1) % maxTam
 *    → Avança o índice inicial, voltando a 0 quando necessário
 * 
 * 3. Para imprimir: itens[i % maxTam] em um laço de ini até (ini+n)
 *    → Acessa elementos de forma circular
 * 
 * Exemplo prático com maxTam=5:
 * 
 *   Arranjo: [0][1][2][3][4]
 *                ↓ volta aqui quando atinge 5
 *   5 % 5 = 0
 *   6 % 5 = 1
 *   7 % 5 = 2
 *   8 % 5 = 3
 *   9 % 5 = 4
 *   10 % 5 = 0 (voltou ao início!)
 * 
 * Isso permite reutilizar espaço sem deslocar elementos! 🔄
 * 
 * =====================================================
 * EXEMPLO PRÁTICO DE USO
 * =====================================================
 * 
 * // Criar fila com capacidade para 5 elementos
 * Fila *minhaFila = FilaCria(5);
 * 
 * // Adicionar elementos (enfileirar)
 * FilaEnfileirar(minhaFila, 10);  // Adiciona 10
 * FilaEnfileirar(minhaFila, 20);  // Adiciona 20
 * FilaEnfileirar(minhaFila, 30);  // Adiciona 30
 * 
 * // Verificar primeiro elemento sem remover
 * Item primeiro;
 * FilaPrimeiro(minhaFila, &primeiro);  // primeiro = 10
 * 
 * // Remover e obter primeiro elemento
 * Item removido;
 * FilaDesenfileirar(minhaFila, &removido);  // removido = 10
 * 
 * // Mostrar conteúdo da fila
 * FilaPrint(minhaFila);  // Exibe [20][30]
 * 
 * // Verificar se está vazia
 * if (FilaEhVazia(minhaFila))
 *     printf("Fila vazia!\n");
 * else
 *     printf("Tamanho da fila: %d\n", FilaTamanho(minhaFila));
 * 
 * // Liberar memória
 * minhaFila = FilaDestroi(minhaFila);  // minhaFila agora é NULO
 */
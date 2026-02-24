#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * ============================================================================
 * ESTRUTURA DE DADOS: PILHA COM PONTEIROS (Lista Ligada)
 * ============================================================================
 * Implementação de uma pilha (STACK) usando lista ligada simples.
 * Princípio LIFO: Last In, First Out (Último a Entrar, Primeiro a Sair)
 * 
 * Vantagens:
 *   - Não tem limite de tamanho (crescimento dinâmico)
 *   - Operações eficientes O(1)
 *   - Usa memória sob demanda
 * ============================================================================
 */

/**
 * TYPEDEF: Definição da célula (nó da lista ligada)
 * 
 * Cada célula representa um "elo" na corrente da pilha.
 * Contém:
 *   - item: os dados armazenados
 *   - prox: endereço da próxima célula (NULL se for a última)
 */
typedef struct celula {
    Item item;              // Armazena o dado (tipo definido em pilha.h)
    struct celula *prox;    // Ponteiro para a próxima célula na pilha
} Celula;

/**
 * ESTRUTURA: A pilha em si
 * 
 * Mantém as informações essenciais da pilha:
 *   - topo: aponta para o primeiro elemento (após o nó sentinela)
 *   - n: quantidade total de elementos na pilha
 */
struct pilha {
    Celula *topo;   // Ponteiro para o nó sentinela (controla o topo real)
    int n;          // Contador de elementos (tamanho da pilha)
};

/**
 * ============================================================================
 * FUNÇÃO: PilhaCria
 * ============================================================================
 * 
 * Propósito: Criar e inicializar uma nova pilha vazia
 * 
 * Parâmetros:
 *   - maxTam: tamanho máximo (ignorado nesta implementação dinâmica)
 * 
 * Retorno: 
 *   - Ponteiro para a nova pilha se sucesso
 *   - NULL se falha na alocação
 * 
 * Complexidade de Tempo: O(1) - constante
 * 
 * Fluxo:
 *   1. Valida se maxTam é positivo
 *   2. Aloca memória para a estrutura Pilha
 *   3. Cria um nó sentinela (nó especial vazio no topo)
 *   4. Inicializa contadores
 */
Pilha* PilhaCria(int maxTam){ // O(1)
    // Validação: tamanho deve ser positivo
    if (maxTam <= 0)
        return NULL;  // Retorna NULL indicando erro
    
    // ALOCAÇÃO DINÂMICA: reserva memória para uma estrutura Pilha
    // malloc() retorna um ponteiro void, então fazemos cast para (Pilha*)
    Pilha *pilha = (Pilha*) malloc(sizeof(Pilha));
    
    // Verifica se a alocação foi bem-sucedida
    if (pilha) {
        // Inicializa o contador de elementos
        pilha->n = 0;  // Pilha começa vazia
        
        // NÓCÃO SENTINELA: cria um nó "fantasma" no topo
        // Facilita operações porque sempre há um nó antes do primeiro elemento
        // Evita casos especiais (empty list, etc)
        pilha->topo = (Celula*) malloc(sizeof(Celula));
        
        // Verifica se a alocação do nó sentinela foi bem-sucedida
        if (!pilha->topo) {
            free(pilha);  // Se falhou, libera o que foi alocado
            return NULL;  // E retorna NULL indicando erro
        }
        
        // O nó sentinela não aponta para nada no início
        pilha->topo->prox = NULL;
    }
    
    return pilha;  // Retorna o ponteiro para a pilha criada
}

/**
 * ============================================================================
 * FUNÇÃO: PilhaDestroi
 * ============================================================================
 * 
 * Propósito: Liberar toda a memória alocada pela pilha
 * 
 * Parâmetros:
 *   - pPilha: ponteiro para a pilha a ser destruída
 * 
 * Retorno:
 *   - Sempre retorna NULL (para que quem chamou possa fazer p = PilhaDestroi(p))
 * 
 * Complexidade de Tempo: O(n) - proporcional ao número de elementos
 * 
 * Fluxo:
 *   1. Remove todos os elementos um por um usando Pop
 *   2. Libera o nó sentinela
 *   3. Libera a estrutura Pilha
 *   4. Retorna NULL
 */
Pilha* PilhaDestroi(Pilha *pPilha) { // O(n) - precisa remover todos os n elementos
    // Verifica se a pilha é válida
    if (pPilha) {
        Item item;  // Variável auxiliar para armazenar dados removidos
        
        // Remove TODOS os elementos um por um
        // Pop retorna false quando a pilha está vazia, encerrando o loop
        while(PilhaPop(pPilha, &item));
        
        // Libera a memória do nó sentinela
        free(pPilha->topo);
        
        // Libera a memória da estrutura Pilha em si
        free(pPilha);
    }
    
    // Retorna NULL (convenção: permite p = PilhaDestroi(p))
    return NULL;
}

/**
 * ============================================================================
 * FUNÇÃO: PilhaTamanho
 * ============================================================================
 * 
 * Propósito: Retornar a quantidade de elementos na pilha
 * 
 * Parâmetros:
 *   - pPilha: ponteiro para a pilha
 * 
 * Retorno:
 *   - Número de elementos se pilha é válida
 *   - -1 se pilha é NULL (erro)
 * 
 * Complexidade de Tempo: O(1) - acesso direto ao campo 'n'
 */
int PilhaTamanho(Pilha *pPilha) { // O(1) - constante
    // Se a pilha é válida, retorna o contador
    if (pPilha)
        return pPilha->n;
    
    // Se a pilha é NULL, retorna -1 indicando erro
    return -1;
}

/**
 * ============================================================================
 * FUNÇÃO: PilhaEhVazia
 * ============================================================================
 * 
 * Propósito: Verificar se a pilha está vazia
 * 
 * Parâmetros:
 *   - pPilha: ponteiro para a pilha
 * 
 * Retorno:
 *   - true se a pilha está vazia (n == 0)
 *   - false se contém elementos ou se pilha é NULL
 * 
 * Complexidade de Tempo: O(1) - constante
 */
bool PilhaEhVazia(Pilha *pPilha){ // O(1) - constante
    // Se a pilha é válida, verifica se n é 0
    if (pPilha)
        return pPilha->n == 0;  // true se vazia, false se contém elementos
    
    // Se pilha é NULL, consideramos como "não vazia" (ou inválida)
    return false;
}

/**
 * ============================================================================
 * FUNÇÃO: PilhaPush
 * ============================================================================
 * 
 * Propósito: Inserir um novo elemento no topo da pilha
 * 
 * Parâmetros:
 *   - pPilha: ponteiro para a pilha
 *   - item: o dado a ser inserido
 * 
 * Retorno:
 *   - true se inserção bem-sucedida
 *   - false se falha na alocação ou pilha inválida
 * 
 * Complexidade de Tempo: O(1) - constante (aloca + 2 atribuições)
 * 
 * VISUALIZAÇÃO:
 * 
 * Antes: topo → [sentinela] → [D] → [C] → NULL
 * 
 * Depois de Push(E):
 *        topo → [sentinela] → [E] → [D] → [C] → NULL
 */
bool PilhaPush(Pilha *pPilha, Item item) { // O(1)
    // Valida se a pilha existe
    if (!pPilha)
        return false;  // Pilha inválida
    
    // ALOCAÇÃO: cria uma nova célula
    Celula *nova = (Celula*) malloc(sizeof(Celula));
    
    // Verifica se a alocação foi bem-sucedida
    if (!nova)
        return false;  // Falha na alocação de memória
    
    // Armazena o item na nova célula
    nova->item = item;
    
    /**
     * INSERÇÃO NO TOPO:
     * 
     * A nova célula deve apontar para quem era o primeiro elemento
     * (ou seja, para onde o sentinela estava apontando)
     */
    nova->prox = pPilha->topo->prox;
    
    /**
     * O sentinela agora deve apontar para a nova célula
     * Isso faz da nova célula o novo "primeiro" elemento
     */
    pPilha->topo->prox = nova;
    
    // Incrementa o contador de elementos
    pPilha->n++;
    
    return true;  // Sucesso!
}

/**
 * ============================================================================
 * FUNÇÃO: PilhaPop
 * ============================================================================
 * 
 * Propósito: Remover e retornar o elemento do topo da pilha
 * 
 * Parâmetros:
 *   - pPilha: ponteiro para a pilha
 *   - pItem: ponteiro para onde armazenar o item removido
 * 
 * Retorno:
 *   - true se remoção bem-sucedida
 *   - false se pilha vazia ou inválida
 * 
 * Complexidade de Tempo: O(1) - constante
 * 
 * VISUALIZAÇÃO:
 * 
 * Antes:  topo → [sentinela] → [E] → [D] → [C] → NULL
 * 
 * Depois de Pop(&item): item = E
 *         topo → [sentinela] → [D] → [C] → NULL
 *         [E] é liberado da memória
 */
bool PilhaPop(Pilha *pPilha, Item *pItem) { // O(1)
    // Valida se a pilha existe
    if (!pPilha)
        return false;
    
    // Valida se a pilha não está vazia
    if (PilhaEhVazia(pPilha))
        return false;  // Não há elementos para remover
    
    /**
     * OBTENÇÃO DO ELEMENTO DO TOPO:
     * 
     * O primeiro elemento real está em pPilha->topo->prox
     * (depois do nó sentinela)
     */
    Celula *aux = pPilha->topo->prox;
    
    /**
     * DESLIGAMENTO:
     * 
     * O sentinela agora aponta para o próximo elemento
     * (pulando o elemento que será removido)
     */
    pPilha->topo->prox = aux->prox;
    
    /**
     * CÓPIA DOS DADOS:
     * 
     * Copia o item da célula para o endereço fornecido
     * Usa dereferência de ponteiro (*pItem)
     */
    *pItem = aux->item;
    
    /**
     * LIBERAÇÃO DE MEMÓRIA:
     * 
     * Libera a célula que foi removida
     * Muito importante para evitar memory leak!
     */
    free(aux);
    
    // Decrementa o contador de elementos
    pPilha->n--;
    
    return true;  // Sucesso!
}

/**
 * ============================================================================
 * FUNÇÃO: PilhaPrint
 * ============================================================================
 * 
 * Propósito: Exibir todos os elementos da pilha na tela
 * 
 * Parâmetros:
 *   - pPilha: ponteiro para a pilha
 * 
 * Retorno: void (sem retorno)
 * 
 * Complexidade de Tempo: O(n) - precisa percorrer todos os n elementos
 * 
 * Nota: Chama ItemPrint() definida em outro módulo
 */
void PilhaPrint(Pilha *pPilha) { // O(n) - proporcional ao número de elementos
    // Valida se a pilha existe
    if (!pPilha)
        return;  // Se inválida, não faz nada
    
    // Imprime o símbolo de abertura
    printf("[");
    
    /**
     * PERCURSO:
     * 
     * Começa no primeiro elemento real (após o sentinela)
     * Vai apontando de célula em célula até chegar ao final (NULL)
     */
    Celula *aux = pPilha->topo->prox;
    
    // Itera por todas as células
    while (aux) {
        // Imprime o item usando a função ItemPrint
        ItemPrint(aux->item);
        
        // Avança para a próxima célula
        aux = aux->prox;
    }    
    
    // Imprime o símbolo de fechamento e quebra de linha
    printf("]\n");
}

/**
 * ============================================================================
 * FUNÇÃO: PilhaTopo
 * ============================================================================
 * 
 * Propósito: Consultar o elemento do topo SEM remover
 * 
 * Parâmetros:
 *   - pPilha: ponteiro para a pilha
 *   - pItem: ponteiro para onde armazenar o item consultado
 * 
 * Retorno:
 *   - true se leitura bem-sucedida
 *   - false se pilha vazia ou inválida
 * 
 * Complexidade de Tempo: O(1) - constante
 * 
 * DIFERENÇA COM pop:
 * - Pop: REMOVE o elemento (libera memória)
 * - Topo: apenas LÊ o elemento (não remove)
 * 
 * VISUALIZAÇÃO:
 * 
 * Antes:  topo → [sentinela] → [E] → [D] → [C] → NULL
 * 
 * Depois de Topo(&item): item = E
 *         topo → [sentinela] → [E] → [D] → [C] → NULL
 *         (nada foi removido!)
 */
bool PilhaTopo(Pilha *pPilha, Item *pItem) { // O(1)
    // Valida se a pilha existe
    if (!pPilha)
        return false;
    
    // Valida se a pilha não está vazia
    if (PilhaEhVazia(pPilha))
        return false;
    
    /**
     * LEITURA SIMPLES:
     * 
     * Copia apenas o item do topo para o endereço fornecido
     * NÃO remove a célula, apenas lê seu conteúdo
     * 
     * Alternativa mais direta (comentada):
     * Celula *aux = pPilha->topo->prox;
     * *pItem = aux->item;
     */
    *pItem = pPilha->topo->prox->item;
    
    return true;  // Sucesso!
}

/**
 * ============================================================================
 * RESUMO DAS OPERAÇÕES
 * ============================================================================
 * 
 * PilhaCria()    → Cria pilha vazia           [O(1)]
 * PilhaDestroi() → Libera toda a memória      [O(n)]
 * PilhaTamanho() → Retorna número elementos   [O(1)]
 * PilhaEhVazia() → Verifica se está vazia     [O(1)]
 * PilhaPush()    → Insere no topo             [O(1)]
 * PilhaPop()     → Remove do topo             [O(1)]
 * PilhaTopo()    → Lê o topo (sem remover)    [O(1)]
 * PilhaPrint()   → Exibe os elementos         [O(n)]
 * 
 * ============================================================================
 */
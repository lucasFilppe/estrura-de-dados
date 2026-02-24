#include "pilha.h"

#include <stdio.h>
#include <stdlib.h>

// ====== ESTRUTURA DA PILHA ======
// Define a estrutura que representa uma pilha
struct pilha {
    Item *itens;    // Ponteiro para array dinâmico que armazena os elementos
    int maxTam;     // Capacidade máxima da pilha (quantos elementos pode conter)
    int n;          // Número atual de elementos na pilha (controla o topo)
};  

// ====== FUNÇÃO: CRIAR PILHA ======
// Cria uma nova pilha com capacidade máxima especificada
// Parâmetro: maxTam = capacidade máxima da pilha
// Retorno: ponteiro para a pilha criada, ou NULL se falhar
// Complexidade: O(1) - tempo constante
Pilha* PilhaCria(int maxTam){
    // Validação: tamanho deve ser positivo
    if (maxTam <= 0)
        return NULL;
    
    // Aloca memória para a estrutura da pilha
    Pilha *pilha = (Pilha*) malloc(sizeof(Pilha));
    
    if (pilha) {
        // Inicializa os campos da estrutura
        pilha->n = 0;              // Começa vazia (n = 0)
        pilha->maxTam = maxTam;    // Define a capacidade máxima
        
        // Aloca um array dinâmico para armazenar os itens
        // Aloca espaço para "maxTam" elementos do tipo Item
        pilha->itens = (Item*) malloc(sizeof(Item) * maxTam);
        
        // Se falhar na alocação do array, libera a estrutura e retorna NULL
        if (!pilha->itens) {
            free(pilha);           // Libera a memória da estrutura
            pilha = NULL;          // Define como NULL
        }
    }
    return pilha;
}

// ====== FUNÇÃO: DESTRUIR PILHA ======
// Libera toda a memória alocada para a pilha
// Parâmetro: pPilha = ponteiro para a pilha a ser destruída
// Retorno: sempre retorna NULL (para evitar ponteiros soltos)
// Complexidade: O(1) - tempo constante
Pilha* PilhaDestroi(Pilha *pPilha) {
    if (pPilha) {
        // Primeiro libera o array de itens
        free(pPilha->itens);
        
        // Depois libera a estrutura da pilha
        free(pPilha);
    }
    // Retorna NULL para indicar que a pilha foi destruída
    return NULL;
}

// ====== FUNÇÃO: OBTER TAMANHO ======
// Retorna o número atual de elementos na pilha
// Parâmetro: pPilha = ponteiro para a pilha
// Retorno: número de elementos, ou -1 se pilha for NULL
// Complexidade: O(1) - tempo constante (apenas lê uma variável)
int PilhaTamanho(Pilha *pPilha) {
    if (pPilha)
        return pPilha->n;  // Retorna a quantidade de elementos
    return -1;             // Erro: pilha não existe
}

// ====== FUNÇÃO: VERIFICAR SE ESTÁ VAZIA ======
// Verifica se a pilha contém algum elemento
// Parâmetro: pPilha = ponteiro para a pilha
// Retorno: true se vazia, false se tem elementos
// Complexidade: O(1) - tempo constante
bool PilhaEhVazia(Pilha *pPilha) {
    if (pPilha)
        // Pilha vazia quando n == 0 (nenhum elemento)
        return pPilha->n == 0;
    return false;  // Se pilha é NULL, considera não vazia (por segurança)
}

// ====== FUNÇÃO: PUSH (EMPILHAR) ======
// Adiciona um novo elemento no topo da pilha
// Parâmetro: pPilha = pilha onde adicionar
//           item = elemento a ser adicionado
// Retorno: true se sucesso, false se falhar (pilha cheia ou nula)
// Complexidade: O(1) - tempo constante
bool PilhaPush(Pilha *pPilha, Item item) {
    // Valida se a pilha existe
    if (!pPilha)
        return false;
    
    // Verifica se há espaço disponível (n não pode ser igual a maxTam)
    if (pPilha->n == pPilha->maxTam) 
        return false;  // Pilha está cheia
    
    // Adiciona o item na posição n (topo)
    // Depois incrementa n com o operador post-incremento (n++)
    pPilha->itens[pPilha->n++] = item;
    
    return true;  // Sucesso
}

// ====== FUNÇÃO: POP (DESEMPILHAR) ======
// Remove o elemento do topo da pilha e o retorna
// Parâmetro: pPilha = pilha de onde remover
//           pItem = ponteiro para receber o elemento removido
// Retorno: true se sucesso, false se falhar (pilha vazia ou nula)
// Complexidade: O(1) - tempo constante
bool PilhaPop(Pilha *pPilha, Item *pItem) {
    // Valida se a pilha existe
    if (!pPilha)
        return false;
    
    // Verifica se a pilha está vazia
    if (PilhaEhVazia(pPilha))
        return false;
    
    // Decrementa n ANTES de usar (pre-decremento com --)
    // Isso faz n apontar para o último elemento válido
    // Copia o elemento removido para o ponteiro pItem
    *pItem = pPilha->itens[--pPilha->n];
    
    return true;  // Sucesso
}

// ====== FUNÇÃO: IMPRIMIR PILHA ======
// Exibe todos os elementos da pilha (do topo para o fundo)
// Parâmetro: pPilha = pilha a ser impressa
// Retorno: void (não retorna nada)
// Complexidade: O(n) - percorre todos os n elementos
void PilhaPrint(Pilha *pPilha) {
    // Valida se a pilha existe
    if (!pPilha)
        return;
    
    printf("[");  // Abre a exibição da pilha
    
    // Loop: começa do topo (n-1) e vai até o fundo (0)
    // Percorre de trás para frente para exibir visualmente do topo para o fundo
    for (int i = PilhaTamanho(pPilha) - 1; i >= 0; i--) {
        // Chama a função ItemPrint para exibir cada elemento
        ItemPrint(pPilha->itens[i]);
    }
    
    printf("]\n");  // Fecha a exibição
}

// ====== FUNÇÃO: OBTER TOPO ======
// Retorna o elemento no topo SEM remover da pilha
// (Diferente do Pop que remove o elemento)
// Parâmetro: pPilha = pilha de onde obter o topo
//           pItem = ponteiro para receber o elemento do topo
// Retorno: true se sucesso, false se falhar (pilha vazia ou nula)
// Complexidade: O(1) - tempo constante
bool PilhaTopo(Pilha *pPilha, Item *pItem) {
    // Valida se a pilha existe
    if (!pPilha)
        return false;
    
    // Verifica se a pilha está vazia
    if (PilhaEhVazia(pPilha))
        return false;
    
    // Copia o elemento do topo (posição n-1) para o ponteiro pItem
    // Não remove o elemento, apenas copia o valor
    *pItem = pPilha->itens[pPilha->n - 1];
    
    return true;  // Sucesso
}
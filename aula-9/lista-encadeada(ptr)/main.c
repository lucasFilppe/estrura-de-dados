#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h" // Inclui suas funções refatoradas

// Definindo o Item auxiliar para o print funcionar
void ItemPrint(Item i) {
    printf("(%s, ID:%d)", i.nome, i.id);
}

int main() {
    printf("=== INICIO DA BATERIA DE TESTES ===\n\n");

    // ---------------------------------------------------------
    // 1. TESTE: CRIAÇÃO E VERIFICAÇÃO DE VAZIA
    // ---------------------------------------------------------
    printf("[1] Criando Lista...\n");
    Lista *minhaLista = ListaCria(10); // O parâmetro 10 é ignorado na encadeada

    if (ListaEhVazia(minhaLista)) {
        printf(" -> Sucesso: A lista foi criada e esta VAZIA.\n");
    } else {
        printf(" -> Erro: A lista deveria estar vazia.\n");
    }

    
    
    // Preparando massa de dados
    Item i1 = {"Mario", 1};
    Item i2 = {"Luigi", 2};
    Item i3 = {"Yoshi", 3};
    Item i4 = {"Toad", 4};
    Item i5 = {"Bowser", 5};

    // ---------------------------------------------------------
    // 2. TESTE: INSERÇÕES (Inicio, Fim e Meio)
    // ---------------------------------------------------------
    printf("\n[2] Testando Insercoes...\n");
    
    // Inserir no INÍCIO
    ListaInsereInicio(minhaLista, i1); 
    printf(" -> Inseriu Inicio (Mario): ");
    ListaPrint(minhaLista); // Esperado: [Mario]

    
    // Inserir no FIM
    ListaInsereFim(minhaLista, i2);    
    printf(" -> Inseriu Fim (Luigi):    ");
    ListaPrint(minhaLista); // Esperado: [Mario, Luigi]

    // Inserir no INÍCIO de novo
    ListaInsereInicio(minhaLista, i3); 
    printf(" -> Inseriu Inicio (Yoshi): ");
    ListaPrint(minhaLista); // Esperado: [Yoshi, Mario, Luigi]

    // Inserir no MEIO (Posição 2)
    // Estado atual: 0:Yoshi, 1:Mario, 2:Luigi. 
    // Inserindo na pos 2, o Toad deve entrar ANTES do Luigi.
    ListaInsereMeio(minhaLista, i4, 2); 
    printf(" -> Inseriu Meio (Pos 2):   ");
    ListaPrint(minhaLista); // Esperado: [Yoshi, Mario, Toad, Luigi]

    // ---------------------------------------------------------
    // 3. TESTE: CONSULTAS (Tamanho, Get e Pesquisa)
    // ---------------------------------------------------------
    printf("\n[3] Testando Consultas...\n");
    
    printf(" -> Tamanho Atual: %d (Esperado: 4)\n", ListaTamanho(minhaLista));
    
    Item recuperado;
    // Teste Get (Pegar o elemento na posição 1 - Mario)
    if (ListaGet(minhaLista, 1, &recuperado)) {
        printf(" -> ListaGet(pos=1): Recuperou %s (Esperado: Mario)\n", recuperado.nome);
    }

    // Teste Pesquisa (Buscar por nome)
    if (ListaPesquisa(minhaLista, "Toad", &recuperado)) {
        printf(" -> ListaPesquisa('Toad'): ENCONTRADO! ID=%d\n", recuperado.id);
    } else {
        printf(" -> ListaPesquisa('Toad'): NAO ENCONTRADO (Erro).\n");
    }

    // ---------------------------------------------------------
    // 4. TESTE: REMOÇÕES
    // ---------------------------------------------------------
    printf("\n[4] Testando Remocoes...\n");
    
    // Remove Inicio (Yoshi)
    ListaRemoveInicio(minhaLista, &recuperado);
    printf(" -> Removeu Inicio (%s): ", recuperado.nome);
    ListaPrint(minhaLista); // Esperado: [Mario, Toad, Luigi]

    // Remove Fim (Luigi)
    ListaRemoveFim(minhaLista, &recuperado);
    printf(" -> Removeu Fim (%s):    ", recuperado.nome);
    ListaPrint(minhaLista); // Esperado: [Mario, Toad]

    // Remove Meio (Posição 1 - Toad)
    // Lista atual: [Mario (0), Toad (1)]
    ListaRemoveMeio(minhaLista, 1, &recuperado); 
    printf(" -> Removeu Meio pos 1 (%s): ", recuperado.nome);
    ListaPrint(minhaLista); // Esperado: [Mario]

    // ---------------------------------------------------------
    // 5. TESTE: DESTRUIÇÃO
    // ---------------------------------------------------------
    printf("\n[5] Destruindo a Lista...\n");
    minhaLista = ListaDestroi(minhaLista);
    
    if (minhaLista == NULL) {
        printf(" -> Sucesso: Ponteiro da lista agora eh NULL.\n");
    }

    printf("\n=== FIM DO TESTE ===\n");
    return 0;
}
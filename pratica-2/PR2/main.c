#include <stdio.h>
#include <string.h>
#include "pratica.h"

#define MAX_PALAVRA 1001

int main() {
    char palavra[MAX_PALAVRA];
    if (scanf("%s", palavra) != 1) {
        return 0; // Se a leitura falhar (ex: fim de arquivo), sai.
    }

    // 2. Chamada das funções e impressão da saída
    
    // a. Reconhecimento de L1
    if (reconheceL1(palavra)) {
        printf("Pertence a linguagem L1\n");
    } else {
        printf("Nao pertence a linguagem L1\n");
    }

    // b. Reconhecimento de L2
    if (reconheceL2(palavra)) {
        printf("Pertence a linguagem L2\n");
    } else {
        printf("Nao pertence a linguagem L2\n");
    }

    return 0;
}
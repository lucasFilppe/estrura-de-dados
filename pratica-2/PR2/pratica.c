#include <string.h>
#include "pratica.h" 

int reconheceL1_aux(const char *palavra, int index, int state, int a_count) {
    // Caso Base 1: Fim da string
    if (palavra[index] == '\0') {
        // Se a string terminou, 
        return (a_count == 0);
    }

    // Estado 0: Lendo 'a's (espera 'a' ou transiciona para 'b')
    if (state == 0) {
        if (palavra[index] == 'a') {
            // Continua lendo 'a's.
            return reconheceL1_aux(palavra, index + 1, 0, a_count + 1);
        } else if (palavra[index] == 'b') {
            // O formato deve ser a...ab...b. Se for 'b', deve haver pelo menos um 'a' para 'gastar'.
            if (a_count > 0) {
                 return reconheceL1_aux(palavra, index + 1, 1, a_count - 1);
            }
            // Se encontrou 'b' mas a_count é 0, o formato está errado (ex: "b", "ba").
            return 0; 
        } else {
            // Caractere inválido
            return 0;
        }
    }

    // Estado 1: Lendo 'b's (só pode ler 'b')
    if (state == 1) {
        if (palavra[index] == 'b') {
            // Continua lendo 'b's e 'gasta' um 'a'
            if (a_count > 0) {
                return reconheceL1_aux(palavra, index + 1, 1, a_count - 1);
            }
            // Se a_count chegou a zero, mas ainda há 'b's, significa que há mais 'b's do que 'a's.
            return 0;
        } else if (palavra[index] == 'a') {
            // Formato inválido: 'a' depois de um 'b' (ex: "aba", "aabba")
            return 0;
        }
    }
    
    return 0;
}

// Função principal de L1
int reconheceL1(const char *palavra) {
    // Caso de palavra vazia (""): n=0, a^0 b^0 = "", pertence.
    if (palavra[0] == '\0') {
        return 1;
    }
    // Começa no índice 0, estado 0 (lendo 'a's), contador de 'a's em 0.
    return reconheceL1_aux(palavra, 0, 0, 0);
}

int reconheceL2_aux(const char *palavra, int index, int balance) {
    // Caso Base: Fim da string
    if (palavra[index] == '\0') {
        // Se terminou, a palavra pertence se o balanço for zero (mesma qtde de a's e b's)
        return (balance == 0);
    }

    // Caso Recursivo
    if (palavra[index] == 'a') {
        // Encontrou 'a': aumenta o balanço em 1.
        return reconheceL2_aux(palavra, index + 1, balance + 1);
    } else if (palavra[index] == 'b') {
        // Encontrou 'b': diminui o balanço em 1.
        return reconheceL2_aux(palavra, index + 1, balance - 1);
    } else {
        // Caractere inválido (não 'a' nem 'b')
        return 0;
    }
}

// Função principal de L2
int reconheceL2(const char *palavra) {
    // Começa no índice 0, balanço 0.
    return reconheceL2_aux(palavra, 0, 0);
}
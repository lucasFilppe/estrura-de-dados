#include "pessoa.h"
#include <stdlib.h>

struct pessoa {
    char sexo;     // 'M' ou 'F'
    char resposta; // 'S' ou 'N'
};

Pessoa* Pessoa_criar(char sexo, char resposta) {
    Pessoa* p = (Pessoa*) malloc(sizeof(Pessoa));
    if (!p) return NULL;

    p->sexo = sexo;
    p->resposta = resposta;
    return p;
}

char Pessoa_getSexo(Pessoa* p) {
    return p->sexo;
}

char Pessoa_getResposta(Pessoa* p) {
    return p->resposta;
}

void Pessoa_destruir(Pessoa* p) {
    free(p);
}


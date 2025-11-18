#include "ponto.h"
#include <stdlib.h>
#include <stdbool.h>

struct ponto {
    float x;
    float y;
};

Ponto* ponto_criar(float x, float y) {
    Ponto* p = (Ponto*)malloc(sizeof(Ponto));
    if (p != NULL) {
        p->x = x;
        p->y = y;
    }
    return p;
}

Ponto* ponto_destruir(Ponto* p) {
    free(p);
    return NULL;
}

bool ponto_acessa(Ponto* p, float* x, float* y) {
    if (p == NULL || x == NULL || y == NULL) {
        return false;
    }
    *x = p->x;
    *y = p->y;
    return true;
}

bool ponto_atribui(Ponto* p, float x, float y) {
    if (p == NULL) {
        return false;
    }
    p->x = x;
    p->y = y;
    return true;
}

float ponto_distancia(Ponto* p1, Ponto* p2) {
    if (p1 == NULL || p2 == NULL) {
        return -1.0f; // Indica erro
    }
    float dx = p2->x - p1->x;
    float dy = p2->y - p1->y;
    return sqrtf(dx * dx + dy * dy);
}
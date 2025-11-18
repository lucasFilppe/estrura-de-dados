#include <stdio.h>
#include "aluno.h"

int main(){
    Estoque* estoque = lerPokemons();

    printf("Maior PC por tipo:\n");
    mostrarMaioresPorTipo(estoque);

    printf("Repetidos:\n");
    mostrarRepetidos(estoque);
    
    liberarEstoque(estoque);

    return 0;
}

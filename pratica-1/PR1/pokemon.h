#ifndef POKEMON_H
#define POKEMON_H

typedef struct pokemon Pokemon;

//cria um pokemon alocado dinamicamente
Pokemon* cria_Pokemon(char *nome, char *tipo, int pc);

//mostra maior por tipo
void maior_Tipo(Pokemon **p, int n);

void nome_Repetido(Pokemon **p, int n);

void libera_Memoria(Pokemon **p, int n);

#endif
#ifndef RESPOSTA_H
#define RESPOSTA_H

typedef struct entrevista Entrevista;

Entrevista* criarEntrevista(char sexo, char resposta);
void qtdRespostasProduto(Entrevista **e, int n, int *, int *);





#endif

#ifndef ALUNO_H
#define ALUNO_H

typedef struct aluno Aluno;

//função que cria um aluno
Aluno* cria_Aluno(char nome[21], float nota);

//função que verifica alunos com notas maiores que 6
void aluno_Aprovado(Aluno **alunos, int n);

void aluno_Imprime(Aluno **alunos, int n);

void destroi_Alunos(Aluno **alunos, int n);

#endif
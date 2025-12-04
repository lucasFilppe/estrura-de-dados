#ifndef ALUNO_H
#define ALUNO_H

typedef struct aluno Aluno;

Aluno* criaAluno(int matricula, int idade);
void lerVetorAlunos(Aluno *v[], int n);
void imprimeAlunos(Aluno *v[], int n);
int maioresIdade(Aluno *v[], int n);

#endif
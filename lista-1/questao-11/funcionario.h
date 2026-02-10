#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

typedef struct funcionario Funcionario;

Funcionario* criaFuncionario(char *nome, int matricula, float salario);
void imprimeFuncionario(Funcionario *f);
Funcionario** criaVetorFuncionarios(int n);
float calculaReajuste(Funcionario** f, int n);

#endif
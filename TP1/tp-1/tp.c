#include <stdio.h>
#include "formula.h"

int main()
{
    int n, m;

    scanf("%d %d", &n, &m);

    Formula *f = criaFormula(n, m);

    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        adicionaClausula(f, x, y, z);
    }

    imprimeFormula(f);
    solucaoFormula(f);

    destroiFormula(&f);

    return 0;
}

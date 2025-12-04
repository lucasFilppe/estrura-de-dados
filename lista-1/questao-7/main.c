#include <stdio.h>
#include "pessoa.h"

#define TOTAL 50

int main() {
    int sim = 0, nao = 0;
    int homens_sim = 0, total_homens = 0;
    int mulheres_nao = 0, total_mulheres = 0;

    for (int i = 0; i < TOTAL; i++) {
        char sexo, resposta;

        printf("Pessoa %d - Sexo (M/F): ", i + 1);
        scanf(" %c", &sexo);

        printf("Pessoa %d - Resposta (S/N): ", i + 1);
        scanf(" %c", &resposta);

        Pessoa* p = Pessoa_criar(sexo, resposta);

        // sim e não totais
        if (Pessoa_getResposta(p) == 'S' || Pessoa_getResposta(p) == 's')
            sim++;
        else
            nao++;

        // homens que disseram sim
        if (Pessoa_getSexo(p) == 'M' || Pessoa_getSexo(p) == 'm') {
            total_homens++;
            if (Pessoa_getResposta(p) == 'S' || Pessoa_getResposta(p) == 's')
                homens_sim++;
        }

        // mulheres que disseram não
        if (Pessoa_getSexo(p) == 'F' || Pessoa_getSexo(p) == 'f') {
            total_mulheres++;
            if (Pessoa_getResposta(p) == 'N' || Pessoa_getResposta(p) == 'n')
                mulheres_nao++;
        }

        Pessoa_destruir(p);
    }

    printf("\n===== RESULTADOS =====\n");
    printf("Quantidade de pessoas que responderam SIM: %d\n", sim);
    printf("Quantidade de pessoas que responderam NAO: %d\n", nao);

    if (total_homens > 0)
        printf("Percentual de homens que responderam SIM: %.2f%%\n",
               (homens_sim * 100.0) / total_homens);
    else
        printf("Nenhum homem entrevistado.\n");

    if (total_mulheres > 0)
        printf("Percentual de mulheres que responderam NAO: %.2f%%\n",
               (mulheres_nao * 100.0) / total_mulheres);
    else
        printf("Nenhuma mulher entrevistada.\n");

    return 0;
}

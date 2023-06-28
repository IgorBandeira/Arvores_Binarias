#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ArvoreAVL.h"
#include "ArvoreLLRB.h"
#include "Ordenacao.h"
#define TAMANHO_MAX_LINHA 15000
#define RED 1
#define BLACK 0

void trocar(struct Funcionario *a, struct Funcionario *b) {
    struct Funcionario temp = *a;
    *a = *b;
    *b = temp;
}

int particao(struct Funcionario *funcionarios, int baixo, int alto) {
    int pivo = funcionarios[alto].id;
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (funcionarios[j].id < pivo) {
            i++;
            trocar(&funcionarios[i], &funcionarios[j]);
        }
    }
    trocar(&funcionarios[i + 1], &funcionarios[alto]);
    return (i + 1);
}

void quickSort(struct Funcionario *funcionarios, int baixo, int alto) {
    if (baixo < alto) {
        int pi = particao(funcionarios, baixo, alto);

        quickSort(funcionarios, baixo, pi - 1);
        quickSort(funcionarios, pi + 1, alto);
    }
}

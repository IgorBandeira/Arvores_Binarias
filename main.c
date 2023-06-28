#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ArvoreAVL.h"
#include "ArvoreLLRB.h"
#include "Ordenacao.h"
#define TAMANHO_MAX_LINHA 15000

int main() {
    int teste;
    do {
        FILE *arquivo = fopen("massaDados.csv", "rb");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo de leitura.\n");
            return 1;
        }

        FILE *arquivo2 = fopen("dadosOrdenadosCrescente.csv", "wb");
        if (arquivo2 == NULL) {
            printf("Erro ao criar o arquivo de escrita.\n");
            fclose(arquivo);
            return 1;
        }

        char linha[TAMANHO_MAX_LINHA];
        struct Funcionario funcionarios[15000];
        int numFuncionarios = 0;

        while (fgets(linha, TAMANHO_MAX_LINHA, arquivo) != NULL) {
            char *token;
            token = strtok(linha, ";");

            funcionarios[numFuncionarios].id = atoi(token);
            token = strtok(NULL, ";");

            funcionarios[numFuncionarios].nome = malloc(strlen(token) + 1);
            strcpy(funcionarios[numFuncionarios].nome, token);

            token = strtok(NULL, ";");
            funcionarios[numFuncionarios].idade = atoi(token);
            token = strtok(NULL, ";");

            funcionarios[numFuncionarios].empresa = malloc(strlen(token) + 1);
            strcpy(funcionarios[numFuncionarios].empresa, token);

            token = strtok(NULL, ";");
            funcionarios[numFuncionarios].departamento = malloc(strlen(token) + 1);
            strcpy(funcionarios[numFuncionarios].departamento, token);

            token = strtok(NULL, ";");
            funcionarios[numFuncionarios].salario = atof(token);

            numFuncionarios++;
        }

        fclose(arquivo);

        quickSort(funcionarios, 0, numFuncionarios - 1); // Ordenar os funcionários pelo ID usando QuickSort

        // Escrever os dados ordenados no novo arquivo
        for (int i = 0; i < numFuncionarios; i++) {
            fprintf(arquivo2, "%d;%s;%d;%s;%s;%.2f\n", funcionarios[i].id, funcionarios[i].nome,
                    funcionarios[i].idade, funcionarios[i].empresa, funcionarios[i].departamento,
                    funcionarios[i].salario);
        }

        fclose(arquivo2);

        // Liberar a memória alocada
        for (int i = 0; i < numFuncionarios; i++) {
            free(funcionarios[i].nome);
            free(funcionarios[i].empresa);
            free(funcionarios[i].departamento);
        }

        // ESCOLHER A ARVORE E GUARDA A ESCOLHA EM opcaoAlgoritmo
        system("cls 2> null");
        system("clear 2> null");
        printf("\tEscolha a arvore que deseja usar:\n\n");
        printf("\t\t1 - Arvore AVL\n");
        printf("\t\t2 - Arvore Rubro Negra\n");

        int opcaoArvore;
        scanf("%d", &opcaoArvore);

        switch (opcaoArvore) {
        case 1:
            system("cls 2> null");
            system("clear 2> null");
            printf("\tVoce escolheu a Arvore AVL.\n\n");
            break;
        case 2:
            system("cls 2> null");
            system("clear 2> null");
            printf("\tVoce escolheu a Arvore Rubro Negra.\n\n");
            break;
        default:
            printf("\tNão há muitas opções, tenho certeza de que na próxima voce acerta!!!.\n");
            return 1;
        }

        switch (opcaoArvore) {
        case 1:
            processarArvoreAVL();
            break;
        case 2:
            processarArvoreLLRB();
            break;
        default:
            printf("\t Opcao errada!\n");
            return 1;
        }

        printf("\nDeseja um novo teste?\nsim = 1 nao = 2\n"); // loop para utilizacao do menu

        scanf("%d", &teste);

    } while (teste == 1);
    system("cls 2> null");
    system("clear 2> null");

    return 0;
}



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ArvoreAVL.h"
#include "Ordenacao.h"
#define TAMANHO_MAX_LINHA 15000


// retorna a altura de um nó
int altura(No* no) {
    if (no == NULL) {
        return 0;
    }
    return no->altura;
}

// retorna o valor máximo entre dois inteiros
int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// cria um novo nó
No* novoNo(int chave) {
    No* no = (No*)malloc(sizeof(No));
    no->chave = chave;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1;
    return no;
}

// realiza uma rotação simples à direita
No* rotacionarDireita(No* no) {
    No* novoNo = no->esquerda;
    no->esquerda = novoNo->direita;
    novoNo->direita = no;
    no->altura = maximo(altura(no->esquerda), altura(no->direita)) + 1;
    novoNo->altura = maximo(altura(novoNo->esquerda), altura(novoNo->direita)) + 1;
    return novoNo;
}

// realiza uma rotação simples à esquerda
No* rotacionarEsquerda(No* no) {
    No* novoNo = no->direita;
    no->direita = novoNo->esquerda;
    novoNo->esquerda = no;
    no->altura = maximo(altura(no->esquerda), altura(no->direita)) + 1;
    novoNo->altura = maximo(altura(novoNo->esquerda), altura(novoNo->direita)) + 1;
    return novoNo;
}

// realiza uma rotação dupla à direita
No* rotacionarDuplaDireita(No* no) {
    no->esquerda = rotacionarEsquerda(no->esquerda);
    return rotacionarDireita(no);
}

// realiza uma rotação dupla à esquerda
No* rotacionarDuplaEsquerda(No* no) {
    no->direita = rotacionarDireita(no->direita);
    return rotacionarEsquerda(no);
}

No* inserir(No* no, int chave, char* nome, int idade, char* empresa, char* departamento, float salario) {
    if (no == NULL) {
        No* novo = novoNo(chave);
        novo->nome = malloc(strlen(nome) + 1);
        strcpy(novo->nome, nome);
        novo->idade = idade;
        novo->empresa = malloc(strlen(empresa) + 1);
        strcpy(novo->empresa, empresa);
        novo->departamento = malloc(strlen(departamento) + 1);
        strcpy(novo->departamento, departamento);
        novo->salario = salario;
        return novo;
    }
    if (chave < no->chave) {
        no->esquerda = inserir(no->esquerda, chave, nome, idade, empresa, departamento, salario);
    }
    else if (chave > no->chave) {
        no->direita = inserir(no->direita, chave, nome, idade, empresa, departamento, salario);
    }
    else {
        return no;
    }
    no->altura = 1 + maximo(altura(no->esquerda), altura(no->direita));
    int balanceamento = altura(no->esquerda) - altura(no->direita);
    if (balanceamento > 1 && chave < no->esquerda->chave) {
        return rotacionarDireita(no);
    }
    if (balanceamento < -1 && chave > no->direita->chave) {
        return rotacionarEsquerda(no);
    }
    if (balanceamento > 1 && chave > no->esquerda->chave) {
        return rotacionarDuplaDireita(no);
    }
    if (balanceamento < -1 && chave < no->direita->chave) {
        return rotacionarDuplaEsquerda(no);
    }
    return no;
}

void imprimirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        printf("Id: %d\n", raiz->chave);
        printf("Nome: %s\n", raiz->nome);
        printf("Idade: %d\n", raiz->idade);
        printf("Empresa: %s\n", raiz->empresa);
        printf("Departamento: %s\n", raiz->departamento);
        printf("Salario: %.2f\n\n", raiz->salario);
        imprimirEmOrdem(raiz->direita);
    }
}

void processarArvoreAVL() {
    struct timeval tempo_inicial, tempo_final;
    double deltaTempo;

    FILE *arquivo3 = fopen("dadosOrdenadosCrescente.csv", "rb");
    if (arquivo3 == NULL) {
        printf("Erro ao abrir o arquivo de leitura.\n");
        return;
    }

    No *raiz = NULL;
    char linha[TAMANHO_MAX_LINHA];

    gettimeofday(&tempo_inicial, NULL);

    while (fgets(linha, TAMANHO_MAX_LINHA, arquivo3) != NULL) {
        char *token;
        token = strtok(linha, ";");

        int id = atoi(token);
        token = strtok(NULL, ";");

        char *nome = malloc(strlen(token) + 1);
        strcpy(nome, token);

        token = strtok(NULL, ";");
        int idade = atoi(token);
        token = strtok(NULL, ";");

        char *empresa = malloc(strlen(token) + 1);
        strcpy(empresa, token);

        token = strtok(NULL, ";");
        char *departamento = malloc(strlen(token) + 1);
        strcpy(departamento, token);

        token = strtok(NULL, ";");
        float salario = atof(token);

        raiz = inserir(raiz, id, nome, idade, empresa, departamento, salario);
    }

    gettimeofday(&tempo_final, NULL);
    deltaTempo = (tempo_final.tv_sec + tempo_final.tv_usec / 1000000.0) - (tempo_inicial.tv_sec + tempo_inicial.tv_usec / 1000000.0); // Faz o calculo para deixar em segundos

    fclose(arquivo3);
    //SÓ PARA PRINTAR PARA VALIDAR MAS PODE EXCLUIR
    //printf("Árvore AVL em ordem:\n");
    //imprimirEmOrdem(raiz);

    printf("\n\nTEMPO TOTAL GASTO NA INSERCAO DA ARVORE AVL COM ARQUIVO ORDENADO: %f segundos\n\n", deltaTempo);

    FILE *arquivo4 = fopen("massaDados.csv", "rb");
    if (arquivo4 == NULL) {
        printf("Erro ao abrir o arquivo de leitura.\n");
        return;
    }

    No *raiz2 = NULL;

    gettimeofday(&tempo_inicial, NULL);

    while (fgets(linha, TAMANHO_MAX_LINHA, arquivo4) != NULL) {
        char *token;
        token = strtok(linha, ";");

        int id = atoi(token);
        token = strtok(NULL, ";");

        char *nome = malloc(strlen(token) + 1);
        strcpy(nome, token);

        token = strtok(NULL, ";");
        int idade = atoi(token);
        token = strtok(NULL, ";");

        char *empresa = malloc(strlen(token) + 1);
        strcpy(empresa, token);

        token = strtok(NULL, ";");
        char *departamento = malloc(strlen(token) + 1);
        strcpy(departamento, token);

        token = strtok(NULL, ";");
        float salario = atof(token);

        raiz2 = inserir(raiz2, id, nome, idade, empresa, departamento, salario);
    }

    gettimeofday(&tempo_final, NULL);
    deltaTempo = (tempo_final.tv_sec + tempo_final.tv_usec / 1000000.0) - (tempo_inicial.tv_sec + tempo_inicial.tv_usec / 1000000.0); // Faz o calculo para deixar em segundos

    fclose(arquivo4);

    //SÓ PARA PRINTAR PARA VALIDAR MAS PODE EXCLUIR
    //printf("Árvore AVL em ordem:\n");
    //imprimirEmOrdem(raiz2);

    printf("\n\nTEMPO TOTAL GASTO NA INSERCAO DA ARVORE AVL COM ARQUIVO DESORDENADO: %f segundos\n\n", deltaTempo);
}


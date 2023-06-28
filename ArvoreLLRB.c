#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "ArvoreLLRB.h"
#include "Ordenacao.h"
#define TAMANHO_MAX_LINHA 15000
#define RED 1
#define BLACK 0

typedef struct NO {
    int info;
    int id;
    char* Nome;
    int idade;
    char* empresa;
    char* departamento;
    float salario;
    struct NO* esq;
    struct NO* dir;
    int cor;
} NO;

int cor(struct NO *H) {
    if (H == NULL) {
        return BLACK;
    } else {
        return H->cor;
    }
}

arvoreLLRB *cria_arvoreLLRB() {
    arvoreLLRB *raiz = (arvoreLLRB*) malloc(sizeof(arvoreLLRB));
    if (raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

int vazia_arvoreLLRB(arvoreLLRB *raiz) {
    if (raiz == NULL) {
        return 1;
    }
    if (*raiz == NULL) {
        return 1;
    }
    return 0;
}

int altura_arvoreLLRB(arvoreLLRB *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    if (*raiz == NULL) {
        return 0;
    }
    int alt_esq = altura_arvoreLLRB(&((*raiz)->esq));
    int alt_dir = altura_arvoreLLRB(&((*raiz)->dir));
    if (alt_esq > alt_dir) {
        return (alt_esq + 1);
    } else {
        return (alt_dir + 1);
    }
}

int totalNO_arvoreLLRB(arvoreLLRB *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    if (*raiz == NULL) {
        return 0;
    }
    int alt_esq = totalNO_arvoreLLRB(&((*raiz)->esq));
    int alt_dir = totalNO_arvoreLLRB(&((*raiz)->dir));
    return (alt_esq + alt_dir + 1);
}

void emOrdem_arvoreLLRB(arvoreLLRB *raiz) {
    if (raiz == NULL) {
        return;
    }
    if (*raiz != NULL) {
        emOrdem_arvoreLLRB(&((*raiz)->esq));
        printf("%d\n", (*raiz)->info);
        emOrdem_arvoreLLRB(&((*raiz)->dir));
    }
}

int insere_arvoreLLRB(arvoreLLRB *raiz, int valor, int id, char* Nome, int idade, char* empresa, char* departamento, float salario) {
    int resp;
    *raiz = insereNO(*raiz, valor, id, Nome, idade, empresa, departamento, salario, &resp);
    if ((*raiz) != NULL) {
        (*raiz)->cor = BLACK;
    }
    return resp;
}

struct NO *insereNO(struct NO *H, int valor, int id, char* Nome, int idade, char* empresa, char* departamento, float salario, int *resp) {
    if (H == NULL) {
        struct NO *Novo;
        Novo = (struct NO*) malloc(sizeof(struct NO));
        if (Novo == NULL) {
            *resp = 0;
            return NULL;
        }
        Novo->info = valor;
        Novo->id = id;
        Novo->Nome = malloc(strlen(Nome) + 1);
        strcpy(Novo->Nome, Nome);
        Novo->idade = idade;
        Novo->empresa = malloc(strlen(empresa) + 1);
        strcpy(Novo->empresa, empresa);
        Novo->departamento = malloc(strlen(departamento) + 1);
        strcpy(Novo->departamento, departamento);
        Novo->salario = salario;
        Novo->cor = RED;
        Novo->dir = NULL;
        Novo->esq = NULL;
        *resp = 1;
        return Novo;
    }
    if (valor == H->info) {
        *resp = 0;
    } else {
        if (valor < H->info) {
            H->esq = insereNO(H->esq, valor, id, Nome, idade, empresa, departamento, salario, resp);
        } else {
            H->dir = insereNO(H->dir, valor, id, Nome, idade, empresa, departamento, salario, resp);
        }
    }
    if (cor(H->dir) == RED && cor(H->esq) == BLACK) {
        H = rotacionaEsquerda(H);
    }
    if (cor(H->esq) == RED && cor(H->esq->esq) == RED) {
        H = rotacionaDireita(H);
    }
    if (cor(H->esq) == RED && cor(H->dir) == RED) {
        trocaCor(H);
    }
    return H;
}

void imprimirArvoreLLRB(arvoreLLRB raiz) {
    if (raiz != NULL) {
        imprimirArvoreLLRBAux(raiz);
    } else {
        printf("A árvore está vazia.\n");
    }
}

void imprimirArvoreLLRBAux(struct NO *no) {
    if (no != NULL) {
        imprimirArvoreLLRBAux(no->esq);
        printf("Id: %d \n", no->id);
        printf("Nome: %s \n", no->Nome);
        printf("Idade: %d \n", no->idade);
        printf("Empresa: %s \n", no->empresa);
        printf("Departamento: %s \n", no->departamento);
        printf("Salario: %2f \n\n", no->salario);

        imprimirArvoreLLRBAux(no->dir);
    }
}

void trocaCor(struct NO *H) {
    H->cor = !H->cor;
    if (H->esq != NULL) {
        H->esq->cor = !H->esq->cor;
    }
    if (H->dir != NULL) {
        H->dir->cor = !H->dir->cor;
    }
}

struct NO *rotacionaEsquerda(struct NO *A) {
    struct NO *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

struct NO *rotacionaDireita(struct NO *A) {
    struct NO *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

struct NO *move2EsqRED(struct NO *H) {
    trocaCor(H);
    if (cor(H->dir->esq) == RED) {
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
}

struct NO *move2DirRED(struct NO *H) {
    trocaCor(H);
    if (cor(H->esq->esq) == RED) {
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
}

struct NO *balancear(struct NO *H) {
    if (cor(H->dir) == RED) {
        H = rotacionaEsquerda(H);
    }
    if (H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED) {
        H = rotacionaDireita(H);
    }
    if (cor(H->esq) == RED && cor(H->dir) == RED) {
        trocaCor(H);
    }
    return H;
}

int consulta_arvoreLLRB(arvoreLLRB *raiz, int valor) {
    if (raiz == NULL) {
        return 0;
    }
    struct NO *atual = *raiz;
    while (atual != NULL) {
        if (valor == atual->info) {
            return 1;
        }
        if (valor > atual->info) {
            atual = atual->dir;
        } else {
            atual = atual->esq;
        }
    }
    return 0;
}

void liberar_arvoreLLRB(arvoreLLRB *raiz) {
    if (raiz == NULL) {
        return;
    }
    libera_NO(*raiz);
    free(raiz);
}

void libera_NO(struct NO *NO) {
    if (NO == NULL) {
        return;
    }
    libera_NO(NO->esq);
    libera_NO(NO->dir);
    free(NO);
    NO = NULL;
}

struct NO *remove_atual(struct NO *atual) {
    struct NO *NO1, *NO2;
    if (atual->esq == NULL) {
        NO2 = atual->dir;
        free(atual);
        return NO2;
    }
    NO1 = atual;
    NO2 = atual->esq;
    while (NO2->dir != NULL) {
        NO1 = NO2;
        NO2 = NO2->dir;
    }
    if (NO1 != atual) {
        NO1->dir = NO2->esq;
        NO2->esq = atual->esq;
    }
    NO2->dir = atual->dir;
    free(atual);
    return NO2;
}

int remove_arvoreLLRB(arvoreLLRB *raiz, int valor) {
    if (consulta_arvoreLLRB(raiz, valor)) {
        struct NO *H = *raiz;
        *raiz = removeNO(H, valor);
        if (*raiz != NULL) {
            (*raiz)->cor = BLACK;
        }
        return 1;
    } else {
        return 0;
    }
}

struct NO *removeNO(struct NO *H, int valor) {
    if (valor < H->info) {
        if (cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK) {
            H = move2EsqRED(H);
        }
        H->esq = removeNO(H->esq, valor);
    } else {
        if (cor(H->esq) == RED) {
            H = rotacionaDireita(H);
        }
        if (valor == H->info && (H->dir == NULL)) {
            free(H);
            return NULL;
        }
        if (valor == H->info) {
            struct NO *x = procuraMenor(H->dir);
            H->info = x->info;
            H->dir = removeMenor(H->dir);
        } else {
            H->dir = removeNO(H->dir, valor);
        }
    }
    return balancear(H);
}

struct NO *removeMenor(struct NO *H) {
    if (H->esq == NULL) {
        free(H);
        return NULL;
    }
    if (cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK) {
        H = move2EsqRED(H);
    }
    H->esq = removeMenor(H->esq);
    return balancear(H);
}

struct NO *procuraMenor(struct NO *atual) {
    struct NO *NO1 = atual;
    struct NO *NO2 = atual->esq;
    while (NO2 != NULL) {
        NO1 = NO2;
        NO2 = NO2->esq;
    }
    return NO1;
}

int verificaBalanceamento(arvoreLLRB *raiz) {
    if (raiz == NULL || *raiz == NULL) {
        return 1;
    }
    return verificaBalanceamentoRec(*raiz) && (*raiz)->cor == BLACK;
}

int verificaBalanceamentoRec(struct NO *NO) {
    if (NO == NULL) {
        return 1;
    }

    if ((NO->cor == RED && cor(NO->esq) == RED) || (NO->cor == RED && cor(NO->dir) == RED)) {
        return 0;
    }

    return verificaBalanceamentoRec(NO->esq) && verificaBalanceamentoRec(NO->dir);
}

void processarArvoreLLRB() {
    struct timeval tempo_inicial, tempo_final;
    double deltaTempo;

    //Primeira Medição de Tempo - Arquivo Ordenado
    FILE *arquivo5 = fopen("dadosOrdenadosCrescente.csv", "rb");
    if (arquivo5 == NULL) {
        printf("Erro ao abrir o arquivo de leitura.\n");
        return;
    }

    char linha[TAMANHO_MAX_LINHA];

    arvoreLLRB *raiz = NULL;  // Criação da Primeira Árvore para preeenchimento dos nós

    gettimeofday(&tempo_inicial, NULL);

    while (fgets(linha, TAMANHO_MAX_LINHA, arquivo5) != NULL) {
        char *token;
        token = strtok(linha, ";");

        int id = atoi(token);
        token = strtok(NULL, ";");

        char *Nome = malloc(strlen(token) + 1);
        strcpy(Nome, token);

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

        int valor = atoi(linha);

        insere_arvoreLLRB(&raiz, valor, id, Nome, idade, empresa, departamento, salario);

    }

    gettimeofday(&tempo_final, NULL);
    deltaTempo = (tempo_final.tv_sec + tempo_final.tv_usec / 1000000.0) - (tempo_inicial.tv_sec + tempo_inicial.tv_usec / 1000000.0);

    fclose(arquivo5);

    printf("\n\nTEMPO TOTAL GASTO NA INSERCAO DA ARVORE LLRB COM ARQUIVO ORDENADO: %f segundos\n\n", deltaTempo);

    //Segunda Medição de Tempo - Arquivo Desordenado
    FILE *arquivo6 = fopen("massaDados.csv", "rb");
    if (arquivo6 == NULL) {
        printf("Erro ao abrir o arquivo de leitura.\n");
        return;
    }

    arvoreLLRB *raiz2 = NULL; // Criação da Segunda Árvore para preeenchimento dos nós

    gettimeofday(&tempo_inicial, NULL);

    while (fgets(linha, TAMANHO_MAX_LINHA, arquivo6) != NULL) {
        char *token;
        token = strtok(linha, ";");

        int id = atoi(token);
        token = strtok(NULL, ";");

        char *Nome = malloc(strlen(token) + 1);
        strcpy(Nome, token);

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

        int valor = atoi(linha);

        insere_arvoreLLRB(&raiz2, valor, id, Nome, idade, empresa, departamento, salario);
    }

    gettimeofday(&tempo_final, NULL);
    deltaTempo = (tempo_final.tv_sec + tempo_final.tv_usec / 1000000.0) - (tempo_inicial.tv_sec + tempo_inicial.tv_usec / 1000000.0); // Faz o calculo para deixar em segundos

    fclose(arquivo6);

    printf("\n\nTEMPO TOTAL GASTO NA INSERCAO DA ARVORE LLRB COM ARQUIVO DESORDENADO: %f segundos\n\n", deltaTempo);
}


typedef struct No {
    int chave;
    char *nome;
    int idade;
    char *empresa;
    char *departamento;
    float salario;
    struct No* esquerda;
    struct No* direita;
    int altura;
} No;

typedef struct Dados {
    int id;
    char *nome;
    int idade;
    char *empresa;
    char *departamento;
    float salario;
} Dados;

int maximo(int a, int b);

No *novoNo(int chave);

No *rotacionarDireita(No *no);

No *rotacionarEsquerda(No *no);

No *rotacionarDuplaDireita(No *no);

No *rotacionarDuplaEsquerda(No *no);

No* inserir(No* no, int chave, char* nome, int idade, char* empresa, char* departamento, float salario);

void imprimirEmOrdem(No* raiz);

void processarArvoreAVL();

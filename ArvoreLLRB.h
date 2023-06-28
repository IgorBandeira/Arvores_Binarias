typedef struct NO *arvoreLLRB;

typedef struct dados {
    int id;
    char *nome;
    int idade;
    char *empresa;
    char *departamento;
    float salario;
} DADOS;

arvoreLLRB *cria_arvoreLLRB();

arvoreLLRB* cria_arvoreLLRB();

int vazia_arvoreLLRB(arvoreLLRB *raiz);

int totalNO_arvoreLLRB(arvoreLLRB *raiz);

void emOrdem_arvoreLLRB(arvoreLLRB *raiz);

int insere_arvoreLLRB(arvoreLLRB *raiz, int valor, int id, char* Nome, int idade, char* empresa, char* departamento, float salario);

int consulta_arvoreLLRB(arvoreLLRB *raiz, int valor);

int remove_arvoreLLRB(arvoreLLRB *raiz, int valor);

void processarArvoreLLRB();

void liberar_arvoreLLRB(arvoreLLRB *raiz);

void imprimirArvoreLLRB(arvoreLLRB raiz);

/* Funções auxiliares */
int cor(struct NO *H);

void trocaCor(struct NO *H);

struct NO* rotacionaEsquerda(struct NO *A);

struct NO* rotacionaDireita(struct NO *A);

struct NO* move2EsqRED(struct NO *H);

struct NO* move2DirRED(struct NO *H);

struct NO* balancear(struct NO *H);

struct NO *insereNO(struct NO *H, int valor, int id, char* Nome, int idade, char* empresa, char* departamento, float salario, int *resp);

void libera_NO(struct NO *no);

struct NO* remove_atual(struct NO *atual);

struct NO* removeNO(struct NO *H, int valor);

struct NO* removeMenor(struct NO *H);

struct NO* procuraMenor(struct NO *atual);




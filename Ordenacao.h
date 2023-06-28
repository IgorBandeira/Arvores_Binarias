struct Funcionario
{
    int id;
    char *nome;
    int idade;
    char *empresa;
    char *departamento;
    float salario;
};

void trocar(struct Funcionario *a, struct Funcionario *b);

int particao(struct Funcionario *funcionarios, int baixo, int alto);

void quickSort(struct Funcionario *funcionarios, int baixo, int alto);


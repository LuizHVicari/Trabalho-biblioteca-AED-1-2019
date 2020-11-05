#include "Biblioteca.h"

//Insere um RA na fila de espera, caso seja poss�vel, retorna 1, se n�o, retorna 0
int InserirEspera(int RA, Livro *livro, Leitores *leitores)
{
    //Inicia leitor com a cabe�a dos leitores
    Leitor *leitor = leitores->head_leitor;

    //Procura o usu�rio paraver se ele existe
    if (BuscarUsuarioRA(RA, leitores) == 0)
    {
        //Se n�o existir, ele informa e retorna 0
        printf("O usu�rio n�o existe\n");
        return 0;
    }

    int i = 0;

    //Percorre a lista de espera at� encontrar um espa�o
    while(livro->espera[i] != 0 && i <= MAX_SIZE)
    {
        i++;
    }

    //Se i passar do tamanho da lista, informa e retorna 0
    if (i >= MAX_SIZE)
    {
        printf("N�o h� lugares dispon�veis na fila de espera\n");
        return 0;
    }

    //Se h� espa�o na lista de espera
    else
    {
        do
        {
            //Se encontrar o leitor, aumenta o n�mero de livros emprestado
            if(leitor->RA == RA)
            {
                leitor->livros_emprestados++;
            }
            //Se n�o, avan�a na lista
            else
            {
                leitor = leitor->next_leitor;
            }

        }
        while (leitor->RA != RA && leitor->RA != leitores->head_leitor);

        //O leitor entra na fila de espera e retorna 0
        livro->espera[i] = RA;
        return 1;
    }
}

//Retira um RA da espera, retorna 1 se for bem sucedido, 0 se nao
int RetirarDaEspera(int RA, Livro *livro, Leitores *leitores)
{
    //Funciona como a de inserir, com algumas mudan�as
    Leitor *leitor = leitores->head_leitor;

    if(BuscarUsuarioRA(RA, leitores) == 0)
    {
        printf("O RA n�o existe");
        return 0;
    }
    int i;

    for(i = 0; i < MAX_SIZE; i++)
    {
        if(livro->espera[i] == RA)
        {
            livro->espera[i] = 0;
        }
    }

    do
    {
        if(leitor->RA == RA)
        {
            //Diminui o n�mero de livros emprestados
            leitor->livros_emprestados--;
        }
        else
        {
            leitor = leitor->next_leitor;
        }

    }
    while (leitor->RA != RA && leitor->RA != leitores->head_leitor);

    //Ordena a nova lista de espera
    OrdenarEspera (livro);

    return 1;
}

//Ordena a lista de espera para n�o ficarem espa�os vazios no meio
void OrdenarEspera(Livro *livro)
{
    //DEclara��o de vari�veis
    int i, j;

    //Percorre o vetor
    for(i = 0; i < MAX_SIZE; i++)
    {
        //Se encontrar um valor como 0
        if(livro->espera[i] == 0)
        {
            //avan�a todos depois dele
            for(j = i; j < MAX_SIZE; j++)
            {
                livro->espera[j] = livro->espera[j+1];

                if(j + 1 > MAX_SIZE)
                {
                    livro->espera[j] = 0;
                }
            }
        }
    }
}

//Imprime a lista de espera
void ImprimirEspera(Livro *livro)
{
    int i;

    //Percorre a lista de esperae imprime o RA indicado
    for(i = 0; i < MAX_SIZE && livro->espera[i] > 0; i++)
    {
        printf("%d\t", livro->espera[i]);
    }
    printf("\n");
}

//Fun��o para pedir empr�stimo de um livro
void EmprestarLivro(int RA, Livro *livro, Leitores *leitores, Biblioteca *biblioteca)
{
    //Se o leitor n�o existir, informa
    if(BuscarUsuarioRA(RA, leitores) == 0)
    {
        printf("O RA n�o existe\n");
    }

    //Se o livro estiver emprestado, entra na espera
    else if(livro->emprestado > 0)
    {
        InserirEspera(RA, livro, leitores);
    }

    //Se o livro estiver dispon�vel, ele realiza o empr�stimo
    else
    {
        livro->emprestado = RA;

        //Aumenta o n�mero de livros emprestados para o usu�rio
        AumentarEmprestado(leitores, RA);
    }

    //Atualiza os arquivos
    ExportarLivroParaArquivo(biblioteca);
    ExportarLeitorParaArquivo(leitores);
}

//Fun��o para devolver o livro, funciona de maneira parecida com a de realizar empr�stimo
void DevolverLivro (int RA, Livro *livro, Leitores *leitores, Biblioteca *biblioteca)
{
    if(BuscarUsuarioRA(RA, leitores) == 0)
    {
        printf("O RA n�o existe\n");
    }
    //Informa que o livro n�o est� dispon�vel
    else if(livro->emprestado == 0)
    {
        printf("O livro n�o est� emprestado\n");
    }

    else
    {
        livro->emprestado = 0;

        //Chama a fun��o para diminuir o n�mero de livros emprestados
        DiminuirEmprestado(leitores, RA);

        if(livro->espera[0] > 0)
        {
            EmprestarLivro(livro->espera[0], livro, leitores, biblioteca);
            RetirarDaEspera(RA, livro, leitores);
        }
    }

    ExportarLivroParaArquivo(biblioteca);
    ExportarLeitorParaArquivo(leitores);
}

int MenuEspera(Biblioteca *biblioteca, Leitores *leitores)
{
    system ("cls");

    char opcao, titulo[MAX_SIZE];
    int RA, ID;
    Livro *livro = biblioteca->head_biblioteca;

    if (biblioteca->head_biblioteca->ID != ID)
    {
        do
        {
            livro = livro->next_livro;
        }
        while(livro != biblioteca->head_biblioteca && livro->ID != ID);
    }
    do
    {
        printf("O que deseja fazer:\n");
        printf("A-) Emprestar livro\n");
        printf("B-) Devolver livro\n");
        printf("C-) Ver fila de espera do livro\n");
        printf("D-) Listar dispon�veis\n");
        printf("E-) Voltar ao menu anterior\n");
        fflush(stdin);
        scanf("%c", &opcao);

        if (opcao == 'a' || opcao == 'b' || opcao == 'c' || opcao == 'd' || opcao =='e')
        {
            opcao = toupper(opcao);
        }

        system("cls");

    }
    while (opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != 'D' && opcao != 'E');

    switch (opcao)
    {
    case 'A':
        printf("Informe o ID do livro que deseja ver: ");
        scanf("%d", &ID);

        if (biblioteca->head_biblioteca->ID != ID)
        {
            do
            {
                livro = livro->next_livro;
            }
            while(livro != biblioteca->head_biblioteca && livro->ID != ID);
        }
        printf("Digite o RA: ");
        scanf("%d", &RA);
        EmprestarLivro(RA, livro, leitores, biblioteca);

        break;

    case 'B':
        printf("Informe o ID dolivro que deseja ver: ");
        scanf("%d", &ID);

        if (biblioteca->head_biblioteca->ID != ID)
        {
            do
            {
                livro = livro->next_livro;
            }
            while(livro != biblioteca->head_biblioteca && livro->ID != ID);
        }
        printf("Digite o RA: ");
        scanf("%d", &RA);
        DevolverLivro(RA, livro, leitores, biblioteca);

        break;

    case 'C':
        printf("Informe o ID dolivro que deseja ver: ");
        scanf("%d", &ID);

        if (biblioteca->head_biblioteca->ID != ID)
        {
            do
            {
                livro = livro->next_livro;
            }
            while(livro != biblioteca->head_biblioteca && livro->ID != ID);
        }
        ImprimirEspera(livro);

        break;

    case 'D':
        ImprimirDisponivel(biblioteca);

        break;

    case 'E':
        MenuGeral(biblioteca, leitores);

    }
}

//Aumenta o n�mero de livros emprestados
void AumentarEmprestado (Leitores *leitores, int RA)
{
    //Inicia aux com a cabe�a da lista
    Leitor *aux = leitores->head_leitor;

    //Enquanto for diferente da cabe�a, percorre o arquivo
    do
    {
        //Se encontrar o leitor
        if(aux->RA == RA)
        {
            //Aumenta o n�mero de livros emprestados e retorna 1
            aux->livros_emprestados++;
            return 1;
        }

        //Avan�a na lista
        aux = aux->next_leitor;
    }
    while(aux != leitores->head_leitor);

    //Retorna 0
    return 0;
}

//Funciona de maneira similar ao AumentarEmprestado, mas diminui o n�mero de livros emprestados
void DiminuirEmprestado (Leitores *leitores, int RA)
{
    Leitor *aux = leitores->head_leitor;

    while(aux != leitores->head_leitor->previous_leitor)
    {
        if(aux->RA == RA)
        {
            //Dimiuni o n�mero de livros emprestados
            aux->livros_emprestados--;

            return 1;
        }
        aux = aux->next_leitor;
    }

    return 0;
}

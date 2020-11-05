#include "Biblioteca.h"

//Cria a lista de leitores
//****Usa s� no come�o da execucao
Leitores *CriarLeitores()
{
    //Aloca o espa�o de mem�ria
    Leitores *leitores = malloc (sizeof (Leitores));
    //Coloca a cabe�a como nula
    leitores->head_leitor = NULL;

    return leitores;
}

//Cria o leitor e o cadastra
void *CriarLeitor (Leitores *leitores)
{
    //Cria e aloca o tamanho do livro
    Leitor *leitor = malloc(sizeof(Leitor));

    //Insere o t�tulo do livro
    printf("Informe nome do usu�rio: ");
    fflush(stdin);
    gets(leitor->nome);

    //Insere o ID do livro
    printf("Informe o RA do usu�rio: ");
    scanf("%d", &leitor->RA);

    //Define o valor como zero (n�o emprestou nada)
    leitor->livros_emprestados = 0;

    //Insere o usu�rio na lista
    InserirNosLeitores(leitor, leitores);

    //Passa os dados para o arquivo
    ExportarLeitorParaArquivo(leitores);

    //Limpa a tela
    system("cls");
}

//Fun��o para buscar o livro por ID
//Retorna 1 se encontrar, 0 se n�o
int BuscarUsuarioRA(int RA, Leitores *leitores)
{
    //V� se a lista est� vazia
    if (leitores->head_leitor == NULL)
    {
        //Informa que n�o h� usu�rios
        printf("N�o h� leitores cadastrados\n");
        //Retorna 0 (n�o encontrou)
        return 0;
    }

    //passa a cabe�a para um auxiliar
    Leitor *aux = leitores->head_leitor;

    //Entra na repeti��o para percorrer a lista de usuarios
    do
    {
        //V� se o usu�rio � o buscado pelo ID
        if (aux->RA == RA)
        {
            //Imprime e retorna 1 para encontrou
            ImprimirLeitor(aux);
            return 1;
        }

        //Avan�a na lista
        aux = aux->next_leitor;

        //Vai at� o fim da lista
    }
    while(aux != leitores->head_leitor);
    //Retorna 0 se n�o encontrar e informa
    printf("O usu�rio n�o existe\n");
    return 0;
}

//Imprime o livro informado e suas informa��es
void ImprimirLeitor(Leitor *leitor)
{
    //Informa o titulo
    printf("Nome: ");
    puts(leitor->nome);

    //Informa o RA
    printf("RA: %d\n", leitor->RA);

}

//Mostra a lista por ordem de RA
void ListarLeitoresRA(Leitores *leitores)
{
    //Chama a ordena��o por RA
    OrdenarUsuarioPorRA(leitores);

    //Verifica se a lista n�o est� vazia
    if (leitores == NULL)
    {
        //Informa que a lista est� vazia
        printf("N�o h� usu�rios cadastrados");
    }

    else
    {
        //Passa a cabe�a da lista para um auxiliar
        Leitor *aux = leitores->head_leitor;

        //Var�vel para as op��es
        char opcao;

        do
        {
            //Imprime os dados do leitor
            ImprimirLeitor(aux);

            do
            {
                //Menu de op��es para passar na lista
                printf("\nO que deseja fazer:");
                printf("\nD-) Avancar");
                printf("\nA-) Voltar");
                printf("\nJ-) Parar\n");
                fflush(stdin);
                scanf("%c", &opcao);

                //Covnerte para mai�sculo
                if (opcao == 'd' || opcao == 'a' || opcao == 'j')
                {
                    opcao = toupper(opcao);
                }

                //Valida para o switch case
            }
            while (opcao != 'A' && opcao != 'D' && opcao != 'J');

            if(opcao == 'D')
            {
                //Sobe na lista
                aux = aux->next_leitor;
            }

            else if(opcao == 'A')
            {
                //Volta na lista
                aux = aux->previous_leitor;
            }
            system("cls");
        }
        while(opcao != 'J');
    }

}

//Ordena a lista de usu�rios pelo RA
int OrdenarUsuarioPorRA(Leitores *leitores)
{
    //Valida para ver se tem algo na lista
    if (leitores == NULL)
    {
        //Avisa que est� vazia e retorna 0
        printf("N�o h� usu�rios cadastrados\n");
        return 0;
    }

    //Declara as vari�veis auxiliares
    Leitor *aux1 = leitores->head_leitor->next_leitor, *aux2, *aux3;

    //Fim do while quando percorrer toda a lista
    while (aux1 != leitores->head_leitor)
    {
        //aux2 recebe a cabe�a
        aux2 = leitores->head_leitor;

        //Fim do while quando os aux forem iguais
        while(aux2 != aux1)
        {
            //Valida se o RA de aux1 � maior que o de aux 2
            if (aux1->RA < aux2->RA)
            {
                //Faz a troca de posi��o das structs Leitor
                aux3 = aux1->previous_leitor;
                aux1->previous_leitor->next_leitor = aux1->next_leitor;
                aux1->next_leitor->previous_leitor = aux1->previous_leitor;
                aux2->previous_leitor->next_leitor = aux1;
                aux1->previous_leitor = aux2->previous_leitor;
                aux1->next_leitor = aux2;

                //Valida se o aux2 chegou na cabe�a
                if(aux2 == leitores->head_leitor)
                    leitores->head_leitor = aux1;

                aux1 = aux3;
                aux2 = aux1->previous_leitor;
            }

            //Avan�a o aux2
            aux2 = aux2->next_leitor;
        }
        //Avan�a o aux1
        aux1 = aux1->next_leitor;
    }

    //Retorna 1 para sucesso
    return 1;
}

//Muda algum dado do cadastro do leitor
int AtualizarLeitor(Leitores *leitores)
{
    //Valida se a lista � nula
    if (leitores->head_leitor == NULL)
    {
        //Avisa e retorna 0
        printf("N�o h� usu�rios cadastrados\n");
        return 0;
    }

    //Declara��o das vari�veis
    int RA;
    char opcao;
    //Inicia aux com a cabe�a
    Leitor *aux = leitores->head_leitor;

    //Pede qual o RA para ser atualizado
    printf("Informe o RA do usu�rio que deseja atualizar: ");
    scanf("%d", &RA);

    //Percorre a lista at� achar o RA certo
    do
    {
        if(RA == aux->RA)
        {
            //Pede se quer atualizar o nome
            printf("Nome atual: ");
            puts(aux->nome);
            printf("Deseja alterar? (S para sim)");
            fflush(stdin);
            scanf("%c", &opcao);
            //Valida a op��o
            if(opcao == 's' || opcao == 'S')
            {
                //Troca o nome
                printf("Informe o novo nome: ");
                fflush(stdin);
                gets(aux->nome);
            }

            //Pede se quer mudar o RA
            printf("RA atual: %d\n", aux->RA);
            printf("Deseja alterar? (S para sim)");
            fflush(stdin);
            scanf("%c", &opcao);
            //Valida a op��o
            if(opcao == 's' || opcao == 'S')
            {
                //Troca o RA
                printf("Informe o novo RA: ");
                scanf("%d", &aux->RA);
            }

            //Passa os novos dados para o arquivo bin�rio e retorna 1
            ExportarLeitorParaArquivo(leitores);
            return 1;
        }
        aux = aux->next_leitor;

    }
    while(aux != leitores->head_leitor);

    //Se o RA n�o foi encontrado, ele avisa e retorna 0
    printf("N�o ha usu�rio com esse RA cadastrado");
    return 0;
}

//Insere um leitor na lista de usu�rios
void InserirNosLeitores(Leitor *leitor, Leitores *leitores)
{
    //Valida para ver se � o primeiro livro da biblioteca
    if(leitores->head_leitor == NULL)
    {
        //printf("Primeiro livro cadastrado");
        leitores->head_leitor = leitor;
        leitor->next_leitor = leitor;
        leitor->previous_leitor =leitor;
    }

    //Se n�o for o primeiro, entra aqui
    else
    {
        leitores->head_leitor->previous_leitor->next_leitor = leitor;
        leitor->next_leitor = leitores->head_leitor;
        leitor->previous_leitor = leitores->head_leitor->previous_leitor;
        leitores->head_leitor->previous_leitor = leitor;
        leitores->head_leitor = leitor;
    }
}

//Remove e libera o espa�o dos leitores da mem�ria
//Eu e o Gustavo Alexandre elaboramos a fun��o juntos
int RemoverUsuario(Leitores *leitores)
{
    //Declara��o das vari�veis
    Leitor *aux;
    int RA;
    //Pede qual o usu�rio a ser removido
    printf("Informe o RA do usu�rio que deseja buscar");
    scanf("%d", &RA);

    //Inicia o auxiliar com a cabe�a
    aux = leitores->head_leitor;

    //Se o leitor for o �nico cadastrado
    if(aux->next_leitor == aux)
    {
        //Libera o espa�o e atualiza o arquivo bin�rio
        free(aux);
        ExportarLeitorParaArquivo(leitores);

        //Retorna 1
        return 1;
    }

    //Se tiver mais de um leitor na lista e a cabe�a vai ser removida
    else if(RA == leitores->head_leitor->RA)
    {
        //Muda a cabe�a e altera os next_leitor e previous_anterior para tirar o aux
        aux = leitores->head_leitor;
        leitores->head_leitor = leitores->head_leitor->next_leitor;
        leitores->head_leitor->previous_leitor = aux->previous_leitor;
        aux->previous_leitor->next_leitor = leitores->head_leitor;

        //Libera o aux e atualiza o bin�rio
        free(aux);
        ExportarLeitorParaArquivo(leitores);

        //Retorna 1
        return 1;
    }

    //Se o RA n�o estiver na cabe�a
    else
    {
        //Percorre a lista at� achar o leitor
        do
        {
            //Avan�a na lista
            aux = aux->next_leitor;

        }while(aux != leitores->head_leitor && aux->RA != RA);

        //Se encontrar
        if(aux->RA == RA)
        {
            //Altera os previous e next para remover o auxiliar
            aux->previous_leitor->next_leitor = aux->next_leitor;
            aux->next_leitor->previous_leitor = aux->previous_leitor;

            //Libera o auxiliar e atualiza o arquivo bin�rio
            free(aux);
            ExportarLeitorParaArquivo(leitores);

            //Retorna 1
            return 1;
        }
    }

    //Se n�o encontrar o usu�rio, avisa e retorna 0
    printf("O livro nao est� na biblioteca\n");
    return 0;
}

//Insere o usu�rio do arquivo binario
void InserirBinLeitor(Leitores *leitores, Leitor leitor)
{
    //Declara��o de vari�veis
    int i;
    //Inicia os leitores
    Leitor *criar = malloc(sizeof(Leitor)), *aux1 = malloc(sizeof(Leitor));

    //Copia os dados no novo leitor
    strcpy(criar->nome, leitor.nome);
    criar->RA = leitor.RA;
    criar->livros_emprestados = leitor.livros_emprestados;

    //Se n�o houver nada na lista
    if(leitores->head_leitor == NULL)
    {
        //A cabe�a, o anterior e o pr�ximo recebem o novo leitor
        criar->previous_leitor = criar;
        criar->next_leitor = criar;
        leitores->head_leitor = criar;
    }
    else
    {
        //O auxiliar recebe a cabe�a
        aux1 = leitores->head_leitor;

        //Percorre a lista at� achar a �ltima posi��o
        do
        {
            aux1 = aux1->next_leitor;
        }while(aux1!= leitores->head_leitor->previous_leitor);

        //Coloca o arquivo na �ltima posi��o da lista
        criar->previous_leitor = aux1->previous_leitor->next_leitor;
        criar->next_leitor = leitores->head_leitor;
        aux1->previous_leitor->next_leitor->next_leitor = criar;
        leitores->head_leitor->previous_leitor = criar;
    }
}

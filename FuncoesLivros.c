#include "Biblioteca.h"

//Cria a biblioteca
Biblioteca *CriarBiblioteca()
{
    //Aloca o espa�o da lista
    Biblioteca *biblioteca = malloc (sizeof (Biblioteca));
    //A cabe�a recebe NULL para indicar que n�o h� nada na lista
    biblioteca->head_biblioteca = NULL;
    //A quantidade recebe 0
    biblioteca->quantidade = 0;

    //Retorna a biblioteca
    return biblioteca;
}

//Cria o livro e insere na biblioteca
void *CriarLivro (Biblioteca *biblioteca)
{
    //Cria a vari�vel para escolher o genero do livro
    char opcao;

    //Cria e aloca o tamanho do livro
    Livro *livro = malloc (sizeof(Livro));

    //Insere o t�tulo do livro
    printf("Informe o t�tulo do livro: ");
    fflush(stdin);
    gets(livro->titulo);

    //Insere o ID do livro
    printf("Informe o ID do livro: ");
    scanf("%d", &livro->ID);

    //Insere o autor do livro
    printf("Informe o autor do livro: ");
    fflush(stdin);
    gets(livro->autor);

    //Abre a repeti��o para validar o g�nero
    do
    {
        //Insere o g�nero do livro
        printf("Qual o g�nero do livro: \n");
        printf("A-) Drama\n");
        printf("B-) Fic��o\n");
        printf("C-) Com�dia\n");
        printf("D-) Romance\n");
        fflush(stdin);
        scanf("%c", &opcao);

        //Valida para convevrter em maiusculo
        if(opcao == 'a' || opcao == 'b' || opcao == 'c' || opcao == 'd')
        {
            opcao = toupper(opcao);
        }

        //Valida para entrar no switch case
    }
    while(opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != 'D' && opcao != 'E' && opcao != 'F');

    //Insere o g�nero do livro
    switch (opcao)
    {
    case 'A':
        strcpy(livro->genero, "Drama");

        break;

    case 'B':
        strcpy(livro->genero, "Fic��o");

        break;

    case 'C':
        strcpy(livro->genero, "Com�dia");

        break;

    case 'D':
        strcpy(livro->genero, "Romance");

        break;

    default:

        break;
    }

    //Aumenta a quantidade de livros na biblioteca
    biblioteca->quantidade++;

    //O livro n�o est� emprestado
    livro->emprestado = 0;

    //Inicia a lista de espera como vazia
    for(int i = 0; i < MAX_SIZE; i++)
    {
        livro->espera[i] = 0;
    }

    //Coloca o livro na lista e atualiza o arquivo bin�rio
    InserirNaBiblioteca(livro, biblioteca);
    ExportarLivroParaArquivo (biblioteca);

    //system("cls");
}

//Fun��o para buscar o livro por ID
//Retorna 1 se encontrar, 0 se n�o
int BuscarLivroID (int ID, Biblioteca *biblioteca)
{
    //Informa se a lista est� vazia e retorna 0
    if(biblioteca == NULL)
    {
        printf("N�o h� livros cadastrados");
        return 0;
    }
    //passa a cabe�a para um auxiliar
    Livro *aux = biblioteca->head_biblioteca;

    //Entra na repeti��o para percorrer a biblioteca
    do
    {
        if (aux->ID == ID)
        {
            //Imprime o livro e retorna 1 para achou
            ImprimirLivro(aux);
            return 1;
        }

        //Avan�a na biblioteca
        aux = aux->next_livro;
    }
    while(aux != biblioteca->head_biblioteca);

    //Retorna 0 se n�o encontrar
    printf("O livro n�o existe\n");
    return 0;
}

//Imprime o livro informado e suas informa��es
void ImprimirLivro(Livro *livro)
{
    //Informa o titulo
    printf("T�tulo: ");
    puts(livro->titulo);

    //Informa o
    printf("Autor: ");
    puts(livro->autor);
    printf("G�nero: ");
    puts(livro->genero);
    printf("ID: %d\n", livro->ID);
}

//Lista os livros de maneira sequencial por g�nero
void ListarLivroGenero(Biblioteca *biblioteca)
{
    //Chama a fun��o de ordenar por g�nero
    OrdenarLivroPorGenero(biblioteca);

    //Se n�o h� nada na biblioteca, informa
    if (biblioteca == NULL)
    {
        printf("N�o h� livros cadastrados");
    }

    else
    {
        //Aux recebe a cabe�a
        Livro *aux = biblioteca->head_biblioteca;
        //Vari�vel para passar ou voltar na lista
        char opcao;

        do
        {
            //Chama a fun��o de imprimir o arquivo
            ImprimirLivro(aux);

            do
            {
                //Pede se quer avan�ar ou voltar na lista
                printf("\nO que deseja fazer:");
                printf("\nD-) Avancar");
                printf("\nA-) Voltar");
                printf("\nJ-) Parar\n");
                fflush(stdin);
                scanf("%c", &opcao);

                //Transforma em mai�sculo
                if (opcao == 'd' || opcao == 'a' || opcao == 'j')
                {
                    opcao = toupper(opcao);
                }

                system("cls");

            }
            while (opcao != 'A' && opcao != 'D' && opcao != 'J');

            if(opcao == 'D')
            {
                //Avan�a na lista
                aux = aux->next_livro;
            }

            else if(opcao == 'A')
            {
                //Retrocede na lista
                aux = aux->previous_livro;
            }
            //Enquanto o usu�rio escolher ver a lista
        }
        while(opcao != 'J');
    }
}

//Lista os livros de maneira sequencial por ID
void ListarLivroID(Biblioteca *biblioteca)
{
    //Chama a fun��o de ordenar
    OrdenarLivroPorID(biblioteca);

    //Se a lista for vazia, informa
    if (biblioteca == NULL)
    {
        printf("N�o h� livros cadastrados");
    }

    else
    {
        //Aux recebe a cabe�a da lista
        Livro *aux = biblioteca->head_biblioteca;
        //Vari�vel para passar a lista
        char opcao;

        do
        {
            //Imprime o livro
            ImprimirLivro(aux);

            do
            {
                //Pede qual op��o realizar
                printf("\nO que deseja fazer:");
                printf("\nD-) Avancar");
                printf("\nA-) Voltar");
                printf("\nJ-) Parar\n");
                fflush(stdin);
                scanf("%c", &opcao);

                //Transforma em mai�scula
                if (opcao == 'd' || opcao == 'a' || opcao == 'j')
                {
                    opcao = toupper(opcao);
                }

                //Limpa a tela
                system("cls");

            }
            while (opcao != 'A' && opcao != 'D' && opcao != 'J');

            if(opcao == 'D')
            {
                //Avan�a na lista
                aux = aux->next_livro;
            }

            else if(opcao == 'A')
            {
                //Volta na lista
                aux = aux->previous_livro;
            }
            //Enquanto escolher prosseguir
        }
        while(opcao != 'J');
    }
}

//Muda as informa��es de um livro j� cadastrado
int AtualizarLivro(Biblioteca *biblioteca, Leitores *leitores)
{
    //Essa fun��o funciona de maneira parecida com a de CriarLivro
    //Por�m, ela percorre a lista at� encontrar o livro certo e n�o insere ele na lista de novo
    //Afinal, ele j� est� inserido nela
    int ID;
    char opcao, op;
    Livro *aux = biblioteca->head_biblioteca;

    //Pede qual o livro que ser� alterado
    printf("Informe o ID do livro que deseja atualizar: ");
    scanf("%d", &ID);

    //Percorre a lista at� achar o livro
    do
    {
        //Se encontrar o livro, pede os novos dados
        if(ID == aux->ID)
        {
            printf("T�tulo atual: ");
            puts(aux->titulo);
            printf("Deseja alterar? (S para sim): ");
            fflush(stdin);
            scanf("%c", &opcao);
            if(opcao == 's' || opcao == 'S')
            {
                printf("Informe o novo t�tulo: ");
                fflush(stdin);
                gets(aux->titulo);
            }

            printf("Autor atual: ");
            puts(aux->autor);
            printf("Deseja alterar? (S para sim): ");
            fflush(stdin);
            scanf("%c", &opcao);
            if(opcao == 's' || opcao == 'S')
            {
                printf("Informe o novo autor: ");
                fflush(stdin);
                gets(aux->autor);
            }

            printf("ID atual: %d\n", aux->ID);
            printf("Deseja alterar? (S para sim): ");
            fflush(stdin);
            scanf("%c", &opcao);
            if(opcao == 's' || opcao == 'S')
            {
                printf("Informe o novo ID: ");
                scanf("%d", &aux->ID);
            }

            printf("G�nero atual: ");
            puts(aux->genero);
            printf("Deseja alterar? (S para sim): ");
            fflush(stdin);
            scanf("%c", &opcao);
            if(opcao == 's' || opcao == 'S')
            {
                do
                {
                    //Insere o g�nero do livro
                    printf("Qual o g�nero do livro: \n");
                    printf("A-) Drama\n");
                    printf("B-) Fic��o\n");
                    printf("C-) Com�dia\n");
                    printf("D-) Romance\n");
                    fflush(stdin);
                    scanf("%c", &op);

                    //Valida para convevrter em maiusculo
                    if(op == 'a' || op == 'b' || op == 'c' || op == 'd')
                    {
                        op = toupper(op);
                    }

                    //Valida para entrar no switch case
                }
                while(op != 'A' && op != 'B' && op != 'C' && op != 'D' && op != 'E' && op != 'F');

                switch (op)
                {
                case 'A':
                    strcpy(aux->genero, "Drama");

                    break;

                case 'B':
                    strcpy(aux->genero, "Fic��o");

                    break;

                case 'C':
                    strcpy(aux->genero, "Com�dia");

                    break;

                case 'D':
                    strcpy(aux->genero, "Romance");

                    break;

                default:

                    break;
                }
            }

            //Atualiza o arquivo bin�rio
            ExportarLivroParaArquivo (biblioteca);
            return 1;
        }
        //Avan�a na lista
        aux = aux->next_livro;

    }
    while(aux != biblioteca->head_biblioteca);

    //Se n�o encontrar, avisa e retorna 0
    printf("N�o h� livro com esse ID cadastrado\n");
    return 0;
}

//Ordena o cat�logo por g�nero , de acordo com o alfabeto
void OrdenarLivroPorGenero(Biblioteca *biblioteca)
{
    //Declara��o das vari�veis, inicia aux1 com a cabe�a da lista
    Livro *aux1 = biblioteca->head_biblioteca->next_livro, *aux2, *aux3;
    int controle;

    //Percorre toda a lista
    while (aux1 != biblioteca->head_biblioteca)
    {
        aux2 = biblioteca->head_biblioteca;

        while(aux2 != aux1)
        {
            controle = strcmp(aux1->titulo, aux2->titulo);
            printf("A");

            //Se a posi��o for encontrada, coloca o livro no lugar
            if (controle == 1)
            {
                aux3 = aux1->previous_livro;
                aux1->previous_livro->next_livro = aux1->next_livro;
                aux1->next_livro->previous_livro = aux1->previous_livro;
                aux2->previous_livro->next_livro = aux1;
                aux1->previous_livro = aux2->previous_livro;
                aux1->next_livro = aux2;

                if(aux2 == biblioteca->head_biblioteca)
                    biblioteca->head_biblioteca = aux1;

                aux1 = aux3;
                aux2 = aux1->previous_livro;
            }

            //Avan�a aux2 na lista
            aux2 = aux2->next_livro;
        }
        //Avan�a aux1 na lista
        aux1 = aux1->next_livro;
    }
}

//Ordena o cat�logo por ID (insetion sort)
void OrdenarLivroPorID(Biblioteca *biblioteca)
{
    //Funciona de maneira parecida com a ordena��o por g�nero, mas compara os IDs
    Livro *aux1 = biblioteca->head_biblioteca->next_livro, *aux2, *aux3;

    while (aux1 != biblioteca->head_biblioteca)
    {
        aux2 = biblioteca->head_biblioteca;

        while(aux2 != aux1)
        {
            if (aux1->ID < aux2->ID)
            {
                aux3 = aux1->previous_livro;
                aux1->previous_livro->next_livro = aux1->next_livro;
                aux1->next_livro->previous_livro = aux1->previous_livro;
                aux2->previous_livro->next_livro = aux1;
                aux1->previous_livro = aux2->previous_livro;
                aux1->next_livro = aux2;

                if(aux2 == biblioteca->head_biblioteca)
                    biblioteca->head_biblioteca = aux1;

                aux1 = aux3;
                aux2 = aux1->previous_livro;
            }

            aux2 = aux2->next_livro;
        }
        aux1 = aux1->next_livro;
    }
}

//Insere um livro no cat�logo
void InserirNaBiblioteca(Livro *livro, Biblioteca *biblioteca)
{
     //Valida para ver se � o primeiro livro da biblioteca
    if(biblioteca->head_biblioteca == NULL)
    {
        biblioteca->head_biblioteca = livro;
        livro->next_livro = livro;
        livro->previous_livro =livro;
    }

    //Se n�o for o primeiro, entra aqui
    else
    {
        biblioteca->head_biblioteca->previous_livro->next_livro = livro;
        livro->next_livro = biblioteca->head_biblioteca;
        livro->previous_livro = biblioteca->head_biblioteca->previous_livro;
        biblioteca->head_biblioteca->previous_livro = livro;
        biblioteca->head_biblioteca = livro;
    }
}

//Remove e libera o espa�o dos livros da mem�ria
//Eu e o Gustavo Alexandre elaboramos a fun��o juntos
int RemoverLivro(Biblioteca *biblioteca)
{
    //Declara as vari�veis
    Livro *aux;
    int ID;
    //Pede qual o Id do livro a ser removido
    printf("Informe o ID do livro que deseja buscar");
    scanf("%d", &ID);

    //Inicia aux com a cabe�a
    aux = biblioteca->head_biblioteca;

    //Se s� houver a cabe�a na lista, remove, atualiza o arquivo e retorna 1
    if(aux->next_livro == aux)
    {
        free(aux);
        ExportarLivroParaArquivo (biblioteca);
        return 1;
    }

    //Se h� mais �tens e a cabe�a ai ser removida, entra aqui
    else if(ID == biblioteca->head_biblioteca->ID)
    {
        //Passa a cabe�a para um auxiliar e altera os next_livro e previous_livro para remover o �tem
        //O pr�ximo recebe um auxiliar
        aux = biblioteca->head_biblioteca;
        biblioteca->head_biblioteca = biblioteca->head_biblioteca->next_livro;
        biblioteca->head_biblioteca->previous_livro = aux->previous_livro;
        aux->previous_livro->next_livro = biblioteca->head_biblioteca;

        //Limpa o espa�o do auxiliar e atualiza o arquivo bin�rio
        free(aux);
        ExportarLivroParaArquivo (biblioteca);

        //Retorna 1
        return 1;
    }

    else
    {
        //Procura o arquivo, avan�ando na lista
        do
        {
            //Avan�a na lista
            aux = aux->next_livro;

        }while(aux != biblioteca->head_biblioteca && aux->ID != ID);

        //Se encontrar o livro entra aqui
        if(aux->ID == ID)
        {
            //Ajeita os next e previous
            aux->previous_livro->next_livro = aux->next_livro;
            aux->next_livro->previous_livro = aux->previous_livro;

            //Libera o espa�o e atualiza o arquivo
            free(aux);
            ExportarLivroParaArquivo (biblioteca);

            return 1;
        }
    }

    //Se n�o encontrar, avisa e retorna 0
    printf("O livro nao est� na biblioteca\n");
    return 0;
}

//Insere um livro vindo do arquivo bin�rio na lista
void InserirBinLivro(Biblioteca *biblioteca, Livro livro)
{
    //Declara��o de vari�veis
    int i;
    //Aloca o espa�o das vari�veis
    Livro *criar = malloc(sizeof(Livro)), *aux1 = malloc(sizeof(Livro));

    //printf("A");

    //Passa os valores para o novo livro
    strcpy(criar->titulo, livro.titulo);
    //printf("B");
    strcpy(criar->autor, livro.autor);
    strcpy(criar->genero, livro.genero);
    criar->ID = livro.ID;
    //printf("B");
    criar->emprestado = livro.emprestado;

    //Copia a lista de espera
    for(i = 0; i < MAX_SIZE; i++)
    {
       // printf("C");
        criar->espera[i] = livro.espera[i];
    }

    //Se a lista est� vazia, insere o novo livro na cabe�a
    if(biblioteca->head_biblioteca == NULL)
    {
        //printf("D");
        criar->previous_livro = criar;
        criar->next_livro = criar;
        biblioteca->head_biblioteca = criar;
    }
    //SE a lista n�o estiver vazia, procura a �ltima posi��o para inserir o livro
    else
    {
        //printf("E");
        aux1 = biblioteca->head_biblioteca;

        do
        {
            aux1 = aux1->next_livro;
        }while(aux1!= biblioteca->head_biblioteca->previous_livro);

        //printf("F");
        criar->previous_livro = aux1->previous_livro->next_livro;
        criar->next_livro = biblioteca->head_biblioteca;
        aux1->previous_livro->next_livro->next_livro = criar;
        biblioteca->head_biblioteca->previous_livro = criar;
    }
}

void ImprimirDisponivel(Biblioteca *biblioteca)
{
    //Inicia aux com a cabe�a da biblioteca
    Livro *aux = biblioteca->head_biblioteca;

    //Percorre a biblioteca
    do
    {
        //Se o livro est� dispon�vel, imprime o livro
        if(aux->emprestado == 0)
        {
            ImprimirLivro(aux);
        }

        //Avan�a na lista
        aux = aux->next_livro;
    }while(aux != biblioteca->head_biblioteca);
}

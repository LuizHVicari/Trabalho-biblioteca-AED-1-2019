#include "Biblioteca.h"

//Cria a biblioteca
Biblioteca *CriarBiblioteca()
{
    //Aloca o espaço da lista
    Biblioteca *biblioteca = malloc (sizeof (Biblioteca));
    //A cabeça recebe NULL para indicar que não há nada na lista
    biblioteca->head_biblioteca = NULL;
    //A quantidade recebe 0
    biblioteca->quantidade = 0;

    //Retorna a biblioteca
    return biblioteca;
}

//Cria o livro e insere na biblioteca
void *CriarLivro (Biblioteca *biblioteca)
{
    //Cria a variável para escolher o genero do livro
    char opcao;

    //Cria e aloca o tamanho do livro
    Livro *livro = malloc (sizeof(Livro));

    //Insere o título do livro
    printf("Informe o título do livro: ");
    fflush(stdin);
    gets(livro->titulo);

    //Insere o ID do livro
    printf("Informe o ID do livro: ");
    scanf("%d", &livro->ID);

    //Insere o autor do livro
    printf("Informe o autor do livro: ");
    fflush(stdin);
    gets(livro->autor);

    //Abre a repetição para validar o gênero
    do
    {
        //Insere o gênero do livro
        printf("Qual o gênero do livro: \n");
        printf("A-) Drama\n");
        printf("B-) Ficção\n");
        printf("C-) Comédia\n");
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

    //Insere o gênero do livro
    switch (opcao)
    {
    case 'A':
        strcpy(livro->genero, "Drama");

        break;

    case 'B':
        strcpy(livro->genero, "Ficção");

        break;

    case 'C':
        strcpy(livro->genero, "Comédia");

        break;

    case 'D':
        strcpy(livro->genero, "Romance");

        break;

    default:

        break;
    }

    //Aumenta a quantidade de livros na biblioteca
    biblioteca->quantidade++;

    //O livro não está emprestado
    livro->emprestado = 0;

    //Inicia a lista de espera como vazia
    for(int i = 0; i < MAX_SIZE; i++)
    {
        livro->espera[i] = 0;
    }

    //Coloca o livro na lista e atualiza o arquivo binário
    InserirNaBiblioteca(livro, biblioteca);
    ExportarLivroParaArquivo (biblioteca);

    //system("cls");
}

//Função para buscar o livro por ID
//Retorna 1 se encontrar, 0 se não
int BuscarLivroID (int ID, Biblioteca *biblioteca)
{
    //Informa se a lista está vazia e retorna 0
    if(biblioteca == NULL)
    {
        printf("Não há livros cadastrados");
        return 0;
    }
    //passa a cabeça para um auxiliar
    Livro *aux = biblioteca->head_biblioteca;

    //Entra na repetição para percorrer a biblioteca
    do
    {
        if (aux->ID == ID)
        {
            //Imprime o livro e retorna 1 para achou
            ImprimirLivro(aux);
            return 1;
        }

        //Avança na biblioteca
        aux = aux->next_livro;
    }
    while(aux != biblioteca->head_biblioteca);

    //Retorna 0 se não encontrar
    printf("O livro não existe\n");
    return 0;
}

//Imprime o livro informado e suas informações
void ImprimirLivro(Livro *livro)
{
    //Informa o titulo
    printf("Título: ");
    puts(livro->titulo);

    //Informa o
    printf("Autor: ");
    puts(livro->autor);
    printf("Gênero: ");
    puts(livro->genero);
    printf("ID: %d\n", livro->ID);
}

//Lista os livros de maneira sequencial por gênero
void ListarLivroGenero(Biblioteca *biblioteca)
{
    //Chama a função de ordenar por gênero
    OrdenarLivroPorGenero(biblioteca);

    //Se não há nada na biblioteca, informa
    if (biblioteca == NULL)
    {
        printf("Não há livros cadastrados");
    }

    else
    {
        //Aux recebe a cabeça
        Livro *aux = biblioteca->head_biblioteca;
        //Variável para passar ou voltar na lista
        char opcao;

        do
        {
            //Chama a função de imprimir o arquivo
            ImprimirLivro(aux);

            do
            {
                //Pede se quer avançar ou voltar na lista
                printf("\nO que deseja fazer:");
                printf("\nD-) Avancar");
                printf("\nA-) Voltar");
                printf("\nJ-) Parar\n");
                fflush(stdin);
                scanf("%c", &opcao);

                //Transforma em maiúsculo
                if (opcao == 'd' || opcao == 'a' || opcao == 'j')
                {
                    opcao = toupper(opcao);
                }

                system("cls");

            }
            while (opcao != 'A' && opcao != 'D' && opcao != 'J');

            if(opcao == 'D')
            {
                //Avança na lista
                aux = aux->next_livro;
            }

            else if(opcao == 'A')
            {
                //Retrocede na lista
                aux = aux->previous_livro;
            }
            //Enquanto o usuário escolher ver a lista
        }
        while(opcao != 'J');
    }
}

//Lista os livros de maneira sequencial por ID
void ListarLivroID(Biblioteca *biblioteca)
{
    //Chama a função de ordenar
    OrdenarLivroPorID(biblioteca);

    //Se a lista for vazia, informa
    if (biblioteca == NULL)
    {
        printf("Não há livros cadastrados");
    }

    else
    {
        //Aux recebe a cabeça da lista
        Livro *aux = biblioteca->head_biblioteca;
        //Variável para passar a lista
        char opcao;

        do
        {
            //Imprime o livro
            ImprimirLivro(aux);

            do
            {
                //Pede qual opção realizar
                printf("\nO que deseja fazer:");
                printf("\nD-) Avancar");
                printf("\nA-) Voltar");
                printf("\nJ-) Parar\n");
                fflush(stdin);
                scanf("%c", &opcao);

                //Transforma em maiúscula
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
                //Avança na lista
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

//Muda as informações de um livro já cadastrado
int AtualizarLivro(Biblioteca *biblioteca, Leitores *leitores)
{
    //Essa função funciona de maneira parecida com a de CriarLivro
    //Porém, ela percorre a lista até encontrar o livro certo e não insere ele na lista de novo
    //Afinal, ele já está inserido nela
    int ID;
    char opcao, op;
    Livro *aux = biblioteca->head_biblioteca;

    //Pede qual o livro que será alterado
    printf("Informe o ID do livro que deseja atualizar: ");
    scanf("%d", &ID);

    //Percorre a lista até achar o livro
    do
    {
        //Se encontrar o livro, pede os novos dados
        if(ID == aux->ID)
        {
            printf("Título atual: ");
            puts(aux->titulo);
            printf("Deseja alterar? (S para sim): ");
            fflush(stdin);
            scanf("%c", &opcao);
            if(opcao == 's' || opcao == 'S')
            {
                printf("Informe o novo título: ");
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

            printf("Gênero atual: ");
            puts(aux->genero);
            printf("Deseja alterar? (S para sim): ");
            fflush(stdin);
            scanf("%c", &opcao);
            if(opcao == 's' || opcao == 'S')
            {
                do
                {
                    //Insere o gênero do livro
                    printf("Qual o gênero do livro: \n");
                    printf("A-) Drama\n");
                    printf("B-) Ficção\n");
                    printf("C-) Comédia\n");
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
                    strcpy(aux->genero, "Ficção");

                    break;

                case 'C':
                    strcpy(aux->genero, "Comédia");

                    break;

                case 'D':
                    strcpy(aux->genero, "Romance");

                    break;

                default:

                    break;
                }
            }

            //Atualiza o arquivo binário
            ExportarLivroParaArquivo (biblioteca);
            return 1;
        }
        //Avança na lista
        aux = aux->next_livro;

    }
    while(aux != biblioteca->head_biblioteca);

    //Se não encontrar, avisa e retorna 0
    printf("Não há livro com esse ID cadastrado\n");
    return 0;
}

//Ordena o catálogo por gênero , de acordo com o alfabeto
void OrdenarLivroPorGenero(Biblioteca *biblioteca)
{
    //Declaração das variáveis, inicia aux1 com a cabeça da lista
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

            //Se a posição for encontrada, coloca o livro no lugar
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

            //Avança aux2 na lista
            aux2 = aux2->next_livro;
        }
        //Avança aux1 na lista
        aux1 = aux1->next_livro;
    }
}

//Ordena o catálogo por ID (insetion sort)
void OrdenarLivroPorID(Biblioteca *biblioteca)
{
    //Funciona de maneira parecida com a ordenação por gênero, mas compara os IDs
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

//Insere um livro no catálogo
void InserirNaBiblioteca(Livro *livro, Biblioteca *biblioteca)
{
     //Valida para ver se é o primeiro livro da biblioteca
    if(biblioteca->head_biblioteca == NULL)
    {
        biblioteca->head_biblioteca = livro;
        livro->next_livro = livro;
        livro->previous_livro =livro;
    }

    //Se não for o primeiro, entra aqui
    else
    {
        biblioteca->head_biblioteca->previous_livro->next_livro = livro;
        livro->next_livro = biblioteca->head_biblioteca;
        livro->previous_livro = biblioteca->head_biblioteca->previous_livro;
        biblioteca->head_biblioteca->previous_livro = livro;
        biblioteca->head_biblioteca = livro;
    }
}

//Remove e libera o espaço dos livros da memória
//Eu e o Gustavo Alexandre elaboramos a função juntos
int RemoverLivro(Biblioteca *biblioteca)
{
    //Declara as variáveis
    Livro *aux;
    int ID;
    //Pede qual o Id do livro a ser removido
    printf("Informe o ID do livro que deseja buscar");
    scanf("%d", &ID);

    //Inicia aux com a cabeça
    aux = biblioteca->head_biblioteca;

    //Se só houver a cabeça na lista, remove, atualiza o arquivo e retorna 1
    if(aux->next_livro == aux)
    {
        free(aux);
        ExportarLivroParaArquivo (biblioteca);
        return 1;
    }

    //Se há mais ítens e a cabeça ai ser removida, entra aqui
    else if(ID == biblioteca->head_biblioteca->ID)
    {
        //Passa a cabeça para um auxiliar e altera os next_livro e previous_livro para remover o ítem
        //O próximo recebe um auxiliar
        aux = biblioteca->head_biblioteca;
        biblioteca->head_biblioteca = biblioteca->head_biblioteca->next_livro;
        biblioteca->head_biblioteca->previous_livro = aux->previous_livro;
        aux->previous_livro->next_livro = biblioteca->head_biblioteca;

        //Limpa o espaço do auxiliar e atualiza o arquivo binário
        free(aux);
        ExportarLivroParaArquivo (biblioteca);

        //Retorna 1
        return 1;
    }

    else
    {
        //Procura o arquivo, avançando na lista
        do
        {
            //Avança na lista
            aux = aux->next_livro;

        }while(aux != biblioteca->head_biblioteca && aux->ID != ID);

        //Se encontrar o livro entra aqui
        if(aux->ID == ID)
        {
            //Ajeita os next e previous
            aux->previous_livro->next_livro = aux->next_livro;
            aux->next_livro->previous_livro = aux->previous_livro;

            //Libera o espaço e atualiza o arquivo
            free(aux);
            ExportarLivroParaArquivo (biblioteca);

            return 1;
        }
    }

    //Se não encontrar, avisa e retorna 0
    printf("O livro nao está na biblioteca\n");
    return 0;
}

//Insere um livro vindo do arquivo binário na lista
void InserirBinLivro(Biblioteca *biblioteca, Livro livro)
{
    //Declaração de variáveis
    int i;
    //Aloca o espaço das variáveis
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

    //Se a lista está vazia, insere o novo livro na cabeça
    if(biblioteca->head_biblioteca == NULL)
    {
        //printf("D");
        criar->previous_livro = criar;
        criar->next_livro = criar;
        biblioteca->head_biblioteca = criar;
    }
    //SE a lista não estiver vazia, procura a última posição para inserir o livro
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
    //Inicia aux com a cabeça da biblioteca
    Livro *aux = biblioteca->head_biblioteca;

    //Percorre a biblioteca
    do
    {
        //Se o livro está disponível, imprime o livro
        if(aux->emprestado == 0)
        {
            ImprimirLivro(aux);
        }

        //Avança na lista
        aux = aux->next_livro;
    }while(aux != biblioteca->head_biblioteca);
}

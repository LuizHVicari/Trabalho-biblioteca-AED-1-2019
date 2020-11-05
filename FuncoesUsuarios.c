#include "Biblioteca.h"

//Cria a lista de leitores
//****Usa só no começo da execucao
Leitores *CriarLeitores()
{
    //Aloca o espaço de memória
    Leitores *leitores = malloc (sizeof (Leitores));
    //Coloca a cabeça como nula
    leitores->head_leitor = NULL;

    return leitores;
}

//Cria o leitor e o cadastra
void *CriarLeitor (Leitores *leitores)
{
    //Cria e aloca o tamanho do livro
    Leitor *leitor = malloc(sizeof(Leitor));

    //Insere o título do livro
    printf("Informe nome do usuário: ");
    fflush(stdin);
    gets(leitor->nome);

    //Insere o ID do livro
    printf("Informe o RA do usuário: ");
    scanf("%d", &leitor->RA);

    //Define o valor como zero (não emprestou nada)
    leitor->livros_emprestados = 0;

    //Insere o usuário na lista
    InserirNosLeitores(leitor, leitores);

    //Passa os dados para o arquivo
    ExportarLeitorParaArquivo(leitores);

    //Limpa a tela
    system("cls");
}

//Função para buscar o livro por ID
//Retorna 1 se encontrar, 0 se não
int BuscarUsuarioRA(int RA, Leitores *leitores)
{
    //Vê se a lista está vazia
    if (leitores->head_leitor == NULL)
    {
        //Informa que não há usuários
        printf("Não há leitores cadastrados\n");
        //Retorna 0 (não encontrou)
        return 0;
    }

    //passa a cabeça para um auxiliar
    Leitor *aux = leitores->head_leitor;

    //Entra na repetição para percorrer a lista de usuarios
    do
    {
        //Vê se o usuário é o buscado pelo ID
        if (aux->RA == RA)
        {
            //Imprime e retorna 1 para encontrou
            ImprimirLeitor(aux);
            return 1;
        }

        //Avança na lista
        aux = aux->next_leitor;

        //Vai até o fim da lista
    }
    while(aux != leitores->head_leitor);
    //Retorna 0 se não encontrar e informa
    printf("O usuário não existe\n");
    return 0;
}

//Imprime o livro informado e suas informações
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
    //Chama a ordenação por RA
    OrdenarUsuarioPorRA(leitores);

    //Verifica se a lista não está vazia
    if (leitores == NULL)
    {
        //Informa que a lista está vazia
        printf("Não há usuários cadastrados");
    }

    else
    {
        //Passa a cabeça da lista para um auxiliar
        Leitor *aux = leitores->head_leitor;

        //Varável para as opções
        char opcao;

        do
        {
            //Imprime os dados do leitor
            ImprimirLeitor(aux);

            do
            {
                //Menu de opções para passar na lista
                printf("\nO que deseja fazer:");
                printf("\nD-) Avancar");
                printf("\nA-) Voltar");
                printf("\nJ-) Parar\n");
                fflush(stdin);
                scanf("%c", &opcao);

                //Covnerte para maiúsculo
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

//Ordena a lista de usuários pelo RA
int OrdenarUsuarioPorRA(Leitores *leitores)
{
    //Valida para ver se tem algo na lista
    if (leitores == NULL)
    {
        //Avisa que está vazia e retorna 0
        printf("Não há usuários cadastrados\n");
        return 0;
    }

    //Declara as variáveis auxiliares
    Leitor *aux1 = leitores->head_leitor->next_leitor, *aux2, *aux3;

    //Fim do while quando percorrer toda a lista
    while (aux1 != leitores->head_leitor)
    {
        //aux2 recebe a cabeça
        aux2 = leitores->head_leitor;

        //Fim do while quando os aux forem iguais
        while(aux2 != aux1)
        {
            //Valida se o RA de aux1 é maior que o de aux 2
            if (aux1->RA < aux2->RA)
            {
                //Faz a troca de posição das structs Leitor
                aux3 = aux1->previous_leitor;
                aux1->previous_leitor->next_leitor = aux1->next_leitor;
                aux1->next_leitor->previous_leitor = aux1->previous_leitor;
                aux2->previous_leitor->next_leitor = aux1;
                aux1->previous_leitor = aux2->previous_leitor;
                aux1->next_leitor = aux2;

                //Valida se o aux2 chegou na cabeça
                if(aux2 == leitores->head_leitor)
                    leitores->head_leitor = aux1;

                aux1 = aux3;
                aux2 = aux1->previous_leitor;
            }

            //Avança o aux2
            aux2 = aux2->next_leitor;
        }
        //Avança o aux1
        aux1 = aux1->next_leitor;
    }

    //Retorna 1 para sucesso
    return 1;
}

//Muda algum dado do cadastro do leitor
int AtualizarLeitor(Leitores *leitores)
{
    //Valida se a lista é nula
    if (leitores->head_leitor == NULL)
    {
        //Avisa e retorna 0
        printf("Não há usuários cadastrados\n");
        return 0;
    }

    //Declaração das variáveis
    int RA;
    char opcao;
    //Inicia aux com a cabeça
    Leitor *aux = leitores->head_leitor;

    //Pede qual o RA para ser atualizado
    printf("Informe o RA do usuário que deseja atualizar: ");
    scanf("%d", &RA);

    //Percorre a lista até achar o RA certo
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
            //Valida a opção
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
            //Valida a opção
            if(opcao == 's' || opcao == 'S')
            {
                //Troca o RA
                printf("Informe o novo RA: ");
                scanf("%d", &aux->RA);
            }

            //Passa os novos dados para o arquivo binário e retorna 1
            ExportarLeitorParaArquivo(leitores);
            return 1;
        }
        aux = aux->next_leitor;

    }
    while(aux != leitores->head_leitor);

    //Se o RA não foi encontrado, ele avisa e retorna 0
    printf("Não ha usuário com esse RA cadastrado");
    return 0;
}

//Insere um leitor na lista de usuários
void InserirNosLeitores(Leitor *leitor, Leitores *leitores)
{
    //Valida para ver se é o primeiro livro da biblioteca
    if(leitores->head_leitor == NULL)
    {
        //printf("Primeiro livro cadastrado");
        leitores->head_leitor = leitor;
        leitor->next_leitor = leitor;
        leitor->previous_leitor =leitor;
    }

    //Se não for o primeiro, entra aqui
    else
    {
        leitores->head_leitor->previous_leitor->next_leitor = leitor;
        leitor->next_leitor = leitores->head_leitor;
        leitor->previous_leitor = leitores->head_leitor->previous_leitor;
        leitores->head_leitor->previous_leitor = leitor;
        leitores->head_leitor = leitor;
    }
}

//Remove e libera o espaço dos leitores da memória
//Eu e o Gustavo Alexandre elaboramos a função juntos
int RemoverUsuario(Leitores *leitores)
{
    //Declaração das variáveis
    Leitor *aux;
    int RA;
    //Pede qual o usuário a ser removido
    printf("Informe o RA do usuário que deseja buscar");
    scanf("%d", &RA);

    //Inicia o auxiliar com a cabeça
    aux = leitores->head_leitor;

    //Se o leitor for o único cadastrado
    if(aux->next_leitor == aux)
    {
        //Libera o espaço e atualiza o arquivo binário
        free(aux);
        ExportarLeitorParaArquivo(leitores);

        //Retorna 1
        return 1;
    }

    //Se tiver mais de um leitor na lista e a cabeça vai ser removida
    else if(RA == leitores->head_leitor->RA)
    {
        //Muda a cabeça e altera os next_leitor e previous_anterior para tirar o aux
        aux = leitores->head_leitor;
        leitores->head_leitor = leitores->head_leitor->next_leitor;
        leitores->head_leitor->previous_leitor = aux->previous_leitor;
        aux->previous_leitor->next_leitor = leitores->head_leitor;

        //Libera o aux e atualiza o binário
        free(aux);
        ExportarLeitorParaArquivo(leitores);

        //Retorna 1
        return 1;
    }

    //Se o RA não estiver na cabeça
    else
    {
        //Percorre a lista até achar o leitor
        do
        {
            //Avança na lista
            aux = aux->next_leitor;

        }while(aux != leitores->head_leitor && aux->RA != RA);

        //Se encontrar
        if(aux->RA == RA)
        {
            //Altera os previous e next para remover o auxiliar
            aux->previous_leitor->next_leitor = aux->next_leitor;
            aux->next_leitor->previous_leitor = aux->previous_leitor;

            //Libera o auxiliar e atualiza o arquivo binário
            free(aux);
            ExportarLeitorParaArquivo(leitores);

            //Retorna 1
            return 1;
        }
    }

    //Se não encontrar o usuário, avisa e retorna 0
    printf("O livro nao está na biblioteca\n");
    return 0;
}

//Insere o usuário do arquivo binario
void InserirBinLeitor(Leitores *leitores, Leitor leitor)
{
    //Declaração de variáveis
    int i;
    //Inicia os leitores
    Leitor *criar = malloc(sizeof(Leitor)), *aux1 = malloc(sizeof(Leitor));

    //Copia os dados no novo leitor
    strcpy(criar->nome, leitor.nome);
    criar->RA = leitor.RA;
    criar->livros_emprestados = leitor.livros_emprestados;

    //Se não houver nada na lista
    if(leitores->head_leitor == NULL)
    {
        //A cabeça, o anterior e o próximo recebem o novo leitor
        criar->previous_leitor = criar;
        criar->next_leitor = criar;
        leitores->head_leitor = criar;
    }
    else
    {
        //O auxiliar recebe a cabeça
        aux1 = leitores->head_leitor;

        //Percorre a lista até achar a última posição
        do
        {
            aux1 = aux1->next_leitor;
        }while(aux1!= leitores->head_leitor->previous_leitor);

        //Coloca o arquivo na última posição da lista
        criar->previous_leitor = aux1->previous_leitor->next_leitor;
        criar->next_leitor = leitores->head_leitor;
        aux1->previous_leitor->next_leitor->next_leitor = criar;
        leitores->head_leitor->previous_leitor = criar;
    }
}

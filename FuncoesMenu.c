#include "Biblioteca.h"

//Menu geral
int MenuGeral(Biblioteca *biblioteca, Leitores *leitores)
{
    system("cls");

    //Vari�vel para o switch case
    char opcao;

    //Valida��o para o switch case
    do
    {
        //Mostra as op��es dispon�veis
        printf("Deseja ver as op��es de: \n");
        printf("A -) Menu de livros\n");
        printf("B -) Menu de usu�rios\n");
        printf("C -) Menu de empr�stimos\n");
        fflush(stdin);
        scanf("%c", &opcao);

        //Valida para entrar no switch case (mai�sculo)
        if (opcao == 'a' || opcao == 'b' || opcao == 'c')
        {
            opcao = toupper(opcao);
        }
    }
    while (opcao != 'A' && opcao != 'B' && opcao != 'C');

    switch (opcao)
    {

    //Cadastro de livros
    case 'A':

        MenuLivros(biblioteca, leitores);

        break;

    //Menu das fun��es de usu�rio
    case 'B':

        MenuUsuario(biblioteca, leitores);

        break;

    //Menu das fun��es de espera
    case 'C':

        MenuEspera(biblioteca, leitores);

        break;
    }

    return 0;
}
//Menu de opcoes para trabalhar com livros
int MenuLivros(Biblioteca *biblioteca, Leitores *leitores)
{
    system("cls");

    //Vari�vel para o switch case
    char opcao;

    //Valida��o para o switch case funcionar
    do
    {
        //Mostra as op��es do menu de livros
        printf("Deseja ver as opcoes de: \n");
        printf("A -) Cadastrar livro no cat�logo\n");
        printf("B -) Procurar livro ID\n");
        printf("C -) Listar todos os livros\n");
        printf("D -) Listar livros por g�nero\n");
        printf("E -) Atualizar cadastro do livro\n");
        printf("F -) Remover livro do cat�logo\n");
        printf("G -) Menu de empr�stimos\n");
        printf("H -) Voltar para o menu anterior\n");

        fflush(stdin);
        scanf("%c", &opcao);

        //Converte para mai�sculo
        if (opcao == 'a' || opcao == 'b' || opcao == 'c' || opcao == 'd' || opcao == 'e' || opcao == 'f' || opcao == 'g' || opcao == 'h')
        {
            opcao = toupper(opcao);
        }

       system("cls");

    }
    while (opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != 'D' && opcao != 'E' && opcao != 'F' && opcao != 'G' && opcao != 'H');

    switch (opcao)
    {

    //Cadastro de livros
    case 'A':

        CriarLivro(biblioteca);

        break;

    //Busca por livro
    case 'B':

        MenuBuscaLivro(biblioteca);

        break;

    //Listar os livros por ID
    case 'C':

        ListarLivroID(biblioteca);

        break;

    //Listar os livros pelo g�nero
    case 'D':

        ListarLivroGenero(biblioteca);

        break;

    //Atualizar o cadastro do livro
    case 'E':

        AtualizarLivro(biblioteca, leitores);

        break;

    //Remover livro
    case 'F':

        RemoverLivro(biblioteca);

        break;

        //Volta para o menu anterior
    case 'G':

        MenuEspera(biblioteca, leitores);

    //Voltar para o menu
    case 'H':

        MenuGeral(biblioteca, leitores);

        break;
    }

    return 0;
}

//Menu de opcoes para trabalhar com usuarios
int MenuUsuario(Biblioteca *biblioteca, Leitores *leitores)
{
    //Limpa a tela
    system("cls");
    //Declaracao de variaveis
    char opcao;

    //Validacao para o switch case funcionar
    do
    {
        //Mostra as op��es do menu para fun��es de usu�rio
        printf("Deseja ver as op��es de: \n");
        printf("A -) Cadastrar usu�rio\n");
        printf("B -) Procurar usu�rio\n");
        printf("C -) Listar todos os usu�rios\n");
        printf("D -) Atualizar cadastro de usu�rio\n");
        printf("E -) Remover usu�rio\n");
        printf("F -) Voltar para o menu anterior\n");

        fflush(stdin);
        scanf("%c", &opcao);

        //Valida para trabalhar com min�sculas
        if (opcao == 'a' || opcao == 'b' || opcao == 'c' || opcao == 'd' || opcao == 'e' || opcao == 'f')
        {
            //Converte para maiuscula
            opcao = toupper(opcao);
        }

        //Limpa a tela
        system("cls");
    }
    while (opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != 'D' && opcao != 'E' && opcao != 'F');

    //Acesso �s fun��es
    switch (opcao)
    {
    //Cadastro de usuario
    case 'A':

        CriarLeitor(leitores);

        break;

    //Busca por usu�rio
    case 'B':

        MenuBuscaUsuario(leitores);

        break;

    //Listar os usu�rios por RA
    case 'C':

        ListarLeitoresRA(leitores);

        break;

    //Atualizar o cadastro do usuario
    case 'D':

        AtualizarLeitor(leitores);

        break;

    //Remover usuario
    case 'E':

        RemoverUsuario(leitores);

        break;

    //Voltar para o menu
    case 'F':

        MenuGeral(biblioteca, leitores);

        break;
    }

    return 0;
}

//Menu para passar as informa��es para a busca de livro
void MenuBuscaLivro(Biblioteca *biblioteca)
{
    system("cls");
    int ID;

    printf("Informe o ID do livro:\n");
    scanf("%d", &ID);
    BuscarLivroID(ID, biblioteca);
}

//Menu para passar as informa��es para a busca de usu�rio
void MenuBuscaUsuario(Leitores *leitores)
{
    system("cls");
    int RA;

    printf("Informe o RA do usu�rio:\n");
    scanf("%d", &RA);
    BuscarUsuarioRA(RA, leitores);
}

/*Menu para recepcionar o programador
void MenuEntrada()
{
    //system("cls");

    printf("Bem vindo, gerenciador\n");
    //printf("Pressione alguma tecla para continuar");
    system("pause");
}*/

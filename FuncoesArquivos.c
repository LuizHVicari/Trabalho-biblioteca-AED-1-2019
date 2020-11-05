#include "Biblioteca.h"

//Função para trazer os dados do arquivo binário para as listas
void ImportarDoArquivo(Biblioteca *biblioteca, Leitores *leitores)
{
    //Abre os dois arquivos
    FILE *file1 = fopen("livro.dat", "rb");
    FILE *file2 = fopen("usuario.dat", "rb");
    Livro livro;
    Leitor leitor;
    int controle;

    //Lê o arquivo com os dados dos livros
    do
    {
        controle = fread(&livro, sizeof(Livro), 1, file1);

        if(controle == 1)
        {
            //Insere o livro na lista
            InserirBinLivro(biblioteca, livro);
        }
    }
    while(!feof(file1));

    //Lê o arquivo com os dados dos usuários
    do
    {
        controle = fread(&leitor, sizeof(Leitor), 1, file2);

        if(controle == 1)
        {
            //Insere o usuário na lista
            InserirBinLeitor(leitores, leitor);
        }
        //Vai até o fim do arquivo
    }
    while(!feof(file2));

    //Fecha os arquivos
    fclose(file1);
    fclose(file2);
}

//Passa os dados do livro para o arquivo
void ExportarLivroParaArquivo(Biblioteca *biblioteca)
{
    //Abre o arquivo dos livros
    FILE *file = fopen("livro.dat", "wb");
    Livro *aux;

    //Vê se a biblioteca é nula
    if(biblioteca->head_biblioteca != NULL)
    {
        aux = biblioteca->head_biblioteca;
    }
    //Se for nula, ele informa
    else
    {
        printf("/Não há nada na biblioteca");
    }

    do
        {
            //Escreve no arquivo
            fwrite(aux, sizeof(Livro), 1, file);
            //Passa para o próximo livro
            aux = aux->next_livro;

            //vai até o "início"/"fim" da biblioteca
        }
        while(aux != biblioteca->head_biblioteca);
}

//Passa os dados dos usuários para o arquivo
void ExportarLeitorParaArquivo (Leitores *leitores)
{
    //Abre o arquivo dos usuários
    FILE *file = fopen("usuario.dat", "wb");
    Leitor *aux;

    //Verifica se a lista está vazia
    if(leitores->head_leitor != NULL)
    {
        aux = leitores->head_leitor;


    }

    //Se estiver vazia, avisa o usuário
    else
    {
        printf("/Não há nada nos usuários");
    }

    do
        {
            //Escreve no arquivo
            fwrite(aux, sizeof(Leitor), 1, file);
            //Passa para o próximo usuário
            aux = aux->next_leitor;

            //Vai até o "início"/"fim" do arquivo
        }
        while(aux != leitores->head_leitor);
}

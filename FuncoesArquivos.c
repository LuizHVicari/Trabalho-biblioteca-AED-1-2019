#include "Biblioteca.h"

//Fun��o para trazer os dados do arquivo bin�rio para as listas
void ImportarDoArquivo(Biblioteca *biblioteca, Leitores *leitores)
{
    //Abre os dois arquivos
    FILE *file1 = fopen("livro.dat", "rb");
    FILE *file2 = fopen("usuario.dat", "rb");
    Livro livro;
    Leitor leitor;
    int controle;

    //L� o arquivo com os dados dos livros
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

    //L� o arquivo com os dados dos usu�rios
    do
    {
        controle = fread(&leitor, sizeof(Leitor), 1, file2);

        if(controle == 1)
        {
            //Insere o usu�rio na lista
            InserirBinLeitor(leitores, leitor);
        }
        //Vai at� o fim do arquivo
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

    //V� se a biblioteca � nula
    if(biblioteca->head_biblioteca != NULL)
    {
        aux = biblioteca->head_biblioteca;
    }
    //Se for nula, ele informa
    else
    {
        printf("/N�o h� nada na biblioteca");
    }

    do
        {
            //Escreve no arquivo
            fwrite(aux, sizeof(Livro), 1, file);
            //Passa para o pr�ximo livro
            aux = aux->next_livro;

            //vai at� o "in�cio"/"fim" da biblioteca
        }
        while(aux != biblioteca->head_biblioteca);
}

//Passa os dados dos usu�rios para o arquivo
void ExportarLeitorParaArquivo (Leitores *leitores)
{
    //Abre o arquivo dos usu�rios
    FILE *file = fopen("usuario.dat", "wb");
    Leitor *aux;

    //Verifica se a lista est� vazia
    if(leitores->head_leitor != NULL)
    {
        aux = leitores->head_leitor;


    }

    //Se estiver vazia, avisa o usu�rio
    else
    {
        printf("/N�o h� nada nos usu�rios");
    }

    do
        {
            //Escreve no arquivo
            fwrite(aux, sizeof(Leitor), 1, file);
            //Passa para o pr�ximo usu�rio
            aux = aux->next_leitor;

            //Vai at� o "in�cio"/"fim" do arquivo
        }
        while(aux != leitores->head_leitor);
}

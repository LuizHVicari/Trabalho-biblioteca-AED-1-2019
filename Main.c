#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include "Biblioteca.h"

//Trabalho do aluno Luiz Henrique Birck Vicari, feito com o auxílio dos colegas: Cinglair Capello, Gustavo Alexandre
//Nunes, Daniel Favero e Jeferson Rosa
//No trabalho, foi considerado 0 como falso e 1 como verdadeiro

//Disciplina: Algorítimos 1

int main (void)
{
    //Define os padrões do aplicativo e libera os acentos
    system("color F1");
    setlocale(LC_ALL, "portuguese");

    //Variável para usar na repetição
    char continuar, ex;

    //Valida para criar os arquivos binários que armazenam as informações
    printf("Essa é a primeira execução do programa? (S para sim): ");
    fflush(stdin);
    scanf("%c", &ex);
    if(ex == 'S' || ex == 's')
    {
        FILE *file1 = fopen("usuario.dat", "wb");
        FILE *file2 = fopen("livro.dat", "wb");

        fclose(file1);
        fclose(file2);
    }

    //Cria as duas listas
    Biblioteca *biblioteca = CriarBiblioteca();
    Leitores *leitores = CriarLeitores();

    //Abre dois arquivos para ver se o aruivo existe
    FILE *file1 =fopen("livro.dat", "r"), *file2 = fopen("usuario.dat", "r");

    //Chama os dados dos arquivos binários
    ImportarDoArquivo (biblioteca, leitores);

    //Inicia o menu com a repetição
    do
    {
        //Chama o menu geral
        MenuGeral(biblioteca, leitores);


        printf("Deseja continuar? (S para sim)");
        fflush(stdin);
        scanf("%c", &continuar);

    }
    while(continuar == 's' | continuar == 'S');

    return 0;
}

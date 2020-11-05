#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#define MAX_SIZE 100

typedef struct Livro Livro;
typedef struct Biblioteca Biblioteca;
typedef struct Leitor Leitor;
typedef struct Leitores Leitores;
typedef struct Fila_de_Espera Fila_de_Espera;
typedef struct Leitor_fila Leitor_fila;

struct Livro
{
    char titulo[MAX_SIZE];
    char autor[MAX_SIZE];
    char genero[MAX_SIZE];
    int ID;
    int espera[MAX_SIZE];
    int emprestado;
    Livro *next_livro;
    Livro *previous_livro;
};

struct Biblioteca
{
    Livro *head_biblioteca;
    int quantidade;
};

struct Leitor
{
    char nome[MAX_SIZE];
    int RA;
    int livros_emprestados;
    Leitor *next_leitor;
    Leitor *previous_leitor;
};

struct Leitores
{
    Leitor *head_leitor;
};

//Funções para menu
int MenuGeral(Biblioteca *biblioteca, Leitores *leitores);
int MenuLivros(Biblioteca *biblioteca, Leitores *leitores);
int MenuUsuario(Biblioteca *biblioteca, Leitores *leitores);
void MenuBuscaLivro(Biblioteca *biblioteca);
void MenuBuscaUsuario(Leitores *leitores);

//Funções para livros
Biblioteca *CriarBiblioteca();
void *CriarLivro (Biblioteca *biblioteca);
int BuscarLivroID (int ID, Biblioteca *biblioteca);
void ImprimirLivro(Livro *livro);
void ListarLivroGenero(Biblioteca *biblioteca);
void ListarLivroID(Biblioteca *biblioteca);
int AtualizarLivro(Biblioteca *biblioteca, Leitores *leitores);
void OrdenarLivroPorGenero(Biblioteca *biblioteca);
void OrdenarLivroPorID(Biblioteca *biblioteca);
void InserirNaBiblioteca(Livro *livro, Biblioteca *biblioteca);
int RemoverLivro(Biblioteca *biblioteca);
void InserirBinLivro(Biblioteca *biblioteca, Livro livro);
void ImprimirDisponivel(Biblioteca *biblioteca);

//Funções para usuários
Leitores *CriarLeitores();
void *CriarLeitor (Leitores *leitores);
int BuscarUsuarioRA(int RA, Leitores *leitores);
void ImprimirLeitor(Leitor *leitor);
void ListarLeitoresRA(Leitores *leitores);
int OrdenarUsuarioPorRA(Leitores *leitores);
int AtualizarLeitor(Leitores *leitores);
void InserirNosLeitores(Leitor *leitor, Leitores *leitores);
int RemoverUsuario(Leitores *leitores);
void InserirBinLeitor(Leitores *leitores, Leitor leitor);

//Funções da lista de espera
int InserirEspera(int RA, Livro *livro, Leitores *leitores);
int RetirarDaEspera(int RA, Livro *livro, Leitores *leitores);
void OrdenarEspera(Livro *livro);
void ImprimirEspera(Livro *livro);
void EmprestarLivro(int RA, Livro *livro, Leitores *leitores, Biblioteca *biblioteca);
void DevolverLivro (int RA, Livro *livro, Leitores *leitores, Biblioteca *biblioteca);
int MenuEspera(Biblioteca *biblioteca, Leitores *leitores);
void AumentarEmprestado (Leitores *leitores, int RA);
void DiminuirEmprestado (Leitores *leitores, int RA);

//Funções de arquivos
void ImportarDoArquivo(Biblioteca *biblioteca, Leitores *leitores);
void ExportarLivroParaArquivo(Biblioteca *biblioteca);
void ExportarLeitorParaArquivo (Leitores *leitores);

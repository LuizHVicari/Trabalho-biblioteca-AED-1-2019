# Trabalho-biblioteca-AED-1-2019
Trabalho de sistema de gerenciamento de bibliotecas, feito para a matéria de Algoritmos e Estrutura de Dados 1, no segundo semestre de 2019

Informações gerais:

O objetivo do trabalho era criar uma espécie de programa que permitisse que um usuário pudesse colocar dados de livros e de alunos, que pudesse visualizar eles em ordem de registro e em ordem alfabética, remover e salvar no computador. A principal ideia do trabalho era aplicar os conhecimentos de lista (nesse caso, usamos listas circulares duplamente encadeada, pois facilitaria a navegação), algoritmos de ordenação e de salvar os dados nas memórias do computador. O trabalho foi desenvolvido no fim do meu segundo semestre da faculdade, em 2019, e para fazer ele tive ajuda do meu professor: Jefferson Tales Oliva, e de alguns colegas, principalmente: Gustavo Alexandre Nunes, Daniel Gustavo Favero, Cinglair Augusto Capello e Jeferson Souza.

Quem quiser, pode se sentir livre para se inspirar nas funções aqui utilizadas para criar seus próprios projetos, porém aconselho a não fazer um simples copiar e colar, mas entender a lógica por trás dos exercícios.

Sobre cada página do aplicativo:

Biblioteca.h: é o cabeçalho, lá constam todas as funções para poder criar elas na ordem que eu quisesse, separadas por suas devidas utilizações no código
FuncoesArquivos.c: são as funções para ler e escrever os dados do programa na memória do computador.
FuncoesListaEspera.c: são as funções que manipulam a lista de espera para cada livro.
FuncoesLivros.c: criam, ordenam e permitem a visualização dos dados dos livros.
FuncoesMenu.c: são os menus que permitem que o usuário interaja com o programa.
FuncoesUsuarios.c: mesma coisa que o FuncoesLivros.c, porém com os dados de usários.
Main.c: a main que chama os menus.

Eu tentei comentar os códigos para que eles ficassem de fácil compreensão, porém quaisquer dúvidas ou erros encontrados, pode me enviar um e-mail em: ikvicari@gmail.com que eventualmente devo responder.

Obs: nesse trabalho tirei 75 pontos de 100, pois o programa foi testado em um computador usando Linux, então perdi pontos pois não rodou nesse sistema, porém nos meus testes usando Windows 10, ele rodou tranquilamente.

/*
*Propriedade de Andre Garrido Damaceno.
*mat. 15/0117531.
*/

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Arvore.h"
#include "Funcs.h"
#include "Vinte_Perguntas.h"

TEST_CASE( "Creating a tree from user input", "Prove that the tree is created" )
{
  arvore *ainicio;
  char pai[4] = "PAI";
  printf("\n\n******************************************************************\n");
  printf("SIGA AS INSTRUÇÕES EM CAIXA ALTA PARA QUE OS TESTES DEEM CERTO!!!\n");
  printf("******************************************************************\n");
  printf("\n\n******************************************************************\n");
  printf("DIGITE 'SAIR' PARA O TESTE DAR CERTO\n");
  printf("******************************************************************\n");
  Constroi_Manual(&ainicio,pai,0);
  REQUIRE( ainicio == NULL );
  printf("\n******************************************************************\n");
  printf("AGORA DIGITE QUALQUER COISA VALIDA, DEPOIS 'SAIR' 2 VEZES\n");
  printf("******************************************************************\n");
  Constroi_Manual(&ainicio,pai,0);
  REQUIRE( ainicio != NULL );
  REQUIRE( ainicio->sim == NULL );
  REQUIRE( ainicio->nao == NULL );
  printf("\n******************************************************************\n");
  printf("AGORA DIGITE QUALQUER COISA VALIDA, DEPOIS ALGO VALIDO E DEPOIS 'SAIR' 3 VEZES\n");
  printf("******************************************************************\n");
  Constroi_Manual(&ainicio,pai,0);
  REQUIRE( ainicio != NULL );
  REQUIRE( ainicio->sim != NULL );
  REQUIRE( ainicio->sim->sim == NULL );
  REQUIRE( ainicio->sim->nao == NULL );
  REQUIRE( ainicio->nao == NULL );
  printf("\n******************************************************************\n");
  printf("AGORA DIGITE QUALQUER COISA VALIDA, DEPOIS 'SAIR', DEPOIS ALGO VALIDO, DEPOIS 'SAIR' 2 VEZES'\n");
  printf("******************************************************************\n");
  Constroi_Manual(&ainicio,pai,0);
  REQUIRE( ainicio != NULL );
  REQUIRE( ainicio->sim == NULL );
  REQUIRE( ainicio->nao->sim == NULL );
  REQUIRE( ainicio->nao->nao == NULL );
  REQUIRE( ainicio->nao != NULL );
  printf("\n******************************************************************\n");
  printf("AGORA DIGITE QUALQUER COISA VALIDA, DEPOIS ALGO VALIDO, DEPOIS 'SAIR' 2 VEZES' DEPOIS ALGO VALIDO, DEPOIS 'SAIR' 2 VEZES'\n");
  printf("******************************************************************\n");
  Constroi_Manual(&ainicio,pai,0);
  REQUIRE( ainicio != NULL );
  REQUIRE( ainicio->sim != NULL );
  REQUIRE( ainicio->sim->sim == NULL );
  REQUIRE( ainicio->sim->nao == NULL );
  REQUIRE( ainicio->nao != NULL );
  REQUIRE( ainicio->nao->sim == NULL );
  REQUIRE( ainicio->nao->nao == NULL );
}

TEST_CASE( "Creating a tree from a file", "Prove that the tree is created" )
{
  arvore *ainicio;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/Perguntas.txt", "r");
  Constroi_TXT(&ainicio,arq);
  REQUIRE( ainicio != NULL );
  REQUIRE( strcmp(ainicio->Pergunta, "O objeto a ser descoberto é um aviao?") == 0);
  REQUIRE( strcmp(ainicio->sim->Pergunta, "O objeto é um abacaxi?") == 0);
  REQUIRE( strcmp(ainicio->nao->Pergunta, "O objeto é de comer?") == 0);
  REQUIRE( ainicio->sim->sim == NULL);
  REQUIRE( ainicio->sim->nao == NULL);
  REQUIRE( ainicio->nao->sim == NULL);
  REQUIRE( ainicio->nao->nao == NULL);
  fclose(arq);
}

TEST_CASE( "Trying to create a tree from an non existing file", "Prove that the tree is not created" )
{
  arvore *ainicio;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/naoexiste.txt", "r");
  Constroi_TXT(&ainicio,arq);
  REQUIRE( ainicio == NULL );
}

TEST_CASE ("Trying to navigate to save a NULL tree to file", "Prove that the txt saves '.'")
{
  arvore *ainicio = NULL;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/NullTree.txt","w");
  Salva_TXT(&ainicio,arq);
  fclose(arq);
  arq = fopen("./Arquivos_de_teste/NullTree.txt","r");
  Constroi_TXT(&ainicio,arq);
  fclose(arq);
  REQUIRE(ainicio == NULL);
}

TEST_CASE ("Saving a tree to file", "Prove that the txt saves the tree")
{
  arvore *ainicio = NULL;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/Perguntas.txt","r");
  Constroi_TXT(&ainicio,arq);
  fclose(arq);
  arq = fopen("./Arquivos_de_teste/Perguntas2.txt","w");
  Salva_TXT(&ainicio,arq);
  fclose(arq);
  arq = fopen("./Arquivos_de_teste/Perguntas2.txt","r");
  Constroi_TXT(&ainicio,arq);
  fclose(arq);
  REQUIRE( ainicio != NULL );
  REQUIRE( strcmp(ainicio->Pergunta, "O objeto a ser descoberto é um aviao?") == 0);
  REQUIRE( strcmp(ainicio->sim->Pergunta, "O objeto é um abacaxi?") == 0);
  REQUIRE( strcmp(ainicio->nao->Pergunta, "O objeto é de comer?") == 0);
  REQUIRE( ainicio->sim->sim == NULL);
  REQUIRE( ainicio->sim->nao == NULL);
  REQUIRE( ainicio->nao->sim == NULL);
  REQUIRE( ainicio->nao->nao == NULL);
}

TEST_CASE ("Saving tree to NULL file", "Prove that the function does nothing and contains the program")
{
  arvore *ainicio;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/naoexiste.txt", "r");
  Constroi_TXT(&ainicio,arq);
  REQUIRE(ainicio == NULL);
}

TEST_CASE ("Freeing an existing tree", "the tree is freed")
{
  arvore *ainicio = NULL;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/Perguntas.txt","r");
  Constroi_TXT(&ainicio,arq);
  fclose(arq);
  REQUIRE(ainicio != NULL);
  Desconstroi(&ainicio);
  REQUIRE(ainicio == NULL);
}

TEST_CASE ("Freeing a NULL tree", "the program is contained")
{
  arvore *ainicio = NULL;
  Desconstroi(&ainicio);
  REQUIRE(ainicio == NULL);
}

TEST_CASE("Reading a tree question", "tree is unmodified and question is read")
{
  arvore *ainicio = NULL;
  arvore *anterior;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/Perguntas.txt","r");
  Constroi_TXT(&ainicio,arq);
  fclose(arq);
  anterior = ainicio;
  Le(ainicio);
  REQUIRE(anterior == ainicio);
}

TEST_CASE("Trying to read NULL tree", "Program is contained and function does nothing")
{
  arvore *ainicio = NULL;
  arvore *anterior;
  anterior = ainicio;
  Le(ainicio);
  REQUIRE(anterior == ainicio);
}

TEST_CASE("Trying to navigate to '->sim' and '->nao' and reading the question", "Tree goes to specific navigation and reads the question")
{
  arvore *ainicio = NULL;
  arvore *navegasim, *naveganao, *ainiciobackup;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/Perguntas.txt","r");
  Constroi_TXT(&ainicio,arq);
  fclose(arq);
  navegasim = ainicio;
  naveganao = ainicio;
  ainiciobackup = ainicio;
  REQUIRE(navegasim != NULL);
  REQUIRE(naveganao != NULL);
  REQUIRE(ainicio != NULL);
  REQUIRE(ainicio == ainiciobackup);
  NavegaSim(&navegasim);
  NavegaNao(&naveganao);
  REQUIRE(navegasim == ainicio->sim);
  REQUIRE(naveganao == ainicio->nao);
  NavegaSim(&navegasim);
  NavegaNao(&naveganao);
  REQUIRE(navegasim == NULL);
  REQUIRE(naveganao == NULL);
}

TEST_CASE("Trying to navigate to '->sim' and '->nao' whith NULL tree", "Program is contained and function returns 2")
{
  arvore *ainicio = NULL;
  arvore *navegasim, *naveganao;
  navegasim = ainicio;
  naveganao = ainicio;
  NavegaSim(&navegasim);
  NavegaNao(&naveganao);
  REQUIRE(navegasim == NULL);
  REQUIRE(naveganao == NULL);
}

TEST_CASE("Creating/Opening a file (read) and (write)", "Function opens/creates the file")
{
  arvore *ainicio=NULL;
  char abrirP[28] = "Aberto (DIGITE 'teste.txt')";
  char abrirE[30] = "Aberto (DIGITE 'escreve.txt')";
  char Escrever[31] = "Escrito (DIGITE 'escreve.txt')";
  char qlqr[57] = "aberto - (DIGITE QUALQUER COISA QUE NAO SEJA UM ARQUIVO)";
  char r[2] = "r";
  char w[2] = "w";
  FILE *arq;
  arq = CriaArquivo(r,abrirP);
  REQUIRE(arq != NULL);
  Constroi_TXT(&ainicio,arq);
  REQUIRE(ainicio != NULL);
  REQUIRE( strcmp(ainicio->Pergunta, "O objeto a ser descoberto é um aviao?") == 0);
  REQUIRE( strcmp(ainicio->sim->Pergunta, "O objeto é um abacaxi?") == 0);
  REQUIRE( strcmp(ainicio->nao->Pergunta, "O objeto é de comer?") == 0);
  fclose(arq);
  arq = CriaArquivo(w, Escrever);
  REQUIRE(arq != NULL);
  Salva_TXT(&ainicio,arq);
  fclose(arq);
  arq = CriaArquivo(r, abrirE);
  Constroi_TXT(&ainicio,arq);
  REQUIRE( strcmp(ainicio->Pergunta, "O objeto a ser descoberto é um aviao?") == 0);
  REQUIRE( strcmp(ainicio->sim->Pergunta, "O objeto é um abacaxi?") == 0);
  REQUIRE( strcmp(ainicio->nao->Pergunta, "O objeto é de comer?") == 0);
  fclose(arq);
  arq = CriaArquivo(r, qlqr);
  REQUIRE(arq == NULL);
}

TEST_CASE("Function that concatenates strings", "Should concatenate the string")
{
  char tes[4] = "tes";
  char tando[6] = "tando";
  char vazio[1] = "";

  REQUIRE(strcmp(ConstroiNo(tes,tando),"testando") == 0);
  REQUIRE(strcmp(ConstroiNo(vazio,tando),"tando") == 0);
  REQUIRE(strcmp(ConstroiNo(tes,vazio),"tes") == 0);
  REQUIRE(strcmp(ConstroiNo(vazio,vazio),"") == 0);
  REQUIRE(strcmp(ConstroiNo(tando,tes),"tandotes") == 0);
}

TEST_CASE("Testing user's answers in game", "Get only 'sim', 'nao', 'editar', 'apagar' answer and nothing else")
{
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'SIM'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Rsim);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'NAO'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Rnao);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'APAGAR'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Rapagar);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'EDITAR'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Reditar);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'sim'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Rsim);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'nao'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Rnao);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'apagar'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Rapagar);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'editar'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Reditar);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE QUALQUER COISA (DE ATE 6 CARACTERES) QUANTAS VEZES QUISER, E POR FIM 'EDITAR'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Reditar);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'SIM'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(simples) == Rsim);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'NAO'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(simples) == Rnao);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'sim'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(simples) == Rsim);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'nao'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(simples) == Rnao);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE QUALQUER COISA (DE ATE 6 CARACTERES) QUANTAS VEZES QUISER, E POR FIM 'SIM'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(simples) == Rsim);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'ABRIR'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(inicializacao) == Rabrir);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'CRIAR'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(inicializacao) == Rcriar);
  printf("PARA PASSAR NO TESTE, DIGITE 'abrir'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(inicializacao) == Rabrir);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'criar'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(inicializacao) == Rcriar);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE QUALQUER COISA (DE ATE 6 CARACTERES) QUANTAS VEZES QUISER, E POR FIM 'ABRIR'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(inicializacao) == Rabrir);
}

TEST_CASE("Receiving null tree or object was not guessed by Vinte_Perguntas", "The function should be contained, should ask the user to add more questions if less than 20 answers")
{
  arvore *ainicio = NULL;
  printf("\n******************************************************************\n");
  printf("DIGITE 'NAO', DEPOIS 'NAO'\n");
  printf("******************************************************************\n");
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio == NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'NAO', DEPOIS 'SIM', EM SEGUIDA CRIE APENAS UMA PERGUNTA EXTRA E DIGITE 'SAIR' 2 VEZES, DEPOIS RESPONDA A PERGUNTA E DIGITE NO FINAL 'SIM'\n");
  printf("******************************************************************\n");
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio != NULL);
}

TEST_CASE("Receiving 20 questions and testing 'apagar' and 'editar' in Vinte_Perguntas", "The function should ask the questions and navigate in the tree, and execute its functions 'apagar', 'editar'")
{
  arvore *ainicio;
  FILE *arq;
  char test[6] = "TESTE";
  printf("******************************************************************\n");
  printf("DIGITE 'SIM' 20 VEZES, NO FIM DIGITE 'SIM'\n");
  printf("******************************************************************\n");
  arq = fopen("./Arquivos_de_teste/Vinte.txt","r");
  Constroi_TXT(&ainicio,arq);
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio != NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'SIM' 20 VEZES, NO FIM DIGITE 'NAO'\n");
  printf("******************************************************************\n");
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio != NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'EDITAR' E ESCREVA 'TESTE' NA PERGUNTA, DEPOIS RESPONDA A EDIÇÃO COM 'NAO', NO FIM DIGITE 'SIM'\n");
  printf("******************************************************************\n");
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(strcmp(ainicio->Pergunta,test) == 0);
  printf("\n******************************************************************\n");
  printf("DIGITE 'APAGAR', DIGITE 'SIM', NO FIM DIGITE 'NAO'\n");
  printf("******************************************************************\n");
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio == NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'SIM', DEPOIS 'APAGAR', DIGITE 'SIM', NO FIM DIGITE 'NAO'\n");
  printf("\n******************************************************************\n");
  arq = fopen("./Arquivos_de_teste/Perguntas.txt","r");
  Constroi_TXT(&ainicio,arq);
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio != NULL);
  REQUIRE(ainicio->sim == NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'NAO', DEPOIS 'APAGAR', DIGITE 'SIM', NO FIM DIGITE 'NAO'\n");
  printf("******************************************************************\n");
  arq = fopen("./Arquivos_de_teste/Perguntas.txt","r");
  Constroi_TXT(&ainicio,arq);
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio != NULL);
  REQUIRE(ainicio->nao == NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'APAGAR', DIGITE 'NAO', DIGITE 'NAO', DIGITE 'NAO' E POR FIM DIGITE 'NAO'\n");
  printf("******************************************************************\n");
  arq = fopen("./Arquivos_de_teste/Vinte.txt","r");
  Constroi_TXT(&ainicio,arq);
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio != NULL);
  REQUIRE(ainicio->nao == NULL);
}

TEST_CASE("Creating childs at the end in 'sim' and 'nao'", "Should normaly create childs")
{
  arvore *ainicio = NULL, *anterior = NULL;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/Perguntas3.txt","r");
  Constroi_TXT(&anterior,arq);
  printf("\n******************************************************************\n");
  printf("DIGITE 'NAO', DEPOIS 'SIM', DEPOIS 'SIM', EM SEGUIDA CRIE APENAS UMA PERGUNTA EXTRA E DIGITE 'SAIR' 2 VEZES, DEPOIS RESPONDA A PERGUNTA E DIGITE NO FINAL 'SIM'\n");
  printf("******************************************************************\n");
  Pergunta_Final(&anterior, &ainicio, 0, Rsim);
  REQUIRE(anterior != NULL);
  REQUIRE(anterior->sim != NULL);
  REQUIRE(anterior->nao == NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'NAO', DEPOIS 'SIM', DEPOIS 'NAO', EM SEGUIDA CRIE APENAS UMA PERGUNTA EXTRA E DIGITE 'SAIR' 2 VEZES, DEPOIS RESPONDA A PERGUNTA E DIGITE NO FINAL 'SIM'\n");
  printf("******************************************************************\n");
  fclose(arq);
  arq = fopen("./Arquivos_de_teste/Perguntas3.txt","r");
  Constroi_TXT(&ainicio,arq);
  Pergunta_Final(&ainicio, &anterior, 0, Rsim);
  REQUIRE(ainicio != NULL);
  REQUIRE(ainicio->sim == NULL);
  REQUIRE(ainicio->nao != NULL);
  fclose(arq);
}

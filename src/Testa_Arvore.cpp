#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Arvore.h"

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
  REQUIRE(NavegaSim(&navegasim) == 1);
  REQUIRE(NavegaNao(&naveganao) == 1);
  REQUIRE(ainicio == ainiciobackup);
  REQUIRE(navegasim == ainicio->sim);
  REQUIRE(naveganao == ainicio->nao);
  REQUIRE(NavegaSim(&navegasim) == 2);
  REQUIRE(NavegaNao(&naveganao) == 2);
  REQUIRE(navegasim == NULL);
  REQUIRE(naveganao == NULL);
}

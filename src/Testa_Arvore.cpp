#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Arvore.h"

TEST_CASE( "Creating a tree from a file", "Prove that the tree is created" )
{
  arvore *ainicio;
  FILE *arq;
  arq = fopen("Perguntas.txt", "r");
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
  arq = fopen("naoexiste.txt", "r");
  Constroi_TXT(&ainicio,arq);
  REQUIRE( ainicio == NULL );
}

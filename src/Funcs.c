/*
Propriedade de Andre Garrido Damaceno.
mat. 15/0117531.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Funcs.h"
#include "Arvore.h"

FILE * CriaArquivo(char *type, char *opcao)
{
  FILE *arq;
  char nome[20];
  printf("Digite o nome do arquivo a ser %s: \n",opcao);
  scanf("%19s",nome);
  arq = fopen(nome, type);
  return arq;
}

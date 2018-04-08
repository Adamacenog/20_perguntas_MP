/*
*Propriedade de Andre Garrido Damaceno.
*mat. 15/0117531.
*/

#ifndef _Primary_libraries
  #define _Primary_libraries
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
#endif

#ifndef _Funcs_library
  #define _Funcs_library
    #include "Funcs.h"
#endif

FILE * CriaArquivo(char *type, char *opcao)
{
  FILE *arq;
  char nome[20];
  printf("Digite o nome do arquivo a ser %s: \n",opcao);
  scanf("%19s",nome);
  arq = fopen(nome, type);
  return arq;
}

char * ConstroiNo(char *no, char *filho)
{
  char *noFilho = (char *) malloc (strlen(no) + strlen(filho) + 1);

  strcpy(noFilho, no);
  strcat(noFilho, filho);

  return noFilho;
}

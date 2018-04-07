/*
Propriedade de Andre Garrido Damaceno.
mat. 15/0117531.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Arvore.h"
#include "Funcs.h"
#include "Vinte_Perguntas.h"

void Resposta(char *resposta)
{
  do
  {
    scanf("%7s", resposta);
    
    for(int i=0;i<strlen(resposta);i++)
    {
      resposta[i] = toupper(resposta[i]);
    }
    if(!(strcmp(resposta,"NAO") == 0 || strcmp(resposta,"SIM") == 0 || strcmp(resposta,"EDITAR") == 0 || strcmp(resposta,"APAGAR") == 0))
    {
      printf("Digite 'sim', 'nao', 'editar' ou 'apagar'\n");
    }
  } while(!(strcmp(resposta,"NAO") == 0 || strcmp(resposta,"SIM") == 0 || strcmp(resposta,"EDITAR") == 0 || strcmp(resposta,"APAGAR") == 0));

  return;
}

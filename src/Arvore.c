/*
Propriedade de Andre Garrido Damaceno.
mat. 15/0117531.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Arvore.h"

void Constroi_TXT (arvore **ainicio, FILE *arq)
{
    const char nulo[2] = ".";
    char pergunta[100];

    if(arq!=NULL)
    {
      if(fgets (pergunta, 100, arq)!=NULL)
      {
          strtok(pergunta, "\n");

          if (strcmp(pergunta, nulo) == 0)
          {
              *ainicio = NULL;
          }
          else
          {
            *ainicio = (arvore*) malloc (sizeof (arvore));
            if(*ainicio != NULL)
            {
              strcpy((*ainicio)->Pergunta,pergunta);
              Constroi_TXT (&((*ainicio)->sim), arq);
              Constroi_TXT (&((*ainicio)->nao), arq);
            }
            else
            {
              printf("Malloc Error! Exiting!");
              exit(1);
            }
          }
        }
    }
    else
    {
      *ainicio = NULL;
    }

    return;
}

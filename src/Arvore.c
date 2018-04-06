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

void Salva_TXT (arvore **ainicio, FILE *arq)
{
  if(arq != NULL)
  {
    if (*ainicio == NULL)
    {
        fprintf(arq, "%s\n", ".");
    }
    else
    {
        fprintf(arq, "%s\n", (*ainicio)->Pergunta);
        Salva_TXT (&(*ainicio)->sim, arq);
        Salva_TXT (&(*ainicio)->nao, arq);
    }
 }
  return;
}

void Le (arvore *a1)
{
    if (a1 != NULL)
    {
      printf ("%s\n" , a1->Pergunta);
    }

    return;
}

int NavegaSim(arvore **pergunta)
{
  if((*pergunta) != NULL)
  {
    if((*pergunta)->sim != NULL)
    {
      *pergunta = (*pergunta)->sim;
      Le(*pergunta);

      return 1;
    }
    else
    {
      *pergunta = NULL;
      return 2;
    }
  }
  else
  {
    return 2;
  }

}

int NavegaNao(arvore **pergunta)
{
  if((*pergunta) != NULL)
  {
    if((*pergunta)->nao != NULL)
    {
      *pergunta = (*pergunta)->nao;
      Le(*pergunta);

      return 1;
    }
    else
    {
      *pergunta = NULL;
      return 2;
    }
  }
  else
  {
    return 2;
  }

}

void Desconstroi (arvore **ainicio)
{
    if (*ainicio != NULL)
    {
        Desconstroi (&((*ainicio)->sim));
        Desconstroi (&((*ainicio)->nao));
        free (*ainicio);
        *ainicio = NULL;
    }

    return;
}

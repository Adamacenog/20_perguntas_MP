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

#ifndef _Arvore_library
  #define _Arvore_library
    #include "Arvore.h"
#endif

#ifndef _Funcs_library
  #define _Funcs_library
    #include "Funcs.h"
#endif

#ifndef _Vinte_Perguntas_library
  #define _Vinte_Perguntas_library
    #include "Vinte_Perguntas.h"
#endif

void Constroi_Manual (arvore **ainicio, char *no, int size)
{
  if(size < 20)
  {
    char pergunta[100];

    printf("\nDigite abaixo a pergunta ou a resposta de uma pergunta ou 'SAIR' para não responder.\n");
    printf("Nó atual: %s\n", no);
    do
    {
      fgets (pergunta, 99, stdin);
    } while(strcmp(pergunta,"\n") == 0);

    strtok(pergunta, "\n");

    if (strcmp(pergunta, "sair") == 0 || strcmp(pergunta, "SAIR") == 0)
    {
        *ainicio = NULL;
    }
    else
    {
      *ainicio = (arvore*) malloc (sizeof (arvore));
      if(*ainicio != NULL)
      {
        char *noFilho;
        char fSim[14] = " - Filho(sim)";
        char fNao[14] = " - Filho(nao)";

        strcpy((*ainicio)->Pergunta,pergunta);
        noFilho = ConstroiNo(no, fSim);
        Constroi_Manual (&((*ainicio)->sim), noFilho, (size + 1));
        free(noFilho);
        noFilho = ConstroiNo(no, fNao);
        Constroi_Manual (&((*ainicio)->nao), noFilho, (size + 1));
        free(noFilho);
      }
      else
      {
        printf("Malloc Error! Exiting!");
        exit(1);
      }
    }
  }
  else
  {
    *ainicio = NULL;
  }

  return;
}

void Constroi_TXT (arvore **ainicio, FILE *arq)
{
    const char nulo[2] = ".";

    if(arq!=NULL)
    {
      char pergunta[100];

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

      return prosseguir;
    }
    else
    {
      *pergunta = NULL;
      return finalizar;
    }
  }
  else
  {
    return finalizar;
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

      return prosseguir;
    }
    else
    {
      *pergunta = NULL;
      return finalizar;
    }
  }
  else
  {
    return finalizar;
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

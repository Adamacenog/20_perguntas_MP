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

int Resposta(int tipo)
{
  do
  {
    char resposta[8];
    scanf("%7s", resposta);

    for(int i=0;i<strlen(resposta);i++)
    {
      resposta[i] = toupper(resposta[i]);
    }
    if(strcmp(resposta,"SIM") == 0) return Rsim;
    if(strcmp(resposta,"NAO") == 0) return Rnao;
    if(strcmp(resposta,"EDITAR") == 0 && tipo == multipla) return Reditar;
    if(strcmp(resposta,"APAGAR") == 0 && tipo == multipla) return Rapagar;
    if(strcmp(resposta, "ABRIR") == 0 && tipo == inicializacao) return Rabrir;
    if(strcmp(resposta, "CRIAR") == 0 && tipo == inicializacao) return Rcriar;

    if(!(strcmp(resposta,"NAO") == 0 || strcmp(resposta,"SIM") == 0 || strcmp(resposta,"EDITAR") == 0 || strcmp(resposta,"APAGAR") == 0) && tipo == multipla)
    {
      printf("Digite 'sim', 'nao', 'editar' ou 'apagar'\n");
    }
    if(!(strcmp(resposta,"CRIAR") == 0 || strcmp(resposta,"ABRIR") == 0) && tipo == inicializacao)
    {
      printf("Digite 'abrir' ou 'criar'\n");
    }
    if(!(strcmp(resposta,"NAO") == 0 || strcmp(resposta,"SIM") == 0) && tipo == simples)
    {
      printf("Digite 'sim' ou 'nao'\n");
    }
  } while(1);
}

void Vinte_Perguntas(arvore **anavega, int numero_respostas)
{
  int opcao;
  arvore *ainicio,*anterior = NULL;

  printf("\nO jogo vai começar! Para editar uma pergunta a qualquer momento digite 'EDITAR', para apagar 'APAGAR'\n\n");
  ainicio = (*anavega);
  Le(*anavega);
  while (numero_respostas < 19 && *anavega != NULL)
  {
    int continua;
    do
    {
      opcao = Resposta(multipla);

      if(opcao == Rsim)
      {
        anterior = (*anavega);
        continua = NavegaSim(anavega);
      }
      if(opcao == Rnao)
      {
        anterior = (*anavega);
        continua = NavegaNao(anavega);
      }
      if(opcao == Reditar)
      {
        char pergunta[100];
        printf("\nDigite abaixo a pergunta ou a resposta de uma pergunta ou 'SAIR' para cancelar a edição.\n");
        do
        {
          fgets (pergunta, 99, stdin);
        } while(strcmp(pergunta,"\n") == 0);

        strtok(pergunta, "\n");

        if (!(strcmp(pergunta, "sair") == 0 || strcmp(pergunta, "SAIR") == 0))
        {
          strcpy((*anavega)->Pergunta,pergunta);
        }
        printf("Responda a pergunta editada agora para continuar...\n");
        continua = prosseguir;
      }
      if(opcao == Rapagar)
      {
        printf("Tem certeza? Apagar removerá todos os filhos do nó e o nó.\n");
        opcao = Resposta(simples);
        if(opcao == Rsim)
        {
          if(anterior != NULL)
          {
            if(anterior->sim == *anavega)
            {
              anterior->sim = NULL;
            }
            if(anterior->nao == *anavega)
            {
              anterior->nao = NULL;
            }
          }

          if(ainicio == *anavega)
          {
            ainicio = NULL;
          }
          Desconstroi(anavega);
          opcao = Rapagar;
          continua = finalizar;
        }
        if(opcao == Rnao)
        {
          continua = prosseguir;
          numero_respostas--;
          Le(*anavega);
        }
      }
      if(continua == prosseguir) numero_respostas++;
    } while(continua == prosseguir);
  }

  Pergunta_Final(&anterior, &ainicio, numero_respostas, opcao);

  *anavega = ainicio;

  return;
}

void Pergunta_Final(arvore **anterior, arvore **ainicio, int numero_respostas, int opcao)
{
  if(opcao != Rapagar)
  {
    printf("\nFim de jogo!, seu objeto foi descoberto?\n");
    opcao = Resposta(simples);
  }
  else
  {
    opcao = Rnao;
  }

  if(opcao == Rsim)
  {
    printf("Que bom!! O computador é esperto!\n");
  }
  if(opcao == Rnao)
  {
    if(numero_respostas < 19)
    {
      printf("Deseja fazer mais perguntas para conseguir responder seu objeto?\n");
      opcao = Resposta(simples);
      if(opcao == Rsim)
      {
        printf("A edição vai começar a partir da última pergunta respondida, que é:\n");
        if(*anterior != NULL)
        {
          int seleciona = 0;
          Le(*anterior);

          if((*anterior)->sim == NULL && (*anterior)->nao == NULL)
          {
            printf("Digite 'SIM' para adicionar no nó PERGUNTA->SIM e 'NAO' para o nó PERGUNTA->NAO\n");
            opcao = Resposta(simples);
            seleciona = 1;
          }
          if((*anterior)->sim == NULL && (((*anterior)->nao != NULL &&  seleciona == 0) || opcao == Rsim))
          {
            char posicaoSim[21] = "ULTIMA PERGUNTA->SIM";
            printf("Construindo a partir do nó ULTIMA PERGUNTA->SIM\n");
            Constroi_Manual(&(*anterior)->sim,posicaoSim, numero_respostas);
            Vinte_Perguntas(&(*anterior)->sim, numero_respostas);
          }
          if((*anterior)->nao == NULL && (((*anterior)->sim != NULL && seleciona == 0) || opcao == Rnao))
          {
            char posicaoNao[21] = "ULTIMA PERGUNTA->NAO";
            printf("Construindo a partir do nó ULTIMA PERGUNTA->NAO\n");
            Constroi_Manual(&(*anterior)->nao,posicaoNao, numero_respostas);
            Vinte_Perguntas(&(*anterior)->nao, numero_respostas);
          }
        }
        else
        {
          printf("\nÚltima pergunta vazia, fazendo jogo novo!\n");
          char posicao[4] = "PAI";
          Constroi_Manual(ainicio,posicao, numero_respostas);
          Vinte_Perguntas(ainicio, numero_respostas);
        }
      }
      if(opcao == Rnao)
      {
          printf("Fim de jogo!\n");
      }
    }
    else
    {
      printf("Que pena :(, não foi dessa vez\n");
    }
  }
  return;
}

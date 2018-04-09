/*
*Propriedade de Andre Garrido Damaceno.
*mat. 15/0117531.
*/

/**
 * @file Vinte_Perguntas.c
 * @author Andre Garrido Damaceno
 * @brief Arquivo que contem a biblioteca de estruturação (execução) do jogo de 20 perguntas.
 *
 *Como esse arquivo contem a biblioteca de execução, necessita dos headers padrões,
 *de funções auxiliares, e de estruturação do jogo.
 */

 /*
 *@brief Header de funções padrão, para I/O, manipulação de strings.
 */
#ifndef _Primary_libraries
  #define _Primary_libraries
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
#endif

/*
*@brief Header da biblioteca de arvore.
*/
#ifndef _Arvore_library
  #define _Arvore_library
    #include "Arvore.h"
#endif

/*
*@brief Header da biblioteca de funções (criação de arquivo e concatenação de strings).
*/
#ifndef _Funcs_library
  #define _Funcs_library
    #include "Funcs.h"
#endif

/*
*@brief Header da biblioteca de estruturação (execução) do jogo de 20 perguntas.
*/
#ifndef _Vinte_Perguntas_library
  #define _Vinte_Perguntas_library
    #include "Vinte_Perguntas.h"
#endif

/*
*@brief Função para pegar o input especifico de opções do usuario.
*Essa função recebe como parametro um inteiro 'int tipo', que especifica o tipo de opção
*que o usuário terá e retorna um inteiro que representa a opção selecionada (escrita) pelo usuario.
*Essa função inicialmente lê a resposta escrita pelo usuário e delimita as respostas para o Tipo
*da pergunta, sendo 'simples' - para perguntas de 'sim' ou 'nao', 'multipla' - para perguntas de
*'sim', 'nao', 'editar' ou 'apagar', e 'inicializacao' - para perguntas de 'abrir' ou 'criar'.
*Caso o usuario tenha respondido algo invalido, é mencionada as respostas que a pergunta espera, e
*dada a chance do usuario responder novamente, caso contrario, é retornado o equivalente da resposta
*do usuario pelo inteiro. Caso haja um erro de leitura pelo 'scanf' (usuario digita mais que 6 caracteres),
* apenas é mencionada a mensagem dos tipos da resposta disponivel multiplas vezes, qualquer outro tipo de
*erro é desconhecido o comportamento (pois estariam dependendo das funções 'strcmp', 'strlen' e toupper).
*/
int Resposta(int tipo)
{
  do
  {
    char resposta[8];  //Variavel que armazena a resposta do usuario
    scanf("%7s", resposta);

    for(int i=0;i<strlen(resposta);i++)  //Transformação de todos os caracteres em maiusculo, para melhor identificação da opcao
    {
      resposta[i] = toupper(resposta[i]);
    }

    //Respostas
    if(strcmp(resposta,"SIM") == 0 && (tipo == multipla || tipo == simples)) return Rsim;
    if(strcmp(resposta,"NAO") == 0 && (tipo == multipla || tipo == simples)) return Rnao;
    if(strcmp(resposta,"EDITAR") == 0 && tipo == multipla) return Reditar;
    if(strcmp(resposta,"APAGAR") == 0 && tipo == multipla) return Rapagar;
    if(strcmp(resposta, "ABRIR") == 0 && tipo == inicializacao) return Rabrir;
    if(strcmp(resposta, "CRIAR") == 0 && tipo == inicializacao) return Rcriar;

    //Caso o usuario tenha digitado algo invalido, há uma condição para cada tipo de pergunta ('simples', 'multipla' e 'inicializacao')
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

/*
*@brief Função de execução do programa.
*Essa função recebe como parametro o endereço do ponteiro da arvore 'arvore **anavega'
*(para as possiveis mudanças na arvore como apagar, editar, navegar e criar novos nós) e
*um inteiro 'int numero_respostas', para saber quantas perguntas ja foram respondidas pelo usuario.
*Essa função não retorna nenhum parametro. A função inicialmente alerta ao usuário que o jogo irá
*começar e analisa se a arvore é vazia ou o numero_respostas é menor que 19 (ja foram respondidas
*20 perguntas). Em seguida é lida a pergunta para o usuário e ele pode navegar pelas perguntas
*(respondendo 'sim' ou 'nao') ou editar/apagar uma pergunta. No fim, é perguntado ao usuário se
*seu objeto pensado foi descoberto. Caso tenha sido, o jogo é finalizado, caso não tenha sido e
*o usuário ainda não tenha respondido 20 perguntas, é perguntado se o usuário deseja inserir mais
*perguntas para o programa descobrir o objeto. Ao fim das inserções, o jogo recomeça a partir do ponto
*da ultima pergunta respondida pelo usuário. Como essa função de execução utiliza a maior parte de todas
*as funções criadas, os erros estão relacionados a essas funções. Mas todas as funções inclusive essa, foi
*desenvolvida para conter erros e finalizar o programa apenas se um erro de alocação de memoria ocorrer.
*/
void Vinte_Perguntas(arvore **anavega, int numero_respostas)
{
  int opcao;  //Variavel com a resposta do usuario ('sim', 'nao', 'editar', 'apagar')
  arvore *ainicio,*anterior = NULL;  /*ainicio - guarda o endereço do inicio da arvore,
                                      anterior - guarda o endereço da jogada anterior feita*/

  printf("\nO jogo vai começar! Para editar uma pergunta a qualquer momento digite 'EDITAR', para apagar 'APAGAR'\n\n");
  ainicio = (*anavega);  //Coloca-se o endereço do inicio da arvore em ainicio
  Le(*anavega);  //A primeira pergunta é lida
  while (numero_respostas < 20 && *anavega != NULL)  //Checa se ja foram respondidas 20 perguntas ou se a arvore chegou ao seu fim
  {
      opcao = Resposta(multipla);

      if(opcao == Rsim)
      {
        anterior = (*anavega);
        NavegaSim(anavega);
      }
      if(opcao == Rnao)
      {
        anterior = (*anavega);
        NavegaNao(anavega);
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
        }
        if(opcao == Rnao)
        {
          numero_respostas--;
          Le(*anavega);
        }
      }
      numero_respostas++;
  }

  Pergunta_Final(&anterior, &ainicio, numero_respostas, opcao);

  *anavega = ainicio;

  return;
}

/*
*@brief
*/
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
    if(numero_respostas < 20)
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

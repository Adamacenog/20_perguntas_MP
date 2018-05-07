/*
*Propriedade de Andre Garrido Damaceno.
*mat. 15/0117531.
*/

/**
 * @file Vinte_Perguntas.c
 * @author Andre Garrido Damaceno
 * @brief Arquivo que contem a biblioteca de estruturação (execução) do jogo de 20 perguntas.
 *
 */

 /**Como esse arquivo contem a biblioteca de execução, necessita dos headers padrões,
 *de funções auxiliares, e de estruturação do jogo.
 */

/**@brief Header de funções padrão, para I/O, manipulação de strings.
*/
#ifndef _Primary_libraries
  #define _Primary_libraries
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #include <assert.h>
#endif

/**@brief Header da biblioteca de arvore.
*/
#ifndef _Arvore_library
  #define _Arvore_library
    #include "Arvore.h"
#endif

/**@brief Header da biblioteca de funções (criação de arquivo e concatenação de strings).
*/
#ifndef _Funcs_library
  #define _Funcs_library
    #include "Funcs.h"
#endif

/**@brief Header da biblioteca de estruturação (execução) do jogo de 20 perguntas.
*/
#ifndef _Vinte_Perguntas_library
  #define _Vinte_Perguntas_library
    #include "Vinte_Perguntas.h"
#endif

/**@brief Função de execução do programa.
*
*Parametros: Essa função recebe como parametro o endereço do ponteiro da arvore 'arvore **anavega'
*(para as possiveis mudanças na arvore como apagar, editar, navegar e criar novos nós) e
*um inteiro 'int numero_respostas', para saber quantas perguntas ja foram respondidas pelo usuario.
*Essa função não retorna nenhum parametro.
*
*Tratamento de erros: Como essa função de execução utiliza a maior parte de todas as funções criadas,
*os erros estão relacionados a essas funções. Mas todas as funções inclusive essa, foi desenvolvida para
*conter erros e finalizar o programa apenas se um erro de alocação de memoria ocorrer.
*
*Descrição: A função inicialmente alerta ao usuário que o jogo irá começar e analisa se a arvore
*é vazia ou o numero_respostas é menor que 19 (ja foram respondidas 20 perguntas). Em seguida é
*lida a pergunta para o usuário e ele pode navegar pelas perguntas (respondendo 'sim' ou 'nao') ou
*editar/apagar uma pergunta. No fim, é perguntado ao usuário se seu objeto pensado foi descoberto.
*Caso tenha sido, o jogo é finalizado, caso não tenha sido e o usuário ainda não tenha respondido 20
*perguntas, é perguntado se o usuário deseja inserir mais perguntas para o programa descobrir o objeto.
*Ao fim das inserções, o jogo recomeça a partir do ponto da ultima pergunta respondida pelo usuário.
*
*numero_respostas menor que 21
*
*Requisitos: A função deve percorrer as perguntas da árvore de acordo com as respostas do usuário,
*também ter a capacidade de verificar se ja foram respondidas 20 perguntas. Ao fim, também oferecer
*a opção de inserir mais perguntas caso ainda não tenham sido respondidas as 20, e a resposta não tenha
*sido encontrada.
*
*Hipoteses: As alocações de memória são feitas com o tamanho ideal e de forma correta, as navegações com
*os ponteiros são feitas de forma adequada.
*
*Assertivas de saida: Não há.
*
*Interface explicita: estrutura de árvore '**anavega', quantidade de respostas 'numero_respostas'
*
*Interface implicita:
*
*Contrato na especificação: A função recebe a árvore com as perguntas e a quantidade de respostas já respondidas,
*ela deve então navegar na árvore de acordo com as respostas do usuário, até o fim da árvore (onde pode ser que
*tenha ou não a resposta do objeto pensado pelo usuário). Caso não chegue na resposta e não tenham sido respondidas
*20 perguntas ainda, a função dá a opção de inserir mais perguntas até que a resposta seja alcançada ou as 20 perguntas
*sejam criadas.
*
*/
void Vinte_Perguntas(arvore **anavega, unsigned int numero_respostas)
{
  int opcao;  //Variavel com a resposta do usuario ('sim', 'nao', 'editar', 'apagar')
  arvore *ainicio,*anterior = NULL;  /*ainicio - guarda o endereço do inicio da arvore,
                                      anterior - guarda o endereço da jogada anterior feita*/
  assert(numero_respostas < 21);
  printf("\nO jogo vai começar! Para editar uma pergunta a qualquer momento digite 'EDITAR', para apagar 'APAGAR'\n\n");
  ainicio = (*anavega);  //Coloca-se o endereço do inicio da arvore em ainicio
  Le(*anavega);  //A primeira pergunta é lida
  while (numero_respostas < 20 && *anavega != NULL)  //Checa se ja foram respondidas 20 perguntas ou se a arvore chegou ao seu fim
  {
      opcao = Resposta(multipla);  //Pega as respostas do usuario (do tipo multipla - 'sim', 'nao', 'editar', 'apagar')

      switch(opcao)
      {
        case Rsim: //Navega para o nó sim
        anterior = (*anavega);
        NavegaSim(anavega);
        break;

        case Rnao:  //Navega para o nó nao
        anterior = (*anavega);
        NavegaNao(anavega);
        break;

        case Reditar:  //Edição da pergunta
        printf("\nDigite abaixo a pergunta ou a resposta de uma pergunta ou 'SAIR' para cancelar a edição.\n");
        char pergunta[100];
        do
        {
          fgets (pergunta, 99, stdin);
        } while(strcmp(pergunta,"\n") == 0);

        strtok(pergunta, "\n");

        if (!(strcmp(pergunta, "sair") == 0 || strcmp(pergunta, "SAIR") == 0))  //Caso a pessoa cancele a edição
        {
          strcpy((*anavega)->Pergunta,pergunta);
        }
        printf("Responda a pergunta editada agora para continuar...\n");
        break;

        case Rapagar:  //Apagar um nó
        printf("Tem certeza? Apagar removerá todos os filhos do nó e o nó.\n");
        opcao = Resposta(simples);
        if(opcao == Rsim)  //Checa se a pessoa realmente deseja apagar o nó
        {
          if(anterior != NULL)  //Essa etapa faz com que a arvore deixe de apontar para anavega, para apaga-la
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

          if(ainicio == *anavega)  //Checa se é o primeiro nó que é apagado
          {
            ainicio = NULL;
          }
          Desconstroi(anavega);  //Apaga o nó da arvore
          opcao = Rapagar;
        }
        if(opcao == Rnao)  //Caso a pessoa desista de apagar o nó
        {
          numero_respostas--;
          Le(*anavega);
        }
        break;
      }
      numero_respostas++;  //Contador de perguntas respondidas
  }

  Pergunta_Final(&anterior, &ainicio, numero_respostas, opcao);

  *anavega = ainicio;  //Coloca o apontador da arvore de volta para o inicio da arvore

  return;
}

/**@brief Função que verifica se o computador acertou o objeto, e cria mais perguntas caso não tenha acertado (se o usuário quiser e ainda não tenham sido respondidas 20 perguntas).
*
*Parametros: Essa função recebe como parametro o endereço do ponteiro da arvore 'arvore **anterior', o endereço do apontador do inicio
*da arvore 'arvore **ainicio', o numero de perguntas ja respondidas 'int numero_respostas' e a última opção selecionada 'int opcao'.
*A função não retorna nenhum parametro.
*
*Tratamento de erros: Os casos de erro são os mesmos das funções 'Vinte_Perguntas()' e 'Constroi_Manual()', pois depende dessas funções e de alocação
*de memoria do computador, sendo assim, a execução é terminada caso haja algum erro de alocação.
*
*Descrição: Essa função tem o objetivo de checar se o computador conseguiu chegar na resposta do objeto que o usuário pensava.
*Dessa forma, a função dá a opção de criar novas perguntas para alcançar esse objetivo (caso o usuário tenha respondido menos
*que 20 perguntas ou um nó foi apagado) e por fim, retorna ao jogo (ou mostra o resultado caso ja tenham sido respondidas as 20 perguntas).
*
*Assertivas de entrada: numero_respostas deve ser menor que 21, apontador da árvore 'anterior' não pode ser NULL.
*
*Requisitos: A função deve verificar se o usuário achou a resposta e se ja foram respondidas as 20 perguntas. Caso ainda não tenha
*chegado na resposta e ja tenha sido respondidas 20 perguntas, nada ocorre. Caso não tenha chegado na resposta e ainda não tenham sido
*respondidas as 20 perguntas, o usuário tem a opção de inserir mais perguntas até que as 20 perguntas sejam completadas, por fim o jogo retorna.
*Caso já tenha achado a resposta do objeto pensado pelo usuário, o programa finaliza.
*
*
*Hipoteses: Todas as memórias alocadas são feitas com o tamanho e a forma adequada, as navegações com os ponteiros são feitas de
*forma correta e com cuidado para não se perder as referências.
*
*Assertivas de saida: Não há.
*
*Interface explicita: estrutura de árvore '**ainicio' e '**anterior', quantidade de respostas 'numero_respostas', ultima opção
*selecionada pelo usuário 'opcao'.
*
*Interface implicita:
*
*Contrato na especificação: A função deve verificar se o usuário já chegou na resposta desejada, caso ja tenha, uma mensagem
*é exibida. Caso ainda não tenha chegado, verifica-se se já foram respondidas 20 perguntas. Caso ja tenha sido respondido,
*é exibida uma mensagem de consolo. Caso contrário, é disponibilizada uma opção de inserir mais perguntas para se chegar na
*resposta (com o limite de 20 perguntas no total). No final, o jogo retorna na útlima pergunta respondida (que não tinha a resposta).
*
*/
void Pergunta_Final(arvore **anterior, arvore **ainicio, unsigned int numero_respostas, unsigned int opcao)
{
  if(opcao != Rapagar)  //Checa se a ultima opcao foi apagar
  {
    printf("\nFim de jogo!, seu objeto foi descoberto?\n");
    opcao = Resposta(simples);
  }
  else  //Caso tenha sido apagar, já vai direto á pergunta se o usuário deseja add mais perguntas
  {
    opcao = Rnao;
  }

  if(opcao == Rsim)  //Verifica a necessidade de criar novas perguntas
  {
    printf("Que bom!! O computador é esperto!\n");
  }
  if(opcao == Rnao)  //Caso não tenha descoberto o objeto
  {
    if(numero_respostas < 20)  //Caso ainda não tenha respondido todas as 20 perguntas
    {
      printf("Deseja fazer mais perguntas para conseguir responder seu objeto?\n");
      opcao = Resposta(simples);
      if(opcao == Rsim)  //Caso a pessoa queira fazer mais perguntas
      {
        printf("A edição vai começar a partir da última pergunta respondida, que é:\n");
        if(*anterior != NULL)  //Checa se a ultima pergunta existe
        {
          int seleciona = 0;
          Le(*anterior);  //Le a ultima pergunta

          if((*anterior)->sim == NULL && (*anterior)->nao == NULL)  //Checa se ambos os filhos da ultima pergunta estao vazios
          {
            printf("Digite 'SIM' para adicionar no nó PERGUNTA->SIM e 'NAO' para o nó PERGUNTA->NAO\n");
            opcao = Resposta(simples);
            seleciona = 1;
          }
          if((*anterior)->sim == NULL && (((*anterior)->nao != NULL &&  seleciona == 0) || opcao == Rsim))  //Caso o filho 'nao' esteja preenchido OU seja selecionado o filho 'sim'
          {
            char posicaoSim[21] = "ULTIMA PERGUNTA->SIM";
            printf("Construindo a partir do nó ULTIMA PERGUNTA->SIM\n");
            Constroi_Manual(&(*anterior)->sim,posicaoSim, numero_respostas);  //Continua a construção da arvore
            Vinte_Perguntas(&(*anterior)->sim, numero_respostas);  //Continua o jogo
          }
          if((*anterior)->nao == NULL && (((*anterior)->sim != NULL && seleciona == 0) || opcao == Rnao))  //Caso o filho 'sim' esteja preenchido OU seja selecionado o filho 'nao'
          {
            char posicaoNao[21] = "ULTIMA PERGUNTA->NAO";
            printf("Construindo a partir do nó ULTIMA PERGUNTA->NAO\n");
            Constroi_Manual(&(*anterior)->nao,posicaoNao, numero_respostas);  //Continua a construção da arvore
            Vinte_Perguntas(&(*anterior)->nao, numero_respostas);  //Continua o jogo
          }
        }
        else  //Caso a ultima pergunta não exista (arvore NULL)
        {
          printf("\nÚltima pergunta vazia, fazendo jogo novo!\n");
          char posicao[4] = "PAI";
          Constroi_Manual(ainicio,posicao, numero_respostas);  //Inicia uma nova arvore
          Vinte_Perguntas(ainicio, numero_respostas);  //Inicia o jogo
        }
      }
      if(opcao == Rnao)  //Caso a pessoa não queira fazer mais perguntas
      {
          printf("Fim de jogo!\n");
      }
    }
    else  //Caso a pessoa ja tenha respondido 20 perguntas e não chegou no seu objeto
    {
      printf("Que pena :(, não foi dessa vez\n");
    }
  }
  return;
}

/*
*Propriedade de Andre Garrido Damaceno.
*mat. 15/0117531.
*/

/**
 * @file Arvore.c
 * @author Andre Garrido Damaceno
 * @brief Arquivo que contem a biblioteca de manipulação e criação da arvore.
 *
 *Como esse arquivo contem a biblioteca da arvore, necessita dos headers padrões e de
 *de funções auxiliares.
 */

/**@brief Header de funções padrão, para I/O, manipulação de strings.
*/
#ifndef _Primary_libraries
  #define _Primary_libraries
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
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

/**@brief Função de criação da arvore de forma manual.
*
*Essa função recebe como parametro o endereço de um ponteiro de arvore 'arvore **ainicio' (para sua criação),
*uma string 'char *no' para a informação a respeito do nó atual para o usuário, um inteiro 'int size', para impedir
*a criação de mais que 20 níveis de perguntas (para garantir que o usuário poderá responder apenas 20 perguntas no máximo).
*A função não retorna nenhum parametro. Essa função cria a arvore de acordo com as perguntas inseridas pelo usuário,
*sendo possível o usuário criar quantas perguntas quiser (com o limite de 1048576 perguntas), podendo parar de inserir quando quiser.
*Caso haja erro de alocação de memória em 'Constroi_Manual' ou nas funções que ela chama, o programa é encerrado com erro.
*/
void Constroi_Manual (arvore **ainicio, char *no, int size)
{
  if(size < 20)  //Verifica se ja foram inseridas 20 perguntas em um nó
  {
    char pergunta[100];  //Variavel que armazena a pergunta

    printf("\nDigite abaixo a pergunta ou a resposta de uma pergunta ou 'SAIR' para não responder.\n");
    printf("Nó atual: %s\n", no);
    do
    {
      /*
        Esse loop é feito para evitar que '\n' seja inserido como pergunta.
      */
      fgets (pergunta, 99, stdin);
    } while(strcmp(pergunta,"\n") == 0);

    strtok(pergunta, "\n");  //Remove o '\n' da pergunta para ficar visualmente melhor

    if (strcmp(pergunta, "sair") == 0 || strcmp(pergunta, "SAIR") == 0)
    {
        *ainicio = NULL;  //Caso o usuário não queira mais inserir, o nó não inserido têm que ser "branco" (NULL)
    }
    else
    {
      *ainicio = (arvore*) malloc (sizeof (arvore));  //Aloca memória para a arvore
      if(*ainicio != NULL)
      {
        char *noFilho;  //Variavel para a concatenação de strings (melhor visualização do nó atual para o usuário)
        char fSim[14] = " - Filho(sim)";  //Variavel do nó sim
        char fNao[14] = " - Filho(nao)";  //Variavel do nó sim

        strcpy((*ainicio)->Pergunta,pergunta);  //Inserção da pergunta na arvore
        noFilho = ConstroiNo(no, fSim);  //Concatenação da string sim
        Constroi_Manual (&((*ainicio)->sim), noFilho, (size + 1));  //Constroi para a esquerda (sim)
        free(noFilho);  //Remove a concatenação feita
        noFilho = ConstroiNo(no, fNao);  //Concatenação para a string nao
        Constroi_Manual (&((*ainicio)->nao), noFilho, (size + 1));  //Constroi para a direita (nao)
        free(noFilho);  //Remove a concatenação feita
      }
      else  //Caso haja problema na alocação da arvore
      {
        exit(1);
      }
    }
  }
  else  //Caso já tenham sido inseridas 20 perguntas
  {
    *ainicio = NULL;
  }

  return;
}

/**@brief Função de criação da arvore por .txt.
*
*Essa função recebe como parametro o endereço de um ponteiro de arvore 'arvore **ainicio' (para sua criação)
*e um arquivo (para a leitura das perguntas e criação da arvore). A função não retorna nenhum parametro.
*Essa função cria a arvore de acordo com um arquivo de texto aberto pelo usuário, sendo os nós nulos identificados
*por pontos '.'. Caso haja erro de alocação de memória em 'Constroi_TXT' o programa é encerrado com erro.
*/
void Constroi_TXT (arvore **ainicio, FILE *arq)
{
    const char nulo[2] = ".";  //Definição do nó nulo

    if(arq!=NULL)  //Verificação de arquivo .txt não existente
    {
      char pergunta[100];  //Variavel que armazena a pergunta

      if(fgets (pergunta, 100, arq)!=NULL)  //Pega uma linha inteira do .txt (pergunta)
      {
          strtok(pergunta, "\n");  //Remove o '\n' da pergunta para ficar visualmente melhor

          if (strcmp(pergunta, nulo) == 0)  //Caso haja um '.' no .txt, criar nó nulo
          {
              *ainicio = NULL;
          }
          else
          {
            *ainicio = (arvore*) malloc (sizeof (arvore));  //Alocação do espaço para a arvore
            if(*ainicio != NULL)  //Verifica se a memoria alocada é nula (NULL)
            {
              strcpy((*ainicio)->Pergunta,pergunta);  //Copia a pergunta para a memoria alocada
              Constroi_TXT (&((*ainicio)->sim), arq);  //Constroi a arvore para a esquerda (sim)
              Constroi_TXT (&((*ainicio)->nao), arq);  //Constroi a arvore para a direita (nao)
            }
            else  //Caso haja erro na alocação, finalizar o programa
            {
              exit(1);
            }
          }
        }
    }
    else  //Caso o arquivo de texto não exista, a arvore não é criada
    {
      *ainicio = NULL;
    }

    return;
}

/**@brief Função para salvar as perguntas da arvore em um .txt.
*
*Essa função recebe como parametro o endereço do ponteiro de uma arvore 'arvore **ainicio',
*e o arquivo de texto a ser salvo as perguntas da arvore 'FILE *arq'. A função não retorna
*nenhum parametro. A função salva a pergunta no arquivo .txt, caso o nó seja NULL, é salvo
*um '.' no arquivo. Caso o arquivo seja inexistente, a função não faz nada. Caso a arvore seja
*inexistente, a função salva apenas um '.' no .txt (não havendo erros).
*/
void Salva_TXT (arvore **ainicio, FILE *arq)
{
  if(arq != NULL)  //Checa se o arquivo .txt existe
  {
    if (*ainicio == NULL)  //Caso o nó esteja em branco (NULL)
    {
        fprintf(arq, "%s\n", ".");  //Coloca o '.' no arquivo .txt
    }
    else
    {
        fprintf(arq, "%s\n", (*ainicio)->Pergunta);  //Insere a pergunta no .txt
        Salva_TXT (&(*ainicio)->sim, arq);  //Salva no .txt o nó da esquerda (sim)
        Salva_TXT (&(*ainicio)->nao, arq);  //Salva no .txt o nó da direita (nao)
    }
 }
  return;
}

/**@brief Função para a leitura da pergunta no nó da Arvore.
*
*Essa função recebe como parametro um ponteiro de arvore 'arvore *a1', não retorna
*nenhum parametro. A função apenas checa se o ponteiro é valido, caso seja, imprime
*na tela a pergunta. Caso o ponteiro não seja valido (NULL), a função não faz nada (não havendo erros).
*/
void Le (arvore *a1)
{
    if (a1 != NULL)  //Checa se o ponteiro é valido (diferente de NULL)
    {
      printf ("%s\n" , a1->Pergunta);  //Imprime a pergunta do nó
    }

    return;
}

/**@brief Função para a navegação e leitura da pergunta para o nó 'sim' da arvore.
*
*Essa função recebe como parametro o endereço do ponteiro da arvore, e não retorna nenhum
*parametro. A função checa se o nó atual é valido e se o nó 'sim' é valido, caso sejam,
*o apontador passa a apontar para o nó 'sim' e a pergunta é lida.
*Caso em algum ponto o nó seja NULL, a função não faz nada, apenas retorna.
*/
void NavegaSim(arvore **pergunta)
{
  if((*pergunta) != NULL)  //Checa se o nó é valido (não NULL)
  {
    if((*pergunta)->sim != NULL)  //Checa se o nó->sim é valido (não NULL)
    {
      *pergunta = (*pergunta)->sim;  //Faz o apontador apontar para o nó 'sim'
      Le(*pergunta);  //Le a pergunta do nó 'sim'
    }
    else  //Caso o nó 'sim' não seja valido
    {
      *pergunta = NULL;
    }
  }
  return;
}

/**@brief Função para a navegação e leitura da pergunta para o nó 'nao' da arvore.
*
*Essa função recebe como parametro o endereço do ponteiro da arvore, e não retorna nenhum
*parametro. A função checa se o nó atual é valido e se o nó 'nao' é valido, caso sejam,
*o apontador passa a apontar para o nó 'nao' e a pergunta é lida.
*Caso em algum ponto o nó seja NULL, a função não faz nada, apenas retorna.
*/
void NavegaNao(arvore **pergunta)
{
  if((*pergunta) != NULL)  //Checa se o nó é valido (não NULL)
  {
    if((*pergunta)->nao != NULL)  //Checa se o nó->'nao' é valido (não NULL)
    {
      *pergunta = (*pergunta)->nao;  //Faz o apontador apontar para o nó 'nao'
      Le(*pergunta);  //Le a pergunta do nó 'nao'
    }
    else  //Caso o nó 'nao' não seja valido
    {
      *pergunta = NULL;
    }
  }
  return;
}

/**@brief Função para apagar a arvore da memória.
*
*Essa função recebe como parametro o endereço do ponteiro da arvore 'arvore **ainicio'
*e não retorna nenhum parametro. A função navega recursivamente para o ultimo nó sim, em seguida o ultimo
*nó nao, e vai apagando a arvore. A função checa se o nó é NULL, para evitar erros e conseguir apagar de forma
*recursiva. Caso seja inserido um nó invalido não NULL, pode ser que ocorra um erro de SegFault.
*/
void Desconstroi (arvore **ainicio)
{
    if (*ainicio != NULL)  //Checa se o nó é valido (não NULL)
    {
        Desconstroi (&((*ainicio)->sim));  //Faz a chamada recursiva para a esquerda (sim)
        Desconstroi (&((*ainicio)->nao));  //Faz a chamada recursiva para a direita (nao)
        free (*ainicio);  //Apaga o nó
        *ainicio = NULL;  //Aponta o nó apagado para NULL (para evitar erros)
    }

    return;
}

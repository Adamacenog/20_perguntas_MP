/*
*Propriedade de Andre Garrido Damaceno.
*mat. 15/0117531.
*/

/**
 * @file Arvore.c
 * @author Andre Garrido Damaceno
 * @brief Arquivo que contem a biblioteca de manipulação e criação da arvore.
 *
 */

/**Como esse arquivo contem a biblioteca da arvore, necessita dos headers padrões e de
 *de funções auxiliares.
 */

/**@brief Header de funções padrão, para I/O, manipulação de strings e asserts.
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

/**@brief Função de criação da arvore de forma manual.
*
*Parâmetros: Essa função recebe como parametro o endereço de um ponteiro de arvore 'arvore **ainicio' (para sua criação),
*uma string 'char *no' para a informação a respeito do nó atual para o usuário, um inteiro 'int size', para impedir
*a criação de mais que 20 níveis de perguntas (para garantir que o usuário poderá responder apenas 20 perguntas no máximo).
*A função não retorna nenhum parametro.
*
*Tratamento de Erros: Caso haja erro de alocação de memória em 'Constroi_Manual' ou nas funções que ela chama, o programa é encerrado com erro.
*
*Descrição: Essa função cria a arvore de acordo com as perguntas inseridas pelo usuário, sendo possível o usuário criar quantas
*perguntas quiser (com o limite de 1048576 perguntas), podendo parar de inserir quando quiser.
*
*Assertivas de entrada: string 'no' não ser null, size ser no máximo 20.
*
*Requisitos: A função deve criar uma árvore binária com todas as perguntas inseridas pelo usuario, mostrando para o usuário sempre,
*o lugar da árvore em que ele está. Deve também inserir apenas no máximo 20 níveis de perguntas.
*
*Hipóteses: A árvore tem o tamanho alocado ideal, a string tem seu tamanho alocado ideal, a arvore deve possuir apenas 20 níveis de
*perguntas. Ao final, toda memória alocada para a string deve ser liberada, apenas a memoria alocada da arvore deve se manter.
*
*Assertivas de saida: alocações internas para strings desalocadas.
*
*Interface explicita: estrutura de árvore '**ainicio', string '*no', profundidade da árvore 'size'
*
*Interface implicita: Não há.
*
*Contrato na especificação: A função deve receber uma árvore vazia ou incompleta, uma string com a localização do nó atual
*e o tamanho atual da profundidade da árvore. A saída de cada chamada vai ser ou um nó null ou um nó de árvore com uma pergunta,
*dependendo apenas se o usuário quis ou não inserir algo naquele nó, e se ainda não havia sido preenchidas os 20 níveis da árvore.
*
*/
void Constroi_Manual (arvore **ainicio, char *no, unsigned int size)
{
  assert(size < 21); //Certifica que no máximo serão inseridos 20 níveis.
  assert(no != NULL); //Certifica que a string nunca é nula.

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
        noFilho = PosicaoNo(no, fSim);  //Concatenação da string sim
        Constroi_Manual (&((*ainicio)->sim), noFilho, (size + 1));  //Constroi para a esquerda (sim)
        free(noFilho);  //Remove a concatenação feita
        noFilho = NULL;
        noFilho = PosicaoNo(no, fNao);  //Concatenação para a string nao
        Constroi_Manual (&((*ainicio)->nao), noFilho, (size + 1));  //Constroi para a direita (nao)
        free(noFilho);  //Remove a concatenação feita
        noFilho = NULL;
        assert(noFilho == NULL); //As strings alocadas sejam desalocadas
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
*Parametros: Essa função recebe como parametro o endereço de um ponteiro de arvore 'arvore **ainicio' (para sua criação)
*e um arquivo (para a leitura das perguntas e criação da arvore). A função não retorna nenhum parametro.
*
*Tratamento de erros: Caso haja erro de alocação de memória em 'Constroi_TXT' o programa é encerrado com erro.
*
*Descrição: Essa função cria a arvore de acordo com um arquivo de texto aberto pelo usuário, sendo os nós nulos identificados
*por pontos '.'.
*
*Assertivas de entrada: a função deve receber um arquivo não nulo.
*
*Requisitos: A função deve criar uma árvore binária de acordo com o arquivo de txt passado como parâmetro.
*
*Hipoteses: O tamanho da árvore é alocado com o tamanho correto, o arquivo txt é lido de forma correta.
*Ao final, deve ser alocada uma árvore em memória idêntica à árvore encontrada no arquivo txt.
*
*Assertivas de saida: Não há, pois o arquivo pode criar a árvore, ou ele ser em branco, não criando a árvore.
*
*Interface explicita: estrutura de árvore '**ainicio', arquivo '*arq'
*
*Interface implicita: Manipulação de arquivos pela variável '*arq'
*
*Contrato na especificação: A função deve receber uma árvore vazia ou incompleta, um arquivo de texto não nulo.
*A função deve criar ou aumentar os nós da árvore de acordo com o arquivo txt (sendo possível inclusive não
*criar nenhum nó ou árvore, caso o arquivo txt esteja em branco).
*
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
*Parametros: Essa função recebe como parametro o endereço do ponteiro de uma arvore 'arvore **ainicio',
*e o arquivo de texto a ser salvo as perguntas da arvore 'FILE *arq'. A função não retorna
*nenhum parametro.
*
*Tratamento de erros: Caso a função receba um arquivo null, nada ocorre.
*
*Descrição: A função salva a pergunta no arquivo .txt, caso o nó seja NULL, é salvo
*um '.' no arquivo. Caso o arquivo seja inexistente, a função não faz nada. Caso a arvore seja
*inexistente, a função salva apenas um '.' no .txt.
*
*Assertivas de entrada: A função deve receber um arquivo não nulo.
*
*Requisitos: Irá ser passado por parâmetro uma árvore e o arquivo txt a ser salvo, a função irá
*então salvar os dados da arvore no arquivo txt.
*
*Hipoteses: A função checa se o arquivo existe, se a arvore ja chegou no fim e salva todas as perguntas
*da arvore de forma adequada.
*
*Assertivas de saida: não há.
*
*Interface explicita: estrutura de árvore '**ainicio', arquivo '*arq'
*
*Interface implicita: Manipulação de arquivo pela variável '*arq'
*
*Contrato na especificação: A função irá salvar a árvore por completo no arquivo txt recebido como
*parametro, inclusive salvando no txt as partes da árvore que são NULL, representando-os com um '.'.
*
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
*Parametros: Essa função recebe como parametro um ponteiro de arvore 'arvore *a1', não retorna
*nenhum parametro.
*
*Tratamento de erros: Caso o ponteiro não seja valido (NULL), a função não faz nada (não havendo erros).
*
*Descrição:  A função apenas checa se o ponteiro é valido, caso seja, imprime na tela a pergunta.
*
*Assertivas de entrada: Ponteiro da árvore válido (não NULL).
*
*Requisitos: A função deve receber uma árvore não nula e imprimir a pergunta que se encontra no nó.
*
*Hipoteses: A função verifica se a árvore é ou não válida e imprime apenas as perguntas de nós validos.
*
*Assertivas de saida: não há.
*
*Interface explicita: estrutura de árvore '**arv'
*
*Interface implicita: Não há.
*
*Contrato na especificação: A função recebe uma árvore como parametro, verifica se ela é valida, apenas
*caso ela seja válida a função imprime a pergunta do nó. Caso não seja valida nada acontece.
*
*/
void Le (arvore *arv)
{
    if (arv != NULL)  //Checa se o ponteiro é valido (diferente de NULL)
    {
      printf ("%s\n" , arv->Pergunta);  //Imprime a pergunta do nó
    }

    return;
}

/**@brief Função para a navegação e leitura da pergunta para o nó 'sim' da arvore.
*
*Parametros: Essa função recebe como parametro o endereço do ponteiro da arvore, e não retorna nenhum
*parametro.
*
*Tratamento de erros: Caso em algum ponto o nó seja NULL, a função não faz nada, apenas retorna.
*
*Descrição: A função checa se o nó atual é valido e se o nó 'sim' é valido, caso sejam,
*o apontador passa a apontar para o nó 'sim' e a pergunta é lida.
*
*Assertivas de entrada: A árvore recebida como parametro e o nó que será navegado não podem ser NULL.
*
*Requisitos: A função deve navegar para o nó 'sim' da arvore recebida como parametro, em seguida ler a
*pergunta desse nó.
*
*Hipoteses: A função lê apenas perguntas validas com nós validos.
*
*Assertivas de saida: não há, pois o nó pode .
*
*Interface explicita: estrutura de árvore '**pergunta'
*
*Interface implicita: Não há.
*
*Contrato na especificação: A função deve receber um nó de árvore, avaliar se ele é valido (não NULL),
*caso seja válido verificar o nó 'sim', caso o nó 'sim' seja válido, navega para ele e imprime a
*pergunta do nó.
*
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
*Parametros: Essa função recebe como parametro o endereço do ponteiro da arvore, e não retorna nenhum
*parametro.
*
*Tratamento de erros: Caso em algum ponto o nó seja NULL, a função não faz nada, apenas retorna.
*
*Descrição: A função checa se o nó atual é valido e se o nó 'nao' é valido, caso sejam,
*o apontador passa a apontar para o nó 'nao' e a pergunta é lida.
*
*Assertivas de entrada: A árvore recebida como parametro e o nó que será navegado não podem ser NULL.
*
*Requisitos: A função deve navegar para o nó 'nao' da arvore recebida como parametro, em seguida ler a
*pergunta desse nó.
*
*Hipoteses: A função lê apenas perguntas validas com nós validos.
*
*Assertivas de saida: não há, pois o nó pode .
*
*Interface explicita: estrutura de árvore '**pergunta'
*
*Interface implicita: Não há.
*
*Contrato na especificação: A função deve receber um nó de árvore, avaliar se ele é valido (não NULL),
*caso seja válido verificar o nó 'nao', caso o nó 'nao' seja válido, navega para ele e imprime a
*pergunta do nó.
*
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
*Parametros: Essa função recebe como parametro o endereço do ponteiro da arvore 'arvore **ainicio'
*e não retorna nenhum parametro.
*
*Tratamento de erros: Caso seja inserido um nó invalido não NULL, pode ser que ocorra um erro de SegFault.
*
*Descrição: A função navega recursivamente para o ultimo nó sim, em seguida o ultimo nó nao, e vai apagando
*a arvore. A função checa se o nó é NULL, para evitar erros e conseguir apagar de forma recursiva.
*
*Assertivas de entrada: Nó da árvore válido (não NULL)
*
*Requisitos: A função deve receber uma árvore não nula, e apagar todos seus nós, liberando toda a memória alocada
*da árvore.
*
*Hipoteses: A funçaõ verifica adequadamente os nós da árvore, sempre libera a memória de forma adequada.
*
*Assertivas de saida: Nó da árvore ser NULL.
*
*Interface explicita: estrutura de árvore '**ainicio'
*
*Interface implicita: Não há.
*
*Contrato na especificação: A função deve receber um endereço de árvore alocado na memória, e deve então
*desalocar toda a memória alocada pela árvore, liberando todos os nós.
*
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

    assert(*ainicio == NULL); //Nó da árvore deve ter sido liberado

    return;
}

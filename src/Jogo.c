/*
*Propriedade de Andre Garrido Damaceno.
*mat. 15/0117531.
*/

/**
 * @file Jogo.c
 * @author Andre Garrido Damaceno
 * @brief Arquivo que contem a Main e uma função de chamadas para executar o jogo.
 *
 */

 /**Como esse arquivo contem a função que inicializa o jogo, são necessários todos arquivos
 *headers que o programa utiliza.
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

/**@brief Header da biblioteca que inicializa o jogo.
*/
#ifndef _Jogo_library
  #define _Jogo_library
    #include "Jogo.h"
#endif

/**@brief Main de inicialização do jogo.
*
*Parametros: Não recebe nenhum parâmetro de entrada, retorna um inteiro no fim da execução,
*sendo 0 - execução bem sucedida, outros valores caso contrário.
*
*Tratamento de erros: Não há, apenas há chamadas de funções. Os tratamentos são feitos dentro
*das funções chamadas.
*
*Descrição: A main apenas chama a função de inicialização 'Jogo_init()',
*que chama as funções do jogo em ordem lógica para sua execução normal.
*
*Assertivas de entrada: Não há
*
*Requisitos: Chamar a função de inicialização 'Jogo_init'.
*
*Hipoteses: A função é chamada com sucesso e o jogo é inicializado.
*
*Assertivas de saida: Não há
*
*Interface explicita:
*
*Interface implicita:
*
*Contrato na especificação: A função deve apenas chamar a função 'Jogo_init'.
*
*/
int main()
{
  Jogo_init();
  return 0;
}

/**@brief Função de inicialização do jogo.
*
*Parametros: A função não recebe nem retorna nenhum parâmentro.
*
*Tratamento de erros: Caso haja algum erro em alocação de memória, o programa é encerrado. Outros casos variam, caso a arvore seja null,
*eventualmente havera a opção de tentar recriar a arvore. Caso haja algum outro erro totalmente imprevisto, ou as funções internas o conterão,
*ou o programa finalizará com erro.
*
*Descrição: Nessa função, primeiramente é populado os dados na arvore (por arquivo de texto ou por criação manual). Em seguida,
*inicializa-se o jogo ao chamar a função 'Vinte_Perguntas()', ao fim, é perguntado ao usuário se quer salvar os dados de seu jogo
*em um arquivo .txt, e por fim é finalizada a execução (deletando a arvore da memoria).
*
*Assertivas de entrada: árvore ser NULL, arquivo ser NULL.
*
*Requisitos: A função deve chamar a função de popular os dados da árvore (de acordo com a escolha do usuario, por arquivo texto
*ou manualmente), em seguida chamar a função de executar o jogo, por fim, verificar se o usuario quer salvar a árvore do Jogo
*em um arquivo de texto, e desalocar a memoria da árvore.
*
*Hipoteses: Toda memória alocada é feita com o tamanho correto, toda memória alocada é desalocada após o uso, todos os arquivos
*de texto abertos são fechados.
*
*Assertivas de saida: A árvore tem que ser NULL (desalocada).
*
*Interface explicita:
*
*Interface implicita:
*
*Contrato na especificação: A função não recebe nenhum parametro nem retorna nenhum parametro, deve apenas chamar as funções
*principais capazes de fazer o jogo rodar, ou seja, em ordem, deve ser populada a árvore com perguntas, em seguida ser chamada a
*função de execução do jogo e por fim deve ser dada a escolha de salvar a arvore do jogo em um arquivo de texto. Devem ser finalizadas
*todas as memorias alocadas e arquivos abertos.
*
*/
void Jogo_init(void)
{
  int opcao;  //Respostas do usuário (podendo ser 'sim', 'nao', 'criar', 'abrir')
  arvore *ainicio = NULL;  //arvore com os dados do jogo (as perguntas)
  FILE *arq = NULL;  //Ponteiro usado para manipulação de arquivos (abrir ou salvar em .txt)

  assert(ainicio == NULL); //Arvore deve ser NULL no inicio
  assert(arq == NULL); //Arquivo deve ser NULL no inicio

  printf("\nDigite 'abrir' para abrir um arquivo ou 'criar' para criar um jogo do zero\n");
  opcao = Resposta(inicializacao);  //Tipo inicializacao tem as opções 'abrir' ou 'criar' apenas
  if(opcao == Rabrir)
  {
    char r[2] = "r";
    char aberto[7] = "aberto";  //Apenas para informar ao usuário se o arquivo é usado para abrir em .txt
    arq = CriaArquivo(r, aberto);
    Constroi_TXT(&ainicio, arq);  //Cria a arvore em memoria, a partir de um .txt
    if(arq != NULL)  //Caso o arquivo não exista, para evitar um segmentation faut
    {
        fclose(arq);
    }
  }
  if(opcao == Rcriar)
  {
    char pai[4] = "PAI";  //Sinalização do nó inicial da arvore
    Constroi_Manual(&ainicio, pai, 0);  //Função de criação da arvore de forma manual
  }

  Vinte_Perguntas(&ainicio, 0);  //Função de execução do jogo
  printf("\nDigite 'sim' para salvar as perguntas em um arquivo ou 'nao' para finalizar\n");
  opcao = Resposta(simples);  //Tipo simples tem as opções 'sim' ou 'nao' apenas
  if(opcao == Rsim)
  {
    char w[2] = "w";
    char salvo[6] = "salvo";  //Apenas para informar ao usuário se o arquivo é usado para salvar em .txt
    arq = CriaArquivo(w,salvo);
    Salva_TXT(&ainicio,arq);  //Salva efetivamente os dados da arvore em um .txt
    if(arq != NULL)  //Caso o arquivo não exista, para evitar um segmentation faut
    {
        fclose(arq);
    }
  }
  Desconstroi(&ainicio);  //Remove a arvore da memoria

  assert(ainicio == NULL);

  return;
}

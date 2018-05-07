/*
*Propriedade de Andre Garrido Damaceno.
*mat. 15/0117531.
*/

/**
 * @file Funcs.c
 * @author Andre Garrido Damaceno
 * @brief Arquivo que contem a função de respostas do usuário, concatenação de string e de criar arquivos txt (abrir ou salvar).
 *
 */

/**Como esse arquivo contem apenas funções auxiliares, necessita apenas dos headers padrões.
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

/**@brief Header da biblioteca de funções (criação de arquivo e concatenação de strings).
*/
#ifndef _Funcs_library
  #define _Funcs_library
    #include "Funcs.h"
#endif

/**@brief Função para pegar o input especifico de opções do usuario.
*
*Parametros: Essa função recebe como parametro um inteiro 'int tipo', que especifica o tipo de opção
*que o usuário terá e retorna um inteiro que representa a opção selecionada (escrita) pelo usuario.
*
*Tratamento de erros: Caso o usuario tenha respondido algo invalido, é mencionada as respostas que a pergunta espera, e
*dada a chance do usuario responder novamente, caso contrario, é retornado o equivalente da resposta
*do usuario pelo inteiro. Caso haja um erro de leitura pelo 'scanf' (usuario digita mais que 6 caracteres),
* apenas é mencionada a mensagem dos tipos da resposta disponivel multiplas vezes, qualquer outro tipo de
*erro é desconhecido o comportamento (pois estariam dependendo das funções 'strcmp', 'strlen' e toupper).
*
*Descrição: Essa função inicialmente lê a resposta escrita pelo usuário e delimita as respostas para o Tipo
*da pergunta, sendo 'simples' - para perguntas de 'sim' ou 'nao', 'multipla' - para perguntas de
*'sim', 'nao', 'editar' ou 'apagar', e 'inicializacao' - para perguntas de 'abrir' ou 'criar'.
*
*Assertivas de entrada: O valor de entrada deve estar entre 0 (pergunta multipla) e 2 (pergunta de inicialização).
*
*Requisitos: A função deve receber a resposta do usuário de acordo com o contexto (se é uma pergunta multipla,
*de inicialização ou simples), e retornar uma resposta válida apenas. A função deve ficar perguntando ao usuário
*até que uma resposta válida seja respondida.
*
*Hipoteses: A leitura da opção é feita de forma correta, de acordo com o tamanho do vetor que fica armazenada a
*resposta do usuário. O loop é feito apenas quando há uma resposta incorreta, saindo dele sempre que a resposta
*correta ser respondida.
*
*Assertivas de saida: O retorno tem que estar entre 0 (Rsim) e 5 (Rabrir).
*
*Interface explicita:
*
*Interface implicita:
*
*Contrato na especificação: A função recebe como parametro o tipo da pergunta e deve retornar com a resposta
*do usuário de acordo com o tipo da pergunta recebida. Caso ela receba um tipo, e é respondido uma resposta
*válida em outros tipos mas não no tipo recebido, a resposta deve ser considerada inválida.
*
*/
unsigned int Resposta(unsigned int tipo)
{
  assert(tipo < 3);
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

/**@brief Função de Criação de arquivos (abertura ou leitura).
*
*Parametros: Essa função recebe como parametro o tipo de abertura 'char *type' ("r" - para read, "w" - para write)
*e também uma string 'char *opcao' para ser impresso na tela (informando ao usuário se o arquivo esta sendo aberto ou salvo).
*A função retorna o arquivo 'FILE *'.
*
*Tratamento de erros: Caso o arquivo não exista, ou ele será criado (no caso do tipo "w" - write), ou a função retornará NULL no 'FILE *'.
*
*Descrição: Essa função apenas abre um arquivo e o retorna para o usuário.
*
*Assertivas de entrada: string 'type' e 'opcao' não NULLs.
*
*Requisitos: A função deve perguntar ao usuário qual o nome do arquivo e abrir ou criar um arquivo de acordo com o parâmetro 'type'.
*
*Hipoteses: A função deve abrir o arquivo de forma adequada de acordo com a forma de abertura 'type' requisitado, retornando o arquivos
*aberto/criado.
*
*Assertivas de saida: Arquivo aberto/criado não ser NUL
*
*Interface explicita:
*
*Interface implicita:
*
*Contrato na especificação: A função deve receber a forma de abertura/criação do arquivo 'type', e uma string com a informação para o
*usuário do que está ocorrendo. Então, deve ser aberto/criado o arquivo de acordo com o parâmetro 'type' e o nome informado pelo usuário,
*e por fim, deve ser retornado o arquivo.
*
*/
FILE * CriaArquivo(char *type, char *opcao)
{
  assert(type != NULL); //Verifica se o tipo é NULL
  assert(opcao != NULL); //Verifica se a opção é NULL

  FILE *arq;  //Ponteiro para o arquivo (para abrir/salvar em .txt).
  char nome[20];  //Variável usada para salvar o nome do arquivo a ser salvo/aberto.
  printf("Digite o nome do arquivo a ser %s: \n",opcao);
  scanf("%19s",nome);
  arq = fopen(nome, type);  //Captura do arquivo de acordo com seu nome e o tipo de abertura, no computador.

  if(arq == NULL)
  {
    printf("\nArquivo não encontrado!\n");
  }

  return arq;
}

/**@brief Função de concatenação de string.
*
*Parametros: Essa função recebe como parametro duas strings 'char *no' e 'char *filho', concatena a string 'filho' na
*string 'no', e retorna essa string 'char *'.
*
*Tratamento de erros: Caso o computador negue a alocação de memória, o programa é finalizado.
*
*Descrição: Inicialmente a função aloca memória suficiente para a concatenação das strings, em seguida copia a string 'no'
*para a memoria alocada, por fim, concatena a string 'filho' na memoria alocada, retornando assim a string com 'no' e
*'filho' concatenados devidamente.
*
*Assertivas de entrada: As strings 'no' e 'filho' não podem ser NULLs.
*
*Requisitos: A função deve concatenar as duas strings recebidas 'no' e 'filho' e retornar a string concatenada.
*
*Hipoteses: A função aloca devidamente memória suficiente para a string final concatenada, e faz a concatenação de forma
*correta, concatenando no sentido 'no' e 'filho'.
*
*Assertivas de saida: A string com o resultado da concatenação não deve ser NULL, O tamanho da string retornada deve ser
*o tamanho de 'no' + 'filho', e o final da string deve conter o caracter '\0'.
*
*Interface explicita:
*
*Interface implicita:
*
*Contrato na especificação: A função deve receber duas strings 'no' e 'filho' não nulas, deve então alocar uma nova string
*'noFilho' que deve possuir o tamanho de 'no' e 'filho' juntas, em seguida colocar o resultado da concatenação de 'no' e 'filho' em
*'noFilho' e retornar 'noFilho'.
*
*/
char * PosicaoNo(char *no, char *filho)
{
  assert(no != NULL); //Verifica a string 'no' diferente de NULL
  assert(filho != NULL); //Verifica a string 'filho' diferente de NULL

  char *noFilho = (char *) malloc (strlen(no) + strlen(filho) + 1);  //Alocação de memoria do tamanho de ambas strings + o finalizador '\0'

  if(noFilho == NULL)  //Caso a alocação dê erro, o programa é finalizado.
  {
    exit(1);
  }

  strcpy(noFilho, no);  //Copia a string 'no' para o novo espaço alocado
  strcat(noFilho, filho);  //Concatena a string 'no' com a string 'filho'
  noFilho[strlen(no) + strlen(filho) + 1] = '\0'; //Coloca o '\0' no final da string

  assert(noFilho != NULL);
  assert(strlen(noFilho) == (strlen(no) + strlen(filho)));
  assert(noFilho[strlen(noFilho) + 1] == '\0');

  return noFilho;
}

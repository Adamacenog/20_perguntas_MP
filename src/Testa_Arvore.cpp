/*
*Propriedade de Andre Garrido Damaceno.
*mat. 15/0117531.
*/

/**
 * @file Testa_Arvore.cpp
 * @author Andre Garrido Damaceno
 * @brief Arquivo que contem os testes do jogo de 20 perguntas.
 *
 *Como esse arquivo contem os testes, necessita dos headers de toda
 *a biblioteca do jogo.
 */

#define CATCH_CONFIG_MAIN

/*
*@brief Header da biblioteca de testes.
*/
#ifndef _Catch
  #define _Catch
    #include "catch.hpp"
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
*@brief Teste da função 'Constroi_Manual'
*Testes feitos e criterio de aceitação:
*Teste de criação de uma arvore NULL - criterio de aceitação é a arvore ser
*null e o programa se conter.
*Teste de criação no nó pai apenas - criterio de aceitação nó pai criado e os nós filhos NULL.
*Teste de criação no pai e no filho 'SIM' - criterio de aceitação pai nao ser NULL,
*filho 'sim' nao ser NULL, filho 'sim' 'sim' ser NULL, filho 'sim' 'nao' ser NULL e filho 'nao' ser
*NULL.
*Teste de criação no pai e no filho 'NAO' - criterio de aceitação pai nao
*ser NULL, filho 'nao' nao ser NULL, filho 'nao' 'sim' ser NULL, filho 'nao' 'nao'
*ser NULL e filho 'sim' ser NULL. Teste de criação de um nó pai, um nó filho 'sim',
*um nó filho 'nao' - criterio de aceitação pai nao ser NULL, filho 'nao' nao ser NULL,
*filho 'nao' 'sim' ser NULL, filho 'nao' 'nao' ser NULL, filho 'sim' não ser NULL
*filho 'sim' nao ser NULL e filho 'sim' 'sim' ser NULL.
*Todos os testes foram bem sucedidos.
*/
TEST_CASE( "Creating a tree from user input", "Prove that the tree is created" )
{
  arvore *ainicio;
  char pai[4] = "PAI";
  printf("\n\n******************************************************************\n");
  printf("SIGA AS INSTRUÇÕES EM CAIXA ALTA PARA QUE OS TESTES DEEM CERTO!!!\n");
  printf("******************************************************************\n");
  printf("\n\n******************************************************************\n");
  printf("DIGITE 'SAIR' PARA O TESTE DAR CERTO\n");
  printf("******************************************************************\n");
  Constroi_Manual(&ainicio,pai,0);
  REQUIRE( ainicio == NULL );
  printf("\n******************************************************************\n");
  printf("AGORA DIGITE QUALQUER COISA VALIDA, DEPOIS 'SAIR' 2 VEZES\n");
  printf("******************************************************************\n");
  Constroi_Manual(&ainicio,pai,0);
  REQUIRE( ainicio != NULL );
  REQUIRE( ainicio->sim == NULL );
  REQUIRE( ainicio->nao == NULL );
  printf("\n******************************************************************\n");
  printf("AGORA DIGITE QUALQUER COISA VALIDA, DEPOIS ALGO VALIDO E DEPOIS 'SAIR' 3 VEZES\n");
  printf("******************************************************************\n");
  Constroi_Manual(&ainicio,pai,0);
  REQUIRE( ainicio != NULL );
  REQUIRE( ainicio->sim != NULL );
  REQUIRE( ainicio->sim->sim == NULL );
  REQUIRE( ainicio->sim->nao == NULL );
  REQUIRE( ainicio->nao == NULL );
  printf("\n******************************************************************\n");
  printf("AGORA DIGITE QUALQUER COISA VALIDA, DEPOIS 'SAIR', DEPOIS ALGO VALIDO, DEPOIS 'SAIR' 2 VEZES'\n");
  printf("******************************************************************\n");
  Constroi_Manual(&ainicio,pai,0);
  REQUIRE( ainicio != NULL );
  REQUIRE( ainicio->sim == NULL );
  REQUIRE( ainicio->nao->sim == NULL );
  REQUIRE( ainicio->nao->nao == NULL );
  REQUIRE( ainicio->nao != NULL );
  printf("\n******************************************************************\n");
  printf("AGORA DIGITE QUALQUER COISA VALIDA, DEPOIS ALGO VALIDO, DEPOIS 'SAIR' 2 VEZES' DEPOIS ALGO VALIDO, DEPOIS 'SAIR' 2 VEZES'\n");
  printf("******************************************************************\n");
  Constroi_Manual(&ainicio,pai,0);
  REQUIRE( ainicio != NULL );
  REQUIRE( ainicio->sim != NULL );
  REQUIRE( ainicio->sim->sim == NULL );
  REQUIRE( ainicio->sim->nao == NULL );
  REQUIRE( ainicio->nao != NULL );
  REQUIRE( ainicio->nao->sim == NULL );
  REQUIRE( ainicio->nao->nao == NULL );
}

/*
*@brief Testes da função 'Constroi_TXT' - Criação normal da arvore.
*Testes feitos e criterio de aceitação:
*Teste de criação da arvore com um arquivo existente (onde os nós pai, filho 'sim'
*filho 'nao' existem na arvore), os criterios de aceitação foram os nós descritos
*serem iguais à frases escritas no teste (comparação feita por strcmp), e os dos filhos
*'sim' e 'nao' serem NULL.
*Todos os testes foram bem sucedidos.
*/
TEST_CASE( "Creating a tree from a file", "Prove that the tree is created" )
{
  arvore *ainicio;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/Perguntas.txt", "r");
  Constroi_TXT(&ainicio,arq);
  REQUIRE( ainicio != NULL );
  REQUIRE( strcmp(ainicio->Pergunta, "O objeto a ser descoberto é um aviao?") == 0);
  REQUIRE( strcmp(ainicio->sim->Pergunta, "O objeto é um abacaxi?") == 0);
  REQUIRE( strcmp(ainicio->nao->Pergunta, "O objeto é de comer?") == 0);
  REQUIRE( ainicio->sim->sim == NULL);
  REQUIRE( ainicio->sim->nao == NULL);
  REQUIRE( ainicio->nao->sim == NULL);
  REQUIRE( ainicio->nao->nao == NULL);
  fclose(arq);
}

/*
*@brief Testes da função 'Constroi_TXT' - tentativa de criar arvore por arquivo Null
*Foi feito um teste, abrindo um arquivo inexistente pela função 'fopen', e passado
*o arquivo para a função 'Constroi_TXT', os criterios de aceitação são a Arvore
*ser NULL, e o programa não ter problemas em sua execução.
*O teste passou com sucesso, e tudo ocorreu como esperado.
*/
TEST_CASE( "Trying to create a tree from an non existing file", "Prove that the tree is not created" )
{
  arvore *ainicio;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/naoexiste.txt", "r");
  Constroi_TXT(&ainicio,arq);
  REQUIRE( ainicio == NULL );
}

/*
*@brief Testes da função 'Salva_TXT' - tentativa de salvar arvore NULL.
*Foi feito um teste, abrindo um arquivo inexistente na forma "w", então
*foi salva uma arvore NULL no arquivo. Em seguida, foi aberto esse arquivo
*e construida a arvore a partir dele com a função 'Constroi_TXT', e por fim,
*o criterio de aceitação é a arvore criada ser NULL.
*O teste passou com sucesso, tudo ocorreu como esperado.
*/
TEST_CASE ("Trying to navigate to save a NULL tree to file", "Prove that the txt saves '.'")
{
  arvore *ainicio = NULL;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/NullTree.txt","w");
  Salva_TXT(&ainicio,arq);
  fclose(arq);
  arq = fopen("./Arquivos_de_teste/NullTree.txt","r");
  Constroi_TXT(&ainicio,arq);
  fclose(arq);
  REQUIRE(ainicio == NULL);
}

/*
*@brief Testes da função 'Salva_TXT' - tentativa de salvar arvore existente.
*Foi aberto um arquivo txt existente com dados de arvore, criada a arvore pela
*função 'Constroi_TXT', em seguida foi salva a arvore criada pela função 'Salva_TXT'
*em um outro arquivo de texto inexistente ('Perguntas2.txt'), por fim, para verificar
*se tudo ocorreu como esperado, foi aberto esse arquivo txt, feito a arvore novamente,
*e checada todas as perguntas que existiam no arquivo, e também se todos os nós inexistentes
*da arvore eram NULL.
*Todos os criterios passaram, tudo ocorreu como esperado.
*/
TEST_CASE ("Saving a tree to file", "Prove that the txt saves the tree")
{
  arvore *ainicio = NULL;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/Perguntas.txt","r");
  Constroi_TXT(&ainicio,arq);
  fclose(arq);
  arq = fopen("./Arquivos_de_teste/Perguntas2.txt","w");
  Salva_TXT(&ainicio,arq);
  fclose(arq);
  arq = fopen("./Arquivos_de_teste/Perguntas2.txt","r");
  Constroi_TXT(&ainicio,arq);
  fclose(arq);
  REQUIRE( ainicio != NULL );
  REQUIRE( strcmp(ainicio->Pergunta, "O objeto a ser descoberto é um aviao?") == 0);
  REQUIRE( strcmp(ainicio->sim->Pergunta, "O objeto é um abacaxi?") == 0);
  REQUIRE( strcmp(ainicio->nao->Pergunta, "O objeto é de comer?") == 0);
  REQUIRE( ainicio->sim->sim == NULL);
  REQUIRE( ainicio->sim->nao == NULL);
  REQUIRE( ainicio->nao->sim == NULL);
  REQUIRE( ainicio->nao->nao == NULL);
}

/*
*@brief Testes da função 'Salva_TXT' - tentativa de salvar arquivo inexistente.
*Foi aberto um arquivo txt na função "r", em seguida foi tentado salvar uma arvore
*NULL em um arquivo inexistente, os criterios de aceitação são a função se conter,
*a arvore ser NULL, o arquivo ser NULL.
*Todos os testes passaram com sucesso.
*/
TEST_CASE ("Saving tree to NULL file", "Prove that the function does nothing and contains the program")
{
  arvore *ainicio = NULL;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/naoexiste.txt", "r");
  Salva_TXT(&ainicio,arq);
  REQUIRE(ainicio == NULL);
  REQUIRE(arq == NULL);
}

/*
*@brief Teste da função 'Desconstroi' - Apagando uma arvore existente
*Foi criada uma arvore por um txt existente, em seguida, foi verificado que
*a arvore não era NULL, por fim, foi chamada a função de desconstrução, e o
*criterio de aceitação é que a função apagasse a arvore e seu ponteiro fosse Null
*no final.
*Todos os testes passaram com sucesso.
*/
TEST_CASE ("Freeing an existing tree", "the tree is freed")
{
  arvore *ainicio = NULL;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/Perguntas.txt","r");
  Constroi_TXT(&ainicio,arq);
  fclose(arq);
  REQUIRE(ainicio != NULL);
  Desconstroi(&ainicio);
  REQUIRE(ainicio == NULL);
}

/*
*@brief Teste da função 'Desconstroi' - Apagando uma arvore inexistente
*Foi passada para a função 'Desconstroi()' uma arvore NULL, o resultado
*esperado e criterio de aceitação é que o programa se contenha e que a
*arvore continue sendo NULL.
*Todos os testes passaram com sucesso.
*/
TEST_CASE ("Freeing a NULL tree", "the program is contained")
{
  arvore *ainicio = NULL;
  Desconstroi(&ainicio);
  REQUIRE(ainicio == NULL);
}

/*
*@brief Teste da função Le - lendo arvore existente
*Foi criada uma arvore por um arquivo txt existente e passado
*o ponteiro da arvore para a função 'Le()', o criterio de aceitação
*é que a mensagem da pergunta apareça na tela e o ponteiro da arvore
*não seja alterado.
*Todos os testes passaram com sucesso.
*/
TEST_CASE("Reading a tree question", "tree is unmodified and question is read")
{
  arvore *ainicio = NULL;
  arvore *anterior;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/Perguntas.txt","r");
  Constroi_TXT(&ainicio,arq);
  fclose(arq);
  anterior = ainicio;
  Le(ainicio);
  REQUIRE(anterior == ainicio);
}

/*
*@brief Teste da função Le - lendo arvore inexistente
*Foi passado um ponteiro NULL de arvore para a função 'Le()', o criterio de aceitação
*é que função não fizesse nada e se contenha e o ponteiro da arvore não fosse
*alterado de NULL.
*Todos os testes passaram com sucesso.
*/
TEST_CASE("Trying to read NULL tree", "Program is contained and function does nothing")
{
  arvore *ainicio = NULL;
  arvore *anterior;
  anterior = ainicio;
  Le(ainicio);
  REQUIRE(anterior == ainicio);
}

/*
*@brief Testes de navegação (sim e nao) - arvore existente
*Foi criada uma arvore por um arquivo txt, e inicializado as variaveis navegasim,
*naveganao e ainiciobackup com o endereço da arvore e verificado se todas continham
*o endereço da arvore, em seguida, foi feita a navegação NavegaSim em navegasim e
*NavegaNao em naveganao e o criterio de aceitação foi se o resultado dos ponteiros eram iguais aos ponteiros
*da arvore original no nó 'sim' e 'nao', por fim, mais uma vez foi chamada as funções NavegaSim e NavegaNao
*e verificado se os nós eram NULL (para checar se eram iguais à arvore original que é NULL).
*Todos os testes e verificações foram bem sucedidas.
*/
TEST_CASE("Trying to navigate to '->sim' and '->nao' and reading the question", "Tree goes to specific navigation and reads the question")
{
  arvore *ainicio = NULL;
  arvore *navegasim, *naveganao, *ainiciobackup;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/Perguntas.txt","r");
  Constroi_TXT(&ainicio,arq);
  fclose(arq);
  navegasim = ainicio;
  naveganao = ainicio;
  ainiciobackup = ainicio;
  REQUIRE(navegasim != NULL);
  REQUIRE(naveganao != NULL);
  REQUIRE(ainicio != NULL);
  REQUIRE(ainicio == ainiciobackup);
  NavegaSim(&navegasim);
  NavegaNao(&naveganao);
  REQUIRE(navegasim == ainicio->sim);
  REQUIRE(naveganao == ainicio->nao);
  NavegaSim(&navegasim);
  NavegaNao(&naveganao);
  REQUIRE(navegasim == NULL);
  REQUIRE(naveganao == NULL);
}

/*
*@brief Testes de navegação (sim e nao) - arvore inexistente
*Para esse teste, foi criado um ponteiro NULL, e feito a navegação de
*NavegaSim e NavegaNao passando como parametro o ponteiro NULL, para criterio
*de aceitação, verifica-se se a função se conteve e se os ponteiros continuam
*sendo NULL.
*Todos os testes e verificações foram bem sucedidos.
*/
TEST_CASE("Trying to navigate to '->sim' and '->nao' whith NULL tree", "Program is contained and function returns 2")
{
  arvore *ainicio = NULL;
  arvore *navegasim, *naveganao;
  navegasim = ainicio;
  naveganao = ainicio;
  NavegaSim(&navegasim);
  NavegaNao(&naveganao);
  REQUIRE(navegasim == NULL);
  REQUIRE(naveganao == NULL);
}

/*
*@brief Teste da função 'CriaArquivo' - arquivos existentes "r" e "w" e arquivos inexistentes
*Primeiramente é aberto um arquivo com a função "r", e criado uma arvore a partir desse arquivo,
*o teste de aceitação é que todos os nós do arquivo sejam iguais à strings colocadas no teste.
*Em seguida, cria-se um arquivo com a função "w", e é feito o teste de escrita, usando a função
*'Salva_TXT' para salvar a arvore no arquivo de texto, o criterio de aceitação é a função se
*conter e o arquivo ser criado com sucesso.
*Por fim, checa-se a abertura de um arquivo inexistente (passando o nome de um arquivo que nao
*se encontra no computador), o criterio de aceitação é que o arquivo seja NULL.
*Todos os testes e criterios passaram com sucesso.
*/
TEST_CASE("Creating/Opening a file (read) and (write)", "Function opens/creates the file")
{
  arvore *ainicio=NULL;
  char abrirP[28] = "Aberto (DIGITE 'teste.txt')";
  char abrirE[30] = "Aberto (DIGITE 'escreve.txt')";
  char Escrever[31] = "Escrito (DIGITE 'escreve.txt')";
  char qlqr[57] = "aberto - (DIGITE QUALQUER COISA QUE NAO SEJA UM ARQUIVO)";
  char r[2] = "r";
  char w[2] = "w";
  FILE *arq;
  arq = CriaArquivo(r,abrirP);
  REQUIRE(arq != NULL);
  Constroi_TXT(&ainicio,arq);
  REQUIRE(ainicio != NULL);
  REQUIRE( strcmp(ainicio->Pergunta, "O objeto a ser descoberto é um aviao?") == 0);
  REQUIRE( strcmp(ainicio->sim->Pergunta, "O objeto é um abacaxi?") == 0);
  REQUIRE( strcmp(ainicio->nao->Pergunta, "O objeto é de comer?") == 0);
  fclose(arq);
  arq = CriaArquivo(w, Escrever);
  REQUIRE(arq != NULL);
  Salva_TXT(&ainicio,arq);
  fclose(arq);
  arq = CriaArquivo(r, abrirE);
  Constroi_TXT(&ainicio,arq);
  REQUIRE( strcmp(ainicio->Pergunta, "O objeto a ser descoberto é um aviao?") == 0);
  REQUIRE( strcmp(ainicio->sim->Pergunta, "O objeto é um abacaxi?") == 0);
  REQUIRE( strcmp(ainicio->nao->Pergunta, "O objeto é de comer?") == 0);
  fclose(arq);
  arq = CriaArquivo(r, qlqr);
  REQUIRE(arq == NULL);
}

/*
*@brief Testando a função 'ConstroiNo' - Concatenação de strings existente e inexistente
*São declaradas strings e feito criterios de aceitação, usando a função 'strcmp' para
*comparar as strings concatenadas com strings digitadas no teste, testando inclusive a
*concatenação de duas strings vazias, sendo o resultado valido da concatenação string vazia.
*Todos os testes e criterios passaram com sucesso.
*/
TEST_CASE("Function that concatenates strings", "Should concatenate the string")
{
  char tes[4] = "tes";
  char tando[6] = "tando";
  char vazio[1] = "";

  REQUIRE(strcmp(ConstroiNo(tes,tando),"testando") == 0);
  REQUIRE(strcmp(ConstroiNo(vazio,tando),"tando") == 0);
  REQUIRE(strcmp(ConstroiNo(tes,vazio),"tes") == 0);
  REQUIRE(strcmp(ConstroiNo(vazio,vazio),"") == 0);
  REQUIRE(strcmp(ConstroiNo(tando,tes),"tandotes") == 0);
}

/*
*@brief Testando a função 'Resposta' - teste para o tipo 'simples', 'multipla' e inicializacao
*Os testes são feitos ao passar todas as possiveis combinações (maiusculo ou minusculo) dos
*resultados das possiveis respostas, e feito uma comparação se a resposta é como a esperada.
*O criterio de aceitação é que todas as variaveis em todas as suas combinações possiveis de
*maiusculo e minusculo sejam reconhecidos, e que as mensagens de erro ao digitar um caracter
*invalido seja exibido de forma correta na tela.
*Todos os testes e requisitos passaram com sucesso.
*/
TEST_CASE("Testing user's answers in game", "Get only 'sim', 'nao', 'editar', 'apagar' answer and nothing else")
{
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'SIM'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Rsim);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'NAO'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Rnao);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'APAGAR'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Rapagar);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'EDITAR'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Reditar);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'sim'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Rsim);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'nao'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Rnao);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'apagar'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Rapagar);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'editar'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Reditar);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE QUALQUER COISA (DE ATE 6 CARACTERES) QUANTAS VEZES QUISER, E POR FIM 'EDITAR'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(multipla) == Reditar);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'SIM'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(simples) == Rsim);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'NAO'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(simples) == Rnao);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'sim'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(simples) == Rsim);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'nao'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(simples) == Rnao);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE QUALQUER COISA (DE ATE 6 CARACTERES) QUANTAS VEZES QUISER, E POR FIM 'SIM'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(simples) == Rsim);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'ABRIR'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(inicializacao) == Rabrir);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'CRIAR'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(inicializacao) == Rcriar);
  printf("PARA PASSAR NO TESTE, DIGITE 'abrir'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(inicializacao) == Rabrir);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE 'criar'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(inicializacao) == Rcriar);
  printf("\n******************************************************************\n");
  printf("PARA PASSAR NO TESTE, DIGITE QUALQUER COISA (DE ATE 6 CARACTERES) QUANTAS VEZES QUISER, E POR FIM 'ABRIR'\n");
  printf("******************************************************************\n");
  REQUIRE(Resposta(inicializacao) == Rabrir);
}

/*
*@brief Teste da função 'Vinte_Perguntas' - Arvore inexistente
*Nesse teste, foi testado o comportamento da função 'Vinte_Perguntas' quando recebe
*uma arvore Null, sendo o primeiro requisito que a arvore continuasse NULL, e que no segundo
*requisito que a arvore fosse criada (no minimo um nó).
*Todos os testes e requisitos passaram com sucesso.
*/
TEST_CASE("Receiving null tree or object was not guessed by Vinte_Perguntas", "The function should be contained, should ask the user to add more questions if less than 20 answers")
{
  arvore *ainicio = NULL;
  printf("\n******************************************************************\n");
  printf("DIGITE 'NAO', DEPOIS 'NAO'\n");
  printf("******************************************************************\n");
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio == NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'NAO', DEPOIS 'SIM', EM SEGUIDA CRIE APENAS UMA PERGUNTA EXTRA E DIGITE 'SAIR' 2 VEZES, DEPOIS RESPONDA A PERGUNTA E DIGITE NO FINAL 'SIM'\n");
  printf("******************************************************************\n");
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio != NULL);
}

/*
*@brief Teste da função 'Vinte_Perguntas' - Arvore existente, cheia, edição, apagar
*Foi testado inicialmente o comportamento da função 'Vinte_Perguntas' ao receber e navegar até o final de uma
*arvore com as 20 perguntas preenchidas, o criterio de aceitação é que o jogo finalizasse se o usuario chegou ou não
*no objeto que ele estava pensando. O outro teste foi de edição do nó principal, o criterio de aceitação foi que a string
*editada seja igual à string digitada no teste, e por fim, foi testado diversas situações de apagar, sendo as situações
*de apagar o nó pai, apagar os nós filhos e desistir de apagar um nó, para cada situação, respectivamente o criterio de
*aceitação é que o nó pai seja NULL, nós filhos sejam NULLs, nada ocorrece ao desistir de apagar e o jogo retorne normalmente
*na ultima pergunta não respondida (que foi tentada ser apagada).
*Todos os testes e requisitos passaram com sucesso.
*/
TEST_CASE("Receiving 20 questions and testing 'apagar' and 'editar' in Vinte_Perguntas", "The function should ask the questions and navigate in the tree, and execute its functions 'apagar', 'editar'")
{
  arvore *ainicio;
  FILE *arq;
  char test[6] = "TESTE";
  printf("******************************************************************\n");
  printf("DIGITE 'SIM' 20 VEZES, NO FIM DIGITE 'SIM'\n");
  printf("******************************************************************\n");
  arq = fopen("./Arquivos_de_teste/Vinte.txt","r");
  Constroi_TXT(&ainicio,arq);
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio != NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'SIM' 20 VEZES, NO FIM DIGITE 'NAO'\n");
  printf("******************************************************************\n");
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio != NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'EDITAR' E ESCREVA 'TESTE' NA PERGUNTA, DEPOIS RESPONDA A EDIÇÃO COM 'NAO', NO FIM DIGITE 'SIM'\n");
  printf("******************************************************************\n");
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(strcmp(ainicio->Pergunta,test) == 0);
  printf("\n******************************************************************\n");
  printf("DIGITE 'APAGAR', DIGITE 'SIM', NO FIM DIGITE 'NAO'\n");
  printf("******************************************************************\n");
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio == NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'SIM', DEPOIS 'APAGAR', DIGITE 'SIM', NO FIM DIGITE 'NAO'\n");
  printf("\n******************************************************************\n");
  arq = fopen("./Arquivos_de_teste/Perguntas.txt","r");
  Constroi_TXT(&ainicio,arq);
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio != NULL);
  REQUIRE(ainicio->sim == NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'NAO', DEPOIS 'APAGAR', DIGITE 'SIM', NO FIM DIGITE 'NAO'\n");
  printf("******************************************************************\n");
  arq = fopen("./Arquivos_de_teste/Perguntas.txt","r");
  Constroi_TXT(&ainicio,arq);
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio != NULL);
  REQUIRE(ainicio->nao == NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'APAGAR', DIGITE 'NAO', DIGITE 'NAO', DIGITE 'NAO' E POR FIM DIGITE 'NAO'\n");
  printf("******************************************************************\n");
  arq = fopen("./Arquivos_de_teste/Vinte.txt","r");
  Constroi_TXT(&ainicio,arq);
  Vinte_Perguntas(&ainicio,0);
  REQUIRE(ainicio != NULL);
  REQUIRE(ainicio->nao == NULL);
}

/*
*@brief Teste da função 'Pergunta_Final'
*Foi aberto um arquivo txt e criado uma arvore, em seguida passada essa arvore para a função
*'Pergunta_Final', com o intuido da criação de um novo nó 'sim' na arvore, o criterio de aceitação
*é que o nó fosse criado com sucesso e que seus filhos fossem NULL, em seguida, novamente foi feito
*o mesmo teste só que para o nó 'nao', o criterio é que o nó 'nao' seja existente e seus filhos sejam
*NULL.
*Todos os testes passaram com sucesso.
*/
TEST_CASE("Creating childs at the end in 'sim' and 'nao'", "Should normaly create childs")
{
  arvore *ainicio = NULL, *anterior = NULL;
  FILE *arq;
  arq = fopen("./Arquivos_de_teste/Perguntas3.txt","r");
  Constroi_TXT(&anterior,arq);
  printf("\n******************************************************************\n");
  printf("DIGITE 'NAO', DEPOIS 'SIM', DEPOIS 'SIM', EM SEGUIDA CRIE APENAS UMA PERGUNTA EXTRA E DIGITE 'SAIR' 2 VEZES, DEPOIS RESPONDA A PERGUNTA E DIGITE NO FINAL 'SIM'\n");
  printf("******************************************************************\n");
  Pergunta_Final(&anterior, &ainicio, 0, Rsim);
  REQUIRE(anterior != NULL);
  REQUIRE(anterior->sim != NULL);
  REQUIRE(anterior->nao == NULL);
  printf("\n******************************************************************\n");
  printf("DIGITE 'NAO', DEPOIS 'SIM', DEPOIS 'NAO', EM SEGUIDA CRIE APENAS UMA PERGUNTA EXTRA E DIGITE 'SAIR' 2 VEZES, DEPOIS RESPONDA A PERGUNTA E DIGITE NO FINAL 'SIM'\n");
  printf("******************************************************************\n");
  fclose(arq);
  arq = fopen("./Arquivos_de_teste/Perguntas3.txt","r");
  Constroi_TXT(&ainicio,arq);
  Pergunta_Final(&ainicio, &anterior, 0, Rsim);
  REQUIRE(ainicio != NULL);
  REQUIRE(ainicio->sim == NULL);
  REQUIRE(ainicio->nao != NULL);
  fclose(arq);
}

/*
*@brief Conclusões
*As descrições dos parametros das funções estão descritos nos .c de todas as funções.
*A unica função que foi observado um resultado não desejado foi a 'Resposta', que quando
*digitado mais que 6 caracteres, ela imprime na tela mais de uma vez a mensagem de erro. Isso
*pode ser contornado ao aumentar o limite de leitura do scanf, porem, sempre averá um limite de
*leitura. Fora esse problema, não foram encontradas nenhumas alteração no comportamento das funções
*em geral, todas foram testadas intensamente durante sua criação, e apresentam uma excelente consistencia
*em seu uso.
*/

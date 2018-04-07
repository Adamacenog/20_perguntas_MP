/*
Propriedade de Andre Garrido Damaceno.
mat. 15/0117531.
*/

typedef enum Acabou_Jogo{finalizar,prosseguir}continuar;
typedef enum Respostas{Rsim,Rnao,Reditar,Rapagar}resposta;
typedef enum TipoPergunta{multipla,simples}pergunta;

int Resposta(int);
void Vinte_Perguntas(arvore **, int);
void Pergunta_Final(arvore **, arvore **,int, int);

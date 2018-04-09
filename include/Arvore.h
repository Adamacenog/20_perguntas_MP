/*
Propriedade de Andre Garrido Damaceno.
mat. 15/0117531.
*/

typedef struct Arvore
{
    char Pergunta[100];
    struct Arvore *sim, *nao;
} arvore;

void Constroi_Manual (arvore **, char *, int);
void Constroi_TXT (arvore **, FILE *);
void Salva_TXT (arvore **, FILE *);
void Le (arvore *);
void NavegaSim(arvore **);
void NavegaNao(arvore **);
void Desconstroi (arvore **);

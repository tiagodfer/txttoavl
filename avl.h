typedef struct TipoAVL
{
    char palavra[50];
    int frequencia;
    struct TipoAVL *esquerda;
    struct TipoAVL *direita;
    int fb;
} PtAVL;

PtAVL* inicializa_avl();
int vazia_avl(PtAVL *avl);
PtAVL* insere_avl(PtAVL *avl, char p[], int *comp_ger, int *rot, int *ok);
PtAVL* insere_avl_freq(PtAVL *print, PtAVL *avl, int *comp_rel);
int conta_avl(PtAVL *avl);
int aux_frequencia_avl(PtAVL *avl, char p[], int *comp_rel);
void frequencia_avl(FILE *saida, PtAVL *avl, char p[], int *comp_rel);
void contador_avl(PtAVL **print, PtAVL *avl, int f0, int f1, int *comp_rel);
int altura_avl(PtAVL *avl);
int fator_balanceamento_nodo(PtAVL *avl);
int fator_balanceamento_avl(PtAVL *avl);
void aux_imprime_avl(FILE *resultado, PtAVL *print);
void imprime_avl(FILE *resultado, PtAVL *print, int f0, int f1);

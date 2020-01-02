#define LINHAS 1000

void caixa_baixa(FILE *entrada, FILE *saida);
void le_para_array(FILE *entrada, char vetor[LINHAS][LINHAS]);
PtAVL* le_para_avl(FILE *entrada, int *comp_ger, int *rot, int *ok);
void le_operacoes(FILE *op, FILE *resultado, PtAVL *print, PtAVL *avl, int *comp_rel);
void relatorio_avl(FILE *saida, FILE *resultado, PtAVL *avl, int nodos, int altura, int fb, double miliseconds_ger, double miliseconds_rel, int comp_ger, int comp_rel);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "avl.h"
#include "texto.h"

#define LINHAS 1000
#define MAX 50

/**
 * INICIALIZA_AVL (PTAVL)
 * Inicializa AVL com NULL.
 */
PtAVL* inicializa_avl()
{
    return NULL;
}

/**
 * VAZIA_AVL (INT)
 * Verifica se AVL é vazia e incrementa contador de comparações.
 *
 * AVL: ponteiro para a AVL a ser verificada;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int vazia_avl(PtAVL *avl, int *comp)
{
    (*comp)++;
    if(!avl)
        return 1;
    else
        return 0;
}

/**
 * COMPARA (INT)
 * Compara strings e incrementa contador de comparações.
 *
 * AVL: ponteiro para a AVL a ser verificada;
 * PALAVRA: ponteiro para a palavra a ser comparada;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int compara(PtAVL *avl, char palavra[MAX], int *comp)
{
    (*comp)++;
    return (strcmp(avl->palavra, palavra));
}

/**
 * MAIOR (INT)
 * Compara inteiros, se I é maior que J e incrementa contador de comparações.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int maior(int i, int j, int *comp)
{
    (*comp)++;
    return i > j;
}

/**
 * MAIOR_IGUAL (INT)
 * Compara inteiros, se I é maior ou igual que J e incrementa contador de comparações.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int maior_igual(int i, int j, int *comp)
{
    (*comp)++;
    return i >= j;
}

/**
 * MENOR (INT)
 * Compara inteiros, se I é menor que J e incrementa contador de comparações.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int menor(int i, int j, int *comp)
{
    (*comp)++;
    return i < j;
}

/**
 * MENOR_IGUAL (INT)
 * Compara inteiros, se I é menor ou igual que J e incrementa contador de comparações.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int menor_igual(int i, int j, int *comp)
{
    (*comp)++;
    return i <= j;
}

/**
 * IGUAL (INT)
 * Compara inteiros, se I é igual a J e incrementa contador de comparações.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int igual(int i, int j, int *comp)
{
    (*comp)++;
    return i == j;
}

/**
 * ROTACAO_DIREITA (PTAVL)
 * Realiza uma rotação à direita.
 *
 * AVL: ponteiro para a AVL a sofrer rotação.
 */
PtAVL* rotacao_direita(PtAVL* avl)
{
    PtAVL *temp;

    temp = avl->esquerda;
    avl->esquerda = temp->direita;
    temp->direita = avl;
    avl->fb = 0;
    avl = temp;
    return avl;
}

/**
 * ROTACAO_ESQUERDA (PTAVL)
 * Realiza uma rotação à esquerda.
 *
 * AVL: ponteiro para a AVL a sofrer rotação.
 */
PtAVL* rotacao_esquerda(PtAVL *avl)
{
    PtAVL *temp;

    temp = avl->direita;
    avl->direita = temp->esquerda;
    temp->esquerda = avl;
    avl->fb = 0;
    avl = temp;
    return avl;
}

/**
 * ROTACAO_DUPLA_DIREITA (PTAVL)
 * Realiza uma rotação dupla à direita.
 *
 * AVL: ponteiro para a AVL a sofrer rotação.
 */
PtAVL* rotacao_dupla_direita (PtAVL* avl, int *comp)
{
    PtAVL *temp_1, *temp_2;

    temp_1 = avl->esquerda;
    temp_2 = temp_1->direita;
    temp_1->direita = temp_2->esquerda;
    temp_2->esquerda = temp_1;
    avl->esquerda = temp_2->direita;
    temp_2->direita = avl;
    if(igual(temp_2->fb, 1, comp))
        avl->fb = -1;
    else
        avl->fb = 0;
    if(igual(temp_2->fb, -1, comp))
        temp_1->fb = 1;
    else
        temp_1->fb = 0;
    avl = temp_2;
    return avl;
}

/**
 * ROTACAO_DUPLA_ESQUERDA (PTAVL)
 * Realiza uma rotação dupla à esquerda.
 *
 * AVL: ponteiro para a AVL a sofrer rotação.
 */
PtAVL* rotacao_dupla_esquerda (PtAVL *avl, int *comp)
{
    PtAVL *temp_1, *temp_2;

    temp_1 = avl->direita;
    temp_2 = temp_1->esquerda;
    temp_1->esquerda = temp_2->direita;
    temp_2->direita = temp_1;
    avl->direita = temp_2->esquerda;
    temp_2->esquerda = avl;
    if(igual(temp_2->fb, -1, comp))
        avl->fb = 1;
    else
        avl->fb = 0;
    if(igual(temp_2->fb, 1, comp))
        temp_1->fb = -1;
    else
        temp_1->fb = 0;
    avl = temp_2;
    return avl;
}

/**
 * CASO_1 (PTAVL)
 * Chama a rotação correta para balancear a AVL, alterando estado da AVL e incrementando contadores.
 *
 * AVL: ponteiro para a AVL a sofrer rotação;
 * COMP: ponteiro para o número de comparações realizadas;
 * ROT: ponteiro para o número de rotações realizadas;
 * OK: ponteiro para estado da AVL.
 */
PtAVL* caso_1 (PtAVL *avl, int *comp, int *rot, int *ok)
{
    PtAVL *temp;

    temp = avl->esquerda;
    if(igual(temp->fb, 1, comp))
    {
        (*rot)++;
        avl = rotacao_direita(avl);
    }
    else
    {
        (*rot)++;
        (*rot)++;
        avl = rotacao_dupla_direita(avl, comp);
    }
    avl->fb = 0;
    *ok = 0;
    return avl;
}

/**
 * CASO_2 (PTAVL)
 * Chama a rotação correta para balancear a AVL, alterando estado da AVL e incrementando contadores.
 *
 * AVL: ponteiro para a AVL a sofrer rotação;
 * COMP: ponteiro para o número de comparações realizadas;
 * ROT: ponteiro para o número de rotações realizadas;
 * OK: ponteiro para estado da AVL.
 */
PtAVL* caso_2 (PtAVL *avl, int *comp, int *rot, int *ok)
{
    PtAVL *temp;

    temp = avl->direita;
    if(igual(temp->fb, -1, comp))
    {
        (*rot)++;
        avl = rotacao_esquerda(avl);
    }
    else
    {
        (*rot)++;
        (*rot)++;
        avl = rotacao_dupla_esquerda(avl, comp);
    }
    avl->fb = 0;
    *ok = 0;
    return avl;
}

/**
 * INSERE_AVL (PTAVL)
 * Insere palavra na AVL, incrementando o número de comparações.
 *
 * AVL: ponteiro para a AVL que está recebendo a nova palavra;
 * P: ponteiro para a palavra a ser inserido;
 * COMP: ponteiro para o número de comparações realizadas;
 * ROT: ponteiro para o número de rotações realizadas;
 * OK: ponteiro para estado da AVL.
 */
PtAVL* insere_avl(PtAVL *avl, char p[], int *comp, int *rot, int *ok)
{
    if(vazia_avl(avl, comp))
    {
        avl = (PtAVL*) malloc(sizeof(PtAVL));
        strcpy(avl->palavra, p);
        avl->esquerda = NULL;
        avl->direita = NULL;
        avl->fb = 0;
        avl->frequencia = 1;
        *ok = 1;
    }
    else if((compara(avl, p, comp)) == 0)
    {
        avl->frequencia++;
        *ok = 0;
    }
    else if((compara(avl, p, comp)) > 0)
    {
        avl->esquerda = insere_avl(avl->esquerda, p, comp, rot, ok);
        if(*ok)
        {
            switch (avl->fb)
            {
            case -1:
                (*comp)++;
                avl->fb = 0;
                *ok = 0;
                break;
            case 0:
                (*comp)+= 2;
                avl->fb = 1;
                break;
            case 1:
                (*comp)+= 3;
                avl=caso_1(avl, comp, rot, ok);
                break;
            }
        }
    }
    else
    {
        avl->direita = insere_avl(avl->direita, p, comp, rot, ok);
        if(*ok)
        {
            switch (avl->fb)
            {
            case 1:
                (*comp)++;
                avl->fb = 0;
                *ok = 0;
                break;
            case 0:
                (*comp)+= 2;
                avl->fb = -1;
                break;
            case -1:
                (*comp)+= 3;
                avl = caso_2(avl, comp, rot, ok);
                break;
            }
        }
    }
    return avl;
}

/**
 * INSERE_AVL_FREQ (PTAVL)
 * Insere palavra na AVL usando como critério a frequência, incrementando o número de comparações.
 *
 * AVL0: ponteiro para a AVL que está recebendo a nova palavra;
 * AVL1: ponteiro para a AVL onde a palavra que será inserida;
 * P: ponteiro para a palavra a ser inserido;
 * COMP: ponteiro para o número de comparações realizadas;
 * ROT: ponteiro para o número de rotações realizadas;
 * OK: ponteiro para estado da AVL.
 */
PtAVL* insere_avl_freq(PtAVL *avl0, PtAVL *avl1, int *comp, int *rot, int *ok)
{
    if(vazia_avl(avl0, comp))
    {
        avl0 = (PtAVL*) malloc(sizeof(PtAVL));
        strcpy(avl0->palavra, avl1->palavra);
        avl0->esquerda = NULL;
        avl0->direita = NULL;
        avl0->fb = 0;
        avl0->frequencia = avl1->frequencia;
        *ok = 1;
    }
    else if(maior_igual(avl0->frequencia, avl1->frequencia, comp))
    {
        avl0->esquerda = insere_avl_freq(avl0->esquerda, avl1, comp, rot, ok);
        if(*ok)
        {
            switch (avl0->fb)
            {
            case -1:
                (*comp)++;
                avl0->fb = 0;
                *ok = 0;
                break;
            case 0:
                (*comp)+= 2;
                avl0->fb = 1;
                break;
            case 1:
                (*comp)+= 3;
                avl0=caso_1(avl0, comp, rot, ok);
                break;
            }
        }
    }
    else
    {
        avl0->direita = insere_avl_freq(avl0->direita, avl1, comp, rot, ok);
        if(*ok)
        {
            switch (avl0->fb)
            {
            case 1:
                (*comp)++;
                avl0->fb = 0;
                *ok = 0;
                break;
            case 0:
                (*comp)+= 2;
                avl0->fb = -1;
                break;
            case -1:
                (*comp)+= 3;
                avl0 = caso_2(avl0, comp, rot, ok);
                break;
            }
        }
    }
    return avl0;
}

/**
 * CONTA_AVL (INT)
 * Conta número de nodos da AVL, incrementando contador de comparações.
 *
 * AVL: ponteiro para a AVL cujos nodos serão contados;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int conta_avl(PtAVL *avl, int *comp)
{
    if(vazia_avl(avl, comp))
        return 0;
    else
    {
        return 1 + conta_avl(avl->esquerda, comp) + conta_avl(avl->direita, comp);
    }
}

/**
 * AUX_FREQUENCIA_AVL (INT)
 * Conta número de ocorrências de uma palavra dentro da AVL, incrementando contador de comparações.
 *
 * AVL: ponteiro para a AVL com a palavra a ser buscada;
 * P: ponteiro para a palavra buscada cujas ocorrências serão devolvidas;
 * COMP: ponteiro para o número de comparaçãoes realizadas.
 */
int aux_frequencia_avl(PtAVL *avl, char p[], int *comp)
{
    if(vazia_avl(avl, comp))
        return 0;
    else if((compara(avl, p, comp)) == 0)
    {
        return avl->frequencia;
    }
    else if((compara(avl, p, comp)) > 0)
    {
        return aux_frequencia_avl(avl->esquerda, p, comp);
    }
    else
    {
        return aux_frequencia_avl(avl->direita, p, comp);
    }
}

/**
 * FREQUENCIA_AVL (VOID)
 * Imprime no arquivo saida a frequência de ocorrência palavra solicitada, incrementando contador de comparações.
 *
 * SAIDA: ponteiro para o arquivo de saída;
 * AVL: ponteiro para a AVL onde a palavra será pesquisada;
 * P: ponteiro para a palavra pesquisada;
 * COMP: ponteiro para o número de comparaçãoes realizadas.
 */
void frequencia_avl(FILE *saida, PtAVL *avl, char p[], int *comp)
{
    fprintf(saida, "*************************************************************\n");
    fprintf(saida, "F %s\n%s: %i\n", p, p, aux_frequencia_avl(avl, p, comp));
}

/**
 * CONTADOR_AVL (VOID)
 * Controla a chamada da função AUX_CONTADOR_AVL, chamando uma vez para cada frequência da série solicitada, incrementando contador de comparações.
 *
 * AVL0: ponteiro duplo para a AVL que receberá as palavras com a frequências solicitadas;
 * AVL1: ponteiro para a AVL onde as palavras serão pesquisadas;
 * F0: frequência inicial das palavras buscadas;
 * F1: frequência final das palavras buscadas;
 * COMP: ponteiro para o número de comparaçãoes realizadas.
 */
void contador_avl(PtAVL **avl0, PtAVL *avl1, int f0, int f1, int *comp, int *rot, int *ok)
{
    if(!(vazia_avl(avl1, comp)))
    {
        contador_avl(avl0, avl1->esquerda, f0, f1, comp, rot, ok);
        if(maior_igual(avl1->frequencia, f0, comp) && menor_igual(avl1->frequencia, f1, comp))
            *avl0 = insere_avl_freq(*avl0, avl1, comp, rot, ok);
        contador_avl(avl0, avl1->direita, f0, f1, comp, rot, ok);
    }
}

/**
 * ALTURA_AVL (INT)
 * Calcula a altura da AVL, incrementando contador de comparações.
 *
 * AVL: ponteiro para a AVL cuja altura será calculada;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int altura_avl(PtAVL *avl, int *comp)
{
    int altura_esquerda = 0;
    int altura_direita = 0;

    if(vazia_avl(avl, comp))
        return 0;
    else
    {
        altura_esquerda = altura_avl(avl->esquerda, comp);
        altura_direita = altura_avl(avl->direita, comp);
        if(altura_esquerda > altura_direita)
            return (1 + altura_esquerda);
        else
            return (1 + altura_direita);
    }
}

/**
 * FATOR_BALANCEAMENTO_NODO (INT)
 * Retorna o FB do nodo, incrementando contador de comparações.
 *
 * AVL: ponteiro para o nodo cuja altura será calculada;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int fator_balanceamento_nodo(PtAVL *avl, int *comp)
{
    return (altura_avl(avl->esquerda, comp) - altura_avl(avl->direita, comp));
}

/**
 * FATOR_BALANCEAMENTO_AVL (INT)
 * Retorna o FB da AVL, incrementando contador de comparações.
 *
 * AVL: ponteiro para a AVL cuja altura será calculada;
 * COMP: ponteiro para o número de comparações realizadas.
 */
int fator_balanceamento_avl(PtAVL *avl, int *comp)
{
    int fator = fator_balanceamento_nodo(avl, comp);

    if(vazia_avl(avl, comp))
        return 0;
    else
    {
        if(avl->esquerda)
        {
            if(abs(fator) <= abs(fator_balanceamento_nodo(avl->esquerda, comp)))
                fator = fator_balanceamento_nodo(avl->esquerda, comp);
        }
        if(avl->direita)
        {
            if(abs(fator) <= abs(fator_balanceamento_nodo(avl->direita, comp)))
            fator = fator_balanceamento_nodo(avl->direita, comp);
        }
        return fator;
    }
}

/**
 * AUX_IMPRIME_AVL (VOID)
 * Imprime AVL no arquivo, em ordem decrescente pela frequência, incrementando contador de comparações.
 *
 * RESULTADO: ponteiro para o arquivo de saída;
 * AVL: ponteiro para a AVL cuja altura será impressa;
 * COMP: ponteiro para o número de comparações realizadas.
 */
void aux_imprime_avl(FILE *resultado, PtAVL *avl, int *comp)
{
    if(!(vazia_avl(avl, comp)))
    {
        aux_imprime_avl(resultado, avl->direita, comp);
        fprintf(resultado, "%s: %i\n", avl->palavra, avl->frequencia);
        aux_imprime_avl(resultado, avl->esquerda, comp);
    }
}

/**
 * IMPRIME_AVL (VOID)
 * Imprime AVL no arquivo, chama laço de impressão da função auxiliar, em ordem decrescente pela frequência, incrementando contador de comparações.
 *
 * RESULTADO: ponteiro para o arquivo de saída;
 * AVL: ponteiro para a AVL cuja altura será impressa;
 * F0: frequência inicial das palavras buscadas;
 * F1: frequência final das palavras buscadas;
 * COMP: ponteiro para o número de comparações realizadas.
 */
void imprime_avl(FILE *resultado, PtAVL *avl, int f0, int f1, int *comp)
{
    fprintf(resultado, "*************************************************************\n");
    fprintf(resultado, "C %i %i\n", f0, f1);
    aux_imprime_avl(resultado, avl, comp);
}

/**
 * DESTROI_AVL (PTAVL)
 * Destroi AVL liberando memória alocada. (optamos por não contabilizar as comparações para destruir)
 */
PtAVL *destroi_avl(PtAVL *avl, int *comp)
{
    if(!(vazia_avl(avl, comp)))
    {
        destroi_avl(avl->esquerda, comp);
        destroi_avl(avl->direita, comp);
        free(avl);
    }
    return NULL;
}

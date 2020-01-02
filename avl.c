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
 * INICIALIZA_ABP (PTABP)
 * Inicializa ABP com NULL.
 */
PtABP* inicializa_abp()
{
    return NULL;
}

/**
 * INICIALIZA_AVL (PTAVL)
 * Inicializa AVL com NULL.
 */
PtAVL* inicializa_avl()
{
    return NULL;
}

/**
 * VAZIA_ABP (INT)
 * Verifica se ABP � vazia e incrementa contador de compara��es.
 *
 * ABP: ponteiro para a ABP a ser verificada;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int vazia_abp(PtABP *abp, int *comp)
{
    (*comp)++;
    if(!abp)
        return 1;
    else
        return 0;
}

/**
 * VAZIA_AVL (INT)
 * Verifica se AVL � vazia e incrementa contador de compara��es.
 *
 * AVL: ponteiro para a AVL a ser verificada;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
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
 * Compara strings e incrementa contador de compara��es.
 *
 * AVL: ponteiro para a AVL a ser verificada;
 * PALAVRA: ponteiro para a palavra a ser comparada;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int compara(PtAVL *avl, char palavra[MAX], int *comp)
{
    (*comp)++;
    return (strcmp(avl->palavra, palavra));
}

/**
 * MAIOR (INT)
 * Compara inteiros, se I � maior que J e incrementa contador de compara��es.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int maior(int i, int j, int *comp)
{
    (*comp)++;
    return i > j;
}

/**
 * MAIOR_IGUAL (INT)
 * Compara inteiros, se I � maior ou igual que J e incrementa contador de compara��es.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int maior_igual(int i, int j, int *comp)
{
    (*comp)++;
    return i >= j;
}

/**
 * MENOR (INT)
 * Compara inteiros, se I � menor que J e incrementa contador de compara��es.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int menor(int i, int j, int *comp)
{
    (*comp)++;
    return i < j;
}

/**
 * MENOR_IGUAL (INT)
 * Compara inteiros, se I � menor ou igual que J e incrementa contador de compara��es.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int menor_igual(int i, int j, int *comp)
{
    (*comp)++;
    return i <= j;
}

/**
 * IGUAL (INT)
 * Compara inteiros, se I � igual a J e incrementa contador de compara��es.
 *
 * I: inteiro a ser comparado;
 * J: inteiro a ser comparado;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int igual(int i, int j, int *comp)
{
    (*comp)++;
    return i == j;
}

/**
 * ROTACAO_DIREITA (PTAVL)
 * Realiza uma rota��o � direita.
 *
 * AVL: ponteiro para a AVL a sofrer rota��o.
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
 * Realiza uma rota��o � esquerda.
 *
 * AVL: ponteiro para a AVL a sofrer rota��o.
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
 * Realiza uma rota��o dupla � direita.
 *
 * AVL: ponteiro para a AVL a sofrer rota��o.
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
 * Realiza uma rota��o dupla � esquerda.
 *
 * AVL: ponteiro para a AVL a sofrer rota��o.
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
 * Chama a rota��o correta para balancear a AVL, alterando estado da AVL e incrementando contadores.
 *
 * AVL: ponteiro para a AVL a sofrer rota��o;
 * COMP: ponteiro para o n�mero de compara��es realizadas;
 * ROT: ponteiro para o n�mero de rota��es realizadas;
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
 * Chama a rota��o correta para balancear a AVL, alterando estado da AVL e incrementando contadores.
 *
 * AVL: ponteiro para a AVL a sofrer rota��o;
 * COMP: ponteiro para o n�mero de compara��es realizadas;
 * ROT: ponteiro para o n�mero de rota��es realizadas;
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
 * Insere palavra na AVL, incrementando o n�mero de compara��es.
 *
 * AVL: ponteiro para a AVL que est� recebendo a nova palavra;
 * P: ponteiro para a palavra a ser inserido;
 * COMP: ponteiro para o n�mero de compara��es realizadas;
 * ROT: ponteiro para o n�mero de rota��es realizadas;
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
                (*comp)++;
                avl->fb = 1;
                break;
            case 1:
                (*comp)++;
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
                (*comp)++;
                avl->fb = -1;
                break;
            case -1:
                (*comp)++;
                avl = caso_2(avl, comp, rot, ok);
                break;
            }
        }
    }
    return avl;
}

/**
 * INSERE_AVL_FREQ (PTABP)
 * Insere nodo na ABP, desta vez usando frequ�ncia como crit�rio, incrementando contador de compara��es.
 *
 * ABP: ponteiro para a ABP que est� recebendo o novo nodo;
 * AVL: ponteiro para a AVL com palavra a ser inserida;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
PtABP* insere_avl_freq(PtABP *abp, PtAVL *avl, int *comp)
{
    if(vazia_abp(abp, comp))
    {
        abp = (PtABP*) malloc(sizeof(PtABP));
        strcpy(abp->palavra, avl->palavra);
        abp->frequencia = avl->frequencia;
        abp->esquerda = NULL;
        abp->direita = NULL;
    }
    else if(menor(abp->frequencia, avl->frequencia, comp))
        abp->direita = insere_avl_freq(abp->direita, avl, comp);
    else
        abp->esquerda = insere_avl_freq(abp->esquerda, avl, comp);
    return abp;
}

/**
 * CONTA_AVL (INT)
 * Conta n�mero de nodos da AVL, incrementando contador de compara��es.
 *
 * AVL: ponteiro para a AVL cujos nodos ser�o contados;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
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
 * Conta n�mero de ocorr�ncias de uma palavra dentro da AVL, incrementando contador de compara��es.
 *
 * AVL: ponteiro para a AVL com a palavra a ser buscada;
 * P: ponteiro para a palavra buscada cujas ocorr�ncias ser�o devolvidas;
 * COMP: ponteiro para o n�mero de compara��oes realizadas.
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
 * Imprime no arquivo saida a frequ�ncia de ocorr�ncia palavra solicitada, incrementando contador de compara��es.
 *
 * SAIDA: ponteiro para o arquivo de sa�da;
 * AVL: ponteiro para a AVL onde a palavra ser� pesquisada;
 * P: ponteiro para a palavra pesquisada;
 * COMP: ponteiro para o n�mero de compara��oes realizadas.
 */
void frequencia_avl(FILE *saida, PtAVL *avl, char p[], int *comp)
{
    fprintf(saida, "*************************************************************\n");
    fprintf(saida, "F %s\n%s: %i\n", p, p, aux_frequencia_avl(avl, p, comp));
}

/**
 * CONTADOR_AVL (VOID)
 * Controla a chamada da fun��o AUX_CONTADOR_AVL, chamando uma vez para cada frequ�ncia da s�rie solicitada, incrementando contador de compara��es.
 *
 * SAIDA: ponteiro para o arquivo de sa�da;
 * AVL: ponteiro para a AVL onde as palavras ser�o pesquisadas;
 * F0: frequ�ncia inicial das palavras buscadas;
 * F1: frequ�ncia final das palavras buscadas;
 * COMP: ponteiro para o n�mero de compara��oes realizadas.
 */
void contador_avl(PtABP **abp, PtAVL *avl, int f0, int f1, int *comp)
{
    if(!(vazia_avl(avl, comp)))
    {
        contador_avl(abp, avl->esquerda, f0, f1, comp);
        if(maior_igual(avl->frequencia, f0, comp) && menor_igual(avl->frequencia, f1, comp))
            *abp = insere_avl_freq(*abp, avl, comp);
        contador_avl(abp, avl->direita, f0, f1, comp);
    }
}

/**
 * ALTURA_AVL (INT)
 * Calcula a altura da AVL, incrementando contador de compara��es.
 *
 * AVL: ponteiro para a AVL cuja altura ser� calculada;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
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
 * Retorna o FB do nodo, incrementando contador de compara��es.
 *
 * AVL: ponteiro para o nodo cuja altura ser� calculada;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
int fator_balanceamento_nodo(PtAVL *avl, int *comp)
{
    return (altura_avl(avl->esquerda, comp) - altura_avl(avl->direita, comp));
}

/**
 * FATOR_BALANCEAMENTO_AVL (INT)
 * Retorna o FB da AVL, incrementando contador de compara��es.
 *
 * AVL: ponteiro para a AVL cuja altura ser� calculada;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
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
 * AUX_IMPRIME_ABP (VOID)
 * Imprime ABP no arquivo, em ordem decrescente pela frequ�ncia, incrementando contador de compara��es.
 *
 * RESULTADO: ponteiro para o arquivo de sa�da;
 * ABP: ponteiro para a ABP cuja altura ser� impressa;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
void aux_imprime_abp(FILE *resultado, PtABP *abp, int *comp)
{
    if(!(vazia_abp(abp, comp)))
    {
        aux_imprime_abp(resultado, abp->direita, comp);
        fprintf(resultado, "%s: %i\n", abp->palavra, abp->frequencia);
        aux_imprime_abp(resultado, abp->esquerda, comp);
    }
}

/**
 * IMPRIME_ABP (VOID)
 * Imprime ABP no arquivo, chama la�o de impress�o da fun��o auxiliar, em ordem decrescente pela frequ�ncia, incrementando contador de compara��es.
 *
 * RESULTADO: ponteiro para o arquivo de sa�da;
 * ABP: ponteiro para a ABP cuja altura ser� impressa;
 * F0: frequ�ncia inicial das palavras buscadas;
 * F1: frequ�ncia final das palavras buscadas;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
void imprime_abp(FILE *resultado, PtABP *abp, int f0, int f1, int *comp)
{
    fprintf(resultado, "*************************************************************\n");
    fprintf(resultado, "C %i %i\n", f0, f1);
    aux_imprime_abp(resultado, abp, comp);
}

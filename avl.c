#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "avl.h"
#include "texto.h"

#define LINHAS 1000

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
 * Verifica se AVL é vazia.
 *
 * AVL: AVL a ser verificada.
 */
int vazia_avl(PtAVL *avl)
{
    if(!avl)
        return 1;
    else
        return 0;
}

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

PtAVL* rotacao_dupla_direita (PtAVL* avl)
{
    PtAVL *temp_1, *temp_2;

    temp_1 = avl->esquerda;
    temp_2 = temp_1->direita;
    temp_1->direita = temp_2->esquerda;
    temp_2->esquerda = temp_1;
    avl->esquerda = temp_2->direita;
    temp_2->direita = avl;
    if (temp_2->fb == 1)
        avl->fb = -1;
    else
        avl->fb = 0;
    if (temp_2->fb == -1)
        temp_1->fb = 1;
    else
        temp_1->fb = 0;
    avl = temp_2;
    return avl;
}

PtAVL* rotacao_dupla_esquerda (PtAVL *avl)
{
    PtAVL *temp_1, *temp_2;

    temp_1 = avl->direita;
    temp_2 = temp_1->esquerda;
    temp_1->esquerda = temp_2->direita;
    temp_2->direita = temp_1;
    avl->direita = temp_2->esquerda;
    temp_2->esquerda = avl;
    if (temp_2->fb == -1)
        avl->fb = 1;
    else
        avl->fb = 0;
    if (temp_2->fb == 1)
        temp_1->fb = -1;
    else
        temp_1->fb = 0;
    avl = temp_2;
    return avl;
}

PtAVL* caso_1 (PtAVL *avl, int *rot, int *ok)
{
    PtAVL *temp;

    temp = avl->esquerda;
    if (temp->fb == 1)
    {
        (*rot)++;
        avl = rotacao_direita(avl);
    }
    else
    {
        (*rot)++;
        (*rot)++;
        avl = rotacao_dupla_direita(avl);
    }
    avl->fb = 0;
    *ok = 0;
    return avl;
}

PtAVL* caso_2 (PtAVL *avl, int *rot, int *ok)
{
    PtAVL *temp;

    temp = avl->direita;
    if (temp->fb == -1)
    {
        (*rot)++;
        avl = rotacao_esquerda(avl);
    }
    else
    {
        (*rot)++;
        (*rot)++;
        avl = rotacao_dupla_esquerda(avl);
    }
    avl->fb = 0;
    *ok = 0;
    return avl;
}

/**
 * INSERE_AVL (PTAVL)
 * Insere nodo na AVL, computando o número de comparações necessária para tal.
 *
 * AVL: AVL que está recebendo o novo nodo;
 * P: Nodo a ser inserido;
 * COMP_GER: Número de comparações executadas.
 */
PtAVL* insere_avl(PtAVL *avl, char p[], int *comp_ger, int *rot, int *ok)
{
    if(vazia_avl(avl))
    {
        avl = (PtAVL*) malloc(sizeof(PtAVL));
        strcpy(avl->palavra, p);
        avl->esquerda = NULL;
        avl->direita = NULL;
        avl->fb = 0;
        avl->frequencia = 1;
        *ok = 1;
    }
    else if(strcmp(avl->palavra, p) == 0)
    {
        (*comp_ger)++;
        avl->frequencia++;
    }
    else if(strcmp(avl->palavra, p) > 0)
    {
        (*comp_ger)++;
        avl->esquerda = insere_avl(avl->esquerda, p, comp_ger, rot, ok);
        if (*ok)
        {
            switch (avl->fb)
            {
            case -1:
                avl->fb = 0;
                *ok = 0;
                break;
            case 0:
                avl->fb = 1;
                break;
            case 1:
                avl=caso_1(avl, rot, ok);
                break;
            }
        }
    }
    else
    {
        avl->direita = insere_avl(avl->direita, p, comp_ger, rot, ok);
        if (*ok)
        {
            switch (avl->fb)
            {
            case 1:
                avl->fb = 0;
                *ok = 0;
                break;
            case 0:
                avl->fb = -1;
                break;
            case -1:
                avl = caso_2(avl, rot, ok);
                break;
            }
        }
    }
    return avl;
}

PtAVL* insere_avl_freq(PtAVL *print, PtAVL *avl, int *comp_rel)
{
    (*comp_rel)++;
    if(vazia_avl(print))
    {
        print = (PtAVL*) malloc(sizeof(PtAVL));
        strcpy(print->palavra, avl->palavra);
        print->frequencia = avl->frequencia;
        print->esquerda = NULL;
        print->direita = NULL;
    }
    else if(print->frequencia < avl->frequencia)
        print->direita = insere_avl_freq(print->direita, avl, comp_rel);
    else
        print->esquerda = insere_avl_freq(print->esquerda, avl, comp_rel);
    return print;
}

/**
 * CONTA_AVL (INT)
 * Conta número de nodos da AVL.
 *
 * AVL: AVL cujos nodos serão contados.
 */
int conta_avl(PtAVL *avl)
{
    if(vazia_avl(avl))
        return 0;
    else
    {
        return 1 + conta_avl(avl->esquerda) + conta_avl(avl->direita);
    }
}

/**
 * AUX_FREQUENCIA_AVL (INT)
 * Conta número de ocorrências de uma palavra dentro da AVL, computando o número de comparações necessária para tal.
 *
 * AVL: AVL com a palavra a ser buscada;
 * P: Palavra buscada cujas ocorrências serão devolvidas;
 * COMP_REL: Número de comparaçãoes executadas.
 */
int aux_frequencia_avl(PtAVL *avl, char p[], int *comp_rel)
{
    if (vazia_avl(avl))
        return 0;
    else if(strcmp(avl->palavra, p) == 0)
    {
        (*comp_rel)++;
        return avl->frequencia;
    }
    else if(strcmp(avl->palavra, p) > 0)
    {
        (*comp_rel)++;
        return aux_frequencia_avl(avl->esquerda, p, comp_rel);
    }
    else
        return aux_frequencia_avl(avl->direita, p, comp_rel);
}

/**
 * FREQUENCIA_AVL  (VOID)
 * Imprime no arquivo saida a frequência de ocorrência palavra solicitada, computando o número de comparações necessária para tal.
 *
 * SAIDA: Arquivo de saída;
 * AVL: AVL onde a palavra será pesquisada;
 * P: Palavra pesquisada;
 * COMP_REL: Número de comparaçãoes executadas.
 */
void frequencia_avl(FILE *saida, PtAVL *avl, char p[], int *comp_rel)
{
    fprintf(saida, "*************************************************************\n");
    fprintf(saida, "F %s\n%s: %i\n", p, p, aux_frequencia_avl(avl, p, comp_rel));
}

/**
 * CONTADOR_AVL  (VOID)
 * Controla a chamada da função AUX_CONTADOR_AVL, chamando uma vez para cada frequência da série solicitada.
 *
 * SAIDA: Arquivo de saída;
 * AVL: AVL onde as palavras serão pesquisadas;
 * F0: Frequência inicial das palavras buscadas;
 * F1: Frequência final das palavras buscadas;
 * COMP_REL: Número de comparaçãoes executadas.
 */
void contador_avl(PtAVL **print, PtAVL *avl, int f0, int f1, int *comp_rel)
{
    if(!(vazia_avl(avl)))
    {
        (*comp_rel)++;
        (*comp_rel)++;
        contador_avl(print, avl->esquerda, f0, f1, comp_rel);
        if(avl->frequencia >= f0 && avl->frequencia <= f1)
            *print = insere_avl_freq(*print, avl, comp_rel);
        contador_avl(print, avl->direita, f0, f1, comp_rel);
    }
}

/**
 * ALTURA_AVL (INT)
 * Calcula a altura da AVL.
 *
 * AVL: AVL cuja altura será calculada.
 */
int altura_avl(PtAVL *avl)
{
    int altura_esquerda = 0;
    int altura_direita = 0;

    if (vazia_avl(avl))
        return 0;
    else
    {
        altura_esquerda = altura_avl(avl->esquerda);
        altura_direita = altura_avl(avl->direita);
        if (altura_esquerda > altura_direita)
            return (1 + altura_esquerda);
        else
            return (1 + altura_direita);
    }
}
/**
 * FATOR_BALANCEAMENTO_NODO (INT)
 * Retorna o FB do nodo.
 *
 * AVL: Nodo cuja altura será calculada.
 */
int fator_balanceamento_nodo(PtAVL *avl)
{
    return (altura_avl(avl->esquerda) - altura_avl(avl->direita));
}
/**
 * FATOR_BALANCEAMENTO_AVL (INT)
 * Retorna o FB da AVL.
 *
 * AVL: AVL cuja altura será calculada.
 */
int fator_balanceamento_avl(PtAVL *avl)
{
    int fator = fator_balanceamento_nodo(avl);

    if(vazia_avl(avl))
        return 0;
    else
    {
        if (avl->esquerda)
        {
            if (abs(fator) <= abs(fator_balanceamento_nodo(avl->esquerda)))
                fator = fator_balanceamento_nodo(avl->esquerda);
        }
        if (avl->direita)
        {
            if (abs(fator) <= abs(fator_balanceamento_nodo(avl->direita)))
            fator = fator_balanceamento_nodo(avl->direita);
        }
        return fator;
    }
}

void aux_imprime_avl(FILE *resultado, PtAVL *print)
{
    if(!(vazia_avl(print)))
    {
        aux_imprime_avl(resultado, print->direita);
        fprintf(resultado, "%s: %i\n", print->palavra, print->frequencia);
        aux_imprime_avl(resultado, print->esquerda);
    }
}

void imprime_avl(FILE *resultado, PtAVL *print, int f0, int f1)
{
    fprintf(resultado, "*************************************************************\n");
    fprintf(resultado, "C %i %i\n", f0, f1);
    aux_imprime_avl(resultado, print);
}

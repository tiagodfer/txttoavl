#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "avl.h"
#include "texto.h"

#define LINHAS 1000

/**
 * CAIXA_BAIXA (VOID)
 * Retorna AVL com os caracteres em caixa baixa e sem pontua��o, incrementando contador de compara��es.
 *
 * ENTRADA: ponteiro para o arquivo que ser� lido;
 * AVL: ponteiro duplo para a AVL de sa�da;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
void caixa_baixa_avl(FILE *entrada, PtAVL **avl, int *comp_ger, int *rot, int *ok)
{
    char *palavra, linha[LINHAS];
    char separador[]= {" ,.&*%\?!;/'@-\"$#=><()][}{:\n\t"};

    while(fgets(linha,LINHAS,entrada)) //percorre todo o arquivo lendo linha a linha
    {
        palavra = strtok(linha, separador); //tokeniza usando como delimitador os caracteres em "separador"
        while (palavra != NULL)
        {
            *avl = insere_avl(*avl, strlwr(palavra), comp_ger, rot, ok); //converte palavras para caixa baixa
            palavra = strtok(NULL, separador);
        }
    }
    fclose (entrada);
}

/**
 * LE_OPERA�OES (VOID)
 * Interpreta as opera��es solicitadas no arquivo de texto de entrada e chama a fun��o de acordo, imprimindo no arquivo de sa�da o resultado destas opera��es, incrementando contador de compara��es.
 *
 * OP: ponteiro para o arquivo que ser� lido;
 * RESULTADO: ponteiro para o arquivo de sa�da com o resultado das opera��es;
 * AVL0: ponteiro para a AVL que ir� receber as palavras ordenadas por frequ�ncia;
 * AVL1: ponteiro para a AVL resultante da leitura do texto;
 * COMP: ponteiro para o n�mero de compara��es realizadas.
 */
void le_operacoes(FILE *op, FILE *resultado, PtABP *avl0, PtAVL *avl1, int *comp)
{
    char *aux, *palavra, linha[LINHAS];
    int f0, f1;

    while (fgets(linha,LINHAS,op))
    {
        aux = strtok(linha, " ");
        while (aux != NULL)
        {
            if(strcmp(aux, "F") == 0 || strcmp(aux, "f") == 0)
            {
                palavra = strtok(NULL, "\n");
                frequencia_avl(resultado, avl1, palavra, comp);
            }
            else if(strcmp(aux, "C") == 0 || strcmp(aux, "c") == 0)
            {
                f0 = atoi(strtok(NULL, " "));
                f1 = atoi(strtok(NULL, "\n"));
                contador_avl(&avl0, avl1, f0, f1, comp);
                imprime_abp(resultado, avl0, f0, f1, comp);
            }
            aux = strtok(NULL, " ");
        }
    }
    fclose(op);
    fclose(resultado);
}

/**
 * RELATORIO_AVL (VOID)
 * Imprime relat�rio final concatenando as informa��es obtidas.
 *
 * SAIDA: ponteiro para o arquivo de sa�da com o relat�rio final.
 * RESULTADO: ponteiro para o arquivo com os resultados das opera��es.
 * AVL: ponteiro para a AVL cujos resultados ser�o exibidos.
 * NODOS: n�mero de nodos da AVL.
 * ALTURA: altura da AVL.
 * FB: fator de balanceamento da AVL.
 * MILISECONDS_GER: tempo de execu��o da AVL.
 * MILISECONDS_REL: tempo de execu��o dos resultados.
 * COMP_GER: n�mero de compara��oes realizadas na montagem da AVL oriunda do texto.
 * COMP_REL: n�mero de compara��oes executadas no c�mputo dos resultados.
 */
void relatorio_avl(FILE *saida, FILE *resultado, PtAVL *avl, int nodos, int altura, int fb, double miliseconds_ger, double miliseconds_rel, int comp_ger, int comp_rel, int rot)
{
    char aux;

    fprintf(saida, "**********ESTAT�STICAS DA GERA��O DA �RVORE AVL *************\n");
    fprintf(saida, "N�mero de Nodos: %i\n", nodos);
    fprintf(saida, "Altura: %i\n", altura);
    fprintf(saida, "Fator de Balanceamento: %i\n", fb);
    fprintf(saida, "Tempo: %f s\n", miliseconds_ger);
    fprintf(saida, "Rota��es: %i\n", rot);
    fprintf(saida, "Compara��es: %i\n", comp_ger);
    while((aux = fgetc(resultado)) != EOF)
        fputc(aux, saida);
    fprintf(saida, "\n");
    fprintf(saida, "Tempo: %f s\n", miliseconds_rel);
    fprintf(saida, "Compara��es: %i\n", comp_rel);
    fclose(saida);
    fclose(resultado);
}

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
 * Retorna arquivo com os caracteres em caixa baixa e sem pontua��o, usando apenas espa�os entre as palavras.
 *
 * FILE *entrada: ponteiro para o arquivo que ser� lido;
 * FILE *saida: ponteiro para o arquivo de sa�da;
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
 * Interpreta as opera��es solicitadas no arquivo de texto de entrada e chama a fun��o de acordo, imprimindo no arquivo de sa�da o resultado destas opera��es, computando o n�mero de compara��es necess�ria para tal.
 *
 * OP: ponteiro para o arquivo que ser� lido;
 * RESULTADO: ponteiro para o arquivo de sa�da com o resultado das opera��es;
 * AVL: AVL onde ser�o efetuadas as opera��es;
 * COMP_GER: N�mero de compara��oes executadas.
 */
void le_operacoes(FILE *op, FILE *resultado, PtAVL *print, PtAVL *avl, int *comp_rel)
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
                frequencia_avl(resultado, avl, palavra, comp_rel);
            }
            else if(strcmp(aux, "C") == 0 || strcmp(aux, "c") == 0)
            {
                f0 = atoi(strtok(NULL, " "));
                f1 = atoi(strtok(NULL, "\n"));
                contador_avl(&print, avl, f0, f1, comp_rel);
                imprime_avl(resultado, print, f0, f1);
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
 * SAIDA: Arquivo de sa�da com o relat�rio final.
 * RESULTADO: Arquivo com os resultados das opera��es.
 * AVL: AVL cujos resultados ser�o exibidos.
 * NODOS: N�mero de nodos da AVL.
 * ALTURA: Altura da AVL.
 * FB: Fator de Balanceamento da AVL.
 * MILISECONDS_GER: tempo de execu��o da AVL.
 * MILISECONDS_REL: Tempo de execu��o dos resultados.
 * COMP_GER: N�mero de compara��oes executadas na montagem da AVL.
 * COMP_REL: N�mero de compara��oes executadas no c�mputo dos resultados.
 */
void relatorio_avl(FILE *saida, FILE *resultado, PtAVL *avl, int nodos, int altura, int fb, double miliseconds_ger, double miliseconds_rel, int comp_ger, int comp_rel)
{
    char aux;

    fprintf(saida, "**********ESTAT�STICAS DA GERA��O DA �RVORE AVL *************\n");
    fprintf(saida, "N�mero de Nodos: %i\n", nodos);
    fprintf(saida, "Altura: %i\n", altura);
    fprintf(saida, "Fator de Balanceamento: %i\n", fb);
    fprintf(saida, "Tempo: %f s\n", miliseconds_ger);
    fprintf(saida, "Compara��es: %i\n", comp_ger);
    while((aux = fgetc(resultado)) != EOF)
        fputc(aux, saida);
    fprintf(saida, "\n");
    fprintf(saida, "Tempo: %f s\n", miliseconds_rel);
    fprintf(saida, "Compara��es: %i\n", comp_rel);
    fclose(saida);
    fclose(resultado);
}

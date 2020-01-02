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
 * Retorna AVL com os caracteres em caixa baixa e sem pontuação, incrementando contador de comparações.
 *
 * ENTRADA: ponteiro para o arquivo que será lido;
 * AVL: ponteiro duplo para a AVL de saída;
 * COMP: ponteiro para o número de comparações realizadas.
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
 * LE_OPERAÇOES (VOID)
 * Interpreta as operações solicitadas no arquivo de texto de entrada e chama a função de acordo, imprimindo no arquivo de saída o resultado destas operações, incrementando contador de comparações.
 *
 * OP: ponteiro para o arquivo que será lido;
 * RESULTADO: ponteiro para o arquivo de saída com o resultado das operações;
 * AVL0: ponteiro para a AVL que irá receber as palavras ordenadas por frequência;
 * AVL1: ponteiro para a AVL resultante da leitura do texto;
 * COMP: ponteiro para o número de comparações realizadas.
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
 * Imprime relatório final concatenando as informações obtidas.
 *
 * SAIDA: ponteiro para o arquivo de saída com o relatório final.
 * RESULTADO: ponteiro para o arquivo com os resultados das operações.
 * AVL: ponteiro para a AVL cujos resultados serão exibidos.
 * NODOS: número de nodos da AVL.
 * ALTURA: altura da AVL.
 * FB: fator de balanceamento da AVL.
 * MILISECONDS_GER: tempo de execução da AVL.
 * MILISECONDS_REL: tempo de execução dos resultados.
 * COMP_GER: número de comparaçãoes realizadas na montagem da AVL oriunda do texto.
 * COMP_REL: número de comparaçãoes executadas no cômputo dos resultados.
 */
void relatorio_avl(FILE *saida, FILE *resultado, PtAVL *avl, int nodos, int altura, int fb, double miliseconds_ger, double miliseconds_rel, int comp_ger, int comp_rel, int rot)
{
    char aux;

    fprintf(saida, "**********ESTATÍSTICAS DA GERAÇÃO DA ÁRVORE AVL *************\n");
    fprintf(saida, "Número de Nodos: %i\n", nodos);
    fprintf(saida, "Altura: %i\n", altura);
    fprintf(saida, "Fator de Balanceamento: %i\n", fb);
    fprintf(saida, "Tempo: %f s\n", miliseconds_ger);
    fprintf(saida, "Rotações: %i\n", rot);
    fprintf(saida, "Comparações: %i\n", comp_ger);
    while((aux = fgetc(resultado)) != EOF)
        fputc(aux, saida);
    fprintf(saida, "\n");
    fprintf(saida, "Tempo: %f s\n", miliseconds_rel);
    fprintf(saida, "Comparações: %i\n", comp_rel);
    fclose(saida);
    fclose(resultado);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "avl.h"
#include "texto.h"

#define LINHAS 1000
#define PARAM 4

/**
 * TXTTOAVL 1.2.2:
 * Recebe dois arquivos de texto como entrada, o primeiro � um texto, o segundo um conjunto de opera��es. Converte todos caracteres do texto para caixa baixa e,
 * passa cada palavra do texto para uma AVL de strings, em seguida, aplica as opera��es contidas no segundo arquivo e emite um relat�rio das opera��es aplicadas e seus resultados.
 * Um otimiza��o na fun��o CONTADOR_AVL evita que se percorra a �rvore em v�o quando se busca uma frequ�ncia a qual nenhuma palavra na AVL tem.
 * Exemplo de chamada "compararvores entrada.txt operacoes.txt saida.txt"
 */

/**
 * MAIN (INT)
 * Recebe dois arquivos de texto como entrada, o primeiro � um texto, o segundo um conjunto de opera��es. Converte todos caracteres do texto para caixa baixa e,
 * passa cada palavra do texto para uma AVL de strings, em seguida, aplica as opera��es contidas no segundo arquivo e emite um relat�rio das opera��es aplicadas e seus resultados.
 * Exemplo de chamada "compararvores entrada.txt operacoes.txt saida.txt"
 *
 * ARGV[1]: texto de entrada;
 * ARGV[2]: texto com as opera��es;
 * ARGV[3]: texto de sa�da.
 */
int main(int argc, char *argv[])
{
    //configura��o do System Locale
    setlocale(LC_ALL,"portuguese");                 //para imprimir corretamente na tela os caracteres acentuados, tive colocar "portuguese" pois minha m�quina est� com system locale configurado para ingl�s

    //declara��o de vari�veis
    clock_t start_ger, end_ger, start_rel, end_rel;     //guardam o tempo inicial e final para c�lculo do tempo de execu��o
    FILE *entrada, *op, *resultado, *saida;             //entrada recebe argv[1]; temp recebe o texto convertido para caixa baixa; op recebe argv[2]; resultado recebe o resultado das opera��es; saida recebe o relat�rio final
    PtAVL *avl;                                         //avl recebe a �rvore bin�ria de pesquisa balanceada (AVL)
    PtAVL *abp;                                         //avl recebe a �rvore bin�ria de pesquisa (ABP)
    int nodos, altura, fb, comp_ger, comp_rel, ok, rot, ok_rel, rot_rel; //nodos recebe o n�mero de nodos; altura recebe a altura da �rvore; fb recebe o fator de balanceamento (FB) da �rvore; comp_ger recebe o n�mero de compara��es realizadas para gerar a �rvore bin�ria de pequisa; comp_rel recebe o n�mero de compara��es realizadas da gera��o dos resultados das opera��es; ok indica se AVL est� ok
    double miliseconds_ger, miliseconds_rel;            //miliseconds_ger recebe o tempo de execu��o da gera��o da AVL; miliseconds_rel recebe o tempo de execu��o da gera��o dos resultados das opera��es

    //inicializa��o de vari�veis
    avl = inicializa_avl();
    abp = inicializa_avl();
    ok = 0;
    ok_rel = 0;
    comp_ger = 0;
    comp_rel = 0;
    rot = 0;
    rot_rel = 0;

    //in�cio do Programa
    if(argc!=PARAM)
    {
        printf("N�mero incorreto de argumentos.\nPara chamar o programa, digite: \"compararvores <entrada>.txt operacoes.txt <saida>.txt\".\n");
        return 1;
    }
    else
    {
        entrada = fopen (argv[1], "r"); //testa se n�meros de par�metros para chamada do programa est� correto, caso contr�rio exibe mensagem de erro, encerrando execu��o com c�digo 1
        if (!entrada) //abre argv[1] e em seguida testa se sua abertura foi bem sucedida, caso contr�rio, encerra execu��o com c�digo 1
        {
            printf("Erro ao abrir o arquivo %s.",argv[1]);
            return 1;
        }
        op = fopen (argv[2], "r"); //abre argv[2] e em seguida testa se sua abertura foi bem sucedida, caso contr�rio, encerra execu��o com c�digo 1
        if (!op)
        {
            printf("Erro ao abrir o arquivo %s.",argv[2]);
            return 1;
        }
        saida = fopen(argv[3], "w");
        resultado = fopen("resultado.txt", "w");

        //gera��o da AVL com as palavras do texto argv[1]
        start_ger = clock();                                              //inicia a contagem do tempo
        caixa_baixa_avl(entrada, &avl, &comp_ger, &rot, &ok);             //converte argv[1] para caixa baixa e exporta o resultado para temp.txt
        end_ger = clock();                                                //finaliza contagem do tempo
        miliseconds_ger = (double)(end_ger - start_ger) / CLOCKS_PER_SEC; //calcula o tempo decorrido

        //realiza��o das opera��es contidas em argv[2]
        start_rel = clock();                                               //inicia a contagem do tempo
        nodos = conta_avl(avl, &comp_rel);                                 //calcula n�mero de nodos da AVL
        altura = altura_avl(avl, &comp_rel);                               //calcula altura da AVL
        fb = fator_balanceamento_avl(avl, &comp_rel);                      //calcula FB da AVL
        le_operacoes(op, resultado, abp, avl, &comp_rel, &rot_rel, &ok_rel);                  //interpreta e realiza as opera��es solicitadas
        resultado = fopen("resultado.txt", "r");                           //abre resultado.txt para leitura
        end_rel = clock();                                                 //finaliza contagem do tempo
        miliseconds_rel = (double)(end_rel - start_rel) / CLOCKS_PER_SEC;  //calcula o tempo decorrido

        //gera relat�rio
        relatorio_avl(saida, resultado, avl, nodos, altura, fb, miliseconds_ger, miliseconds_rel, comp_ger, comp_rel, rot, rot_rel);
        return 0;
    }
}

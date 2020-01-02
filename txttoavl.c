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
 * Recebe dois arquivos de texto como entrada, o primeiro é um texto, o segundo um conjunto de operações. Converte todos caracteres do texto para caixa baixa e,
 * passa cada palavra do texto para uma AVL de strings, em seguida, aplica as operações contidas no segundo arquivo e emite um relatório das operações aplicadas e seus resultados.
 * Um otimização na função CONTADOR_AVL evita que se percorra a árvore em vão quando se busca uma frequência a qual nenhuma palavra na AVL tem.
 * Exemplo de chamada "compararvores entrada.txt operacoes.txt saida.txt"
 */

/**
 * MAIN (INT)
 * Recebe dois arquivos de texto como entrada, o primeiro é um texto, o segundo um conjunto de operações. Converte todos caracteres do texto para caixa baixa e,
 * passa cada palavra do texto para uma AVL de strings, em seguida, aplica as operações contidas no segundo arquivo e emite um relatório das operações aplicadas e seus resultados.
 * Exemplo de chamada "compararvores entrada.txt operacoes.txt saida.txt"
 *
 * ARGV[1]: texto de entrada;
 * ARGV[2]: texto com as operações;
 * ARGV[3]: texto de saída.
 */
int main(int argc, char *argv[])
{
    //configuração do System Locale
    setlocale(LC_ALL,"portuguese");                 //para imprimir corretamente na tela os caracteres acentuados, tive colocar "portuguese" pois minha máquina está com system locale configurado para inglês

    //declaração de variáveis
    clock_t start_ger, end_ger, start_rel, end_rel;     //guardam o tempo inicial e final para cálculo do tempo de execução
    FILE *entrada, *op, *resultado, *saida;             //entrada recebe argv[1]; temp recebe o texto convertido para caixa baixa; op recebe argv[2]; resultado recebe o resultado das operações; saida recebe o relatório final
    PtAVL *avl;                                         //avl recebe a árvore binária de pesquisa balanceada (AVL)
    PtAVL *abp;                                         //avl recebe a árvore binária de pesquisa (ABP)
    int nodos, altura, fb, comp_ger, comp_rel, ok, rot, ok_rel, rot_rel; //nodos recebe o número de nodos; altura recebe a altura da árvore; fb recebe o fator de balanceamento (FB) da árvore; comp_ger recebe o número de comparações realizadas para gerar a árvore binária de pequisa; comp_rel recebe o número de comparações realizadas da geração dos resultados das operações; ok indica se AVL está ok
    double miliseconds_ger, miliseconds_rel;            //miliseconds_ger recebe o tempo de execução da geração da AVL; miliseconds_rel recebe o tempo de execução da geração dos resultados das operações

    //inicialização de variáveis
    avl = inicializa_avl();
    abp = inicializa_avl();
    ok = 0;
    ok_rel = 0;
    comp_ger = 0;
    comp_rel = 0;
    rot = 0;
    rot_rel = 0;

    //início do Programa
    if(argc!=PARAM)
    {
        printf("Número incorreto de argumentos.\nPara chamar o programa, digite: \"compararvores <entrada>.txt operacoes.txt <saida>.txt\".\n");
        return 1;
    }
    else
    {
        entrada = fopen (argv[1], "r"); //testa se números de parâmetros para chamada do programa está correto, caso contrário exibe mensagem de erro, encerrando execução com código 1
        if (!entrada) //abre argv[1] e em seguida testa se sua abertura foi bem sucedida, caso contrário, encerra execução com código 1
        {
            printf("Erro ao abrir o arquivo %s.",argv[1]);
            return 1;
        }
        op = fopen (argv[2], "r"); //abre argv[2] e em seguida testa se sua abertura foi bem sucedida, caso contrário, encerra execução com código 1
        if (!op)
        {
            printf("Erro ao abrir o arquivo %s.",argv[2]);
            return 1;
        }
        saida = fopen(argv[3], "w");
        resultado = fopen("resultado.txt", "w");

        //geração da AVL com as palavras do texto argv[1]
        start_ger = clock();                                              //inicia a contagem do tempo
        caixa_baixa_avl(entrada, &avl, &comp_ger, &rot, &ok);             //converte argv[1] para caixa baixa e exporta o resultado para temp.txt
        end_ger = clock();                                                //finaliza contagem do tempo
        miliseconds_ger = (double)(end_ger - start_ger) / CLOCKS_PER_SEC; //calcula o tempo decorrido

        //realização das operações contidas em argv[2]
        start_rel = clock();                                               //inicia a contagem do tempo
        nodos = conta_avl(avl, &comp_rel);                                 //calcula número de nodos da AVL
        altura = altura_avl(avl, &comp_rel);                               //calcula altura da AVL
        fb = fator_balanceamento_avl(avl, &comp_rel);                      //calcula FB da AVL
        le_operacoes(op, resultado, abp, avl, &comp_rel, &rot_rel, &ok_rel);                  //interpreta e realiza as operações solicitadas
        resultado = fopen("resultado.txt", "r");                           //abre resultado.txt para leitura
        end_rel = clock();                                                 //finaliza contagem do tempo
        miliseconds_rel = (double)(end_rel - start_rel) / CLOCKS_PER_SEC;  //calcula o tempo decorrido

        //gera relatório
        relatorio_avl(saida, resultado, avl, nodos, altura, fb, miliseconds_ger, miliseconds_rel, comp_ger, comp_rel, rot, rot_rel);
        return 0;
    }
}

/* Desafio de Programação - Grafos - Pacman Simples
*  11218963 - Ana Luisa T. Costa
*  9866531  - Ana Laura Chioca
*  11218809 - Flavio Salles
*  11219004 - Yasmin O. de Araujo
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listaadj.h"
#include "fila.h"

/* 
*  Função que realiza busca em amplitude (BFS) para preencher o tabuleiro
*  com as distâncias em relação ao "fantasma" 
*/
void bfs(int vf, int n, int **tabuleiro, GRAFO *lista_adj)
{
    int i = vf / n; // Coordenadas do fantasma
    int j = vf % n;
    int dist = 0;

    // Inicializar as filas com valores do primeiro vértice
    FILA *fila = fila_criar();
    FILA *fila_dist = fila_criar();
    fila_entra(fila, vf);
    fila_entra(fila_dist, dist);

    while (!fila_vazia(fila))
    {
        // Pegar primeiro vértice da fila e sua distância
        int v = fila_sai(fila);
        dist = fila_sai(fila_dist);

        // Inserir a distância no tabuleiro caso esteja como 0 e não seja a posição do fantasma
        if ((v / n != i || v % n != j) && tabuleiro[v / n][v % n] == 0)
            tabuleiro[v / n][v % n] = dist;

        // Adicionar adjacencias do v na lista
        for (int x = 0; x < tamanho_lista(lista_adj, v); x++)
        {
            int prox = get_valor(lista_adj, v, x);

            // Caso vértice ainda não tenha sido processado e não seja a posição do fantasma
            if ((prox / n != i || prox % n != j) && tabuleiro[prox / n][prox % n] == 0)
            {
                // Inserir valores do vértice nas filas
                fila_entra(fila, prox);
                fila_entra(fila_dist, dist + 1);
            }
        }
    }
    // Desaloca espaço reservado na memória para as filas
    fila_apagar(&fila);
    fila_apagar(&fila_dist);
}

// Função para movimentar o pacman para uma posição de menor valor
int moverPacman(int pos, int n, int **tabuleiro, GRAFO *lista_adj)
{
    int i = pos / n;
    int j = pos % n;
    int valor_atual = tabuleiro[i][j];
    int prox_pos;

    // Checar valor de cada adjacencia até achar um menor ao atual
    for (int x = 0; x < tamanho_lista(lista_adj, pos); x++)
    {
        prox_pos = get_valor(lista_adj, pos, x);
        // Conferir se é menor
        if (tabuleiro[prox_pos / n][prox_pos % n] < valor_atual)
            return prox_pos;
    }
    return -1;
}

// Função para imprimir o tabuleiro do jogo na partida atual
void mostraTabuleiro(int pos_pac, int n, int **tabuleiro)
{
    for (int i = 0; i < n; i++)
    {
        printf("|");
        for (int j = 0; j < n; j++)
        {
            if (pos_pac == (i * n) + j)
            {
                printf("\033[1;33m"); // Código para mudar as cores no terminal
                printf(" P ");
                printf("\033[0m");
                printf("|");
            }
            else if (tabuleiro[i][j] == 0)
            {
                printf("\033[1;31m");
                printf(" F ");
                printf("\033[0m");
                printf("|");
            }
            else
                printf(" %d |", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int n; // Tamanho da matriz quadrada (tabuleiro)
    do
    {
        printf("Digite o tamanho do tabuleiro: ");
        scanf("%d", &n);
    } while (n < 2);

    // Criar tabuleiro de tamanho nxn e preenchendo com 0
    int **tabuleiro = (int **)malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++)
        tabuleiro[i] = (int *)calloc(n, sizeof(int));

    // Criar um grafo com n^2 nós
    GRAFO *lista_adj = criagrafo(n * n);

    // Preencher lista de adj
    for (int i = 0; i < n * n; i++)
    {
        // Inserir aresta com o próximo valor da mesma linha
        if (i + 1 < n * n && i / n == (i + 1) / n)
            inserearesta(lista_adj, i, i + 1);

        // Inserir aresta com o próximo valor da mesma coluna
        if (i + n < n * n)
            inserearesta(lista_adj, i, i + n);
    }

    // Gerar a posição do fantasma
    srand(time(NULL));
    int pos_fant = rand() % (n * n);

    // Modelar a vizinhança
    bfs(pos_fant, n, tabuleiro, lista_adj);

    // Gerar a posição do pacman
    int pos_pac = rand() % (n * n);

    // Gerar uma nova posição para o pacman caso ele esteja no mesmo lugar do fantasma
    while (pos_fant == pos_pac)
        pos_pac = rand() % (n * n);

    // Mostrar tabuleiro
    mostraTabuleiro(pos_pac, n, tabuleiro);

    // Movimentar o fantasma pelo menor caminho
    while (pos_pac != pos_fant)
    {
        pos_pac = moverPacman(pos_pac, n, tabuleiro, lista_adj);
        mostraTabuleiro(pos_pac, n, tabuleiro);
    }

    printf("Achou o fantasma!\n");

    // Desalocar espaço reservado na memória para as estruturas de dados
    deletagrafo(lista_adj);

    for (int i = 0; i < n; i++)
        free(tabuleiro[i]);
    free(tabuleiro);

    return 0;
}
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <list>
#include "dimacsFile.h"
#include "bitMapGraph.h"
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

#include <bits/stdc++.h>

#define eps 0.000001
#define WHITE 0
#define BLUE 1
#define RED 2

using namespace std;

#include <iostream>
#include <limits.h>

int n, LB, LR, contB, contR; // Class B = Blue and Class R = Red
long long m;
int *cls, *realSolutioncls, *mark;
int **d;
bool ***D, realInst; // D = Shortest Path Sets
double *grau, *grauMmc;

typedef long long int ll;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Teoria para entendimento da implementação
// a: matrix(solucao), k: grupo, z: fecho convexo

// um grupo por classe (classe blue e classe red)

// 'a' representa a matriz da solucao incial
//  a[k][i] = 1

// Preenchendo Matriz 'a' (solucao inicial) (provavelmente inviável)
//
// for(int i=0; i < n; i++){
//     if(cls[i] == BLUE){
//            a[0][i] = 1;
//            a[1][i] = 0;
//
//     }if(cls[i] == RED) {
//            a[0][i] = 0;
//            a[1][i] = 1;
//
//     }if()cls[i] == WHITE){
//            a[0][i] = 0;
//            a[1][i] = 0;
//     }
// }

// Depois disso calcular o fecho convexo passando 'a' e grupo(B e R)

// Representando uma matriz onde cada vértice é azul, ou vermelho, ou não classificado
// (portanto, nesse caso não vai existir outlier)
//
// (k)     0    ...    i      ...     (n-1)
//  B 0    1 1 0 1 0 1 0 0 0 0 0  ...   1
//  R 1    0 0 1 0 0 0 1 1 0 1 1  ...   0
//
////////////////////////////////////////////////////////////////////////////////////////////////

// Utility function to find MDC of 'a' and 'b'
int mdc(int a, int b)
{
    if (b == 0)
        return a;
    return mdc(b, a % b);
}

// Returns MMC of array elements
ll calMmc(int arr[], int n)
{
    // Initialize result
    ll ans = arr[0];

    // ans contains MMC of arr[0], ..arr[i]
    // after i'th iteration,
    for (int i = 1; i < n; i++)
        ans = (((arr[i] * ans)) /
               (mdc(arr[i], ans)));
    return ans;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Critérios:
//
// Escolher aleatoriamente um vértive i :
//      1. dentro do grupo de MENOR cardinalidade
//      2. dentro do grupo de MAIOR cardinalidade
//      3. dentro do grupo de MENOR cardinalidade
//         "dando prioridade, através de pesos nos vértices", para os vértices de MAIOR grau.
//      4. dentro do grupo de MENOR cardinalidade
//         "dando prioridade, através de pesos nos vértices", para os vértices de MENOR grau.
//      5. dentro do grupo de MAIOR cardinalidade
//         "dando prioridade, através de pesos nos vértices", para os vértices de MAIOR grau.
//      6. dentro do grupo de MAIOR cardinalidade
//         "dando prioridade, através de pesos nos vértices", para os vértices de MENOR grau
//
//////////////////////////////////////////////////////////////////////////////////////////////////

// Critério 6
int setOutlier6(int vViolado, int b, int r, int **a, int *contVetor)
{

    if (cls[vViolado] == BLUE)
    {
        a[b][vViolado] = 0; // settando vértice BLUE como outlier
        return b;
    }
    else if (cls[vViolado] == RED)
    {
        a[r][vViolado] = 0; // settando vértice RED como outlier
        return r;

        // critério 6
    }
    else
    {
        if (contVetor[0] >= contVetor[1])
        {

            int *grausGrupoB;
            grausGrupoB = (int *)malloc(contVetor[0] * sizeof(int));
            int j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    grausGrupoB[j] = grau[i]; // grausGrupoB[j] é um vetor com os graus de cada vértice do grupo da classe azul
                    j++;
                }
            }

            int mmc = calMmc(grausGrupoB, j);

            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    grauMmc[i] = mmc / grauMmc[i]; // grauMmc[i] é uma copia de grau[i]
                }
            }

            int somaGraus = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    somaGraus += grauMmc[i];
                }
            }

            if (somaGraus == 0)
            {
                return -1;
            }

            srand((unsigned)time(0));
            int iRand = (rand() % (somaGraus)) + 1; // calcular a soma dos graus de cada vertice que ta no grupo (neste caso, o azul)

            j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    if (j + grauMmc[i] >= iRand)
                    {
                        a[0][i] = 0;
                        return 0;
                    }
                    j += grauMmc[i];
                }
            }
            free(grausGrupoB);
            return -1;
        }
        else
        {

            int *grausGrupoR;
            grausGrupoR = (int *)malloc(contVetor[1] * sizeof(int));
            int j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    grausGrupoR[j] = grau[i];
                    j++;
                }
            }

            int mmc = calMmc(grausGrupoR, j);

            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    grauMmc[i] = mmc / grauMmc[i];
                }
            }

            int somaGraus = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    somaGraus += grauMmc[i];
                }
            }

            if (somaGraus == 0)
            {
                return -1;
            }

            srand((unsigned)time(0));
            int iRand = (rand() % (somaGraus)) + 1; // somaGraus = calcular a soma dos graus de cada vertice que ta no grupo (neste caso, o vermelho)
            j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    if (j + grauMmc[i] >= iRand)
                    {
                        a[1][i] = 0;
                        return 1;
                    }
                    j += grauMmc[i];
                }
            }
            free(grausGrupoR);
        }
    }
    for (int i = 0; i < n; i++)
    {
        grauMmc[i] = grau[i]; // grauMmc[i] é uma copia de grau[i]
    }

    return -1;
}

// Critério 5

int setOutlier5(int vViolado, int b, int r, int **a, int *contVetor)
{

    if (cls[vViolado] == BLUE)
    {
        a[b][vViolado] = 0; // settando vértice BLUE como outlier
        return b;
    }
    else if (cls[vViolado] == RED)
    {
        a[r][vViolado] = 0; // settando vértice RED como outlier
        return r;

        // critério 5
    }
    else
    {
        if (contVetor[0] >= contVetor[1])
        {
            int somaGraus = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    somaGraus += grau[i];
                }
            }

            srand((unsigned)time(0));
            int iRand = (rand() % (somaGraus)) + 1; // calcular a soma dos graus de cada vertice que ta no grupo (neste caso, o azul)

            int j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    if (j + grau[i] >= iRand)
                    {
                        a[0][i] = 0;
                        return 0;
                    }
                    j += grau[i];
                }
            }
        }
        else
        {
            int somaGraus = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    somaGraus += grau[i];
                }
            }
            srand((unsigned)time(0));
            int iRand = (rand() % (somaGraus)) + 1; // calcular a soma dos graus de cada vertice que ta no grupo (neste caso, o vermelho)
            int j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    if (j + grau[i] >= iRand)
                    {
                        a[1][i] = 0;
                        return 1;
                    }
                    j += grau[i];
                }
            }
        }
    }
    return -1;
}

// Critério 4
int setOutlier4(int vViolado, int b, int r, int **a, int *contVetor)
{

    if (cls[vViolado] == BLUE)
    {
        a[b][vViolado] = 0; // settando vértice BLUE como outlier
        return b;
    }
    else if (cls[vViolado] == RED)
    {
        a[r][vViolado] = 0; // settando vértice RED como outlier
        return r;

        // critério 4
    }
    else
    {
        if (contVetor[0] <= contVetor[1])
        {

            int *grausGrupoB;
            grausGrupoB = (int *)malloc(contVetor[0] * sizeof(int));
            int j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    grausGrupoB[j] = grau[i]; // grausGrupoB[j] é um vetor com os graus de cada vértice do grupo da classe azul
                    j++;
                }
            }

            int mmc = calMmc(grausGrupoB, j);

            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    grauMmc[i] = mmc / grauMmc[i]; // grauMmc[i] é uma copia de grau[i]
                }
            }

            int somaGraus = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    somaGraus += grauMmc[i];
                }
            }

            if (somaGraus == 0)
            {
                return -1;
            }

            srand((unsigned)time(0));
            int iRand = (rand() % (somaGraus)) + 1; // calcular a soma dos graus de cada vertice que ta no grupo (neste caso, o azul)

            j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    if (j + grauMmc[i] >= iRand)
                    {
                        a[0][i] = 0;
                        return 0;
                    }
                    j += grauMmc[i];
                }
            }
            free(grausGrupoB);
        }
        else
        {

            int *grausGrupoR;
            grausGrupoR = (int *)malloc(contVetor[1] * sizeof(int));
            int j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    grausGrupoR[j] = grau[i];
                    j++;
                }
            }

            int mmc = calMmc(grausGrupoR, j);

            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    grauMmc[i] = mmc / grauMmc[i];
                }
            }

            int somaGraus = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    somaGraus += grauMmc[i];
                }
            }

            if (somaGraus == 0)
            {
                return -1;
            }

            srand((unsigned)time(0));
            int iRand = (rand() % (somaGraus)) + 1; // somaGraus = calcular a soma dos graus de cada vertice que ta no grupo (neste caso, o vermelho)
            j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    if (j + grauMmc[i] >= iRand)
                    {
                        a[1][i] = 0;
                        return 1;
                    }
                    j += grauMmc[i];
                }
            }
            free(grausGrupoR);
        }
    }

    for (int i = 0; i < n; i++)
    {
        grauMmc[i] = grau[i]; // grauMmc[i] é uma copia de grau[i]
    }
    return -1;
}

// Critério 3

int setOutlier3(int vViolado, int b, int r, int **a, int *contVetor)
{

    if (cls[vViolado] == BLUE)
    {
        a[b][vViolado] = 0; // settando vértice BLUE como outlier
        return b;
    }
    else if (cls[vViolado] == RED)
    {
        a[r][vViolado] = 0; // settando vértice RED como outlier
        return r;

        // Critério 3
    }
    else
    {
        if (contVetor[0] <= contVetor[1])
        {
            // somaGraus = vetor que tem a soma dos graus de um grupo
            int somaGraus = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    somaGraus += grau[i]; // calcular a soma dos graus de cada vertice que ta no grupo (neste caso, o azul)
                }
            }

            srand((unsigned)time(0));
            int iRand = (rand() % (somaGraus)) + 1;

            // vai percorrer os valores de 1 até soma de graus
            int j = 0;
            for (int i = 0; i < n; i++)
            { // Para cada vértice que ta no grupo, vou percorrer x pontos, onde x é o grau do vértice, e verificar se esse ponto é o ponto sorteado
                if (a[0][i] == 1)
                {

                    // Exemplo:
                    // 1 2 3 4 5 6 7 8 ...
                    // 2   3     3        = 8 (somaGraus)
                    // v1  v2    v3

                    if (j + grau[i] >= iRand)
                    {
                        a[0][i] = 0;
                        return 0;
                    }
                    j += grau[i];
                }
            }
        }
        else
        {
            int somaGraus = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    somaGraus += grau[i];
                }
            }
            srand((unsigned)time(0));
            int iRand = (rand() % (somaGraus)) + 1; // calcular a soma dos graus de cada vertice que ta no grupo (neste caso, o azul)
            int j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    if (j + grau[i] >= iRand)
                    {
                        a[1][i] = 0;
                        return 1;
                    }
                    j += grau[i];
                }
            }
        }
    }
    return -1;
}

// Critério 2 :

int setOutlier2(int vViolado, int b, int r, int **a, int *contVetor)
{

    if (cls[vViolado] == BLUE)
    {
        a[b][vViolado] = 0; // settando vértice BLUE como outlier
        return b;
    }
    else if (cls[vViolado] == RED)
    {
        a[r][vViolado] = 0; // settando vértice RED como outlier
        return r;

        // Critério 2
        // setteando um vértice aleatório dentro do grupo de MAIOR cardinalidade
    }
    else
    {
        if (contVetor[0] >= contVetor[1])
        {
            int cont = -1;
            srand((unsigned)time(0));
            int iRand = rand() % (contVetor[0]);
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    cont++;
                    if (cont == iRand)
                    {
                        a[0][i] = 0;
                        return 0;
                    }
                }
            }
        }
        else
        {
            int cont = -1;
            srand((unsigned)time(0));
            int iRand = rand() % (contVetor[1]);
            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    cont++;
                    if (cont == iRand)
                    {
                        a[1][i] = 0;
                        return 1;
                    }
                }
            }
        }
    }
    return -1;
}

//      Critério 1 :

int setOutlier1(int vViolado, int b, int r, int **a, int *contVetor)
{

    if (cls[vViolado] == BLUE)
    {
        a[b][vViolado] = 0; // settando vértice BLUE como outlier
        return b;
    }
    else if (cls[vViolado] == RED)
    {
        a[r][vViolado] = 0; // settando vértice RED como outlier
        return r;

        // Critério 1
        // setteando um vértice aleatório dentro do grupo de MENOR cardinalidade
    }
    else
    {
        if (contVetor[0] <= contVetor[1])
        {
            int cont = -1;
            srand((unsigned)time(0));
            int iRand = rand() % (contVetor[0]);
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    cont++;
                    if (cont == iRand)
                    {
                        a[0][i] = 0;
                        return 0;
                    }
                }
            }
        }
        else
        {
            int cont = -1;
            srand((unsigned)time(0));
            int iRand = rand() % (contVetor[1]);
            for (int i = 0; i < n; i++)
            {
                if (a[1][i] == 1)
                {
                    cont++;
                    if (cont == iRand)
                    {
                        a[1][i] = 0;
                        return 1;
                    }
                }
            }
        }
    }
    return -1;
}

// Funcao shuffle
void shuffle(int *array, int n)
{
    if (n > 1)
    {
        int i;
        for (i = 0; i < n - 1; i++)
        {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

// Calculates all Dhj sets by the Breath First Search algorithm (BFS)(Busca em largura)
// and also calculate all arborescenses A[h] of all minimum paths from h
void BFS_make_Dhj(int h)
{
    int k = 0;
    list<int> queue;

    for (int i = 0; i < n; i++)
        d[h][i] = n + 1;
    d[h][h] = 0;
    queue.push_back(h);

    while (!queue.empty())
    {
        k = queue.front();
        queue.pop_front();

        for (int j = 0; j < n; j++)
            if (j != k && hasEdge(k, j) && d[h][k] < d[h][j])
            {
                if (d[h][j] > n)
                {
                    queue.push_back(j);
                }
                d[h][j] = d[h][k] + 1;
                if (d[h][j] > 1)
                {
                    D[h][j][k] = true;
                    for (int i = 0; i < n; i++)
                        if (D[h][k][i])
                            D[h][j][i] = true;
                }
            }
    }
}

// Função que calcula o fecho convexo de um grupo
void cal_Conv(int **a, int k, int **z)
{

    z[k] = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        z[k][i] = a[k][i]; // colocando todos os elementos da matriz 'a' (com seus respectivos grupos)
                           // no fecho convexo do grupo.
    }
    bool finished = false, brk = false;
    while (!finished)
    {
        finished = true;
        for (int i = 0; i < n; i++)
        {
            //verificar se o vertice i não está no fecho convexo do grupo da classe k (azul ou vermelha)
            if (z[k][i] == 0)
            {
                brk = false;
                for (int h = 0; h < n; h++)
                {
                    if (z[k][h] == 1)
                    { // verifica se um vertice h está no fecho convexo
                        for (int j = h + 1; j < n; j++)
                            if (z[k][j] == 1 && D[h][j][i])
                            { // verifica se um vertice j está no fecho convexo
                                // e se i está no caminho mínimo de h ate j

                                finished = false;
                                brk = true;
                                z[k][i] = 1; // atribui i ao fecho convexo do grupo
                                break;
                            }
                    }
                    if (brk)
                        break;
                }
            }
        }
    }
}

void cal_Conv_Grups(int **a, int **z)
{
    for (int k = 0; k < (LB + LR); k++)
    {
        cal_Conv(a, k, z);
    }
}

// Calcula o número de outliers da solução 'a'
int objetivo(int **a, int *contVetor)
{

    int totalK = 0;
    for (int k = 0; k < (LB + LR); k++)
    {                                   //LB: quantidade de grupos azuis (1, no nosso caso)
        totalK = contVetor[k] + totalK; //contVetor[k] : quantidade de vértices do grupo k
    }
    return (contB + contR) - totalK; // (contB + contR) : Total de vértices inicialmete classificados.
                                     // return quantidade de outliers.
}

// Funçao que verifica se alguma restrição é violada (1, 2 ou 3).
int viavel(int **a, int **z, int *b_, int *r_)
{

    int *V = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        V[i] = i;
    }

    shuffle(V, n);

    for (int j = 0; j < n; j++)
    {

        int i = V[j];
        if (cls[i] == RED)
        {
            // verifica se i é um vertice inicialmente RED
            int r;
            for (r = LB; r < (LB + LR); r++)
            { // percorrendo todos os grupos vermelhos(no nosso caso, so um)
                if (a[r][i] == 1)
                { // verifica se i pertence a um grupo vermelho, se for 0, não pertence
                    break;
                }
            }
            if (r == (LB + LR))
                continue;

            for (int b = 0; b < LB; b++)
            { //percorrendo classe azul
                if (z[b][i] == 1)
                { //verifica se o vertice i pertence ao fecho convexo de
                    // um grupo da classe azul.
                    *b_ = b;
                    *r_ = r;
                    free(V);
                    return i;
                    //return 0;
                }
            }
        }

        // Fazer a mesma coisa para os grupos da classe BLUE
        if (cls[i] == BLUE)
        { // verifica se i é um vertice inicialmente BLUE
            int b;
            for (b = 0; b < LB; b++)
            {
                if (a[b][i] == 1)
                {
                    break;
                }
            }
            if (b == LB)
                continue;
            for (int r = LB; r < (LB + LR); r++)
            {
                if (z[r][i] == 1)
                {
                    *b_ = b;
                    *r_ = r;
                    free(V);
                    return i;
                }
            }
        }

        // Verificar se restrição do tipo 3 foi violada.
        // Verificar se um vertice inicialmente nao classificado tá no fecho convexo de dois grupos
        // de classes opostas simultaneamente.
        if (cls[i] == WHITE)
        {
            for (int b = 0; b < (LB); b++)
            { // percorrendo grupos azuis
                for (int r = LB; r < (LB + LR); r++)
                { // percorrendo grupos vermelhos
                    if (z[b][i] == 1 && z[r][i] == 1)
                    { // verificando se o vertice pertence aos dois grupos
                        *b_ = b;
                        *r_ = r;
                        free(V);
                        return i; //return vertice i que a restrição foi violada
                    }
                }
            }
        }
    }
    free(V);
    return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  ALGORITMO PROBABILÍSTICO:
//

void algProb(int **a, int **z, int *contVetor)
{

    // Montar a solucao trivial sem outliers (solução parcial inicial)
    for (int i = 0; i < n; i++)
    {
        if (cls[i] == BLUE)
        {
            a[0][i] = 1;
            a[1][i] = 0;
            contVetor[0]++;
        }
        if (cls[i] == RED)
        {
            a[0][i] = 0;
            a[1][i] = 1;
            contVetor[1]++;
        }
        if (cls[i] == WHITE)
        {
            a[0][i] = 0;
            a[1][i] = 0;
        }
    }

    // Calcula o fecho convexo dos dois grupos
    cal_Conv_Grups(a, z);

    int b, r, vViolado, k;
    vViolado = viavel(a, z, &b, &r); // Calculca se a solucao é viavel
    while (vViolado != -1)
    { // Verifica se a solução não é viável

        // Definir algum vertice do grupo, no qual a restrição foi violada, como outlier
        k = setOutlier1(vViolado, b, r, a, contVetor); //retorno da funcao é o grupo em que o vértice foi settado outlier, ou seja, foi retirado (k)
        if (k != -1)
        {
            contVetor[k]--;
            cal_Conv(a, k, z); // Recalcula o fecho convexo do grupo que o vértice foi retirado
        }
        vViolado = viavel(a, z, &b, &r); // Calculca se a solução é viavel
    }
}

//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Procedure()
{
    bool finished = false;
    int best_sol_val = n + 1;
    int **a, **z;
    int *contVetor;
    int sol_val = -1;

    a = (int **)malloc((LB + LR) * sizeof(int *));
    z = (int **)malloc((LB + LR) * sizeof(int *));
    contVetor = (int *)malloc((LB + LR) * sizeof(int));
    for (int k = 0; k < (LB + LR); k++)
    {
        a[k] = (int *)malloc(n * sizeof(int));
        memset(a[k], 0, n * sizeof(int));

        z[k] = (int *)malloc(n * sizeof(int));
        memset(z[k], 0, n * sizeof(int));
    }
    //LB: Quantidade de grupos blue
    //LR: Quantidade de grupos red
    for (int o = 0; o < (LB + LR); o++)
    {
        contVetor[o] = 0;
    }

    algProb(a, z, contVetor);

    sol_val = objetivo(a, contVetor);

    //  TESTE: min{|V_B|,|V_R|} < qtd_outliers:
    int min = contR;
    if (contB <= contR)
    {
        min = contB;
    }
    if ((sol_val > contR || sol_val > contB))
    {

        for (int k = 0; k < 2; k++)
        {
            memset(a[k], 0, n * sizeof(int));
            contVetor[k] = 0;
        }

        if (min == contB)
        {
            for (int i = 0; i < n; i++)
            {
                if (cls[i] == RED)
                {
                    a[1][i] = 1;
                    contVetor[1]++;
                }
            }
            sol_val = contB;
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                if (cls[i] == BLUE)
                {
                    a[0][i] = 1;
                    contVetor[0]++;
                }
            }
            sol_val = contR;
        }
    }

    printf("%d; ", sol_val);

    int nVN = 0;
    if (realInst)
    { // If it is a realistic instance!
        int nerror = 0;
        for (int i = 0; i < n; i++)
            if (cls[i] == WHITE)
            {
                nVN++;
                int solutioncls = WHITE;
                for (int b = 0; b < LB; b++)
                    if (z[b][i] == 1)
                    {
                        solutioncls = BLUE;
                        break;
                    }
                if (solutioncls == WHITE)
                    for (int r = LB; r < (LB + LR); r++)
                        if (z[r][i] == 1)
                        {
                            solutioncls = RED;
                            break;
                        }

                if (solutioncls == WHITE)
                {
                    int neighB = 0, neighR = 0;
                    for (int j = 0; j < n; j++)
                    {
                        if (j != i && cls[j] == BLUE && hasEdge(i, j))
                            neighB++;
                        if (j != i && cls[j] == RED && hasEdge(i, j))
                            neighR++;
                    }
                    if (neighB > neighR)
                        solutioncls = BLUE;
                    if (neighB < neighR)
                        solutioncls = RED;
                    if (neighB == neighR)
                    {
                        if (contB >= contR)
                            solutioncls = BLUE;
                        else
                            solutioncls = RED;
                    }
                }
                if (solutioncls != realSolutioncls[i])
                    nerror++;
            }
        printf("%.2lf; ", (double)100 * (nVN - nerror) / (double)(nVN));
    }

    for (int k = 0; k < (LB + LR); k++)
    {
        free(a[k]);
        free(z[k]);
    }
    free(a);
    free(z);
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Please, specify the graph file in the DIMACS format.\n");
        return 0;
    }
    FILE *graphFile = fopen(argv[1], "r");
    //// cout << argv[1] << endl;
    if (graphFile == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 0;
    }

    int *cls_aux = (int *)malloc(MAX_N * sizeof(int));
    int *realSolutioncls_aux = (int *)malloc(MAX_N * sizeof(int));

    if (readFile(graphFile, graph, &n, &m, &LB, &LR, cls_aux, realSolutioncls_aux, &realInst))
    {
        fclose(graphFile);
        printf("Could not read graph file %s.", argv[1]);
        return 0;
    }
    fclose(graphFile);

    cls = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        cls[i] = cls_aux[i];
    free(cls_aux);
    realSolutioncls = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        realSolutioncls[i] = realSolutioncls_aux[i];
    free(realSolutioncls_aux);

    D = new bool **[n];
    d = new int *[n];
    mark = new int[n + 1];
    for (int h = 0; h < n; h++)
    {
        D[h] = new bool *[n];
        d[h] = new int[n];
        for (int j = 0; j < n; j++)
        {
            D[h][j] = new bool[n];
            for (int i = 0; i < n; i++)
            {
                D[h][j][i] = new bool;
                D[h][j][i] = false;
            }
        }
    }
    for (int h = 0; h < n; h++)
        BFS_make_Dhj(h);

    contB = 0, contR = 0;
    for (int i = 0; i < n; i++)
        if (cls[i] == 1)
            contB++;
    for (int i = 0; i < n; i++)
        if (cls[i] == 2)
            contR++;
    clock_t start, end;
    double elapsed;
    start = clock();

    grau = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        grau[i] = 0;
        for (int j = 0; j < n; j++)
        {
            if (i != j && hasEdge(i, j))
            {
                grau[i]++;
            }
        }
    }

    grauMmc = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        grauMmc[i] = 0;
        for (int j = 0; j < n; j++)
        {
            if (i != j && hasEdge(i, j))
            {
                grauMmc[i]++;
            }
        }
    }
    // Solving the problem
    Procedure();

    free(grau);
    free(grauMmc);

    // Free memory
    free(cls);
    free(realSolutioncls);
    for (int h = 0; h < n; h++)
    {
        for (int j = 0; j < n; j++)
        {
            delete[] D[h][j];
        }
    }
    for (int h = 0; h < n; h++)
    {
        delete[] D[h];
        delete[] d[h];
    }
    delete[] D;
    delete[] d;
    delete[] mark;

    // Getting run time
    end = clock();
    elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    //printf("Time: %.5g second(s).\n", elapsed);
    printf("%.5g\n", elapsed);

    return 0;
}
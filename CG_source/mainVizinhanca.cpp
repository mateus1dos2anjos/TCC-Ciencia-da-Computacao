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

////////////////////////////////////////////////////////////////////////
//
//      Critério 6

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
    }
    else
    { // critério 6
        if (contVetor[0] >= contVetor[1])
        {

            int *grausGrupoB;
            grausGrupoB = (int *)malloc(contVetor[0] * sizeof(int));
            int j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    grausGrupoB[j] = grau[i]; // grausGrupoB[j] é um vetor com os graus de cada vértice do grp Azul
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
            int iRand = (rand() % (somaGraus)) + 1; // calcular a soma dos graus de cada vertice q ta no grupo (neste caso, o azul)

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
            int iRand = (rand() % (somaGraus)) + 1; // somaGraus = calcular a soma dos graus de cada vertice q ta no grupo (neste caso, o vermelho)
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

////////////////////////////////////////////////////////////////////////
//
//      Critério 5

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
    }
    else
    { // critério 5
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
            int iRand = (rand() % (somaGraus)) + 1; // calcular a soma dos graus de cada vertice q ta no grupo (neste caso, o azul)

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
            int iRand = (rand() % (somaGraus)) + 1; // calcular a soma dos graus de cada vertice q ta no grupo (neste caso, o vermelho)
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

////////////////////////////////////////////////////////////////////////
//
//      Critério 4

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
    }
    else
    { // critério 4
        if (contVetor[0] <= contVetor[1])
        {
            int *grausGrupoB;
            grausGrupoB = (int *)malloc(contVetor[0] * sizeof(int));
            int j = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    grausGrupoB[j] = grau[i]; // grausGrupoB[j] é um vetor com os graus de cada vértice do grp Azul
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
            int iRand = (rand() % (somaGraus)) + 1; // calcular a soma dos graus de cada vertice q ta no grupo (neste caso, o azul)

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
            int iRand = (rand() % (somaGraus)) + 1; // somaGraus = calcular a soma dos graus de cada vertice q ta no grupo (neste caso, o vermelho)
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

////////////////////////////////////////////////////////////////////////
//
//      Critério 3

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
    }
    else
    { // critério 3
        if (contVetor[0] <= contVetor[1])
        {
            // somaGraus = vetor que tem a soma dos graus de um grupo
            int somaGraus = 0;
            for (int i = 0; i < n; i++)
            {
                if (a[0][i] == 1)
                {
                    somaGraus += grau[i];
                }
            }

            srand((unsigned)time(0));
            int iRand = (rand() % (somaGraus)) + 1; // calcular a soma dos graus de cada vertice q ta no grupo (neste caso, o azul)

            int j = 0;
            for (int i = 0; i < n; i++)
            { // Para cada vértice que ta no grupo, vou percorrer x pontos, onde x é o grau do vértice, e verificar se esse ponto é o ponto sorteado
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
            int iRand = (rand() % (somaGraus)) + 1; // calcular a soma dos graus de cada vertice q ta no grupo (neste caso, o azul)
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      Critério 2 :

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
    }
    else
    { // stteando um vértice aleatório dentro do grupo de MAIOR cardinalidade
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

////////////////////////////////////////////////////////////////////////
//
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
    }
    else
    { // stteando um vértice aleatório dentro do grupo de MENOR cardinalidade
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
    //pi[h][h] = -1;
    queue.push_back(h);

    while (!queue.empty())
    {
        k = queue.front();
        //cout << k << " ";
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
                    //Operation: Dhj = Dhj U {k} U Dhk;
                    D[h][j][k] = true;
                    for (int i = 0; i < n; i++)
                        if (D[h][k][i])
                            D[h][j][i] = true;
                }
            }
    }
}

// Função que calcula o fecho convexo de um grupo:
void cal_Conv(int **a, int k, int **z)
{
    z[k] = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        z[k][i] = a[k][i]; // ta colocando todo mundo da matriz a (com seus respectivos grupos )
                           // no fecho convexo do grupo.
    }
    bool finished = false, brk = false;
    while (!finished)
    {
        finished = true;
        for (int i = 0; i < n; i++)
        {
            //verificar se o vertice i nao ta no fecho convexo do grupo k
            if (z[k][i] == 0)
            {
                brk = false;
                for (int h = 0; h < n; h++)
                {
                    if (z[k][h] == 1)
                    { // verifica se um vertice h ta no fecho convexo
                        for (int j = h + 1; j < n; j++)
                            if (z[k][j] == 1 && D[h][j][i])
                            { // verifica se um vertice j ta no fecho convexo
                                // e se i ta no caminho minimo de h ate j

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

int cal_solucaoInicial(int **a, int **z, int *contVetor)
{
    int b = 0;
    int r = LB;
    int totalK = 0;
    // COMEÇO DA ATRIBUIÇÃO INICIAL DOS GRUPOS
    int *ordenado;
    int *usado;
    int restoGruposB = contB % LB;
    int restoGruposR = contR % LR;
    int tamB;
    int tamR;
    usado = (int *)malloc(n * sizeof(int));
    ordenado = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        ordenado[i] = 0;
        usado[i] = 0;
    }

    // Definir os vertices azuis mais proximos de cada
    // vertice azul (armazenar essa informacao em um vetor)
    for (int i = 0; i < n; i++)
    {
        if (usado[i] == 0)
        {
            usado[i] = 1;
            for (int j = 0; j < n; j++)
            {
                ordenado[j] = j;
            }
            for (int j = 0; j < (n - 1); j++)
            {
                if (d[i][ordenado[j]] > d[i][ordenado[j + 1]])
                {
                    int aux = ordenado[j];
                    ordenado[j] = ordenado[j + 1];
                    ordenado[j + 1] = aux;
                }
            }
            if (cls[i] == BLUE)
            {
                a[b][i] = 1;
                contVetor[b]++;
                if (restoGruposB == 0)
                {
                    tamB = (contB / LB) - 1;
                }
                else
                {
                    restoGruposB--;
                    tamB = contB / LB;
                }
                for (int j = 0; j < n; j++)
                {
                    if (cls[ordenado[j]] == BLUE)
                    {
                        if (usado[ordenado[j]] == 0)
                        {
                            a[b][ordenado[j]] = 1;
                            tamB--;
                            usado[ordenado[j]] = 1;
                            contVetor[b]++;
                        }
                        if (tamB == 0)
                        {
                            b++;
                            break;
                        }
                    }
                }
            }
            if (cls[i] == RED)
            {
                a[r][i] = 1;
                contVetor[r]++;
                if (restoGruposR == 0)
                {
                    tamR = (contR / LR) - 1;
                }
                else
                {
                    restoGruposR--;
                    tamR = contR / LR;
                }
                for (int j = 0; j < n; j++)
                {
                    if (cls[ordenado[j]] == RED)
                    {
                        if (usado[ordenado[j]] == 0)
                        {
                            a[r][ordenado[j]] = 1;
                            tamR--;
                            usado[ordenado[j]] = 1;
                            contVetor[r]++;
                        }
                        if (tamR == 0)
                        {
                            r++;
                            break;
                        }
                    }
                }
            }
        }
    }
    free(ordenado);
    free(usado);

    // FIM DA ATRIBUIÇÃO INICIAL DOS GRUPOS

    cal_Conv_Grups(a, z);

    for (int i = 0; i < n; i++)
    {
        if (cls[i] == RED)
        {
            int r;
            for (r = LB; r < (LB + LR); r++)
            {
                if (a[r][i] == 1)
                {
                    break;
                }
            }
            if (r >= (LB + LR))
                continue;
            for (int b = 0; b < LB; b++)
            {
                if (z[b][i] == 1)
                {
                    a[r][i] = 0; // settando vértice RED como outlier
                    contVetor[r]--;
                    cal_Conv(a, r, z);
                    break;
                }
            }
        }

        if (cls[i] == BLUE)
        {
            int b;
            for (b = 0; b < LB; b++)
            {
                if (a[b][i] == 1)
                {
                    break;
                }
            }
            if (b >= LB)
                continue;
            for (int r = LB; r < (LB + LR); r++)
            {
                if (z[r][i] == 1)
                {
                    a[b][i] = 0; // settando vértice BLUE como outlier
                    contVetor[b]--;
                    cal_Conv(a, b, z);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (cls[i] == WHITE)
        {
            bool bMenor = false;
            int rinicial = LB;
            for (int b = 0; b < (LB); b++)
            {
                for (int r = rinicial; r < (LB + LR); r++)
                {
                    if (z[b][i] == z[r][i] && z[r][i] == 1)
                    {
                        if (contVetor[b] > contVetor[r])
                        {
                            for (int j = 0; j < n; j++)
                            {
                                if (cls[j] == RED && a[r][j] == 1)
                                {
                                    a[r][j] = 0; // settando vértice RED como outlier
                                    contVetor[r]--;
                                    cal_Conv(a, r, z);
                                    r--;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            bMenor = true;
                            for (int j = 0; j < n; j++)
                            {
                                if (cls[j] == BLUE && a[b][j] == 1)
                                {
                                    a[b][j] = 0; // settando vértice BLUE como outlier
                                    contVetor[b]--;
                                    cal_Conv(a, b, z);
                                    b--;
                                    rinicial = r;
                                    break;
                                }
                            }
                        }
                    }
                    if (bMenor)
                        break;
                }
                if (!bMenor)
                    rinicial = LB;
                bMenor = false;
            }
        }
    }

    for (int k = 0; k < (LB + LR); k++)
    {
        totalK = contVetor[k] + totalK;
    }

    if (((contB + contR) - totalK) <= contB && ((contB + contR) - totalK) <= contR)
    {
        return (contB + contR) - totalK;
    } //koroz
    else
    {
        b = 0;
        r = LB;
        for (int k = 0; k < (LB + LR); k++)
        {
            memset(a[k], 0, n * sizeof(int));
            contVetor[k] = 0;
        }
        if (contB > contR)
        {
            for (int i = 0; i < n; i++)
            { //
                if (cls[i] == BLUE)
                {
                    a[b][i] = 1;
                    contVetor[b]++;
                    b++;
                    if (b == LB)
                    {
                        b = 0;
                    }
                }
            }
            return contR;
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                if (cls[i] == RED)
                {
                    a[r][i] = 1;
                    contVetor[r]++;
                    r++;
                    if (r == (LB + LR))
                    {
                        r = LB;
                    }
                }
            }
            return contB;
        }
    }
}

// Calcula o numero de outliers da solução a
int objetivo(int **a, int *contVetor)
{
    int totalK = 0;
    for (int k = 0; k < (LB + LR); k++)
    {                                   //LB: qtd de grupos azuis (1, no nosso caso)
        totalK = contVetor[k] + totalK; //contVetor[k] : quantidade de vertices do grupo k
    }
    return (contB + contR) - totalK; // (contB + contR) : Total de vértices inicialmete
                                     //                   classificados.
}

// Funçao que verifica se alguma restrição é quebrada (1, 2 ou 3).
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
        { // verifica se i é um vertice inicialmente RED
            int r;
            for (r = LB; r < (LB + LR); r++)
            { // percorrendo tds os grps vermelhos(no nosso caso so um)
                if (a[r][i] == 1)
                { // verifica se i ta em um grupo vermelho, se for 0, não ta
                    break;
                }
            }
            //if(r>=(LB+LR)) break;
            if (r == (LB + LR))
                continue;

            for (int b = 0; b < LB; b++)
            { //percorrendo classe azul
                //  if(z[b][i] == a[r][i] && a[r][i]== 1){
                if (z[b][i] == 1)
                { //verifica se o vertice i ta no fecho convexo de
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
        // de classes opostas.
        if (cls[i] == WHITE)
        {
            for (int b = 0; b < (LB); b++)
            { // percorrendo grupos azuis
                for (int r = LB; r < (LB + LR); r++)
                { // percorrendo grupos vermelhos
                    if (z[b][i] == 1 && z[r][i] == 1)
                    { // verificando se o vertice ta nos dois grupos
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

        // Definir algum vertice do grupo, no qual a restrição foi quebrada, como outlier
        k = setOutlier6(vViolado, b, r, a, contVetor); //retorno da funcao é o grupo em q o vertice foi settado outlier, ou seja, foi retirado (k)
        if (k != -1)
        {
            contVetor[k]--;
            cal_Conv(a, k, z); // Recalcula o fecho convexo do grupo q ele foi retirado
        }
        vViolado = viavel(a, z, &b, &r); // Calculca se a solucao é viavel
    }
}

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
    //LB: Qtd de grupos blue
    //LR: Qtd de grupos red
    for (int o = 0; o < (LB + LR); o++)
    {
        contVetor[o] = 0;
    }

    int solutioncls = WHITE;
    for (int i = 0; i < n; i++)
    {
        if (cls[i] == WHITE)
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
    }

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
    printf("%.5g\n", elapsed);

    return 0;
}

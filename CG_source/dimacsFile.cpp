#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"dimacsFile.h"
#include <iostream>
#include <vector>
#include <list>

#define WHITE 0
#define BLUE  1
#define RED  2

using namespace std;

/* // EXAMPLE: Calculating the convex hull of all blue vertices and all red vertices

    int *cls_aux=(int*) malloc(nT*sizeof(int));
    int **z=(int**) malloc(2*sizeof(int *));
    for(int color=BLUE;color<=RED;color++) {
        z[color-1]=(int*) malloc(nT*sizeof(int));
        memset(z[color-1],0,nT*sizeof(int));
    }

    for(int color=BLUE;color<=RED;color++) {
        for(int i=0;i<nT;i++)
            if(cls[i]==color) z[color-1][i]=1;

        bool finished=false, brk=false;
        while(!finished) {
            finished=true;
            for(int i=0;i<nT;i++)
                if(z[color-1][i]==0) {
                    brk=false;
                    for(int h=0;h<nT;h++) {
                        if(z[color-1][h]==1)
                            for(int j=h+1;j<nT;j++)
                                if(z[color-1][j]==1 && D[h][j][i]) {
                                    finished=false;
                                    brk=true;
                                    z[color-1][i]=1;
                                    break;
                                }
                        if(brk) break;
                    }
                }
        }
    }
*/

int readFile(FILE * graphFile, const graphType t, int *n, long long *m, 
int *L1, int *L2, int *cls, int *realSolutioncls, bool *realInst) {
    char               type  = ' ';
    char               linestr[100], linestrHUGE[10000];
    char *             datastr;
    int                r,diam = 0,dgmin = 0,dgmax = 0;
    long               i, j;
    bool               namePrinted = false;

    *n = 0;
    *m = 0;
    *L1 = 0;
    *L2 = 0;
    memset(cls,0,MAX_N*sizeof(int));
    memset(realSolutioncls,0,MAX_N*sizeof(int));

    //printf("Reading graph...\n");
    *realInst = false;
    while (type != 'p') {
        type = fgetc(graphFile);
        if (type != EOF) {

            /* header */
            if (type == 'c') {
                datastr = fgets(linestr, 100, graphFile);
                if (datastr != NULL) {
                    if(!namePrinted) {
                        //printf("%s", linestr);
                        datastr = strtok(linestr,":");
                        datastr = strtok(NULL," ");
                        printf("%.*s; ", (int) (strlen(datastr)-5), datastr);
                        namePrinted = true;                    }
                } else return -1;
            }

            /* CPP Parameters: Max number of groups for each class */
            if (type == 'l') {
                datastr = fgets(linestr, 100, graphFile);
                if (datastr == NULL) return -1;

                datastr = strtok(linestr," ");
                *L1 = atoi(datastr);

                datastr = strtok(NULL," ");
                *L2 = atoi(datastr);
            }

	    /* CPP Parameters: Real blue vertices */
            if (type == 'q') {
		*realInst = true;
                datastr = fgets(linestrHUGE, 10000, graphFile);
                if (datastr == NULL) return -1;

                datastr = strtok(linestrHUGE," ");
                realSolutioncls[atoi(datastr) - 1] = 1;

                datastr = strtok(NULL," ");
                while(datastr != NULL) {
                    realSolutioncls[atoi(datastr) - 1] = 1;
                    datastr = strtok(NULL," ");
                }
            }

            /* CPP Parameters: Real red vertices */
            if (type == 'w') {
                datastr = fgets(linestrHUGE, 10000, graphFile);
                if (datastr == NULL) return -1;

                datastr = strtok(linestrHUGE," ");
                realSolutioncls[atoi(datastr) - 1] = 2;

                datastr = strtok(NULL," ");
                while(datastr != NULL) {
                    realSolutioncls[atoi(datastr) - 1] = 2;
                    datastr = strtok(NULL," ");
                }
            }

            /* CPP Parameters: Blue vertices */
            if (type == 'b') {
                datastr = fgets(linestrHUGE, 10000, graphFile);
                if (datastr == NULL) return -1;

                datastr = strtok(linestrHUGE," ");
                cls[atoi(datastr) - 1] = 1;

                datastr = strtok(NULL," ");
                while(datastr != NULL) {
                    cls[atoi(datastr) - 1] = 1;
                    datastr = strtok(NULL," ");
                }
            }

            /* CPP Parameters: Red vertices */
            if (type == 'r') {
                datastr = fgets(linestrHUGE, 10000, graphFile);
                if (datastr == NULL) return -1;

                datastr = strtok(linestrHUGE," ");
                cls[atoi(datastr) - 1] = 2;

                datastr = strtok(NULL," ");
                while(datastr != NULL) {
                    cls[atoi(datastr) - 1] = 2;
                    datastr = strtok(NULL," ");
                }
            }

	    /* Diameter and degrees */
            if (type == 'd') {
                datastr = fgets(linestr, 100, graphFile);
                if (datastr == NULL)
                    return -1;

                datastr = strtok(linestr," ");
		datastr = strtok(NULL," ");

                datastr = strtok(NULL," ");
                diam = atoi(datastr);

                datastr = strtok(NULL," ");
                dgmin = atoll(datastr);

		datastr = strtok(NULL," ");
                dgmax = atoll(datastr);
            }
	
            /* Vertices */
            if (type == 'p') {
                datastr = fgets(linestr, 100, graphFile);
                if (datastr == NULL)
                    return -1;

                datastr = strtok(linestr," ");

                datastr = strtok(NULL," ");
                *n = atoi(datastr);

                datastr = strtok(NULL," ");
                *m = atoll(datastr);
                //if (t == complement)
                //*m = (((*n)*(*n) - *n) >> 1) - *m;
            }
        }
    }

    //printf("Graph with %d vertices and %d edges.\n", *n, *m);

    if (t == graph) setAllEdges(0);

    type = fgetc(graphFile);
    while (type != EOF) {
        /* Edges */
        if (type == 'e') {
            datastr = fgets(linestr, 100, graphFile);
            if (datastr == NULL)
                return -1;

            datastr = strtok(linestr," ");
            i = atol(datastr) - 1;

            datastr = strtok(NULL," ");
            j = atol(datastr) - 1;

            //printf("edge (%ld,%ld)\n",i,j);
            addEdge(i, j);
            addEdge(j, i);
        }
        else {
            datastr = fgets(linestr, 100, graphFile);
            if (datastr == NULL) return -1;
        }
        type = fgetc(graphFile);
    }

    double d = 200*( (*m)/ (double) (((*n)*((*n)-1))));
    //printf("n= %d m= %lld d= %.0lf diam= %d dgmin= %d dgmax= %d\n",*n,*m,d,diam,dgmin,dgmax);
    return 0;
}

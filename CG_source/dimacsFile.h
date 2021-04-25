#ifndef DIMACESFILE_H_
#define DIMACESFILE_H_

#include"graphMacros.h"
#include"bitMapGraph.h"
#include<stdio.h>

#define MAX_N 10000

typedef enum GT { graph, complement } graphType;

int readFile(FILE * graphFile, const graphType t, int *n, long long *m, int *L1, int *L2, int *cls, int *realSolutioncls, bool *realInst);

#endif /*DIMACESFILE_H_*/

#ifndef GRAPHSIZES_H_
#define GRAPHSIZES_H_

// VERY IMPORTANT: VERTICES MUST BE INDEXED WITH long INTEGERS

/**
 * Maximum number of vertices of a graph
 */
#define MAX_SIZE 1024
#define LOG_MAX_SIZE 10
#define SQRT_MAX_SIZE 33
/**
 * Size of the vector storing the graph
 */
#define BYTE_SIZE ((1+(MAX_SIZE >> LOG_BYTEBITS)) << LOG_MAX_SIZE)
/**
 * Number of bits in a byte
 */
#define BYTEBITS 8
#define LOG_BYTEBITS 3

extern unsigned char bitmapG[];
extern unsigned char addMask[];
extern unsigned char removeMask[];

#define addEdge(i, j) (bitmapG[((i) << (LOG_MAX_SIZE-LOG_BYTEBITS))+((j) >> LOG_BYTEBITS)] |= addMask[(j)%BYTEBITS])
#define removeEdge(i, j) (bitmapG[((i) << (LOG_MAX_SIZE-LOG_BYTEBITS))+((j) >> LOG_BYTEBITS)] &= removeMask[(j)%BYTEBITS])
#define hasEdge(i, j) (bitmapG[((i) << (LOG_MAX_SIZE-LOG_BYTEBITS))+((j) >> LOG_BYTEBITS)] & addMask[(j)%BYTEBITS])
#define setAllEdges(i) (memset(bitmapG, i, BYTE_SIZE))

#endif /*GRAPHSIZES_H_*/

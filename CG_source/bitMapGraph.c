
#include"bitMapGraph.h"

unsigned char bitmapG[BYTE_SIZE];
unsigned char addMask[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
unsigned char removeMask[] = { 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F };




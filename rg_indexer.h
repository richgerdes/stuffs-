/* Author: Rich Gerdes
 * Date: 10/20/2014
 * CS214
 *
 * File: RGIndexer.h
 *
 */

#ifndef RG_Indexer
#define RG_Indexer
#include <stdlib.h>
#include <string.h>
#include "RG_SDLL.h"

typedef struct _RGIndexerFile RGIndexerFile;
typedef struct _RGIndexerWord RGIndexerWord;
typedef struct _RGIndexer RGIndexer;

struct _RGIndexerFile{
char* filename;
int hitcount;
};

struct _RGIndexerWord{
char* word;
RGSDLL* files;
};

struct _RGIndexer{
RGSDLL* words;
};

int RGIndexerFileCompare(void*, void*);
void RGIndexerFileDestroy(void*);

int RGIndexerWordCompare(void*, void*);
void RGIndexerWordDestroy(void*);

RGIndexerFile* RGcreateRGIndexerFile(char*, int);
RGIndexerWord* RGcreateRGIndexerWord(char*);
RGIndexer* RGcreateRGIndexer();

void RGdestroyRGIndexer(RGIndexer*);

void RGIndexerAdd(RGIndexer*, char*, char*);

#endif
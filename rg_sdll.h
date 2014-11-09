/* Author: Rich Gerdes
 * Date: 10/20/2014
 * CS214
 *
 * File: RGSDLL.h
 *
 */

/*
 * Data type blind Sorted Doubly Linked List
 */
 
#ifndef RG_SDLL
#define RG_SDLL

#include <stdlib.h>
#include <stdio.h>

typedef struct _RGSDLLNode RGSDLLNode;
typedef struct _RGSDLLIter RGSDLLIter;
typedef struct _RGSDLLIternode RGSDLLIterNode;
typedef struct _RGSDLL RGSDLL;

typedef int (*CompareFuncT)( void *, void * );
typedef void (*DestructFuncT)( void * );

struct _RGSDLLNode{
	RGSDLLNode* prev;
	RGSDLLNode* next;
	void* data;
};

struct _RGSDLLIter{
	void* data;
	RGSDLLNode* next;
	RGSDLL* list;
};

struct _RGSDLLIternode{
	RGSDLLIter* iter;
	RGSDLLIterNode* next;
};

struct _RGSDLL{
	CompareFuncT cft;
	DestructFuncT dft;
	RGSDLLNode* head;
	RGSDLLIterNode* ihead;
};

RGSDLLNode* RGcreateRGSDLLNode(void*,RGSDLLNode*,RGSDLLNode*);
RGSDLLIter* RGcreateRGSDLLIter(RGSDLL*);
RGSDLLIterNode* RGcreateRGSDLLIterNode(RGSDLLIter*,RGSDLLIterNode*);
RGSDLL* RGcreateRGSDLL(CompareFuncT cf, DestructFuncT df);

void RGdestroyRGSDLLNode(RGSDLLNode*);
void RGdestroyRGSDLLIter(RGSDLLIter*);
void RGdestroyRGSDLLIterNode(RGSDLLIterNode*);
void RGdestroyRGSDLL(RGSDLL*);

void RGSDLLadd(void*, RGSDLL*);
void RGSDLLSort(RGSDLL*);
void* RGSDLLremove(void*, RGSDLL*);

RGSDLLIter* RGSDLLgetIter(RGSDLL*);
void* RGSDLLIterGetCurrent(RGSDLLIter*);
void* RGSDLLIterGetNext(RGSDLLIter*);

#endif
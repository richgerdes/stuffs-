/* Author: Rich Gerdes
 * Date: 10/20/2014
 * CS214
 *
 * File: RGLinkedList.h
 *
 */

/*
 * Data Type Blind Singly Linked List
 */
 
#ifndef RG_LinkedList
#define RG_LinkedList
#include <stdlib.h>

typedef struct _RGlinkedistNode RGLinkedListNode;
typedef struct _RGlinkedistIter RGLinkedListIter;
typedef struct _RGlinkedistIterNode RGLinkedListIterNode;
typedef struct _RGlinkedist RGLinkedList;

struct _RGlinkedistNode{
void *data;
int ref;
RGLinkedListNode* next;
};

struct _RGlinkedistIterNode{
RGLinkedListIter *iter;
RGLinkedListIterNode* next;
};

struct _RGlinkedistIter{
void *data;
RGLinkedList* list;
RGLinkedListNode* next;
};

struct _RGlinkedist{
RGLinkedListNode* head;
RGLinkedListIterNode* ihead;
};

RGLinkedListNode* RGcreateLLNode(void*,RGLinkedListNode*);
RGLinkedListIterNode* RGcreateLLIterNode(RGLinkedListIter*,RGLinkedListIterNode*);
RGLinkedListIter* RGcreateLLIter(RGLinkedList*);
RGLinkedList* RGcreateLL();

void RGdestroyLLNode(RGLinkedListNode*);
void RGdestroyLLIterNode(RGLinkedListIterNode*);
void RGdestroyLLIter(RGLinkedListIter*);
void RGdestroyLL(RGLinkedList*);

void RGLLadd(RGLinkedList*, void*);
void* RGLLremove(RGLinkedList*, void*);
RGLinkedListIter* RGLLgetIter(RGLinkedList *);
void* RGLLIterGetNext(RGLinkedListIter*);
void* RGLLIterGetCurrent(RGLinkedListIter*);

#endif
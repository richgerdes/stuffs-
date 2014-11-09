/* Author: Rich Gerdes
 * Date: 10/20/2014
 * CS214
 *
 * File: RGLinkedList.c
 *
 */
 
/*
 * Data Type Blind Singly Linked List
 */

#include "RG_LinkedList.h"

/*
 * create list node
 */
RGLinkedListNode* RGcreateLLNode(void* data,RGLinkedListNode* next){
	RGLinkedListNode* newNode = (RGLinkedListNode*) malloc(sizeof(RGLinkedListNode));
	
	if(newNode == NULL)
		return NULL;
	
	newNode->next = next;
	newNode->data = data;
	newNode->ref = 0;
	return newNode;
}

/*
 * create reference to iter for list to save
 */
RGLinkedListIterNode* RGcreateLLIterNode(RGLinkedListIter* iter, RGLinkedListIterNode* next){
	RGLinkedListIterNode* inode = (RGLinkedListIterNode*) malloc(sizeof(RGLinkedListIterNode));
	if(inode == NULL)
		return NULL;
		
	inode->iter = iter;
	inode->next = next;

	return inode;
}

/*
 * create iterator
 */
RGLinkedListIter* RGcreateLLIter(RGLinkedList* list){
	if(list == NULL)
		return NULL;
	if(list->head == NULL)
		return NULL;
	RGLinkedListIter* iter = (RGLinkedListIter*) malloc(sizeof(RGLinkedListIter));
	if(iter == NULL)
		return NULL;
	iter->list = list;
	iter->data = list->head->data;
	iter->next = list->head->next;
	if(iter->next != NULL)
		iter->next->ref++;
	return iter;
}

/*
 * create empty list
 */
RGLinkedList* RGcreateLL(){

	RGLinkedList* list = (RGLinkedList*) malloc(sizeof(RGLinkedList));
	if(list == NULL)
		return NULL;
		
	list->head = NULL;
	list->ihead = NULL;
	
	return list;
}

/*
 * free list node
 */
void RGdestroyLLNode(RGLinkedListNode* node){
	if(node == NULL)
		return;
		
	free(node);
}

/*
 * free list iterator reference
 */
void RGdestroyLLIterNode(RGLinkedListIterNode* node){
	if(node == NULL)
		return;
		
	free(node);
}

/*
 * free iterator 
 */
void RGdestroyLLIter(RGLinkedListIter* iter){
	if(iter == NULL)
		return;
	if(iter->next != NULL){
		iter->next->ref--;
		if(iter->next->ref <=0)
			RGdestroyLLNode(iter->next);
	}
	RGLinkedListIterNode* icurr = iter->list->ihead;
	if(icurr == NULL){
	
	}else if(icurr->iter == iter){
		RGLinkedListIterNode* tmp = icurr;
		iter->list->ihead = iter->list->ihead->next;
		RGdestroyLLIterNode(tmp);
	}else{
		while(icurr->next != NULL){
			if(icurr->next->iter == iter){
				RGLinkedListIterNode* tmp = icurr->next;
				icurr->next = icurr->next->next;
				RGdestroyLLIterNode(tmp);
			}
		}
	}
	iter->next = NULL;
	free(iter);
}

/*
 * free list
 */
void RGdestroyLL(RGLinkedList* list){
	if(list == NULL)
		return;
	
	while(list->head != NULL){
		free(list->head->data);
		RGLinkedListNode* tmp = list->head;
		list->head = list->head->next;
		tmp->next = NULL;
		free(tmp->data);
		tmp->data = NULL;
		free(tmp);
	}
	
	while(list->ihead != NULL){
		free(list->ihead->iter);
		RGLinkedListIterNode* tmp = list->ihead;
		list->ihead = list->ihead->next;
		tmp->next = NULL;
		RGdestroyLLIter(tmp->iter);
		tmp->iter = NULL;
		free(tmp);
	}
	
	free(list);
	
}

/*
 * add new item to list
 */
void RGLLadd(RGLinkedList* list, void* data){
	if(list == NULL)
		return;
	if(data == NULL)
		return;
	RGLinkedListNode* node = RGcreateLLNode(data, NULL);
	if(node == NULL)
		return;
	node->next = list->head;
	list->head = node;
	list->head->ref++;
}

/*
 * remove item from list
 */
void* RGLLremove(RGLinkedList* list, void* data){
	RGLinkedListNode* curr = list->head;

	if(curr == NULL)
		return NULL;
	if(curr->data == data){
		list->head = curr->next;
		void* oldData = curr->data;
		curr->data = NULL;
		RGdestroyLLNode(curr);
		return oldData;
	}

	while(curr->next != NULL){
		if(curr->next->data == data){
			RGLinkedListIterNode* icurr = list->ihead;
			while(icurr != NULL){
				if(icurr->iter == NULL)
					continue;
				if(icurr->iter->next == curr->next){
					icurr->iter->next->ref--;
					icurr->iter->next = icurr->iter->next->next;
				}
			}
			RGLinkedListNode* old = curr->next;
			void* oldData = old->data;
			curr->next = curr->next->next;
			old->next = NULL;
			old->data = NULL;
			old->ref--;
			if(old->ref <= 0)
				RGdestroyLLNode(old);
			return oldData;
		}
		curr = curr->next;
	}
	return NULL;
}

/*
 * Get Iterator for list
 */
RGLinkedListIter* RGLLgetIter(RGLinkedList * list){
	if(list == NULL)
		return NULL;
	RGLinkedListIter* iter = RGcreateLLIter(list);
	RGLinkedListIterNode* inode = RGcreateLLIterNode(iter, list->ihead);
	list->ihead = inode;
	if(iter == NULL)
		return NULL;
	return iter;
}

/*
 * get next value in list (increment iter)
 */
void* RGLLIterGetNext(RGLinkedListIter* iter){
	if(iter == NULL)
		return NULL;
	if(iter->next == NULL){
		if(iter->list == NULL)
			return NULL;
		RGLinkedListIterNode* icurr = iter->list->ihead;
		if(icurr == NULL)
			return NULL;
		if(icurr->iter == iter){
			iter->list->ihead = icurr->next;
			icurr->next = NULL;
			RGdestroyLLIterNode(icurr);
			return NULL;
		}
		while(icurr->next != NULL){
			if(icurr->next->iter == iter){
				RGLinkedListIterNode* tmp = icurr->next;
				icurr->next = tmp->next;
				tmp->next = NULL;
				tmp->iter = NULL;
				RGdestroyLLIterNode(tmp);
				iter->data = NULL;
			}
		}
		return NULL;
	}
	RGLinkedListNode* tmp;
	tmp = iter->next;
	iter->data = iter->next->data;
	iter->next = iter->next->next;
	if(iter->next != NULL)
		iter->next->ref++;
	tmp->ref--;
	if(tmp->ref <=0)
		RGdestroyLLNode(tmp);
	return iter->data;
}

/*
 * get current value of an iterator
 */
void* RGLLIterGetCurrent(RGLinkedListIter* iter){
	if(iter != NULL)
		return iter->data;
	return NULL;
}
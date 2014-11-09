/* Author: Rich Gerdes
 * Date: 10/20/2014
 * CS214
 *
 * File: RGLinkedList.h
 *
 */
 
/*
 * Data type blind Sorted Doubly Linked List
 */
 
#include "RG_SDLL.h"

/*
 * create list node 
 */
RGSDLLNode* RGcreateRGSDLLNode(void* data, RGSDLLNode* prev, RGSDLLNode*next){
	RGSDLLNode* node = (RGSDLLNode*) malloc(sizeof(RGSDLLNode));
	if(node == NULL)
		return NULL;
	
	node->prev = prev;
	node->next = next;
	node->data = data;
	
	return node;
}

/*
 * create iter
 */
RGSDLLIter* RGcreateRGSDLLIter(RGSDLL* list){
	if(list == NULL || list->head == NULL)
		return NULL;
	RGSDLLIter* iter = (RGSDLLIter*) malloc(sizeof(RGSDLLIter));
	if(iter == NULL)
		return NULL;
	
	iter->list = list;
	iter->data = list->head->data;
	iter->next = list->head->next;
	
	return iter;
}

/*
 * create iter storage ref
 */
RGSDLLIterNode* RGcreateRGSDLLIterNode(RGSDLLIter* iter,RGSDLLIterNode* next){
	RGSDLLIterNode* node = (RGSDLLIterNode*) malloc(sizeof(RGSDLLIterNode));
	if(node == NULL)
		return NULL;
		
	node->iter = iter;
	node->next = next;
	
	return node;

}

/*
 * create new list
 */
RGSDLL* RGcreateRGSDLL(CompareFuncT cf, DestructFuncT df){
	RGSDLL* list = (RGSDLL*) malloc(sizeof(RGSDLL));
	if(list == NULL)
		return NULL;
	
	list->cft = cf;
	list->dft = df;
	list->head = NULL;
	list->ihead = NULL;
	
	return list;
}

/*
 * free node
 */
void RGdestroyRGSDLLNode(RGSDLLNode* node){
	if(node == NULL)
		return;
	node->next = NULL;
	node->prev = NULL;
	free(node);
}

/*
 * free iter
 */
void RGdestroyRGSDLLIter(RGSDLLIter* iter){
	if(iter == NULL)
		return;
	
	if(iter->list != NULL){
		RGSDLLIterNode* icurr = iter->list->ihead;
		if(icurr != NULL){
			if(icurr->iter == iter){
				iter->list->ihead = iter->list->ihead->next;
				icurr->iter = NULL;
				RGdestroyRGSDLLIterNode(icurr);
				icurr = iter->list->ihead;
			}
			while(icurr != NULL){
				if(icurr->next == NULL)
					break;
				if(icurr->next->iter == iter){
					RGSDLLIterNode* tmp = icurr->next;
					icurr->next = tmp->next;
					tmp->iter=NULL;
					RGdestroyRGSDLLIterNode(tmp);
				}
			}
		}	
	}
		
	iter->list = NULL;
	iter->next = NULL;
	iter->data = NULL;
	free(iter);
}

/*
 * free iter ref
 */
void RGdestroyRGSDLLIterNode(RGSDLLIterNode* node){
	if(node == NULL)
		return;
	
	node->iter = NULL;
	node->next = NULL;
	free(node);
}

/*
 * free list
 */
void RGdestroyRGSDLL(RGSDLL* list){
	if(list == NULL)
		return;
		
	if(list->head != NULL){
		
		RGSDLLNode* curr = list->head;
		while(curr->next!=NULL){
			RGSDLLIterNode* icurr = list->ihead;
			while(icurr != NULL){
				if(icurr->iter->next == curr){
					icurr->iter->next = icurr->iter->next->next;
				}
			}
			curr = curr->next;
			list->dft(curr->prev->data);
			curr->prev->data = NULL;
			RGdestroyRGSDLLNode(curr->prev);
			curr->prev = NULL;
		}
		list->dft(curr->data);
		curr->data = NULL;
		RGdestroyRGSDLLNode(curr);
		
		list->head = NULL;
	}
	if(list->ihead != NULL){
		RGSDLLIterNode* icurr = list->ihead;
		while(icurr->next != NULL){
			RGSDLLIterNode* tmp = icurr->next;
			icurr->next = icurr->next->next;
			if(tmp->iter != NULL)
				tmp->iter->list = NULL;
			tmp->next = NULL;
			RGdestroyRGSDLLIterNode(tmp);
		}
		if(icurr!=NULL){
			if(icurr->iter != NULL)
				icurr->iter->list = NULL;
			icurr->next = NULL;
			RGdestroyRGSDLLIterNode(icurr);
		}
		list->ihead = NULL;
	}
	list->cft = NULL;
	list->dft = NULL;
	free(list);
}

/*
 * add new node to list
 */
void RGSDLLadd(void* newData, RGSDLL* list){
	RGSDLLNode* newNode = RGcreateRGSDLLNode(newData,NULL, NULL);
	if(list->head == NULL){
		list->head = newNode;
		return;
	}
	if(list->cft(list->head->data,newNode->data) > 0){
		newNode->next = list->head;
		list->head->prev = newNode;
		list->head = newNode;
		return;
	}
	if(list->head->next == NULL){
		list->head->next = newNode;
		newNode->prev = list->head;
		return;
	}
	RGSDLLNode* curr = list->head->next;
	while(curr != NULL){
		if(list->cft(curr->data,newNode->data) > 0){
			curr->prev->next = newNode;
			newNode->prev = curr->prev;
			curr->prev = newNode;
			newNode->next = curr;
			return;
		}else if(curr->next == NULL){
			curr->next = newNode;
			newNode->prev = curr;
			return;
		}else{
			curr = curr->next;
		}
	}
	return;
}

/*
 * sort items in list
 */
void RGSDLLSort(RGSDLL* list){
	RGSDLLNode* curr = list->head;
	
	while(curr!=NULL){
		if(curr->next == NULL)
			break;
		if(list->cft(curr->data, curr->next->data) > 0){
			RGSDLLNode* tmp = curr;
			if(curr == list->head){
				list->head = curr->next;
				curr = list->head;
			}else{
				curr = curr->prev;
			}
			if(tmp->prev != NULL)
				tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			if(tmp->next->next != NULL)
				tmp->next->next->prev = tmp;
			tmp->prev = tmp->next;
			tmp->next = tmp->next->next;
			tmp->prev->next = tmp;
		}else{
			curr = curr->next;
		}
	
	}
}

/*
 * remove item
 */
void* RGSDLLremove(void* data, RGSDLL* list){
	if(data == NULL || list == NULL || list->head == NULL)
		return NULL;
	if(list->cft(data,list->head->data) == 0){
		RGSDLLNode* tmp = list->head;
		list->head = tmp->next;
		tmp->next = NULL;
		if(list->head != NULL)
			list->head->prev = NULL;
		
		RGSDLLIterNode* icurr = list->ihead;
		while(icurr != NULL){
			if(icurr->iter->next == tmp){
				icurr->iter->next = icurr->iter->next->next;
			}
			icurr = icurr->next;
		}
		
		void* oldData = tmp->data;
		tmp->next = NULL;
		tmp->data = NULL;
		RGdestroyRGSDLLNode(tmp);
		
		return oldData;
	}else{
	
		RGSDLLNode* curr = list->head;
		if(curr == NULL)
			return NULL;
		while(curr->next != NULL){
			if(list->cft(curr->next->data, data) == 0){
				RGSDLLNode* tmp = curr->next;
				curr->next = tmp->next;
				if(curr->next != NULL)
					curr->next->prev = curr;
				
				RGSDLLIterNode* icurr = list->ihead;
				while(icurr != NULL){
					if(icurr->iter->next == tmp){
						icurr->iter->next = icurr->iter->next->next;
					}
					icurr = icurr->next;
				}
				void* oldData = tmp->data;
				tmp->next = NULL;
				tmp->data = NULL;
				RGdestroyRGSDLLNode(tmp);
				
				return oldData;
			}
			curr = curr->next;
		}
		
		return NULL;
	}

}

/*
 * Get new iter for a given list
 */
RGSDLLIter* RGSDLLgetIter(RGSDLL* list){
	if(list == NULL)
		return NULL;
	RGSDLLIter* iter = RGcreateRGSDLLIter(list);
	if(iter == NULL)
		return NULL;
	RGSDLLIterNode* node = RGcreateRGSDLLIterNode(iter, list->ihead);
	if(node != NULL)
		list->ihead = node;
	return iter;
}

/*
 * get current data value for an iter
 */
void* RGSDLLIterGetCurrent(RGSDLLIter* iter){
	if(iter == NULL)
		return NULL;
	return iter->data;
}

/*
 * move iterator and get value
 */
void* RGSDLLIterGetNext(RGSDLLIter* iter){
	if(iter == NULL)
		return NULL;
	if(iter->next == NULL){
		iter->data = NULL;
		RGSDLLIterNode* node = iter->list->ihead;
		if(node != NULL){
			if(node->iter == iter){
				iter->list->ihead = node->next;
				node->next = NULL;
				node->iter = NULL;
				RGdestroyRGSDLLIterNode(node);			
			}else{
				while(node->next != NULL){
					if(node->next->iter == iter){
						RGSDLLIterNode* tmp = node->next;
						node->next = tmp->next;
						tmp->iter = NULL;
						tmp->next = NULL;
						RGdestroyRGSDLLIterNode(tmp);
						break;
					}
				}
			}
		}		
		return NULL;
	}
	iter->data = iter->next->data;
	iter->next = iter->next->next;
	return iter->data;
}
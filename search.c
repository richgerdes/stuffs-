#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "fileops.h"
#include "indexer.h"

Node* clone(Node* head){
	Node new = (Node*) malloc(sizeof(Node));
	new->fileName = (char*) malloc((strlen(head->fileName) + 1) * sizeof(char));
	memset(new->fileName, 0, strlen(head->fileName) + 1);
	memcpy(new->fileName, head->fileName, strlen(head->fileName));
	new->occurences = head->occurences
	new->next = clone(head->next);
	return new;
}

Node* cloneNode(Node){
	Node new = (Node*) malloc(sizeof(Node));
	new->fileName = (char*) malloc((strlen(head->fileName) + 1) * sizeof(char));
	memset(new->fileName, 0, strlen(head->fileName) + 1);
	memcpy(new->fileName, head->fileName, strlen(head->fileName));
	new->occurences = head->occurences
	new->next = NULL;
	return new;
}

Node* intersectLists(Node* destHead, Node* srcHead){
	if(destHead == NULL)
		return clone(srcHead);
	if(srcHead == NULL)
		return clone(destHead);
	
	Node* newHead = NULL;
	Node* curr = destHead;
	Node* scurr = srcHead;
	Node* prev = NULL;
	
	while(scurr != NULL){
		if(strcmp(curr->fileName, scurr->fileName) == 0){
			if(newHead == NULL){
				newHead = cloneNode(curr);
			}else{
				if(strcmp(curr->fileName,newHead->fileName) == 0){
					
				}
			}
		}
	}
	
	if(scurr == NULL){
		Node* tmp = destHead;
		rNodeFree(tmp);
		destHead = curr;
		
	}
	
	prev = curr;
	curr = curr->next;
	
	while(curr != NULL){
		
		scurr = srcHead;
		
		while(scurr != NULL){
			
		}
		
		if(scurr == NULL){
			if(destHead == curr){
				Node* tmp = destHead;
				rNodeFree(tmp);
				destHead = curr;
			}
		}
		
	}

	return newHead;
}

void* unionLists(void* destHead, void* srcHead){
	if(destHead == NULL)
		return clone(srcHead);
	if(srcHead == NULL)
		return clone(destHead);
	
	/*
	for each item in destHead
		if item in srcHead
			next
		else
			remove it
	*/

	return NULL;
}

void *getFiles(Indexer indexer, char* word){
	
	//go through list
	// if if item is word return sub list
	
	//If not found return null
	
	return NULL;
	
}

void search(Indexer indexer, int type, int count, char* words[]){
	if(indexer == NULL)
		return;
	if(words == NULL)
		return;
	if(type < 0)
		return;
		
	/*
	resultFiles = null
	
	if type == and then
		for each word in words
			getfiles(indexer, word) -> files
			intersect(resultFiles, files);
	else if type == or then
		for each word in words
			getfiles(indexer, word) -> files
			union(resultFiles, files);
	
	return resultFiles
	*/
}
char* readWord( FILE *fp){
	
	char* string = (char*)malloc(sizeof(char) *200);
	int i = 0;
	char a;
	
	a = fgetc(fp);
	
	while(a != EOF){
		if(a != ' ' && a != '\n'){											
			while(a != EOF && a != ' ' && a != '\n'){	
				string[i] = a;
				i++;
				a = fgetc(fp);
			}
				string[i]= '\0';	
				return string;
			}else{
				a = fgetc(fp);									
			}
	}	
	return NULL;
}

int main(int argc, char* argv[]){
	//load file -> indexer
	
	FILE *fp;
	char* result;
	hashTable* table = CTable();
	
	if(argc != 2 ){
		printf("error need to enter a file\n");
		return 0;
	}
	if(strcmp(argv[0], "-h") == 0 || strcmp(argv[1], "-h") == 0){	
		printf("Help with file\n");	
		return 0;
	}
	fp = fopen(argv[1], "r");								
	if( fp == NULL){
		printf("The file is empty, please enter a file with information\n");
		return 0;
	}
	while(1){
		result = readWord(fp);
		if(result == NULL){
			break;
		}
		if(strcmp( result, "<list>") == 0){
			char* word = readWord(fp);
			while(1){
				char* fileName = readWord(fp);
				if(fileName == NULL){
					break;
				}
				if(strcmp( fileName, "</list>") == 0){
					break;
				}
				insertIndex(table, word, fileName);
			}
		}
	}
	
	while(1){
		//input->string
		//split string -> type, words, word count
		
		//search(indexer, type, word) -> files
		//for each file in files
		//	print (file);
	
	
		break; //remove this line!
		
	}
	
	
	return 1;
}
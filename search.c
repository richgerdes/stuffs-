#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "fileops.h"
#include "indexer.h"

Node* clone(Node* head){
	if(head == NULL)
		return NULL;
	Node new = cloneNode(head);
	new->next = clone(head->next);
	return new;
}

Node* cloneNode(Node* node){
	if(node == NULL)
		return NULL;
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
				Node* nprev = newHead;
				Node* ncurr = newHead->next;
				while(ncurr != NULL){
					if(curr->occurences > ncurr->occurences){
						nprev->next = cloneNode(curr);
					}
				}
			}
		}
		
		curr = curr->next;
	}
	
	prev = curr;
	curr = curr->next;
	
	while(curr != NULL){
		
		scurr = srcHead;
		
		if(strcmp(curr->fileName, scurr->fileName) == 0){
			if(newHead == NULL){
				newHead = cloneNode(curr);
			}else{
				Node* nprev = newHead;
				Node* ncurr = newHead->next;
				while(ncurr != NULL){
					if(curr->occurences > ncurr->occurences){
						nprev->next = cloneNode(curr);
					}
				}
			}
		}
		
		curr = curr->next;
	}

	return newHead;
}

Node* unionLists(Node* destHead, Node* srcHead){
	if(destHead == NULL)
		return clone(srcHead);
	if(srcHead == NULL)
		return clone(destHead);
	
	Node* newHead = clone(destHead);
	Node* scurr = srcHead;
	Node* prev = NULL;
	
	while(scurr != NULL){
		Node* curr = newHead;
		while(curr != NULL){
			if(strcmp(curr->fileName, scurr->fileName) != 0){
				Node* n = cloneNode(curr);
				Node* ncurr = newHead;
				if(strcmp(scurr->fileName,ncurr->fileName) < 0){
					n->next = ncurr;
					ncurr = n;
					newHead = n;
					break;
				}
				Node* nprev = ncurr;
				ncurr = ncurr->next;
				while(ncurr != NULL){
					if(strcmp(scurr->fileName,ncurr->fileName) < 0){
						nprev->next = n;
						n->next = ncurr;
						break;
					}
					
					nprev = ncurr;
					ncurr = ncurr->next;
				}
				
				if(ncurr == NULL){
					nprev->next = n;
				}
				break;
			}
		}
	}
	
	return newHead;
}

Node *getFiles(hashTable* table, char* word){
	
	char* key = tolower(word);
	int i = hash(table, key);
	
	Bucket* bucket = table->buckets[i];
	
	while(bucket != NULL){
		if(strcmp(bucket->key,key)==0){
			return bucket->value;
		}
		bucket = bucket->next;
	}
	
	return NULL;
	
}

void search(hashTable* table, int type, int count, char* words[]){
	if(indexer == NULL)
		return;
	if(words == NULL)
		return;
	if(type < 0)
		return;
	int SEARCH_AND = 0;
	int SEARCH_OR = 1;
	Node* resultFiles = NULL;
	
	if(type == SEARCH_AND){
		int i = 0;
		while(i < count){
			Node* files = getfiles(indexer, words[i])
			Node* ret = intersect(resultFiles, files);
			DNode(resultFiles);
			resultFiles = ret;
		}
	}else if(type == SEARCH_OR){
		int i = 0;
		while(i < count){
			Node* files = getfiles(indexer, words[i])
			Node* ret = unionLists(resultFiles, files);
			DNode(resultFiles);
			resultFiles = ret;
		}
	}
	
	return resultFiles;
	
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
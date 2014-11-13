#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "hashTable.h"

Node* cloneNode(Node* node){
	if(node == NULL)
		return NULL;
	Node* new = (Node*) malloc(sizeof(Node));
	new->fileName = (char*) malloc((strlen(node->fileName) + 1) * sizeof(char));
	memset(new->fileName, 0, strlen(node->fileName) + 1);
	memcpy(new->fileName, node->fileName, strlen(node->fileName));
	new->occurences = node->occurences;
	new->next = NULL;
	return new;
}

Node* clone(Node* head){
	if(head == NULL)
		return NULL;
	Node* new = cloneNode(head);
	new->next = clone(head->next);
	return new;
}

Node* intersectLists(Node* h1, Node* h2){
	if(h1 == NULL)
		return clone(h2);
	if(h2 == NULL)
		return clone(h1);
	
	Node* newHead = NULL;
	Node* c1 = h1;
	Node* c2 = h2;
	
	while(c1 != NULL){
		while(c2 != NULL){
			if(strcmp(c1->fileName, c2->fileName) == 0){
				Node* n = cloneNode(c1);
				n->next = newHead;
				newHead = n;
			}
			c2 = c2->next;
		}
		c1 = c1->next;
	}
/*	while(scurr != NULL){
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
		
		scurr = scurr->next;
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
	*/
	return newHead;
}

Node* unionLists(Node* h1, Node* h2){
	if(h1 == NULL)
		return clone(h2);
	if(h2 == NULL)
		return clone(h1);
	
	Node* newHead = clone(h1);
	Node* c1 = h1;
	Node* c2 = h2;
	//Node* scurr = srcHead;
			
	while(c1 != NULL){
		while(c2 != NULL){
			if(strcmp( c1->fileName, c2->fileName) == 0){
				break;
			}
			c2 = c2->next;
		}
		if(h1 == NULL){
			Node* n = cloneNode(c1);
			n->next = newHead;
			newHead = n;
		}
		c1 = c1->next;
	}
	
	
	/*while(scurr != NULL){
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
			curr = curr->next;
		}
		scurr = scurr->next;
	}
	*/
	return newHead;
}

Node *getFiles(hashTable* table, char* word){
	
	char* key = toLower(word);
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
		//printf("r-'%s'\n",result);
		if(strcmp( result, "<list>") == 0){
			char* word = readWord(fp);
			//printf("'%s'\n",word);
			while(1){
				char* fileName = readWord(fp);
				if(fileName == NULL){
					//printf("<end>\n");
					break;
				}
				//printf("->'%s'\n",fileName);
				if(strcmp( fileName, "</list>") == 0){
					break;
				}
				readWord(fp);
				insert(table, word, fileName);
			}
		}
	}
	
	fclose(fp);

	if(table == NULL){
		printf("failed to build table");
		return -1;
	}
	int SEARCH_AND = 0;
	int SEARCH_OR = 1;
	int type = -1;
	
	char* str = malloc(100 * sizeof(char));
	scanf(" %[^\n]s",str);
	char* word = strtok (str," ");
	while(1){
		if(strcmp(word,"q") == 0){
			break;
		}
		if(strcmp(word,"sa") == 0)
			type = 0;
		else if(strcmp(word,"so") == 0)
			type = 1;
			
		if(type < 0){
			scanf(" %[^\n]s",str);
			word = strtok (str," ");
			continue;
		}
			
		Node* resultFiles = NULL;
		
		while((word = strtok (NULL, " ")) != NULL){
			if(type == SEARCH_AND){
				Node* files = getFiles(table, word);
				Node* ret = intersectLists(resultFiles, files);
				rNodeFree(resultFiles);
				resultFiles = ret;
			}else if(type == SEARCH_OR){
				Node* files = getFiles(table, word);
				Node* ret = unionLists(resultFiles, files);
				rNodeFree(resultFiles);
				resultFiles = ret;
			}
		}
		
		Node* curr = resultFiles;
		
		while(curr != NULL){
			printf("%s, ", curr->fileName);
			curr = curr->next;
		}
		printf("\n");
		
		scanf(" %[^\n]s",str);
		word = strtok (str," ");
	}
	
	deletetable(table);
	free(str);
	
	return 1;
}
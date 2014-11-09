#include "hashTable.h"
#include <stdlib.h>    /* has malloc function*/
#include <stdio.h>     /* Uses Printf, scanf  */
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int hash(hashTable *table, char *key);
void insertBucket( Bucket *bucket, char *filename);
void rBinFree( Bucket *bucket);
void rNodeFree( Node *data);

void rBinFree( Bucket *bucket){
		if(bucket == NULL){
				return;
		}
		rNodeFree(bucket->value);
		rBinFree(bucket->next);
		bucket->value = 0;
		bucket->next = 0;

		if(bucket->key != NULL){
				free(bucket->key);
				bucket->key = NULL;	
		}
		free(bucket);

}
void rNodeFree( Node *data){

		if(data == NULL){
				return;
		}
		rNodeFree(data->next);
		if(data->fileName != NULL){
				free(data->fileName);
				data->fileName = NULL;
		}
		free(data);
} 

hashTable *CTable( char *data){

		hashTable *table = (hashTable*)malloc(sizeof(struct hashTable));
		table->buckets = (Bucket**)calloc(36, sizeof(Bucket*));				/*mallocing space for bucket pointer*/
		table->numBins = 36; 
		table->items = 0;													/*number of items in the hashtabl*/
		table->loadFactor = 2.0f;   										/*cuz 2.0f is standard*/

		return table;
}

void printTable( hashTable *table, FILE *fp){
		int i;
		Bucket *bucket;
		Node *node;
		for(i = 0; i < table->numBins; i++){
				for( bucket = table->buckets[i]; bucket != NULL; bucket = bucket->next){
						fprintf(fp,"<list> %s\n", bucket->key);
						for(node = bucket->value; node != NULL; node = node->next){
								fprintf(fp,"%s,%d  ", node->fileName, node->occurences);
						}
						fprintf(fp,"\n");
						fprintf(fp,"</list>\n");
				}
		}
		fclose(fp);
}

void deletetable( hashTable *table){

		int i;
		if(table->buckets == NULL){
				return;
		}
		for(i = 0; i<table->numBins; i++){
				rBinFree(table->buckets[i]);
		}
		free(table->buckets);
		table->buckets = NULL;
		free(table);
}
int hash( hashTable *table, char *key){
		/* This method is getting the key to hash*/

		int index = 0;
		if(isdigit(key[0])){
				index = key[0] - '1';

		}else{
				index = toupper(key[0]) - 'A';
				index = index + 10;
		}
		return index;

}

void insertBucket( Bucket *bucket, char *fileName){

		/* The insert method is trying to add the data in the hashtable array which is called buckets */

		Node *ptr;
		Node *prev = NULL;

		for(ptr = bucket->value; ptr != NULL; ptr = ptr->next){
				if(strcmp(ptr->fileName, fileName) == 0){
						ptr->occurences++;
						return;
				}
				prev = ptr;
		}
		if(prev != NULL){
				prev->next = (Node*)malloc(sizeof(Node));
				ptr = prev->next;
		}else{
				bucket->value = (Node*)malloc(sizeof(Node));
				ptr = bucket->value;
		}
		ptr->fileName = (char*)malloc((strlen(fileName) + 1) * sizeof(char));
		strcpy(ptr->fileName, fileName);
		ptr->occurences = 1;
		ptr->next = NULL;
}


void insert( hashTable *table, char* key, char *data){

		/* This insert method is inserting the file name using the key*/

		int index = hash(table, key);
		Bucket *ptr;
		Bucket *prev = NULL;

		for( ptr = table->buckets[index]; ptr != NULL; ptr = ptr->next){
				if(strcmp(key, ptr->key) == 0){
						insertBucket(ptr, data);
						return;
				}else if(strcmp(key, ptr->key) <= 0){
						Bucket* new = (Bucket*) malloc(sizeof(Bucket));
						new->next = ptr;
						if(prev != NULL)
							prev->next = new;
						else
							table->buckets[index] = new;
						insertBucket(new, data);
						new->key = (char*)malloc((strlen(key) + 1) * sizeof(char));
						strcpy(new->key, key);
						return;
				}
				prev = ptr;
		}
		if(prev != NULL){
				/*inserts at the end*/
				prev->next = (Bucket*)malloc(sizeof(Bucket));
				ptr = prev->next;
		}else{
				/* Inserts at the head */
				table->buckets[index] = (Bucket*)malloc(sizeof(Bucket));
				ptr = table->buckets[index];
		}
		insertBucket(ptr, data);
		ptr->key = (char*)malloc((strlen(key) + 1) * sizeof(char));
		strcpy(ptr->key, key);
		ptr->next = NULL;

}


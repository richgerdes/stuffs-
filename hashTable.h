#ifndef _HashTable_h_
#define _HashTable_h_
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

typedef struct hashTable hashTable;
typedef struct Bucket Bucket;
typedef struct Node Node;
 
struct Node{ 
	char *fileName;
	int occurences;
	Node *next;
};

struct Bucket{
	Node *value;
	Bucket *next;
	char *key;
};

struct hashTable {

	Bucket **buckets;
	int numBins;
	int items;
	float loadFactor;

};

hashTable *CTable();
void printTable( hashTable *table, FILE *fp);
void deletetable( hashTable *table);
int hash( hashTable *table, char *key);
void insertBucket( Bucket *bucket, char *filename);
void insert( hashTable *table, char* key, char *data);

















#endif

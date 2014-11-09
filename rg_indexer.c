/* Author: Rich Gerdes
 * Date: 10/20/2014
 * CS214
 *
 * File: indexer.c
 *
 */

#include "rg_indexer.h"
/*
 * comparison for file counts in linked list
 */
int RGIndexerFileCompare(void* a, void* b){
	IndexerFile* file1 = a;
	IndexerFile* file2 = b;
	if(file1 == NULL || file2 == NULL)
		return -1;
	return (file2->hitcount)-(file1->hitcount);
}
/*
 * free for file counts in list
 */
void RGIndexerFileDestroy(void* ptr){
	IndexerFile* file = ptr;
	
	if(file == NULL)
		return;
	
	free(file->filename);
	free(file);
	
}	
/*
 * word data comparison 
 */
int RGIndexerWordCompare(void* a, void* b){
	IndexerWord* word1 = a;
	IndexerWord* word2 = b;
	
	if(word1 == NULL || word2 == NULL)
		return -1;
	if(word1->word == NULL || word2->word == NULL)
		return -1;
		
	return strcmp(word1->word, word2->word);
	
}

/*
 * free for word data
 */
void RGIndexerWordDestroy(void* ptr){
	IndexerWord* word = ptr;
	
	if(word != NULL)
		free(word->word);
	if(word->files != NULL){
		RGdestroyRGSDLL(word->files);
		word->files = NULL;
	}
	free(word);
}

/*
 * malloc for file node
 */
IndexerFile* RGcreateIndexerFile(char* filename, int count){
	IndexerFile* file = (IndexerFile*) malloc(sizeof(IndexerFile));
	if(file == NULL) 
		return NULL;
	
	file->filename = filename;
	file->hitcount = count;
	
	return file;
}

/*
 * malloc for word node data
 */
IndexerWord* RGcreateIndexerWord(char* word){
	IndexerWord* ptr = (IndexerWord*) malloc(sizeof(IndexerWord));
	if(word == NULL) 
		return NULL;
	
	ptr->word = word;
	ptr->files = RGcreateRGSDLL((*RGIndexerFileCompare),(*RGIndexerFileDestroy));
	
	if(ptr->files == NULL)
		printf("ERROR: no memory to build file linked list for files");
	
	return ptr;
}

/*
 * build empty iterator
 */
Indexer* RGcreateIndexer(){
	Indexer* indexer = (Indexer*) malloc(sizeof(Indexer));
	if(indexer == NULL)
		return NULL;
	indexer->words = RGcreateRGSDLL((*RGIndexerWordCompare),(*RGIndexerWordDestroy));
	
	if(indexer->words == NULL)
		printf("ERROR: no memory to build file linked list for words");
	return indexer;
}

/*
 * cleanup
 */
void RGdestroyIndexer(Indexer* indexer){
	if(indexer == NULL)
		return;
		
	RGdestroyRGSDLL(indexer->words);
	indexer->words = NULL;
	free(indexer);
}

/*
 * add data to indexer 
 */
void RGIndexerAdd(Indexer* indexer, char* word, char* file){
	if(indexer == NULL || word == NULL || file == NULL)
		return;
		
	RGSDLLIter* words = RGSDLLgetIter(indexer->words); //for all words
	if(words != NULL){ 
		void* data = RGSDLLIterGetCurrent(words);//iterate through
		while(data != NULL){ 
			IndexerWord* w = data;
			if(w->word != NULL && strcmp(w->word,word) == 0){
				RGSDLLIter* files = RGSDLLgetIter(w->files); //for all files
				if(files == NULL){
					RGdestroyRGSDLLIter(words);
					return; //stop add on alloc failure
				}
				void* fvoid = RGSDLLIterGetCurrent(files); //iterate through
				while(fvoid != NULL){
					IndexerFile* f = fvoid;
					if(f->filename != NULL && strcmp(f->filename, file)==0){ //file found
						f->hitcount++;
						RGSDLLSort(w->files);
						data = RGSDLLIterGetNext(files);
						RGdestroyRGSDLLIter(files);
						RGdestroyRGSDLLIter(words);
						return;
					}
					fvoid = RGSDLLIterGetNext(files); //next fi;e
				}
				//file not found
				RGdestroyRGSDLLIter(files); //cleanup
				//copy strings
				char* fnew = malloc(strlen(file) * sizeof(char) + 1);
				memset(fnew,'\0',strlen(file) * sizeof(char) + 1);
				strcpy(fnew,file);
				IndexerFile* newData = RGcreateIndexerFile(fnew, 1);
				RGSDLLadd(newData,w->files);	//add new node
				RGdestroyRGSDLLIter(words); //next word
				return;
			}
			data = RGSDLLIterGetNext(words); //next word
		}
		RGdestroyRGSDLLIter(words); //clean up
	}
	
	//word not found
	//copy strings
	char* wnew = malloc(strlen(word) * sizeof(char) + 1);
	memset(wnew,'\0',strlen(word) * sizeof(char) + 1);
	strcpy(wnew,word);
	IndexerWord* newWord = RGcreateIndexerWord(wnew);
	char* fnew = malloc(strlen(file) * sizeof(char) + 1);
	memset(fnew,'\0',strlen(file) * sizeof(char) + 1);
	strcpy(fnew,file);
	IndexerFile* newData = RGcreateIndexerFile(fnew, 1);
	RGSDLLadd(newData,newWord->files); //add new file to new word
	RGSDLLadd(newWord,indexer->words); //add new word
}
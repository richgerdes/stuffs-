#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "fileops.h"
#include "indexer.h"

void* clone(void* list){
	return NULL;
}

void* intersectLists(void* destHead, void* srcHead){
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

int main(int argc, char* argv[]){
	//load file -> indexer
	
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
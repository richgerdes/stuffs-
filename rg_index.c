/* Author: Rich Gerdes
 * Date: 10/20/2014
 * CS214
 *
 * File: index.c
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "rg_fileops.h"
#include "rg_indexer.h"
#include "RG_LinkedList.h"
/*
 * print indexer object to console. Iterate through the nested linked lists to print both lists
 *
 */
void RGprintIndexer(Indexer* indexer){
	if(indexer == NULL)
		return;	
	RGSDLLIter* words = RGSDLLgetIter(indexer->words);
	if(words == NULL)
		return;
	void* data = RGSDLLIterGetCurrent(words);
	while(data != NULL){
		IndexerWord* w = data;
		RGSDLLIter* files = RGSDLLgetIter(w->files);
		printf("<%s>",w->word);
		if(files == NULL){
			RGdestroyRGSDLLIter(words);
			return;
		}
		void* fvoid = RGSDLLIterGetCurrent(files);
		while(fvoid != NULL){
			IndexerFile* f = fvoid;
			printf("(%s,%d)->",f->filename,f->hitcount);
			fvoid = RGSDLLIterGetNext(files);
		}
		RGdestroyRGSDLLIter(files);
		printf("\n");
		data = RGSDLLIterGetNext(words);
	}
	RGdestroyRGSDLLIter(words);
}

/*
 * Export indexed results to the file system
 *
 */
void RGwriteIndexerToFile(Indexer* indexer, char* filename){
	
	if(indexer == NULL || filename == NULL)
		return;	
		
    FILE *output;
     
    output = fopen(filename, "w"); //open file
    if (output == NULL)
    {
		//exit function
        fprintf(stderr, "Error : Failed to open output file - %s\n", strerror(errno));
        return;
    }
	
	RGSDLLIter* words = RGSDLLgetIter(indexer->words); //setup iter
	if(words == NULL){
		fclose(output); //close file on error
		return;
	}
	void* data = RGSDLLIterGetCurrent(words); //get first word
	while(data != NULL){
		IndexerWord* w = data;
		RGSDLLIter* files = RGSDLLgetIter(w->files); //setup iter
		fprintf(output,"<list> %s\n",w->word);
		if(files == NULL){
			RGdestroyRGSDLLIter(words); //cleanup
			fclose(output); //close file
			return;
		}
		void* fvoid = RGSDLLIterGetCurrent(files); //get first
		while(fvoid != NULL){
			IndexerFile* f = fvoid;
			fprintf(output,"%s %d ",f->filename,f->hitcount); //write to file
			fvoid = RGSDLLIterGetNext(files); // get next
		}
		RGdestroyRGSDLLIter(files); //cleanup
		fprintf(output,"\n</list>\n");
		data = RGSDLLIterGetNext(words); //get next
	}
	RGdestroyRGSDLLIter(words); //cleanup
	
	fclose(output); //close file
}

/*
 * call perams <outputfile> <root directory>
 *
 * builds and exports an index of all files in the dir to outputfile
 *
 */
int RGmain(int argc, char* argv[]){
	//args check
	if(argc < 2){
		printf("Usage: ./index <outputfile> <directory>");
		return -1;
	}

	RGLinkedList* list = RGgetFileList(argv[2]); //get file list
	RGLinkedListIter* iter = RGLLgetIter(list); //iter for files
	char* data = RGLLIterGetCurrent(iter); //get first
    char* buffer = NULL;
	char c;
	Indexer* indexer = RGcreateIndexer(); //new indexer
	
    FILE *fileread;
	
	if(list == NULL) //chk valid list
		printf("ignore anything that's right\n");

	while(data != NULL){ //read files if they exist
		
		fileread = fopen(data, "rw"); //open file
        if (fileread == NULL) //cant open file
        {
            fprintf(stderr, "Error : Failed to open data file '%s'- %s\n",data, strerror(errno));
			void* old = RGLLremove(list,data);
			free(old); 
			data = RGLLIterGetNext(iter);//next file
            continue; //next file
        }

        while((c = tolower(fgetc(fileread))) != EOF){ //read chars
			if(isalnum(c)){ //not delim
				if(buffer == NULL){ //new word
					buffer = malloc(sizeof(char) * 2);
					memset(buffer,'\0',sizeof(char) * 2);
					buffer[0] = c;
				}else{ //add to word
					char* cc = malloc(sizeof(char) * 2);
					memset(cc,'\0',sizeof(char) * 2);
					cc[0] = c;
					char* tmp = RGconcat(buffer,cc);
					free(cc);
					free(buffer);
					buffer = tmp;
				}
			}else{ //delim
				IndexerAdd(indexer,buffer,data); // add to indexer
				free(buffer); //free old ref
				buffer = NULL;
			}
		}

		fclose(fileread);//close file
		fileread = NULL;
		
		void* old = RGLLremove(list,data); //cleanup
		free(old);
		
		data = RGLLIterGetNext(iter);//next file
	}
	RGdestroyLLIter(iter); //close file list iter
	
	RGdestroyLL(list); //destory file list
	
	printf("---\n");
	RGprintIndexer(indexer); //print
	printf("---\n");
	
	RGwriteIndexerToFile(indexer,argv[1]); //write to file
	
	RGdestroyIndexer(indexer); //cleanup
	
	return 0;
}

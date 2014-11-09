/* Author: Rich Gerdes
 * Date: 10/20/2014
 * CS214
 *
 * File: fileops.c
 *
 */

#include "rg_fileops.h"

/*
 * copy two char* into not char*
 */
char* RGconcat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
	memset(result,'\0',strlen(s1)+strlen(s2)+1);//clean
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

/*
 * checks if file path is dir
 */
int RGisdir(char *in_string)
{
	DIR *dir;
	// Access function 0 determines if an object exits, whether file or directory
	if (access(in_string,0) != 0) // object DNE
		return -1; 
	// The object, whatever it is, exists
	dir = opendir(in_string);
	if (dir != NULL)
	{
		// Object successfully opened as a directory stream
		closedir(dir);
		return 1;
	}
	return 0;
}

/*
 * calls RGloadFiles to recusively get file list
 */
RGLinkedList* RGgetFileList(char* path){
	RGLinkedList* list = RGcreateLL();
	if(RGisdir(path) == 1){
		RGloadFiles(list,path);
		return list;
	}
	RGdestroyLL(list);
	return NULL;
}

/*
 * recursive file list retrieval
 */
void RGloadFiles(RGLinkedList* list, char* path){
	DIR* FD;
    struct dirent* in_file;

    /* Scanning the in directory */
    if (NULL == (FD = opendir (path))) 
    {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));

        return;
    }
	
	char* dir = RGconcat(path, "/");
    while ((in_file = readdir(FD))) 
    {
        if (!strcmp (in_file->d_name, "."))
            continue;
        if (!strcmp (in_file->d_name, ".."))    
            continue;
		char* fullPath = RGconcat(dir, in_file->d_name);
		if (RGisdir(fullPath) == 1){
			RGloadFiles(list, fullPath); //check new dir
			free(fullPath); //clean up
		}else{
			RGLLadd(list,fullPath); //add file
		}
    }
	//clean up
	closedir(FD);
	free(dir);
}
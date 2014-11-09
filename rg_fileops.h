/* Author: Rich Gerdes
 * Date: 10/20/2014
 * CS214
 *
 * File: fileops.h
 *
 */

#ifndef RG_FILEOPS
#define RG_FILEOPS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include "RG_LinkedList.h"

char* RGconcat(char *s1, char *s2);
int RGisdir(char *in_string);

/**
 *	Load files recursively from a directory;
 *	calls RGloadFiles to load the initial directory.
 *	takes char* files path of initial directory;
 *
 *	returns a linked list of the files;
 */
RGLinkedList* RGgetFileList(char*);

/**
 *	recursively loads file name from a directory tree. 
 *	takes a linked list to store the files name and char* file name
 *	
 */
void RGloadFiles(RGLinkedList*, char*);

#endif
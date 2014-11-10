#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>  //So you can use the struct stat
#include <dirent.h> 
#include <unistd.h>

#include "hashTable.h"

int isReg(char *path){
  struct stat finfo;
  stat(path, &finfo);
  return S_ISREG(finfo.st_mode); 

  }
  int isDir(char *path){
  struct stat finfo;
  stat(path, &finfo);
  return S_ISDIR(finfo.st_mode);
  }

 void processFile(hashTable *table, char *name, char *path){
		char c;
		char string[1000]; 
		FILE *fp;
		int i = 0;
		
		fp = fopen(name, "r");								
		if( fp == NULL){
			printf("The file is empty, please enter a file with information\n");
			return;
		}else{
			c = fgetc(fp);									
		}
		while(c != EOF)													
		{
				if(isalpha(c)){											
						while(c != EOF && (isalpha(c) || isdigit(c))){	
								string[i] =(c);
								i++;
								c = fgetc(fp);
						}
						string[i]= '\0';	
						insert(table, string, name);								
						i = 0;
						string[i] = '\0';
				}else if(isdigit(c) && (string[0] == '\0')){
						while(c != EOF && (isalpha(c) || isdigit(c))){	
								string[i] = (c);
								i++;
								c = fgetc(fp);
						}
						string[i]= '\0';
						insert(table, string, name);								
						i = 0;
						string[i] = '\0';
				}else{
						c = fgetc(fp);									
				}
		}
 
 
 }
 void processDir(hashTable *table, char *name){
 
		/* This goes into the folder*/
		
		DIR *dp;
		//struct dirent *dir;
		//struct stat s;
		//char path[sizeof(name) + 1];
		dp = opendir(name);
	
		if(dp){
			while(1){
				struct dirent *dir;
     	        char *path;
				char dirname[4096];
				dir = readdir(dp);
				
				if(!dir){
				break;
				}
				
				path = dir->d_name;
				strcpy(dirname, name);
				strcat(dirname, "/");
				strcat(dirname, path);
				
				if(strcmp(dirname, ".") == 0)
					continue;
				if(strcmp(dirname, "..") == 0)
					continue;
				else {
					processFile(table, dirname, path);

					if(dir->d_type & DT_DIR){
						if(strcmp(path, ".") != 0 && strcmp(path, "..") != 0){
							char p[BUFSIZ];
							strcpy(dirname, name);
							strcat(dirname, "/");
							strcat(dirname, path);
							processDir(table, dirname);
						}
					}
				} 
			}
		}else{
				printf("error");
		}	


 /* strcpy(path, name);
		strcat(path, "/");
		
		dp = opendir(path);
		char *f;
		
		if(dp){
			
			while((dir = readdir(dp)) != NULL){
				
				if(strcmp(dir->d_name, ".") == 0)
					continue;
				if(strcmp(dir->d_name, "..") == 0){
					continue;
				}else{
					strcpy(path, name);
					strcat(path, "/");
					f = path;
					strcat(f, dir->d_name);
					printf("%s\n", f);
					processFile(table, f, path);
				
				}		
			} 
		}
	*/
 }
 
int main( int argc, char **argv){
		
		hashTable *table = CTable();
		FILE *fp;

		if(argc != 3 ){
				printf("error need to enter a file\n");
				return 0;
		}else{
				if(isDir(argv[2]) == 1){
					processDir(table, argv[2]);
				}else if(isReg(argv[2]) == 1){
					processFile(table, argv[2],"");
				}else{
					printf("IT IS AN ERRRR");
					return 0;
				}
		}
		fp = fopen("output.txt", "rb+");
			if(fp == NULL){
				fp = fopen("output.txt", "w");
				
				if(fp == NULL){
					printf("Error writing to file");
					return 0;
				}
				printTable(table, fp);
			}else{
				printTable(table, fp);
			}
				
		//deletetable(table);
		return 0;
}



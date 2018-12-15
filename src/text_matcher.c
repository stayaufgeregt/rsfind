#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>

#include "structures.h"

//bool hasName(char* fileName);			//fileName==CHAINE with --name CHAINE 
//bool hasText(char* filePath,struct stat* fileStat);		//file located at filePath contains string CHAINE with -t CHAINE

bool regexNameMatch(char * path){
	printf("%s\n%s\n",myArgs.ename,path);
	return true;
}

bool regexTextMatch(char* path){
	printf("%s\n%s\n",myArgs.T,path);
	return true;
}

bool hasName(char* name){
	return name!=NULL && !strcmp(name,myArgs.name);
}



bool hasText(char* path,struct stat* path_stat){
	
	if(!S_ISREG(path_stat->st_mode))
		return false;
	
	int fd;
	fd = open(path,O_RDONLY);
	char fileBuffer[path_stat->st_size];
	read(fd,fileBuffer,path_stat->st_size);
	/////////////if read fails ????
	return strstr(fileBuffer,myArgs.text)!=NULL;
}
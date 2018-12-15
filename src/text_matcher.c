#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include <fcntl.h>

#include "structures.h"
#include "text_matcher.h"

bool regexNameMatch(char * name){
	return name!=NULL;
}

bool regexTextMatch(char* path){
	return path!=NULL;
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

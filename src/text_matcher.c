#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include <fcntl.h>

#include "structures.h"
#include "text_matcher.h"


bool regexPerl(char* fileToCmp,char* ptrn){

	PCRE2_SPTR strCompare =(PCRE2_SPTR) fileToCmp;
	PCRE2_SPTR pattern =(PCRE2_SPTR) ptrn; 

	pcre2_code* regexPattern;
	pcre2_match_data *match_data;
	int errornumber;
	PCRE2_SIZE erroroffset;

	regexPattern = pcre2_compile(pattern,PCRE2_ZERO_TERMINATED,0,&errornumber,&erroroffset,NULL); //On compile le pattern


	//on regarde si la compilation a marchée
	if (regexPattern == NULL){
 		PCRE2_UCHAR buffer[256];
  		pcre2_get_error_message(errornumber, buffer, sizeof(buffer));
  		printf("PCRE2 compilation failed at offset %d: %s\n", (int)erroroffset,buffer);
  		return 0;
  	} else {

		match_data = pcre2_match_data_create_from_pattern(regexPattern, NULL);

		// On regarde dans le fichier si quelque chose correspond au pattern
		int a = pcre2_match(regexPattern,strCompare,strlen((char *)strCompare),0,0,match_data,NULL);

	  	pcre2_match_data_free(match_data);
	  	pcre2_code_free(regexPattern);
	  	
		if(a>=1){
			return 1;
		} else {
			return 0;
		}		
	}
	return 0;

}


bool regexNameMatch(char* fileName){
	return fileName != NULL && regexPerl(fileName,myArgs.ename);
}


bool regexTextMatch(char* path,struct stat* path_stat){

	if(!S_ISREG(path_stat->st_mode))
		return false;
	
	int fd;
	fd = open(path,O_RDONLY);
	char fileBuffer[path_stat->st_size];
	read(fd,fileBuffer,path_stat->st_size);
	close(fd);
	return regexPerl(fileBuffer,myArgs.T);
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

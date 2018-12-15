#ifndef TEXT_MATCHER_H_
#define TEXT_MATCHER_H_

#include <sys/stat.h>

//bool hasName(char* fileName);			//fileName==CHAINE with --name CHAINE 
//bool hasText(char* filePath,struct stat* fileStat);		//file located at filePath contains string CHAINE with -t CHAINE

bool regexNameMatch(char * name);
bool regexTextMatch(char* path);
bool hasName(char* name);
bool hasText(char* path,struct stat* path_stat);

#endif
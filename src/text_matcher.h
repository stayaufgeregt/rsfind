#ifndef TEXT_MATCHER_H_
#define TEXT_MATCHER_H_

#define PCRE2_CODE_UNIT_WIDTH 8
#include <sys/stat.h>
#include <pcre2.h>
//bool hasName(char* fileName);			//fileName==CHAINE with --name CHAINE 
//bool hasText(char* filePath,struct stat* fileStat);		//file located at filePath contains string CHAINE with -t CHAINE

bool regexNameMatch(char * name);
bool regexTextMatch(char* fileName);
bool hasName(char* name);
bool hasText(char* path,struct stat* path_stat);

#endif
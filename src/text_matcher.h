#ifndef TEXT_MATCHER_H_
#define TEXT_MATCHER_H_

#define PCRE2_CODE_UNIT_WIDTH 8
#include <sys/stat.h>
#include <pcre2.h>
#include <stdio.h>
#include <stdlib.h>

//bool hasName(char* fileName);			//fileName==CHAINE with --name CHAINE 
//bool hasText(char* filePath,struct stat* fileStat);		//file located at filePath contains string CHAINE with -t CHAINE

bool regexPerl(char* fileToCmp,char* pattern);
bool regexNameMatch(char* fileName);
bool regexTextMatch(char* path,struct stat* path_stat);
bool hasName(char* name);
bool hasText(char* path,struct stat* path_stat);

#endif
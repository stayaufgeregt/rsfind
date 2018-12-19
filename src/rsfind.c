#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

#include "structures.h"
#include "text_matcher.h"
#include "image.h"



void recursiveSearch(char* path,char* name){
	
	struct stat path_stat;
	memset(&path_stat,0,sizeof(path_stat));
    stat(path, &path_stat);
	

	if( (!myArgs.flags[_name] 	|| hasName(name) ) &&
		(!myArgs.flags[_t]	 	|| hasText(path,&path_stat) ) &&
		(!myArgs.flags[_i] 	 	|| isImage(path) ) &&
		(!myArgs.flags[_ename]	|| regexNameMatch(name) ) &&
		(!myArgs.flags[_T]		|| regexTextMatch(path,&path_stat) ))
		push_back_cpy(filesFound,path);

		//applyAction(path);
	
	//recursive call if the file is a directory
	if(S_ISDIR(path_stat.st_mode)){
		
		DIR* dp;			//directory to list		
		struct dirent *ep;	//current file being listed
		dp=opendir(path);
		
		if(dp!=NULL){
			
			while((ep=readdir(dp))!=NULL){
			
				//if it is not current dir or parent dir
				if(strcmp(ep->d_name,"..") && strcmp(ep->d_name,".")){
					
					//creation of the child's path
					char *childPath;
					size_t path_len=strlen(path);
					if(path[path_len-1]=='/')	//avoid excedent '/' when parameter is "DOSSIER/+"
						path_len--;
					childPath=malloc(sizeof(char)*(path_len+strlen(ep->d_name)+2));
					strncpy(childPath,path,path_len);
					childPath[path_len]='\0';
					strcat(childPath,"/");
					strcat(childPath,ep->d_name);		
					
					recursiveSearch(childPath,ep->d_name);
					free(childPath);
				}
			}
			closedir(dp);
		}
		else{
			exit(1);
		}		
	}
}

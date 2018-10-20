#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "argParser.c"
#include <errno.h>

void lsDir(char* path,args* mesArgs){


	DIR* dp;
	//directory to list
	
	struct dirent *ep;
	//curent file being listed

	dp=opendir(path);
	
	printf("%s\n",path);
	
	//if we can open the directory
	if(dp!=NULL){

	
		//while there is a file to read
		while((ep=readdir(dp))!=NULL){

		
			//d_name == filename
			//if it is not current dir or parent dir
			if(strcmp(ep->d_name,"..") && strcmp(ep->d_name,".")){

				
				
				
				//if the file is a directory : recursive call
				if(ep->d_type==DT_DIR){
					
					
					//display name of dir is done at the beginning of function
					char childPath[strlen(path)+strlen(ep->d_name)+2];
					strcpy(childPath,path);
					strcat(childPath,"/");
					strcat(childPath,ep->d_name);
					
					lsDir(childPath,mesArgs);
				}
				else{	
				//otherwise, display name
					
					if(mesArgs->flags[NAME]){
					//--name CHAINE
					//if filename == CHAINE : display
					printf("not supposed to be here\n");
					if(!strcmp(ep->d_name,mesArgs->name))
						printf("%s/%s\n",path,ep->d_name);
					}
					else{
						//default without options
						printf("%s/%s\n",path,ep->d_name);
					}
					
				}
			}
		}
		closedir(dp);
	}
	else{
		printf("Couldn't open directory, error : %d.\n",errno);
	}
}